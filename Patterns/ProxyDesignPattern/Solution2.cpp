#include <iostream>
#include <string>
using namespace std;

// Protection Proxy — control access to a real object based on caller permissions.
// Example: a bank account where only the account owner can withdraw funds.

class BankAccount
{
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual ~BankAccount() = default;
};

class RealBankAccount : public BankAccount
{
    double balance;

public:
    RealBankAccount(double initialBalance) : balance(initialBalance) {}

    void deposit(double amount) override
    {
        balance += amount;
        cout << "Deposited $" << amount << ". New balance: $" << balance << "\n";
    }

    void withdraw(double amount) override
    {
        if (amount > balance)
        {
            cout << "Insufficient funds.\n";
            return;
        }
        balance -= amount;
        cout << "Withdrew $" << amount << ". New balance: $" << balance << "\n";
    }

    double getBalance() const override
    {
        return balance;
    }
};

class BankAccountProxy : public BankAccount
{
    RealBankAccount *account;
    string ownerName;
    string callerName;

    bool isAuthorized() const
    {
        return callerName == ownerName; // only owner may perform sensitive operations
    }

public:
    BankAccountProxy(double initialBalance, const string &owner, const string &caller)
        : account(new RealBankAccount(initialBalance)), ownerName(owner), callerName(caller) {}

    void deposit(double amount) override
    {
        account->deposit(amount); // anyone can deposit
    }

    void withdraw(double amount) override
    {
        if (!isAuthorized())
        {
            cout << "Access denied: " << callerName << " is not authorized to withdraw.\n";
            return;
        }
        account->withdraw(amount);
    }

    double getBalance() const override
    {
        return account->getBalance();
    }

    ~BankAccountProxy()
    {
        delete account;
    }
};

int main()
{
    cout << "--- Owner accessing account ---\n";
    BankAccount *ownerAccess = new BankAccountProxy(1000.0, "Alice", "Alice");
    ownerAccess->deposit(200.0);  // allowed
    ownerAccess->withdraw(300.0); // allowed — caller is owner
    cout << "Balance: $" << ownerAccess->getBalance() << "\n";

    cout << "\n--- Stranger accessing account ---\n";
    BankAccount *strangerAccess = new BankAccountProxy(1000.0, "Alice", "Bob");
    strangerAccess->deposit(50.0);  // allowed — deposits are open
    strangerAccess->withdraw(500.0); // denied — Bob is not Alice

    delete ownerAccess;
    delete strangerAccess;
    return 0;
}
