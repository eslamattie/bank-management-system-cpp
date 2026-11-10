#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"
using namespace std;
class clsBankClient :public clsPerson
{
private:
	enum _enMode { EmbtyMode = 0, updetmod = 1, AddNewMode = 2 };

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	_enMode _Mode;
	bool _MarkforDelet = false;
	
	 string ConcertRecordToLine( clsBankClient Client2,float Amount)
	{
		string Line = "";
		Line += clsDate::GetSystemDate() + "#//#";
		Line += getAccountNumber() + "#//#";
		Line += Client2.getAccountNumber()+ "#//#";
		Line += to_string(Amount) + "#//#";
		Line += to_string(getAccountBalance())+ "#//#";
		Line += to_string(Client2.getAccountBalance())+ "#//#";
		Line += currentUser.UserName;
		return Line;
	}
	 void AddTransferLoginToFile( clsBankClient Client2, float Amount)
	{
		fstream File;
		File.open("TransferLog.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << ConcertRecordToLine(Client2, Amount) << endl;

			File.close();
		}
	}
	static clsBankClient _convertlinetoobject(string line)
	{
		vector<string>vAccountRecord = clsString::Split(line, "#//#");
		return clsBankClient(_enMode::updetmod, vAccountRecord[0], vAccountRecord[1], vAccountRecord[2], vAccountRecord[3], vAccountRecord[4], vAccountRecord[5], stof(vAccountRecord[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(_enMode::EmbtyMode, "", "", "", "", "", "", 0);
	}

	static string _convertrecordtoline(clsBankClient client, string separetor = "#//#")
	{
		string DateLine = "";
		DateLine += client.FirstName + separetor;
		DateLine += client.LastName + separetor;
		DateLine += client.Email + separetor;
		DateLine += client.Phone + separetor;
		DateLine += client.getAccountNumber() + separetor;
		DateLine +=client.PinCode + separetor;
		DateLine += to_string(client.AccountBalance);
		return DateLine;
	}

	static vector<clsBankClient>LoadclientDateFromFile()
	{
		fstream file;
		vector<clsBankClient>vclient;
		file.open("Clients.txt", ios::in);
		if (file.is_open())
		{

			string line;

			while (getline(file, line))
			{
				clsBankClient client = _convertlinetoobject(line);
				vclient.push_back(client);
			}
			file.close();

		}
		return vclient;
	}

	static void _saveclientDatetofile(vector<clsBankClient>vclient)
	{
		fstream file;
		file.open("Clients.txt", ios::out);
		string DateLine;
		if (file.is_open())
		{
			for (clsBankClient& client : vclient)
			{
				DateLine = _convertrecordtoline(client);
				file << DateLine << endl;
			}
			file.close();
		}
	}
	void _AddDateLinetofile(string line)
	{

		fstream file;
		file.open("Clients.txt", ios::app);
		if (file.is_open())
		{
			file << line << endl;
			file.close();
		}

	}
	void _Updet()
	{
		vector<clsBankClient>vclient = LoadclientDateFromFile();
		fstream file;
		file.open("Clients.txt", ios::in);
		if (file.is_open())
		{

			for (clsBankClient& client : vclient)
			{
				if (client.getAccountNumber() == getAccountNumber())
				{
					client = *this;
					break;
				}
			}
			_saveclientDatetofile(vclient);
		}
	}
	void _AddNew()
	{
		_AddDateLinetofile(_convertrecordtoline(*this));

	}
	static void _saveclientDatetofileAfterDelet(vector<clsBankClient>vclient)
	{
		fstream file;
		file.open("Clients.txt", ios::out);
		string DateLine;
		if (file.is_open())
		{
			for (clsBankClient& client : vclient)
			{
				if (client._MarkforDelet==false)
				{
				DateLine = _convertrecordtoline(client);
				file << DateLine << endl;
				}
			}
			file.close();
		}
	}
public:

	clsBankClient(_enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pincode, float AccountBalance) :clsPerson(FirstName, LastName, Email, Phone)
	{
		_AccountNumber = AccountNumber;
		_PinCode = Pincode;
		_AccountBalance = AccountBalance;
		_Mode = Mode;
	}
	bool IsEmpty()
	{
		return (_Mode == _enMode::EmbtyMode);
	}
	string getAccountNumber()
	{
		return _AccountNumber;
	}

	void setPincode(string Pincode)
	{
		_PinCode = Pincode;
	}
	string getPincode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPincode, put = setPincode)) string PinCode;
	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;
	
	static clsBankClient Find(string AccountNumber)
	{
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _convertlinetoobject(line);
				if (client.getAccountNumber() == AccountNumber)
				{
					file.close();
					return client;
				}
			}

			file.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string Pincode)
	{
		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _convertlinetoobject(line);
				if (client._AccountNumber == AccountNumber && client._PinCode == Pincode)
				{
					file.close();
					return client;
				}
			}

			file.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return(!Client.IsEmpty());
	}
	enum _enSaveclient { svFaildEmptyObject = 0, svSucceeded = 1, SaveFalidAccountNumberIsExist = 2 };
	_enSaveclient Save()
	{
		switch (_Mode)
		{
		case _enMode::EmbtyMode:
		{

			return _enSaveclient::svFaildEmptyObject;

		}
		case _enMode::updetmod:
		{

			_Updet();
			return _enSaveclient::svSucceeded;

		}
		case _enMode::AddNewMode:
		{

			if (IsClientExist(_AccountNumber))
			{
				return _enSaveclient::SaveFalidAccountNumberIsExist;
			}
			else
			{
			  _AddNew();
			  _Mode = _enMode::updetmod;
			  return _enSaveclient::svSucceeded;

			}

		}
		}
	}
	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient(_enMode::AddNewMode, " ", " ", " ", " ", AccountNumber, " ", 0);
	}


	bool Delete()
	{
		vector<clsBankClient>Vclient = LoadclientDateFromFile();

		for (clsBankClient &client:Vclient)
		{
			if (client.getAccountNumber() == _AccountNumber)
			{
				client._MarkforDelet = true;
				break;
			}
		}
		_saveclientDatetofileAfterDelet(Vclient);
		*this = _GetEmptyClientObject();
	return true;
	}

	static vector<clsBankClient>GetClientsList()
	{
		return LoadclientDateFromFile();
	}

	static double GetTotalBalance()
	{
		vector <clsBankClient>vclient = GetClientsList();
		double totalbalance = 0;
		for (clsBankClient &client :vclient)
		{
			totalbalance += client.AccountBalance;
		}
		return totalbalance;
	}

	 void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	 bool Withdraw(float Amount)
	 {
		 if (Amount > _AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 _AccountBalance -= Amount;
			 Save();
			 return true;
		 }
	 }

	 bool Transfer(float amount, clsBankClient& DestinationClient)
	 {
		 Withdraw(amount);
		 DestinationClient.Deposit(amount);	
		 AddTransferLoginToFile( DestinationClient, amount);
		 return true;
	 }
	 static bool isSameAccount(clsBankClient Client1, clsBankClient Client2)
	 {
		 return Client1.getAccountNumber() == Client2.getAccountNumber();

	 }
	 static struct stTransferLog
	 {
		 string time;
		 string AccountNumberFrom;
		 string AccountNumberto;
		 float Amount;
		 float AccontBalanceFrom;
		 float AccontBalanceTo;
		 string User;
	 };
	 static stTransferLog  concertLineToStruct(string Line, string separetor = "#//#")
	 {
		 stTransferLog TransferLog;
		 vector <string>veachLine = clsString::Split(Line, separetor);
		 TransferLog.time = veachLine[0];
		 TransferLog.AccountNumberFrom = veachLine[1];
		 TransferLog.AccountNumberto = veachLine[2];
		 TransferLog.Amount = stof(veachLine[3]);
		 TransferLog.AccontBalanceFrom = stof(veachLine[4]);
		 TransferLog.AccontBalanceTo = stof(veachLine[5]);
		 TransferLog.User = veachLine[6];
		 return TransferLog;
	 }

	 static vector <stTransferLog>vconcertLineToRecord()
	 {
		 vector <stTransferLog>TransferLog;
		 string line;
		 fstream File;
		 File.open("TransferLog.txt", ios::in);
		 if (File.is_open())
		 {
			 while (getline(File, line))
			 {
				 TransferLog.push_back(concertLineToStruct(line));
			 }
			 File.close();
		 }
		 return TransferLog;
		 
	 }
};

