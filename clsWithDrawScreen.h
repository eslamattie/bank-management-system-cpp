#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsWithDrawScreen:protected clsScreen
{
private:
    static void _Print(clsBankClient Client1)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client1.FirstName;
        cout << "\nLastName    : " << Client1.LastName;
        cout << "\nFull Name   : " << Client1.FullName();
        cout << "\nEmail       : " << Client1.Email;
        cout << "\nPhone       : " << Client1.Phone;
        cout << "\nAcc. Number : " << Client1.getAccountNumber();
        cout << "\nPassword    : " << Client1.PinCode;
        cout << "\nBalance     : " << Client1.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "please enter client account number: ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
public:
    static void ShowWithDrawScreen()
    {
        _DrawScreenHeader("\tWithdraw  Screen");
        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);
        float Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadDblNumber();
        if (Amount <= Client1.AccountBalance)
        {
            cout << "\nAre you sure you want to perform this transaction n/y ? ";
            char choose = 'n';
            cin >> choose;
            if (toupper(choose) == 'Y')
            {
                Client1.Withdraw(Amount);
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.AccountBalance;

            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }
        }
        else
        {
            cout << "\nCannot withdraw, Insufficient Balance!\n";
            cout << "\Amount to withdraw is: " << Amount;
            cout << "\nYour Balance is: " << Client1.AccountBalance;
        }
        

    }
};

