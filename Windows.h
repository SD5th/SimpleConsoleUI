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
        virtual int         Get_Number() = 0;
        virtual bool        Get_IsVisible() = 0;
        virtual Window*     Get_Window() = 0; 
        virtual Function*   Get_Function() = 0;
};

class WindowShell : public Shell
{
    private:
        Window* window;
        bool visibility;
        int number;
    public:
        // конструкторы
        WindowShell(Window*, bool, int);
        ShellType   Get_Type() override;
        int         Get_Number() override;
        bool        Get_IsVisible() override;
        Window*     Get_Window() override; 
        Function*   Get_Function() override;

};

class WindowShell : public Shell
{
    private:
        Window* window;
        bool visibility;
        int number;
    public:
        // конструкторы
        WindowShell(Window*, bool, int);
        ShellType   Get_Type() override;
        int         Get_Number() override;
        bool        Get_IsVisible() override;
        Window*     Get_Window() override; 
        Function*   Get_Function() override;

};

class FunctionShell : public Shell
{
    private:
        Function* function;
        bool visibility;
        int number;
    public:
        ShellType   Get_Type() override;
        bool        Get_Number() override;
        bool        Get_IsVisible() override;
        Window*     Get_Window() override; 
        Function*   Get_Function() override;};



class Window
{
    private:
        string windowName;                         // Имя окна
        string welcomeMessage;                     // Сообщение при переходе на окно


        DynamicArray<Window*>* childWindows;             // Ссылка на динамический массив окон, на которые можно перейти
        DynamicArray<bool>* isVisible_ChildWindows;     // Ссылка на динамический массив bool переменных, которые показывают, видно ли окно в переходе

        DynamicArray<Function*>* functions; // Ссылка на динамический массив функций в этом окне
        DynamicArray<bool>* isVisible_functions;  // Ссылка на динамический массив bool переменных, которые показывают, видно ли функцию в окне


    public:
        // конструкторы
        Window();
        Window(string, string);
        ~Window();

        // декомпозиция
        string                          Get_WindowName();
        string                          Get_WelcomeMessage();

        DynamicArray<Window*>*          Get_ChildWindows();
        int                             Get_Amount_ChildWindows();
        DynamicArray<bool>*             Get_IsVisible_ChildWindows();
        
        DynamicArray<Function*>*  Get_Functions();
        int                             Get_Amount_Functions();
        DynamicArray<bool>*             Get_IsVisible_Functions();

        // операции
        void Change_WindowName(string);
        void Change_WelcomeMessage(string);
        
        void Append_ChildWindow(Window*, bool);
        void Insert_ChildWindow(Window*, bool, int);
        void Change_ChildWindow(Window*, bool, int);

        void Append_Function(Function*, bool);
        void Insert_Function(Function*, bool, int);
        void Change_Function(Function*, bool, int);


};

class CurrentWindow
{
    private:
        Window* window;
        Window* prevWindow; 
};

// FunctionShell
    // конструкторы
        FunctionShell::FunctionShell(Function* function, bool visibility, int number):
            function(function),
            visibility(visibility),
            number(number)
        { }

    // деконструкция
        WindowShell::ShellType WindowShell::Get_Type() 
        {
            return ShellType::WindowType;
        }

        int WindowShell::Get_Number()
        {
            return number;
        }

        bool WindowShell::Get_IsVisible()
        {
            return visibility;
        }

        Window*     WindowShell::Get_Window()
        {
            return window;
        }  
        Function*   WindowShell::Get_Function()
        {
            return nullptr;
        } 


// WindowShell
    // конструкторы
        WindowShell::WindowShell(Window* window, bool visibility, int number):
            window(window),
            visibility(visibility),
            number(number)
        { }

    // деконструкция
        WindowShell::ShellType WindowShell::Get_Type() 
        {
            return ShellType::WindowType;
        }

        int WindowShell::Get_Number()
        {
            return number;
        }

        bool WindowShell::Get_IsVisible()
        {
            return visibility;
        }

        Window*     WindowShell::Get_Window()
        {
            return window;
        }  
        Function*   WindowShell::Get_Function()
        {
            return nullptr;
        } 



// Window
    // конструкторы-деструкторы
        Window::Window():
            windowName("Empty windowName"),
            welcomeMessage("Empty welcomeMessage"),

            isVisible_ChildWindows(new DynamicArray<bool>),
            childWindows(new DynamicArray<Window*>),

            isVisible_WindowFunctions(new DynamicArray<bool>),
            windowFunctions(new DynamicArray<WindowFunction*>)
        { }

        Window::Window(string windowName, string welcomeMessage):
            windowName(windowName),
            welcomeMessage(welcomeMessage),

            isVisible_ChildWindows(new DynamicArray<bool>),
            childWindows(new DynamicArray<Window*>),

            isVisible_WindowFunctions(new DynamicArray<bool>),
            windowFunctions(new DynamicArray<WindowFunction*>)
        { }

        Window::~Window()
        {
            delete childWindows;
            delete windowFunctions;
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

        DynamicArray<Window*>*          Window::Get_ChildWindows()
        {
            return childWindows;
        }

        int                             Window::Get_Amount_ChildWindows()
        {
            return childWindows->GetSize();
        }

        DynamicArray<bool>*             Window::Get_IsVisible_ChildWindows()
        {
            return isVisible_ChildWindows;
        }

        DynamicArray<Function*>*        Window::Get_Functions()
        {
            return windowFunctions;
        }

        int                             Window::Get_Amount_Functions()
        {
            return windowFunctions->GetSize();
        }

        DynamicArray<bool>*             Window::Get_IsVisible_Functions()
        {
            return isVisible_WindowFunctions;
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

        void Window::Append_ChildWindow(Window* newWindow, bool isVisible)
        {
            childWindows->Append(newWindow);
            isVisible_ChildWindows->Append(isVisible);
        }

        void Window::Insert_ChildWindow(Window* newWindow, bool isVisible, int index)
        {
            childWindows->Insert(index, newWindow);

        }

        void Window::Change_ChildWindow(Window* newWindow, bool isVisible)
        {
            childWindows->Append(newWindow);

        }
        
        void Window::AddWindowFunction(WindowFunction*, bool)
        {

        }
