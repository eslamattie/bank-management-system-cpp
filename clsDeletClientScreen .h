#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <string>
#include "clsUtil.h"
using namespace std;
class clsDeletClientScreen : protected clsScreen
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
        cout << "\nPassword    : " <<Client1.PinCode;
        cout << "\nBalance     : " << Client1.AccountBalance;
        cout << "\n___________________\n";

    }

public:
    static void ShowDeletClientScreen()
    {

        if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pDeleteClient)))
        {
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");
        string AccountNumber = "";
        cout << "please enter client account number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "account number is not found , choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "Are You Sure You Want to Delet This Client y/n? ";
        char choose = 'c';
        cin >> choose;
        if (toupper(choose) == 'Y')
        {

            if (Client1.Delete())
            {
                cout << "\nAccount Deleted Successfully :-)" << endl;
                _PrintClient(Client1);
            }
            else
            {
                cout << "\nError Client Was Not Deleted\n";
            }
        }

    }

};