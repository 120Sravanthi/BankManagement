#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    double balance;

public:
    // Constructor
    Account(int accNum = 0, string accName = "", double accBalance = 0.0) 
        : accountNumber(accNum), name(accName), balance(accBalance) {}

    // Function to create a new account
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore(); // To ignore the newline character left in the buffer
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "Account Created Successfully!\n";
    }

    // Function to display account details
    void displayAccount() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder Name: " << name << "\n";
        cout << "Balance: $" << balance << "\n";
    }

    // Function to deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "$" << amount << " deposited successfully!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    // Function to withdraw money
    void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "$" << amount << " withdrawn successfully!\n";
        } else {
            cout << "Invalid amount or insufficient balance!\n";
        }
    }

    // Function to get account number
    int getAccountNumber() const {
        return accountNumber;
    }
};

void writeAccount(Account &acc) {
    ofstream outFile;
    outFile.open("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
    outFile.close();
}

bool readAccount(int accountNumber, Account &acc) {
    ifstream inFile;
    inFile.open("accounts.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account))) {
        if (acc.getAccountNumber() == accountNumber) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void displayMenu() {
    cout << "\n--- Bank Management System ---\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Balance Inquiry\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Account acc;
    int choice, accNum;
    double amount;

    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                acc.createAccount();
                writeAccount(acc);
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accNum;
                if (readAccount(accNum, acc)) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    acc.deposit(amount);
                    writeAccount(acc); // Overwrite the account with the new balance
                } else {
                    cout << "Account not found!\n";
                }
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNum;
                if (readAccount(accNum, acc)) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc.withdraw(amount);
                    writeAccount(acc); // Overwrite the account with the new balance
                } else {
                    cout << "Account not found!\n";
                }
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNum;
                if (readAccount(accNum, acc)) {
                    acc.displayAccount();
                } else {
                    cout << "Account not found!\n";
                }
                break;

            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
