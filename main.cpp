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
    BankAccount(string accountNumber, string accountName, double balance) {
        accountNumber = accountNumber;
        accountName = accountName;
        balance = balance;
    }
    BankAccount() {
        accountNumber = "";
        accountName = "";
        balance = 0.0;
    }
    void deposit(double amount) {
        if (amount > 0 ) {
            balance += amount;
            cout << accountNumber << " deposit " << amount << endl;
            cout << "New Balance is " << balance << endl;
        }else {
            cout << "Deposit Failed ! Deposit value must be positive" << endl;
        }
    };
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << accountNumber << " withdraw " << amount << endl;

            cout << "New Balance is " << balance << endl;
        }
        else {
            cout << "Withdraw Failed ! Withdraw value must be positive or Insufficient Funds" << endl;
        }
    }

    void checkBalance() {
        cout << "Account Balance: "<< balance << endl;
    }

    void saveToFile() const {
        ofstream file(accountNumber + ".txt");
        if (file.is_open()) {
            file << accountNumber << endl;
            file << accountName << endl;
            file << balance << endl;
            file.close();
        }else {
            cout << "Unable to save account" << endl;
        }
    }

    static BankAccount loadFromFile(string accountNumber) {
        ifstream file(accountNumber + ".txt");
        string accName;
        double bal;
        if (file.is_open()) {
            getline(file,accName);
            getline(file,accName);
            file >> bal;
            file.close();

            return  BankAccount(accountNumber, accName, bal);
        } else {
            cout << "Unable to load account" << endl;
            return BankAccount();
        }

    };

    bool isVaild() const {
        return  !accountNumber.empty();
    }
};
int main() {
    string accNum;
    double initialBalance;

    cout << "Enter account number: ";
    cin >> accNum;

    BankAccount acc = BankAccount::loadFromFile(accNum);

    if (!acc.isVaild()) {
        string accName;

        cout << "\n Creating New Bank Account " << accNum << endl;
        cout << "Enter account name: ";
        cin >> accName;

        cin.ignore();
        getline(cin,accName);

        cout << "Enter Initial account balance: ";
        cin >> initialBalance;

        acc = BankAccount(accNum, accName, initialBalance);

    }


    int choice;

    do {
        cout << "\nBank Menu: \n" << endl;
        cout << "1. Deposit Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Save As Account" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";

        cin >> choice;
        switch (choice) {
            case 1:
                double depAmount;
                cout << "Enter amount to deposit: ";
                cin >> depAmount;

                acc.deposit(depAmount);
                break;

            case 2:
                double withAmount;
                cout << "Enter amount to withdraw: ";
                cin >> withAmount;
                acc.withdraw(withAmount);
                break;

            case 3:
                acc.checkBalance();
                break;

            case 4:
                acc.saveToFile();
                break;

            case 5:
                exit(0);
            default:
                cout << "Invalid choice, Try Again!" << endl;
                break;
        }
    } while (choice != 5);
}