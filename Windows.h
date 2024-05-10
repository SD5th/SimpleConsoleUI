#include <iostream>
#include "DynamicArray.h"

using namespace std;

class Shell;
class WindowShell;
class FunctionShell;

class Window;
class CurrentWindow;
class Function;


class Shell
{
    public:
        enum ShellType {
            WindowType,
            FunctionType
        };
        virtual ShellType   Get_Type() = 0;
        virtual bool        Get_IsVisible() = 0;
        virtual Window*     Get_Window() = 0; 
        virtual Function*   Get_Function() = 0;
};

class WindowShell : public Shell
{
    private:
        Window* window;
        bool visibility;
    public:
        // конструкторы
        WindowShell(Window*, bool);
        ShellType   Get_Type() override;
        bool        Get_IsVisible() override;
        Window*     Get_Window() override; 
        Function*   Get_Function() override;

};

class FunctionShell : public Shell
{
    private:
        Function* function;
        bool visibility;
    public:
        FunctionShell(Function*, bool);
        ShellType   Get_Type() override;
        bool        Get_IsVisible() override;
        Window*     Get_Window() override; 
        Function*   Get_Function() override;
};


class Window
{
    private:
        string windowName;                         // Имя окна
        string welcomeMessage;                     // Сообщение при переходе на окно

        DynamicArray<Shell*>* shells;

    public:
        // конструкторы
        Window();
        Window(string, string);
        ~Window();

        // декомпозиция
        string                          Get_WindowName();
        string                          Get_WelcomeMessage();

        DynamicArray<Shell*>*          Get_Shells();
        int                             Get_Amount_Shells();

        // операции
        void Change_WindowName(string);
        void Change_WelcomeMessage(string);
        
        void Append_WindowShell(Window*, bool);
        void Insert_WindowShell(Window*, bool, int);
        void Change_WindowShell(Window*, bool, int);

        void Append_FunctionShell(Function*, bool);
        void Insert_FunctionShell(Function*, bool, int);
        void Change_FunctionShell(Function*, bool, int);


};

class CurrentWindow
{
    private:
        Window* window;
        Window* prevWindow; 
};

// FunctionShell
    // конструкторы
        FunctionShell::FunctionShell(Function* function, bool visibility):
            function(function),
            visibility(visibility)
        { }
    // деконструкция
        Shell::ShellType    FunctionShell::Get_Type() 
        {
            return ShellType::WindowType;
        }
        bool                FunctionShell::Get_IsVisible()
        {
            return visibility;
        }
        Window*             FunctionShell::Get_Window()
        {
            return nullptr;
        }  
        Function*           FunctionShell::Get_Function()
        {
            return function;
        } 

// WindowShell
    // конструкторы-деструкторы
        WindowShell::WindowShell(Window* window, bool visibility):
            window(window),
            visibility(visibility)
        { }
    // деконструкция
        Shell::ShellType    WindowShell::Get_Type() 
        {
            return ShellType::WindowType;
        }
        bool                WindowShell::Get_IsVisible()
        {
            return visibility;
        }
        Window*             WindowShell::Get_Window()
        {
            return window;
        }  
        Function*           WindowShell::Get_Function()
        {
            return nullptr;
        } 

// Window
    // конструкторы-деструкторы
        Window::Window():
            windowName("Empty windowName"),
            welcomeMessage("Empty welcomeMessage"),
            shells(new DynamicArray<Shell*>)
        { }
        Window::Window(string windowName, string welcomeMessage):
            windowName(windowName),
            welcomeMessage(welcomeMessage),
            shells(new DynamicArray<Shell*>)
        { }
        
        Window::~Window()
        {
            delete shells;
        }

    // декомпозиция
        string                          Window::Get_WindowName()
        {
            return windowName;
        }
        string                          Window::Get_WelcomeMessage()
        {
            return welcomeMessage;
        }
        DynamicArray<Shell*>*           Window::Get_Shells()
        {
            return shells;
        }
        int                             Window::Get_Amount_Shells()
        {
            return shells->GetSize();
        }

    // операции
        void Window::Change_WindowName(string newWindowName)
        {
            windowName = newWindowName;
        }   
        void Window::Change_WelcomeMessage(string newWelcomeMessage)
        {
            welcomeMessage = newWelcomeMessage;
        }

        void Window::Append_WindowShell(Window* window, bool visibility = true)
        {
            shells->Append(new WindowShell(window, visibility)); 
        }

        void Window::Insert_WindowShell(Window* window, bool visibility = true, int index)
        {
            shells->Insert(new WindowShell(window, visibility), index);
        }

        void Window::Change_WindowShell(Window* window, bool visibility = true, int index)
        {
            delete shells->Get(index);
            shells->Set(new WindowShell(window, visibility), index);
        }
        
        void Window::Append_FunctionShell(Function* function, bool visibility = true)
        {
            shells->Append(new FunctionShell(function, visibility)); 
        }

        void Window::Insert_FunctionShell(Function* function, bool visibility = true, int index)
        {
            shells->Insert(new FunctionShell(function, visibility), index);
        }

        void Window::Change_FunctionShell(Function* function, bool visibility = true, int index)
        {
            delete shells->Get(index);
            shells->Set(new FunctionShell(function, visibility), index);
        }        