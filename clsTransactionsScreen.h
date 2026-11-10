#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransfer.h"
#include "clsTransferLog.h"
class TransactionsScreen:protected clsScreen
{
private:

    enum enTransacthionsMenuOptions {
        eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog=5,eMainMenu = 6
    };

    static short _ReadTransacthionMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    static void Deposit()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void Withdraw()
    {
        clsWithDrawScreen::ShowWithDrawScreen();
    }
    static void Transfer()
    {
        clsTransfer::ShowTransferScreen();
    }
    static void TransferLog()
    {
        clsTransferLog::ShowTransferLog();
    }
    static void TotalBalances()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void MainMenu()
    {

    }

    static void GetBackToTransactionsMenu()
    {

        cout  << "\nPress any key to go back to Transaction Menue...\n";

        system("pause>0");
        ShowTransactionsScreen();
    }
    static void PerformTransactionsScreen(enTransacthionsMenuOptions Transactions)
    {
        switch (Transactions)
        {
        case enTransacthionsMenuOptions::eDeposit:
            system("cls");
            Deposit();
            GetBackToTransactionsMenu();
            break;
        case enTransacthionsMenuOptions::eWithdraw:
            system("cls");
            Withdraw();
            GetBackToTransactionsMenu();
            break;
        case enTransacthionsMenuOptions::eTotalBalances:
            system("cls");
            TotalBalances();
            GetBackToTransactionsMenu();
            break;
        case enTransacthionsMenuOptions::eTransfer:
            system("cls");
            Transfer();
            GetBackToTransactionsMenu();
            break;
        case enTransacthionsMenuOptions::eTransferLog:
            system("cls");
            TransferLog();
            GetBackToTransactionsMenu();
            break;
        case enTransacthionsMenuOptions::eMainMenu:
            MainMenu();
            break;
        }
    }
public:
	static void ShowTransactionsScreen()
	{

        if (!(clsScreen::CheckAccessRight(clsUser::enPermissions::pTransactions)))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t  Transaction Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        PerformTransactionsScreen((enTransacthionsMenuOptions)_ReadTransacthionMenuOption());
	}
};

