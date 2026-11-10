#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <string>
#include "clsUtil.h"
class clsAddNewClientScreen:protected clsScreen
{

private:

    static void Readclientinfo(clsBankClient& Client1)
    {
        cout << "\nEnter first name: ";
        Client1.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter last name: ";
        Client1.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        Client1.Email = clsInputValidate::ReadString();
        cout << "\nEnter phone: ";
        Client1.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Account Balance: ";
        Client1.AccountBalance = clsInputValidate::ReadFloatNumber();
        cout << "\nEnter Pin code: ";
        Client1.PinCode = clsInputValidate::ReadString();
    }
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
public:

   static void AddNewClient()
    {

       if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pAddNewClient)))
       {
           return;
       }
       _DrawScreenHeader("\t  Add New Client Screen");
        string AccountNumber = "";
        cout << "please enter client account number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "account number is Already Used, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Newclient = clsBankClient::GetAddNewClient(AccountNumber);
        Readclientinfo(Newclient);
        clsBankClient::_enSaveclient saveresult;
        saveresult = Newclient.Save();
        switch (saveresult)
        {
        case clsBankClient::_enSaveclient::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        case clsBankClient::_enSaveclient::SaveFalidAccountNumberIsExist:
            cout << "\nError account was not saved because it's Already Used";
            break;
        case clsBankClient::_enSaveclient::svSucceeded:
            cout << "\nAccount Added Successfully :-)";
            _Print(Newclient);
            break;
        }
    }

};

