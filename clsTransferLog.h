#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;
class clsTransferLog:protected clsScreen
{
private:
	
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.time;
        cout << "| " << setw(8) << left << TransferLogRecord.AccountNumberFrom;
        cout << "| " << setw(8) << left << TransferLogRecord.AccountNumberto;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.AccontBalanceFrom;
        cout << "| " << setw(10) << left << TransferLogRecord.AccontBalanceTo;
        cout << "| " << setw(8) << left << TransferLogRecord.User;
        
    }

public:
   static void ShowTransferLog()
    {
    vector<clsBankClient::stTransferLog >vTransferLogRecord = clsBankClient::vconcertLineToRecord();
    string Title = "\t  Transfer  List Screen";
    string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Transfer(s).";
    _DrawScreenHeader(Title, SubTitle);
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
    cout << "| " << left << setw(8) << "s.Acct";
    cout << "| " << left << setw(8) << "d.Acct";
    cout << "| " << left << setw(8) << "Amount";
    cout << "| " << left << setw(10) << "s.Balance";
    cout << "| " << left << setw(10) << "d.Balance";
    cout << "| " << left << setw(8) << "User";

    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vTransferLogRecord.size() == 0)
        cout << "\t\t\t\tNo Transfers Available In the System!";
    for (clsBankClient::stTransferLog Record : vTransferLogRecord)
    {
        PrintTransferLogRecordLine(Record);
        cout << endl;
    }
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

   }
};

