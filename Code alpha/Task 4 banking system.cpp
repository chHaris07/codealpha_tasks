#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
    string type;
    float amount;
public:
    Transaction(string t, float a) : type(t), amount(a) {}
    void showTransaction() const {
        cout << "  " << type << ": $" << amount << "\n";
    }
};

class Account {
    string accountNumber;
    float balance;
    vector<Transaction> history;

public:
    Account(string accNo, float initialBalance = 0.0f) : accountNumber(accNo), balance(initialBalance) {
        if (initialBalance > 0) {
            history.emplace_back("Initial Deposit", initialBalance);
        }
    }

    void deposit(float amount) {
        if (amount > 0) {
            balance += amount;
            history.emplace_back("Deposit", amount);
            cout << "Deposited: $" << amount << "\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw(float amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            history.emplace_back("Withdrawal", amount);
            cout << "Withdrawn: $" << amount << "\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void transfer(Account& to, float amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            to.balance += amount;
            history.emplace_back("Transfer To " + to.accountNumber, amount);
            to.history.emplace_back("Transfer From " + accountNumber, amount);
            cout << "Transferred: $" << amount << " to " << to.accountNumber << "\n";
        } else {
            cout << "Transfer failed.\n";
        }
    }

    void showInfo() const {
        cout << "Account Number: " << accountNumber << ", Balance: $" << balance << "\n";
    }

    void showTransactions() const {
        cout << "Transaction History for " << accountNumber << ":\n";
        for (const auto& t : history) t.showTransaction();
    }

    string getAccountNumber() const {
        return accountNumber;
    }
};

class Customer {
    string name;
    vector<Account> accounts;

public:
    Customer(string name) : name(name) {}

    void addAccount(string accNo, float balance = 0.0f) {
        accounts.push_back(Account(accNo, balance));
        cout << "Account created successfully.\n";
    }

    Account* findAccount(const string& accNo) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNo) return &acc;
        }
        return nullptr;
    }

    void showAccounts() const {
        cout << "Customer: " << name << "\n";
        for (const auto& acc : accounts)
            acc.showInfo();
    }

    void showAllTransactions() const {
        for (const auto& acc : accounts)
            acc.showTransactions();
    }

    string getName() const {
        return name;
    }
};

class BankSystem {
    vector<Customer> customers;

    Customer* findCustomer(const string& name) {
        for (auto& cust : customers) {
            if (cust.getName() == name) return &cust;
        }
        return nullptr;
    }

    Account* findAccountGlobal(const string& accNo) {
        for (auto& cust : customers) {
            Account* acc = cust.findAccount(accNo);
            if (acc) return acc;
        }
        return nullptr;
    }

public:
    void menu() {
        int choice;
        string name;
        do {
            cout << "\n----- Banking System Menu -----\n";
            cout << "1. Add Customer\n";
            cout << "2. Add Account to Customer\n";
            cout << "3. Deposit\n";
            cout << "4. Withdraw\n";
            cout << "5. Transfer\n";
            cout << "6. View Customer Accounts\n";
            cout << "7. View Transactions\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            string accNo;
            float amount;
            Customer* cust = nullptr;

            switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                customers.push_back(Customer(name));
                cout << "Customer added.\n";
                break;

            case 2:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cust = findCustomer(name);
                if (cust) {
                    cout << "Enter account number: ";
                    cin >> accNo;
                    cout << "Enter initial balance: ";
                    cin >> amount;
                    cust->addAccount(accNo, amount);
                } else {
                    cout << "Customer not found.\n";
                }
                break;

            case 3:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cust = findCustomer(name);
                if (cust) {
                    cout << "Enter account number: ";
                    cin >> accNo;
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    if (Account* acc = cust->findAccount(accNo))
                        acc->deposit(amount);
                    else
                        cout << "Account not found.\n";
                } else {
                    cout << "Customer not found.\n";
                }
                break;

            case 4:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cust = findCustomer(name);
                if (cust) {
                    cout << "Enter account number: ";
                    cin >> accNo;
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    if (Account* acc = cust->findAccount(accNo))
                        acc->withdraw(amount);
                    else
                        cout << "Account not found.\n";
                } else {
                    cout << "Customer not found.\n";
                }
                break;

            case 5: {
                string fromAcc, toAcc;
                cout << "Enter sender account number: ";
                cin >> fromAcc;
                cout << "Enter recipient account number: ";
                cin >> toAcc;
                cout << "Enter amount to transfer: ";
                cin >> amount;
                Account* from = findAccountGlobal(fromAcc);
                Account* to = findAccountGlobal(toAcc);
                if (from && to)
                    from->transfer(*to, amount);
                else
                    cout << "One of the accounts not found.\n";
                break;
            }

            case 6:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cust = findCustomer(name);
                if (cust)
                    cust->showAccounts();
                else
                    cout << "Customer not found.\n";
                break;

            case 7:
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                cust = findCustomer(name);
                if (cust)
                    cust->showAllTransactions();
                else
                    cout << "Customer not found.\n";
                break;

            case 8:
                cout << "Thank you for using the Banking System!\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    BankSystem bank;
    bank.menu();
    return 0;
}
