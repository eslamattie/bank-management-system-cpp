# Security and reliability limitations

This is a learning project. Please do not use it with real money, real accounts or real personal data.

I decided to keep this version unchanged, exactly as I wrote it. The problems below are still in the code and I have not fixed them.

## Passwords and PINs

| Problem | Where |
|---|---|
| Passwords are saved with a fixed character shift (+5). It can be reversed easily. It is not encryption or hashing. | `clsUtil.h`, `clsUser.h` |
| Client PINs are saved as plain text. | `clsBankClient.h` |
| Every login writes the password (shifted) into `LoginRegister.txt`, and the login register screen shows it. | `clsUser.h`, `clsLoginRegister.h` |
| PINs and passwords are printed on many screens. | the client and user screens, `clsLoginRegister.h`, `clsDepositScreen.h`, `clsWithDrawScreen.h` |
| The password is visible while you type it. | `clsInputValidate.h`, `clsLoginScreen.h` |
| After three wrong logins the program closes. If you start it again, you get three more tries. | `clsLoginScreen.h` |

## Money

| Problem | Where |
|---|---|
| Negative amounts are accepted. A negative withdrawal adds money. A negative transfer moves money the wrong way. | `clsBankClient.h`, `clsDepositScreen.h`, `clsWithDrawScreen.h`, `clsTransfer.h` |
| `Transfer` does not check the result of `Withdraw`, so the deposit can happen even if the withdrawal failed. Today the transfer screen checks the balance first, so this only matters if the balance changed in between. | `clsBankClient.h`, `clsTransfer.h` |
| `Transfer` does not check for the same account. Only the transfer screen does. | `clsBankClient.h`, `clsTransfer.h` |
| Balances are `float`. It has about seven digits of precision, so decimals and large amounts can be wrong. | `clsBankClient.h`, `clsInputValidate.h` |
| A transfer is two separate file rewrites. If the program stops between them, the money is lost. | `clsBankClient.h` |
| If a file cannot be saved, the screen still says the operation worked. | `clsBankClient.h`, `clsDepositScreen.h`, `clsWithDrawScreen.h` |

## Data files and program structure

| Problem | Where |
|---|---|
| Every save empties the file and writes all records again. A crash in the middle can lose data. | `clsBankClient.h`, `clsUser.h` |
| `Split` skips empty fields. A record with an empty field shifts the columns and can crash the program. A value that contains `#//#` breaks its record. | `clsString.h` |
| The global user object in `Global.h` reads `Users.txt` before `main` starts. | `Global.h` |
| Menus call themselves again after every action, so the call stack grows. | `clsMainScreen.h`, `clsTransactionsScreen.h`, `clsManageUsersMenue.h` |
| It uses `system("cls")` and `__declspec(property)`, so it only works on Windows with the Microsoft compiler. | most of the headers |

## Data files included with the original project

`Clients.txt`, `Users.txt`, `LoginRegister.txt` and `TransferLog.txt` are fictional test data and are included unchanged from the original project archive. They are not real customer or account records.

Anyone who can read the repository can read the test PINs in `Clients.txt`. Because of the character shift, anyone can also recover the test passwords in `Users.txt` and `LoginRegister.txt`. These values are included only for demonstration. Never use real PINs or passwords in these files.
