#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <string>
using namespace std;
class clsFindClientScreen:protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client1)
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

public:
    static void ShowFindClientScreen()
    {

        if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pFindClient)))
        {
            return;
        }
        _DrawScreenHeader("\tFind Client Screen");
        string AccountNumber = "";
        cout << "please enter client account number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "account number is not found , choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        if (!Client1.IsEmpty())
        {
           cout << "Client Found :-)\n";
        }
        else
        {
            cout << "Client Not Found :-(\n";
        }
        _PrintClient(Client1);

    }
};

