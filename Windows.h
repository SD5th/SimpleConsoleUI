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
        virtual Window*     Get_Window() = 0; 
        virtual Function*   Get_Function() = 0;
        
        // операции
        virtual void        Set_Window(Window*) = 0; 
        virtual void        Set_Function(Function*) = 0;
};

class WindowShell : public Shell
{
    private:
        Window* window;
    public:
        // конструкторы-деструкторы
        WindowShell(Window*);

        // деконструкция
        ShellType   Get_Type()      override;
        Window*     Get_Window()    override; 
        Function*   Get_Function()  override;

        // операции
        void        Set_Window(Window*) override; 
        void        Set_Function(Function*) override;
};

class FunctionShell : public Shell
{
    private:
        Function* function;
        int number;     
    public:
        // конструкторы-деструкторы
        FunctionShell(Function*);

        //деконструкция
        ShellType   Get_Type()      override;
        Window*     Get_Window()    override; 
        Function*   Get_Function()  override;

        //операции
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
        
        void Append_WindowShell(Window*);
        void Insert_WindowShell(Window*, int);
        void Change_WindowShell(Window*, int);

        void Append_FunctionShell(Function*);
        void Insert_FunctionShell(Function*, int);
        void Change_FunctionShell(Function*, int);
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
        DynamicArray<Shell*>* shells;

    public:
        // конструкторы-деструкторы
        ActiveWindow(Window* window);

        // деконструкция
        Window* Get_CurrentWindow();
        Window* Get_PreviousWindow();
        DynamicArray<Shell*>* Get_Shells();
    
        //операции
        void Set_CurrentWindow(Window*);
        void Set_PreviousWindow(Window*);
        void Set_Shells(DynamicArray<Shell*>*);

        void InitializeWindow();
        void MoveToWindow(Window*);
        void PickOption(int);
        void PrintWindow(); 

         

};


// WindowShell
    // конструкторы-деструкторы
        WindowShell::WindowShell(Window* window):
            window(window)
        { }
    
    // деконструкция
        Shell::ShellType    WindowShell::Get_Type() 
        {
            return ShellType::WindowType;
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
        void                WindowShell::Set_Window(Window* newWindow)
        {
            window = newWindow;
        } 
        void                WindowShell::Set_Function(Function* newFunction)
        {
            return;
        }

// FunctionShell
    // конструкторы
        FunctionShell::FunctionShell(Function* function):
            function(function)
        { }
    // деконструкция
        Shell::ShellType    FunctionShell::Get_Type() 
        {
            return ShellType::FunctionType;
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
        void                FunctionShell::Set_Window(Window* newWindow)
        {
            return;
        } 
        void                FunctionShell::Set_Function(Function* newFunction)
        {
            function = newFunction;
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
        {        }

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

        void Window::Append_WindowShell(Window* window)
        {
            shells->Append(new WindowShell(window)); 
        }
        void Window::Insert_WindowShell(Window* window, int index)
        {
            shells->Insert(new WindowShell(window), index);
        }
        void Window::Change_WindowShell(Window* window, int index)
        {
            delete shells->Get(index);
            shells->Set(new WindowShell(window), index);
        }
    
        void Window::Append_FunctionShell(Function* function)
        {
            shells->Append(new FunctionShell(function)); 
        }
        void Window::Insert_FunctionShell(Function* function, int index)
        {
            shells->Insert(new FunctionShell(function), index);
        }
        void Window::Change_FunctionShell(Function* function, int index)
        {
            delete shells->Get(index);
            shells->Set(new FunctionShell(function), index);
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

// ActiveWindow
    // конструкторы-деструкторы
        ActiveWindow::ActiveWindow(Window* window):
            currentWindow(window),
            previousWindow(nullptr)
        {  }

    // деконструкция
        Window* ActiveWindow::Get_CurrentWindow()
        {
            return currentWindow;
        }
        Window* ActiveWindow::Get_PreviousWindow()
        {
            return previousWindow;
        }
        DynamicArray<Shell*>* ActiveWindow::Get_Shells()
        {
            return shells;
        }
    // операции
        void ActiveWindow::Set_CurrentWindow(Window* newCurrentWindow)
        {
            currentWindow = newCurrentWindow;
        }
        void ActiveWindow::Set_PreviousWindow(Window* newPreviousWindow)
        {
            previousWindow = newPreviousWindow;
        }
        void ActiveWindow::Set_Shells(DynamicArray<Shell*>* newShells)
        {
            shells = newShells;
        }

        void ActiveWindow::MoveToWindow(Window* nextWindow)
        {
            previousWindow = currentWindow;
            currentWindow = nextWindow;
        }