#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;
class clsTransfer:protected clsScreen
{
    
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:\n\n";
        cout << "-----------------------------------\n\n";
        cout << "Full Name     :" << Client.FullName()<<endl;
        cout << "Acc. Number   :" << Client.getAccountNumber() << endl;
        cout << "Balance       :" << Client.getAccountBalance();
        cout << "\n\n-----------------------------------\n";
    }

    static string FindAccountNumber()
    {
        string AccountNumber1 = "";

        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber1 = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber1))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber1 = clsInputValidate::ReadString();
        }
        return AccountNumber1;
    }

    static float readAmount(clsBankClient Client1)
    {
        cout << "\n\nEnter Transfar Amount ? ";
        float TransfarAmount = clsInputValidate::ReadFloatNumber();
        while (TransfarAmount > Client1.getAccountBalance())
        {
            cout << "\n\nAmount Exceeds the available Balance, Enter Another Amount ?   ";
            TransfarAmount = clsInputValidate::ReadFloatNumber();
        }
        return TransfarAmount;
    }
    
public:

    static void ShowTransferScreen()
    {

        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient Client1 = clsBankClient::Find(FindAccountNumber());
        _PrintClient(Client1);
        clsBankClient Client2 = clsBankClient::Find(FindAccountNumber());
        while (clsBankClient::isSameAccount(Client1, Client2))
        {
            cout << "\nYou Cannot Transfer to the same Account!\n";
            Client2 = clsBankClient::Find(FindAccountNumber());
        }
        _PrintClient(Client2);
        float TransfarAmount = readAmount(Client1);
        char choose = 'n';
        cout << "Are You Sure You Want to Perform This operathion? y/n? ";
        choose = clsInputValidate::ReadChar();
        if (toupper(choose)=='Y')
        {
            if ( Client1.Transfer(TransfarAmount, Client2))
            {
                cout << "\nTransfar Done Successfully\n";
            }

        }

        _PrintClient(Client1);
        _PrintClient(Client2);

    }
    
};

