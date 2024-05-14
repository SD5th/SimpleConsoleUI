#include "SimpleConsoleUI.h"


string UserName = "Unknown";
void Head_Function()
{
    if (UserName == "Unknown")
        cout << "Hey, user! I don't know your name yet.";
    else
        cout << "Hey, " << UserName << "! I know your name.";
    cout << "\n\n";
}
Shell* Head = new Shell("Head Window", Head_Function, new Connector);

void WhatIsYourName_Function()
{
    cout << "Input your name.\n";
    getline(cin, UserName);
    cout << "Good to know. Your name: " << UserName <<".\n";
}
Shell* WhatIsYourName = new Shell("What Is Your Name Window", WhatIsYourName_Function, new Connector);

void Exit_Function()
{
    cout << "Confirm exit from the program. Type EXIT\n";
    string UserText; 
    getline(cin, UserText);
    if (UserText == "EXIT")
    {
        if (UserName == "Unknown")
            cout << "So sad.. Bye, unknown user!\n";
        else 
            cout << "So sad.. Bye, " << UserName << "!\n"; 
        exit(1);
    }
    else 
    {
        cout << "Then let's stay together!\n";
    }
}
Shell* Exit = new Shell("Exit Window", Exit_Function, new Connector);

int main()
{
    //SetConsoleOutputCP(CP_UTF8);
    Head->Get_Connector()->Append_Shell(WhatIsYourName);
    Head->Get_Connector()->Append_Shell(Exit);

    WhatIsYourName->Get_Connector()->Append_Shell(Head);

    Exit->Get_Connector()->Append_Shell(Head);

    ActiveShell Active(Head);
    Active.StartUI();
}