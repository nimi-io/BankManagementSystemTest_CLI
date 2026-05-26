#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount {

private:
    string accountNumber;
    string accountName;
    double balance;

public:

    // Constructor
    BankAccount(string accountNumber, string accountName, double balance) {
        this->accountNumber = accountNumber;
        this->accountName = accountName;
        this->balance = balance;
    }

    // Default constructor
    BankAccount() {
        accountNumber = "";
        accountName = "";
        balance = 0.0;
    }

    void deposit(double amount) {

        if (amount > 0) {

            balance += amount;

            cout << accountNumber << " deposited " << amount << endl;
            cout << "New Balance is " << balance << endl;

        } else {
            cout << "Deposit Failed! Amount must be positive." << endl;
        }
    }

    void withdraw(double amount) {

        if (amount > 0 && amount <= balance) {

            balance -= amount;

            cout << accountNumber << " withdrew " << amount << endl;
            cout << "New Balance is " << balance << endl;

        } else {

            cout << "Withdraw Failed! Invalid amount or insufficient funds." << endl;
        }
    }

    void checkBalance() {
        cout << "Account Balance: " << balance << endl;
    }

    void saveToFile() const {

        ofstream file(accountNumber + ".txt");

        if (file.is_open()) {

            file << accountNumber << endl;
            file << accountName << endl;
            file << balance << endl;

            file.close();

            cout << accountNumber << " saved successfully." << endl;

        } else {
            cout << "Unable to save account." << endl;
        }
    }

    static BankAccount loadFromFile(string accountNumber) {

        ifstream file(accountNumber + ".txt");

        string accNum;
        string accName;
        double bal;

        if (file.is_open()) {

            getline(file, accNum);
            getline(file, accName);
            file >> bal;

            file.close();

            return BankAccount(accNum, accName, bal);

        } else {

            cout << "Unable to load account." << endl;
            return BankAccount();
        }
    }

    bool isValid() const {
        return !accountNumber.empty();
    }
};

int main() {

    string accNum;
    double initialBalance;

    cout << "Enter account number: ";
    cin >> accNum;

    BankAccount acc = BankAccount::loadFromFile(accNum);

    if (!acc.isValid()) {

        string accName;

        cout << "\nCreating New Bank Account " << accNum << endl;

        cin.ignore();

        cout << "Enter account name: ";
        getline(cin, accName);

        cout << "Enter Initial account balance: ";
        cin >> initialBalance;

        acc = BankAccount(accNum, accName, initialBalance);
    }

    int choice;

    do {

        cout << "\nBank Menu:\n" << endl;

        cout << "1. Deposit Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Save Account" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                double depAmount;

                cout << "Enter amount to deposit: ";
                cin >> depAmount;

                acc.deposit(depAmount);
                break;
            }

            case 2: {
                double withAmount;

                cout << "Enter amount to withdraw: ";
                cin >> withAmount;

                acc.withdraw(withAmount);
                break;
            }

            case 3:
                acc.checkBalance();
                break;

            case 4:
                acc.saveToFile();
                break;

            case 5:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice, Try Again!" << endl;
                break;
        }

    } while (choice != 5);

    return 0;
}