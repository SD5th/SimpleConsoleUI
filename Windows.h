#include <iostream>
#include "DynamicArray.h"

using namespace std;

class Shell;

class Connector;
class Function;
class ActiveShell;


class Shell
{
    public:
        // конструкторы-деструкторы
        Shell(string, Function*, Function*, Connector*);

        // деконструкция
        Function*   Get_EntranceFunction();

        Connector*     Get_ShellConnector(); 
        Function*   Get_ShellFunction();
        
        // операции
        void        Set_EntranceFunction(Function*);

        void        Set_ShellConnector(Connector*); 
        void        Set_ShellFunction(Function*);
    private:
        string shellName;
        Function* entranceFunction;
        Function* shellFunction;
        Connector* shellConncetor;
};


class Connector
{
    private:
        DynamicArray<Shell*>* shells;

    public:
        // конструкторы
        Connector();
        Connector(DynamicArray<Shell*>*);
        ~Connector();

        // декомпозиция
        DynamicArray<Shell*>*       Get_Shells();

        // операции
        void Set_Shells(DynamicArray<Shell*>*);
        
        void Append_Shell(Shell*);
        void Insert_Shell(Shell*, int);
        void Change_Shell(Shell*, int);
        void Delete_Shell(int);
};

typedef void (*adapter_ptr)(DynamicArray<string>);
class Function
{
    private:    
        adapter_ptr adapter;

    public:
        // конструкторы-деструкторы
        Function(adapter_ptr);  

        // деконструкция
        adapter_ptr Get_Adapter();

        // операции
        void Set_Adapter(adapter_ptr);
        void RunFunction(DynamicArray<string>);
};


class ActiveShell
{
    private:
        Shell* currentShell;
        Shell* previousShell;

    public:
        // конструкторы-деструкторы
        ActiveShell(Shell*);

        // деконструкция
        Shell* Get_CurrentShell();
        Shell* Get_PreviousShell();
    
        //операции
        void Set_CurrentShell(Shell*);
        void Set_PreviousShell(Shell*);

        void InitializeWindow();
        void MoveToShell(Shell*);
        void PickOption(int);
        void PrintWindow(); 

         

};


// Connector
    // конструкторы-деструкторы
        Connector::Connector():
            shells(new DynamicArray<Shell*>)    
        { }
        Connector::Connector(DynamicArray<Shell*>* shells):
            shells(shells)    
        { }
        Connector::~Connector()
        {
            if (shells != nullptr)
                free(shells);
        }


    // декомпозиция
        DynamicArray<Shell*>*           Connector::Get_Shells()
        {
            return shells;
        }
    // операции
        void Connector::Set_Shells(DynamicArray<Shell*>* newShells)
        {
            shells = newShells;
        }

        void Connector::Append_Shell(Shell* shell)
        {
            shells->Append(shell); 
        }
        void Connector::Insert_Shell(Shell* shell, int index)
        {
            shells->Insert(shell, index);
        }
        void Connector::Change_Shell(Shell* shell, int index)
        {
            shells->Set(shell, index);
        }
        void Connector::Delete_Shell(int index)
        {
            shells->Delete(index);
        }


// Function
    // конструкторы-деструкторы
        Function::Function(adapter_ptr adapter):
            adapter(adapter)
        { }

    // декомпозиция
        adapter_ptr Function::Get_Adapter()
        {
            return adapter;
        }
    // операции
        void Function::Set_Adapter(adapter_ptr newAdapter)
        {
            adapter = newAdapter;
        }

// ActiveShell
    // конструкторы-деструкторы
        ActiveShell::ActiveShell(Shell* shell):
            currentShell(shell),
            previousShell(nullptr)
        {  }

    // деконструкция
        Shell* ActiveShell::Get_CurrentShell()
        {
            return currentShell;
        }
        Shell* ActiveShell::Get_PreviousShell()
        {
            return previousShell;
        }
    // операции
        void ActiveShell::Set_CurrentShell(Shell* newCurrentShell)
        {
            currentShell = newCurrentShell;
        }
        void ActiveShell::Set_PreviousShell(Shell* newPreviousShell)
        {
            previousShell = newPreviousShell;
        }