#pragma once

#include <iostream>
#include "C:\Main\Kodiki\C++\SimpleConsoleUI\DynamicArrayForUI.h"
using namespace std;

class Shell;

class Connector;
class Function;
class ActiveShell;



typedef void (*Function_ptr)();
class Shell
{
    private:
        string name;
        Function_ptr function;
        Connector* connector;
    public:
        // конструкторы-деструкторы
        Shell(string, Function_ptr, Connector*);

        // деконструкция
        string      Get_Name();

        Connector*      Get_Connector(); 
        Function_ptr    Get_Function();
        
        // операции
        void        Set_Name(string);

        void        Set_Connector(Connector*); 
        void        Set_Function(Function_ptr);
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

class ActiveShell
{
    private:
        Shell* shell;

        void    ClearOutput();
        void    PressEnterToContinue();
        void    ProcessShell();

    public:
        // конструкторы-деструкторы
        ActiveShell(Shell*);

        // деконструкция
        Shell*  Get_Shell();
    
        //операции
        void    StartUI();
        void    Set_Shell(Shell*);
        void    TableOutput(string&);
        void    TableOutput(DynamicArray<string>&);
};


// Shell
    // конструкторы-деструкторы
        Shell::Shell(string name, Function_ptr function, Connector* connector):
            name(name),
            function(function),
            connector(connector)
        {  }
    // деструкторы
        string      Shell::Get_Name()
        {
            return name;
        }
        Connector*  Shell::Get_Connector()
        {
            return connector;
        }
        Function_ptr   Shell::Get_Function()
        {
            return function;
        }
    // операции
        void        Shell::Set_Name(string newShellName)
        {
            name = newShellName;
        }
        void        Shell::Set_Connector(Connector* newShellConnector)
        {
            connector = newShellConnector;
        }
        void        Shell::Set_Function(Function_ptr newShellFunction)
        {
            function = newShellFunction;
        }

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
        DynamicArray<Shell*>*   Connector::Get_Shells()
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

// ActiveShell
    // конструкторы-деструкторы
        ActiveShell::ActiveShell(Shell* shell):
            shell(shell)
        {  }

    // деконструкция
        Shell*  ActiveShell::Get_Shell()
        {
            return shell;
        }
    // операции
        void    ActiveShell::Set_Shell(Shell* newShell)
        {
            shell = newShell;
        }
        void    ActiveShell::ClearOutput()
        {
            cout << "\033[2J\033[1;1H";
        }
        void    ActiveShell::TableOutput(string& str)
        {
            cout << "┏"; 
            for (int i = 0; i < str.size()+2; i++) cout << "━";
            cout << "┓\n";
            cout << "┃ " << str << " ┃\n";
            cout << "┗";
            for (int i = 0; i < str.size()+2; i++) cout << "━";
            cout << "┛\n";
        }
        void    ActiveShell::TableOutput(DynamicArray<string> &strings)
        {
            int width = -1;
            for (int i = 0; i < strings.GetSize(); i++)
                width = max(width, int(strings[i].size()));
            width += 2;
            cout << "┏"; 
            for (int i = 0; i < width; i++) cout << "━";
            cout << "┓\n";

            for (int i = 0; i < strings.GetSize() - 1; i++)
            {
                cout << "┃ " << strings[i];
                for (int j = 0; j < width - 1 - strings[i].size(); j++)
                    cout << " ";
                cout << "┃\n";
                cout << "┠";
                for (int j = 0; j < width; j++) cout << "─";
                cout << "┨\n";
            }
            cout << "┃ " << strings[strings.GetSize()-1];
            for (int i = 0; i < width - 1 - strings[strings.GetSize()-1].size(); i++)
                cout << " ";
            cout << "┃\n";
            cout << "┗";
            for (int i = 0; i < width; i++) cout << "━";
            cout << "┛\n";
        }
        void    ActiveShell::PressEnterToContinue()
        {

            cout << "╔═══════════════════════════╗\n"
                 << "║ Press 'Enter' to continue ║\n"
                 << "╚═══════════════════════════╝\n";
            string pressEnter;
            getline(cin, pressEnter);
        }
        void    ActiveShell::ProcessShell()
        {
            ClearOutput();

            if (shell->Get_Function() != nullptr)
            {
                shell->Get_Function()();
                PressEnterToContinue();
                ClearOutput();
            }

            if (shell->Get_Connector()->Get_Shells()->GetSize() == 0)
            {
                string tableOutput = "End of the Program";
                TableOutput(tableOutput);
                exit(1);
            }
            else if (shell->Get_Connector()->Get_Shells()->GetSize() == 1)
            {
                DynamicArray<string> tableOutput;
                tableOutput.Append("Current Window: " + shell->Get_Name());
                tableOutput.Append("Next Window: " + shell->Get_Connector()->Get_Shells()->Get(0)->Get_Name());
                TableOutput(tableOutput);
                PressEnterToContinue();   
                shell = shell->Get_Connector()->Get_Shells()->Get(0);      
            }
            else 
            {
                DynamicArray<string> tableOutput;
                tableOutput.Append("Current Window: " + shell->Get_Name());
                for (int i = 0; i < shell->Get_Connector()->Get_Shells()->GetSize(); i++)
                    tableOutput.Append(to_string(i + 1) + ") " + shell->Get_Connector()->Get_Shells()->Get(i)->Get_Name());
                TableOutput(tableOutput);
                string tableOutput2 = "Input integer from 1 to " + to_string(shell->Get_Connector()->Get_Shells()->GetSize());
                TableOutput(tableOutput2);
                string stringOption;
                int intOption;
                bool correctInput;
                while (true)
                {
                    correctInput = true;
                    getline(cin, stringOption);
                    if (stringOption.size() == 0)
                        correctInput = false;
                    if (correctInput)
                    {
                        for (int i = 0; i < stringOption.size(); i++)
                        {
                            if (!isdigit(stringOption[i]))
                            {
                                correctInput = false;
                                break;
                            }
                        }
                    }
                    if (correctInput)
                    {
                        intOption = stoi(stringOption);
                        if ((intOption - 1 < 0) || (shell->Get_Connector()->Get_Shells()->GetSize() <= intOption - 1))
                            correctInput = false;
                    }   
                    if (correctInput)
                        break;
                    tableOutput2 = "Wrong. Try input integer from 1 to " + to_string(shell->Get_Connector()->Get_Shells()->GetSize());
                    TableOutput(tableOutput2);
                }
                shell = shell->Get_Connector()->Get_Shells()->Get(intOption - 1);
            } 
        }
        void    ActiveShell::StartUI()
        {
            while (true)
            {
                ProcessShell();
            }
        }