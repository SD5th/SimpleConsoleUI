#include <iostream>
#include "DynamicArray.h"

using namespace std;

class Shell;
class WindowShell;
class FunctionShell;

class Window;
class Function;
class ActiveWindow;


class Shell
{
    public:
        enum ShellType {
            WindowType,
            FunctionType
        };
        // деконструкция
        virtual ShellType   Get_Type() = 0;
        virtual bool        Get_Visibility() = 0;
        virtual int         Get_Number() = 0;
        virtual Window*     Get_Window() = 0; 
        virtual Function*   Get_Function() = 0;

        // операции
        virtual void        Set_Visibility(bool) = 0;
        virtual void        Set_Number(int) = 0;
        virtual void        Set_Window(Window*) = 0; 
        virtual void        Set_Function(Function*) = 0;
};

class WindowShell : public Shell
{
    private:
        Window* window;
        bool visibility;
        int number;
    public:
        // конструкторы-деструкторы
        WindowShell(Window*, bool);

        // деконструкция
        ShellType   Get_Type()      override;
        bool        Get_Visibility() override;
        int         Get_Number() override;
        Window*     Get_Window()    override; 
        Function*   Get_Function()  override;

        // операции
        void        Set_Visibility(bool) override;
        void        Set_Number(int) override;
        void        Set_Window(Window*) override; 
        void        Set_Function(Function*) override;
};

class FunctionShell : public Shell
{
    private:
        Function* function;
        bool visibility;
        int number;
    public:
        // конструкторы-деструкторы
        FunctionShell(Function*, bool);

        //деконструкция
        ShellType   Get_Type()      override;
        bool        Get_Visibility() override;
        int         Get_Number() override;
        Window*     Get_Window()    override; 
        Function*   Get_Function()  override;

        //операции
        void        Set_Visibility(bool) override;
        void        Set_Number(int) override;
        void        Set_Window(Window*) override; 
        void        Set_Function(Function*) override;
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
        string                      Get_WindowName();
        string                      Get_WelcomeMessage();

        DynamicArray<Shell*>*       Get_Shells();
        int                         Get_Amount_Shells();

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


typedef void (*adapter_ptr)(DynamicArray<string>);
class Function
{
    private:    
        string functionName;
        adapter_ptr adapter;

    public:
        // конструкторы-деструкторы
        Function(string, adapter_ptr);  

        // деконструкция
        string Get_FunctionName();
        adapter_ptr Get_Adapter();

        // операции
        void Set_FunctionName(string);
        void Set_Adapter(adapter_ptr);
        
};




class ActiveWindow
{
    private:
        Window* currentWindow;
        Window* previousWindow; 
    public:
        // конструкторы-деструкторы
        ActiveWindow(Window* window);

        // деконструкция
        Window* Get_CurrentWindow();
        Window* Get_PreviousWindow();
    
        //операции
};

// FunctionShell
    // конструкторы
        FunctionShell::FunctionShell(Function* function, bool visibility):
            function(function),
            visibility(visibility),
            number(0)
        { }
    // деконструкция
        Shell::ShellType    FunctionShell::Get_Type() 
        {
            return ShellType::WindowType;
        }
        bool                FunctionShell::Get_Visibility()
        {
            return visibility;
        }
        int                 FunctionShell::Get_Number()
        {
            return number;
        }
        Window*             FunctionShell::Get_Window()
        {
            return nullptr;
        }  
        Function*           FunctionShell::Get_Function()
        {
            return function;
        } 
    // операции
        void                FunctionShell::Set_Visibility(bool newVisibility)
        {
            visibility = newVisibility;
        }
        void                FunctionShell::Set_Number(int newNumber)
        {
            number = newNumber;
        }
        void                FunctionShell::Set_Window(Window* newWindow)
        {
            return;
        } 
        void                FunctionShell::Set_Function(Function* newFunction)
        {
            function = newFunction;
        }

// WindowShell
    // конструкторы-деструкторы
        WindowShell::WindowShell(Window* window, bool visibility):
            window(window),
            visibility(visibility),
            number(0)
        { }
    
    // деконструкция
        Shell::ShellType    WindowShell::Get_Type() 
        {
            return ShellType::WindowType;
        }
        bool                WindowShell::Get_Visibility()
        {
            return visibility;
        }
        int                 WindowShell::Get_Number()
        {
            return number;
        }
        Window*             WindowShell::Get_Window()
        {
            return window;
        }  
        Function*           WindowShell::Get_Function()
        {
            return nullptr;
        } 
    // операции
        void                WindowShell::Set_Visibility(bool newVisibility)
        {
            visibility = newVisibility;
        }
        void                WindowShell::Set_Number(int newNumber)
        {
            number = newNumber;
        }
        void                WindowShell::Set_Window(Window* newWindow)
        {
            window = newWindow;
        } 
        void                WindowShell::Set_Function(Function* newFunction)
        {
            return;
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

// Function
    // конструкторы-деструкторы
        Function::Function(string functionName, adapter_ptr adapter):
            functionName(functionName),
            adapter(adapter)
        { }

    // декомпозиция
        string Function::Get_FunctionName()
        {
            return functionName;
        }
        adapter_ptr Function::Get_Adapter()
        {
            return adapter;
        }
    // операции
        void Function::Set_FunctionName(string newFunctionName)
        {
            functionName = newFunctionName;
        }
        void Function::Set_Adapter(adapter_ptr newAdapter)
        {
            adapter = newAdapter;
        }
