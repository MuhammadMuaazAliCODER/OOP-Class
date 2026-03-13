#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    BankAccount() {
        accountNumber = 0;
        balance = 0.0;
    }

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount No: " << accountNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }
};

// ================= FILE FUNCTIONS =================

void createAccount() {
    BankAccount acc;
    ofstream out("accounts.dat", ios::binary | ios::app);

    acc.createAccount();
    out.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

    out.close();
    cout << "\n✔ Account Created Successfully\n";
}

void displayAllAccounts() {
    BankAccount acc;
    ifstream in("accounts.dat", ios::binary);

    if (!in) {
        cout << "\nNo accounts found.\n";
        return;
    }

    cout << "\n===== ALL ACCOUNTS =====\n";
    while (in.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        acc.showAccount();
        cout << "------------------------\n";
    }
    in.close();
}

void searchAccount(int accNo) {
    BankAccount acc;
    ifstream in("accounts.dat", ios::binary);
    bool found = false;

    while (in.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            acc.showAccount();
            found = true;
            break;
        }
    }
    in.close();

    if (!found)
        cout << "\n❌ Account Not Found\n";
}

void transaction(int accNo, bool isDeposit) {
    BankAccount acc;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(BankAccount))) {
        if (acc.getAccountNumber() == accNo) {
            double amount;
            cout << "Enter Amount: ";
            cin >> amount;

            if (isDeposit) {
                acc.deposit(amount);
                cout << "✔ Deposit Successful\n";
            } else {
                if (!acc.withdraw(amount)) {
                    cout << "❌ Insufficient Balance\n";
                    break;
                }
                cout << "✔ Withdrawal Successful\n";
            }

            int pos = file.tellg();
            file.seekp(pos - sizeof(BankAccount));
            file.write(reinterpret_cast<char*>(&acc), sizeof(BankAccount));

            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "\n❌ Account Not Found\n";
}

// ================= MAIN =================

int main() {
    int choice, accNo;

    do {
        cout << "\n\n===== BANK MENU =====";
        cout << "\n1. Create Account";
        cout << "\n2. View All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit Money";
        cout << "\n5. Withdraw Money";
        cout << "\n6. Exit";
        cout << "\nChoose Option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            displayAllAccounts();
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            searchAccount(accNo);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            transaction(accNo, true);
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> accNo;
            transaction(accNo, false);
            break;
        case 6:
            cout << "\n👋 Thank you for using our bank!\n";
            break;
        default:
            cout << "\n❌ Invalid Option\n";
        }

    } while (choice != 6);

    return 0;
}
