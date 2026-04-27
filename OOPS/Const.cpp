#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : const Member Function ───────────────────────────────────────
//-------------------------------------------------------------------------------
class BankAccount {
private:
    string owner;
    double balance;

public:
    BankAccount(string o, double b) : owner(o), balance(b) {}

    double getBalance() const {      // read-only: can be called on const objects
        return balance;
    }

    string getOwner() const {        // read-only
        return owner;
    }

    void deposit(double amount) {    // modifies state: NOT const
        balance += amount;
    }

    void withdraw(double amount) {   // modifies state: NOT const
        balance -= amount;
    }
};

void example1() {
    BankAccount acc("Alice", 1000.0);
    acc.deposit(500.0);
    cout << acc.getOwner() << " balance: " << acc.getBalance() << "\n";  // Alice balance: 1500
}


//-------------------------------------------------------------------------------
// ── Example 2 : const Object — can only call const functions ─────────────────
//-------------------------------------------------------------------------------
void example2() {
    const BankAccount readOnly("Bob", 2000.0);

    cout << readOnly.getBalance() << "\n";   // OK — const function
    // readOnly.deposit(100);               // COMPILE ERROR — non-const function on const object
}


//-------------------------------------------------------------------------------
// ── Example 3 : const Data Member — must use initializer list ────────────────
//-------------------------------------------------------------------------------
class Circle {
private:
    const int    id;          // const member — set once at construction, never changed
    double       radius;

public:
    Circle(int i, double r) : id(i), radius(r) {}

    int    getId()     const { return id; }
    double getRadius() const { return radius; }
    double area()      const { return 3.14159 * radius * radius; }

    void setRadius(double r) { radius = r; }   // id is const but radius isn't
};

void example3() {
    Circle c(1, 5.0);
    cout << "Circle " << c.getId() << " area: " << c.area() << "\n";  // Circle 1 area: 78.5397

    c.setRadius(10.0);
    cout << "After resize: " << c.area() << "\n";                     // 314.159
    // c.id = 2;   // COMPILE ERROR — const member
}



//-------------------------------------------------------------------------------
// ── Example 4 : LLD — CQS with const ────────────────────
//-------------------------------------------------------------------------------

class Account {
    int balance;
public:
    int getBalance() const { return balance; } // Query
    void deposit(int amt) { balance += amt; }  // Command
};


int main() {
    cout << "=== Example 1: const Member Function ===\n";        example1();
    cout << "\n=== Example 2: const Object ===\n";               example2();
    cout << "\n=== Example 3: const Data Member ===\n";          example3();
}
