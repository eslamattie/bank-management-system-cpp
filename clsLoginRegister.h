#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsUtil.h"
class clsLoginRegister:protected clsScreen
{
private:

	static void printLoginRegisterFile(clsUser::stLoginRegister Login)
	{
		cout << setw(8) << left << ""<< "| " << setw(35) << left << Login.DateTime;
		cout << "| " << setw(20) << left << Login.UserName;
		cout << "| " << setw(20) << left << Login.Password;
		cout << "| " << setw(10) << left << Login.Permissions;
	}

public:

	static void ShowLoginRegister()
	{
		if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pLoginRegister)))
		{
			return;
		}
		vector<clsUser::stLoginRegister>LoginRegister = clsUser::GetLoginRecordFromFile();
		string Title = "\tLogin Register List Screen";
		string Subtitle = "\t\t " + to_string(LoginRegister.size()) + " Record(s).";
		_DrawScreenHeader(Title, Subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (LoginRegister.size()==0)
		{
			cout << "\t\t\t\tNo Logins Available In the System!";
		}
		else
		{

			for (clsUser::stLoginRegister l : LoginRegister)
			{

				printLoginRegisterFile(l);
				cout << endl;

			}

			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "_________________________________________\n" << endl;

		}
	}
};

