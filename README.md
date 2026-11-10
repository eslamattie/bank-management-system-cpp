# Bank Management System

A console bank management system written in C++. You can manage clients and system users, deposit, withdraw and transfer money, and look at a log of transfers and logins. Everything is saved in text files.

I made it to practice classes, inheritance and file handling. It is a learning project, not a real banking system. It still has problems that I list below, so please do not use it with real data.

## Technologies

- C++20
- Visual Studio (the project uses the v145 toolset)
- Text files for storage
- Windows console

## Features

**Clients**
- List, add, update, delete and find clients
- Every account number is unique

**Transactions**
- Deposit and withdraw
- Total balances of all clients
- Transfer between two clients
- Transfer log

**Users and login**
- Log in with a username and password (three tries)
- List, add, update, delete and find users
- Every user has permissions, so each user only opens the parts of the program they are allowed to use
- Login register with the date and user of each login

## How it works

**Classes.** A client is an object of `clsBankClient` and a user is an object of `clsUser`. Both inherit from `clsPerson`. These classes find records in the files, save changes and delete records. The screens only ask for input, print the result and call these methods.

**Permissions.** A user's permissions are saved as one number. Each permission is one bit: list clients is 1, add is 2, delete is 4, update is 8, find is 16, transactions is 32, manage users is 64 and login register is 128. The value -1 means everything. Every screen checks the permission of the logged-in user before it opens.

**Transactions.** `Deposit`, `Withdraw` and `Transfer` are methods of `clsBankClient`. The screen reads the account number and the amount, asks for a confirmation and then calls the method. A transfer takes the money from one client, adds it to the other and writes a line to the transfer log.

## OOP in this project

- Classes and objects
- Encapsulation: private data members with getters, setters and `__declspec(property)` (this only works with the Microsoft compiler)
- Inheritance: `clsBankClient` and `clsUser` inherit from `clsPerson`. The 20 screen classes inherit from `clsScreen` with `protected` inheritance.
- Static methods in the screens and the helper classes
- Enums for menu options, permissions and save results

I did not use polymorphism, abstract classes, templates or interfaces.

## Data storage and file handling

There is no database. The data is in four text files in the project folder:

| File | Content |
|---|---|
| `Clients.txt` | one client per line |
| `Users.txt` | one user per line |
| `LoginRegister.txt` | one login per line |
| `TransferLog.txt` | one transfer per line |

These four files are fictional test data and are included unchanged from the original project archive. They contain account records, PINs and login data. PINs are stored in plain text and passwords use a reversible character shift, so do not replace these test values with real credentials.

The fields in a line are separated by `#//#`. To update or delete a record, the program loads the whole file into a `vector`, changes it and writes the file again. New records and log lines are added at the end of the file. The program reads the files from its working directory. The project does not set one, so Visual Studio uses the project folder, which is where these files are.

## Open and run it in Visual Studio

1. Download or clone the repository.
2. Open `BankSystembyOOP.slnx` in Visual Studio.
3. Build and run with F5. Keep the four text files next to `BankSystembyOOP.vcxproj`.
4. Log in with a user from `Users.txt`. Passwords are stored with a simple character shift, see [docs/SECURITY_LIMITATIONS.md](docs/SECURITY_LIMITATIONS.md).

The program changes these files while you use it. To get the original test data back, run `git restore Clients.txt Users.txt LoginRegister.txt TransferLog.txt`.

## Requirements

- Windows
- Visual Studio with the "Desktop development with C++" workload and the v145 platform toolset. With an older Visual Studio, retarget the project in its properties.
- Other systems are not supported. The code uses `system("cls")` and `__declspec(property)`.

## Known limitations

I decided to keep this version unchanged, so these problems are still in the code:

- Negative amounts are accepted. A negative withdrawal adds money to the balance.
- A transfer does not check that the withdrawal worked before it makes the deposit.
- Passwords are saved with a simple character shift, which is not real encryption. PINs are saved as plain text. Both are shown on some screens.
- Balances are `float`, so decimals and large amounts can be wrong.
- Every save rewrites the whole file. A record with an empty field can break loading.
- It only works on Windows with Visual Studio.

The full list is in [docs/SECURITY_LIMITATIONS.md](docs/SECURITY_LIMITATIONS.md).

## Documentation

- [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md): classes, files, program flow and data format
- [docs/SECURITY_LIMITATIONS.md](docs/SECURITY_LIMITATIONS.md): all known problems with the file names where they are
- [NOTICE.md](NOTICE.md): author and license status

## License

There is no license file, so all rights stay with the author. See [NOTICE.md](NOTICE.md).

## Author

Eslam Attia Ahmed Ibrahim
