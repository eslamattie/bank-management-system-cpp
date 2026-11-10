
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <string>
#include "clsUser.h"
using namespace std;
class clsUsersListScreen :protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }


public:

    static void ShowClientsList()
    {

        vector <clsUser> vUser = clsUser::GetUsersList();
        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUser.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vUser.size() == 0)
        {
            cout << "\t\t\t\tNo Users Available In the System!";
        }
        else
        {
            for (clsUser& User : vUser)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }

        cout << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};


