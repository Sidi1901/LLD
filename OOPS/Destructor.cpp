#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : Basic Destructor — Stack vs Heap ────────────────────────────
//-------------------------------------------------------------------------------
class Resource {
    string name;
public:
    Resource(string n) : name(n) {
        cout << "  [+] Acquired: " << name << "\n";
    }
    ~Resource() {
        cout << "  [-] Released: " << name << "\n";
    }
};

void example1() {
    cout << "-- entering scope --\n";
    Resource r("stack-resource");        // destructor called when scope ends

    Resource* h = new Resource("heap-resource");
    delete h;                            // destructor called here explicitly

    cout << "-- leaving scope --\n";
    // r's destructor called automatically here
}


//-------------------------------------------------------------------------------
// ── Example 2 : Destructor Order in Inheritance ──────────────────────────────
//-------------------------------------------------------------------------------
class Base2 {
public:
    Base2()  { cout << "  Base2 constructor\n"; }
    ~Base2() { cout << "  Base2 destructor\n"; }   // NOTE: not virtual here (demo only)
};

class Derived2 : public Base2 {
public:
    Derived2()  { cout << "  Derived2 constructor\n"; }
    ~Derived2() { cout << "  Derived2 destructor\n"; }
};

void example2() {
    Derived2 d;
    // Construction:  Base2 → Derived2
    // Destruction:   Derived2 → Base2  (reverse)
}


//-------------------------------------------------------------------------------
// ── Example 3 : Virtual Destructor ──────────────────────────────────────────
//-------------------------------------------------------------------------------

// WITHOUT virtual destructor — Derived3 destructor is NEVER called
class BadBase {
public:
    ~BadBase() { cout << "  BadBase destructor\n"; }   // not virtual!
};

class BadDerived : public BadBase {
    int* data;
public:
    BadDerived() : data(new int(99)) {}
    ~BadDerived() {
        delete data;
        cout << "  BadDerived destructor (may never run!)\n";
    }
};

// WITH virtual destructor — correct, full cleanup guaranteed
class GoodBase {
public:
    virtual ~GoodBase() { cout << "  GoodBase destructor\n"; }
};

class GoodDerived : public GoodBase {
    int* data;
public:
    GoodDerived() : data(new int(99)) {}
    ~GoodDerived() override {
        delete data;
        cout << "  GoodDerived destructor\n";
    }
};

void example3() {
    cout << "Bad (non-virtual base destructor):\n";
    BadBase* b1 = new BadDerived();
    delete b1;   // only BadBase::~BadBase() runs — BadDerived::~BadDerived() skipped!

    cout << "\nGood (virtual base destructor):\n";
    GoodBase* b2 = new GoodDerived();
    delete b2;   // GoodDerived::~GoodDerived() runs first, then GoodBase::~GoodBase()
}




int main() {
    cout << "=== Example 1: Basic Destructor (Stack vs Heap) ===\n";
    example1();

    cout << "\n=== Example 2: Destructor Order in Inheritance ===\n";
    example2();

    cout << "\n=== Example 3: Virtual Destructor ===\n";
    example3();

}
