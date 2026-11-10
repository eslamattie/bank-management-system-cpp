#pragma once
#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDate.h"
using namespace std;
class clsLoginScreen:protected clsScreen
{

private:
	static bool _Login()
	{

		short _FaildLoginCount = 0;
		string _UserName;
		string _Passward;
		bool LoginFaild = false;

		do
		{

			if (LoginFaild== true)
			{
				_FaildLoginCount++;
				cout << "\nInvlaid Username/Password!\n";
				cout << "You Have " << (3-_FaildLoginCount) << " Trial(s) to login.\n\n";
				if (_FaildLoginCount ==3)
				{
					cout << "\nYour are Locked after 3 faild trails\n\n";
					return false;
				}
			}

			cout << "Enter Username? ";
			_UserName = clsInputValidate::ReadString();
			cout << "Enter Password? ";
			_Passward = clsInputValidate::ReadString();
			currentUser = clsUser::Find(_UserName, _Passward);
			LoginFaild = currentUser.IsEmpty();
		} while (LoginFaild==true);
		currentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{

		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();

	}

	
};

