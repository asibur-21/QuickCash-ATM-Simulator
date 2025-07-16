#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_LOGIN_ATTEMPTS = 3;
const int PIN_LENGTH = 4;

class ATM
{
private:
    string name;
    int pin;
    int balance;
    vector<string> transactions;

    void addTransaction(const string &record)
    {
        if (transactions.size() >= 5)
            transactions.erase(transactions.begin());
        transactions.push_back(record);
    }

public:
    ATM(const string &userName, int userPin, int initBalance)
        : name(userName), pin(userPin), balance(initBalance) {}

    bool validatePIN(int enteredPin)
    {
        return enteredPin == pin;
    }

    void showMenu()
    {
        int choice;
        do
        {
            cout << "\n======= ATM Menu =======\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. View Mini Statement\n";
            cout << "5. Exit\n";
            cout << "Select an option (1-5): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                checkBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                miniStatement();
                break;
            case 5:
                cout << "\nThank you, " << name << ". Have a great day!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        } while (choice != 5);
    }

    void checkBalance()
    {
        cout << fixed << setprecision(2);
        cout << "Your current balance is: $" << balance << "\n";
    }

    void deposit()
    {
        int amount;
        cout << "Enter amount to deposit: $";
        cin >> amount;

        if (amount > 0)
        {
            balance += amount;
            cout << "Successfully deposited $" << amount << ".\n";
            addTransaction("Deposited $" + to_string(amount));
        }
        else
        {
            cout << "Invalid amount. Please enter a positive number.\n";
        }
    }

    void withdraw()
    {
        int amount;
        cout << "Enter amount to withdraw: $";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount.\n";
        }
        else if (amount > balance)
        {
            cout << "Insufficient balance. Withdrawal failed.\n";
        }
        else
        {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << ".\n";
            addTransaction("Withdrew $" + to_string(amount));
        }
    }

    void miniStatement()
    {
        cout << "\n==== Mini Statement (Last 5 Transactions) ====\n";
        if (transactions.empty())
        {
            cout << "No transactions to display.\n";
        }
        else
        {
            for (const auto &t : transactions)
                cout << "- " << t << "\n";
        }
    }
};

int main()
{
    string name;
    int pin, initialBalance;

    cout << "=====================================\n";
    cout << "     Welcome to QuickCash ATM\n";
    cout << "=====================================\n";
    cout << "Enter your Full name: ";
    getline(cin, name);

    cout << "Set a 4-digit PIN: ";
    cin >> pin;
    while (pin < 1000 || pin > 9999)
    {
        cout << "PIN must be 4 digits. Try again: ";
        cin >> pin;
    }

    cout << "Enter initial balance: $";
    cin >> initialBalance;

    ATM user(name, pin, initialBalance);

    int attempts = 0, enteredPin;
    cout << "\n==== ATM Login ====\n";
    while (attempts < 3)
    {
        cout << "Enter your PIN to login: ";
        cin >> enteredPin;

        if (user.validatePIN(enteredPin))
        {
            cout << "Login successful. Welcome, " << name << "!\n";
            user.showMenu();
            break;
        }
        else
        {
            attempts++;
            cout << "Incorrect PIN. Attempts left: " << 3 - attempts << "\n";
        }

        if (attempts == 3)
        {
            cout << "Account locked. Too many failed attempts.\n";
        }
    }

    return 0;
}
