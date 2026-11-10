#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersMenue:protected clsScreen
{
	enum enManageUsersScreen 
	{
		eListUser = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};
	static short _ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}
    static  void _GoBackToManageUserMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowManageUserMenue();
    }

    static void _ShowAllManagesScreen()
    {
        clsUsersListScreen::ShowClientsList();
    }

    static void _ShowAddNewManagesScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();

    }

    static void _ShowDeleteManageScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateManageScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();

    }

    static void _ShowFindManageScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();

    }


    static void _ShowMainMenu()
    {
    }
    static void _PerfromMainMenueOption(enManageUsersScreen ManageUsersOption)
    {
        switch (ManageUsersOption)
        {
        case enManageUsersScreen::eListUser:
        {
            system("cls");
            _ShowAllManagesScreen();
            _GoBackToManageUserMenue();
            break;
        }
        case enManageUsersScreen::eAddNewUser:
            system("cls");
            _ShowAddNewManagesScreen();
            _GoBackToManageUserMenue();
            break;

        case enManageUsersScreen::eDeleteUser:
            system("cls");
            _ShowDeleteManageScreen();
            _GoBackToManageUserMenue();
            break;

        case enManageUsersScreen::eUpdateUser:
            system("cls");
            _ShowUpdateManageScreen();
            _GoBackToManageUserMenue();
            break;

        case enManageUsersScreen::eFindUser:
            system("cls");
            _ShowFindManageScreen();
            _GoBackToManageUserMenue();
            break;

        case enManageUsersScreen::eMainMenu:
            _ShowMainMenu();
            break;

        }

    }

public:
    static void ShowManageUserMenue()
    {

        if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pManageUsers)))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\t\tManage User Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage User Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enManageUsersScreen)_ReadManageUsersMenueOption());
    }
};

