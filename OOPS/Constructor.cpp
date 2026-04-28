#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : Default Constructor ─────────────────────────────────────────
//-------------------------------------------------------------------------------
class Point {
public:
    int x, y;

    Point() : x(0), y(0) {}   // default constructor — called with no args

    void print() { cout << "(" << x << ", " << y << ")\n"; }
};

void example1() {
    Point p;      // default constructor called
    p.print();    // (0, 0)
}


//-------------------------------------------------------------------------------
// ── Example 2 : Parameterized Constructor + Overloading ─────────────────────
//-------------------------------------------------------------------------------
class Car {
private:
    string brand;
    int    speed;

public:
    Car() : brand("Unknown"), speed(0) {}              // default

    Car(string b, int s) : brand(b), speed(s) {}       // parameterized

    Car(string b) : brand(b), speed(60) {}             // single-arg overload

    void print() { cout << brand << " @ " << speed << " km/h\n"; }
};

void example2() {
    Car c1;                        // default
    Car c2("Toyota", 120);         // parameterized
    Car c3("Honda");               // single-arg overload

    c1.print();   // Unknown @ 0 km/h
    c2.print();   // Toyota @ 120 km/h
    c3.print();   // Honda @ 60 km/h
}


//-------------------------------------------------------------------------------
// ── Example 3 : Copy Constructor — Shallow vs Deep Copy ─────────────────────
//-------------------------------------------------------------------------------

// --- Shallow copy (dangerous with raw pointers) ---
class Shallow {
public:
    int* data;

    Shallow(int val) {
        data = new int(val);
    }

    // both pointers point to the same memory after copy
    // Shallow(const Shallow& other) : data(other.data) {}

    ~Shallow() { delete data; }   // double-free when both objects die
};

// --- Deep copy (safe) ---
class Deep {
public:
    int* data;

    Deep(int val) {
        data = new int(val);
    }

    Deep(const Deep& other) {
        data = new int(*other.data);   // allocate fresh memory, copy value
    }

    ~Deep() { delete data; }
};

void example3() {
    // Shallow copy — both share the same pointer
    Shallow s1(10);
    Shallow s2 = s1;            // s2.data == s1.data (same address)

    *s2.data = 99;
    cout << "s1.data = " << *s1.data << "\n";   // 99  (mutated through s2!)
    cout << "s2.data = " << *s2.data << "\n";   // 99
    cout << "same pointer? " << (s1.data == s2.data ? "yes" : "no") << "\n";
    // ⚠ s1's destructor deletes the pointer, then s2's destructor deletes it again — UB

    cout << "\n";

    // Deep copy — each object owns its own memory
    Deep a(42);
    Deep b = a;             // deep copy — b gets its own memory

    *b.data = 99;
    cout << "a.data = " << *a.data << "\n";   // 42  (unchanged)
    cout << "b.data = " << *b.data << "\n";   // 99
}


//-------------------------------------------------------------------------------
// ── Example 4 : Member Initializer List ─────────────────────────────────────
//-------------------------------------------------------------------------------
class Config {
private:
    const int  maxRetries;   // const — MUST use initializer list
    int&       ref;          // reference — MUST use initializer list
    int        timeout;

public:
    Config(int retries, int& r, int t)
        : maxRetries(retries), ref(r), timeout(t) {}

    void print() const {
        cout << "maxRetries=" << maxRetries
             << "  ref="      << ref
             << "  timeout="  << timeout << "\n";
    }
};

void example4() {
    int x = 5;
    Config cfg(3, x, 30);
    cfg.print();   // maxRetries=3  ref=5  timeout=30
}




//-------------------------------------------------------------------------------
// ── Example 7 : Constructor in Inheritance ───────────────────────────────────
//-------------------------------------------------------------------------------
class Animal {
protected:
    string name;

public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << "\n";
    }
};

class Dog : public Animal {
private:
    string breed;

public:
    // must forward args to base via initializer list
    Dog(string n, string b) : Animal(n), breed(b) {
        cout << "Dog constructor: " << breed << "\n";
    }
};

class Labrador : public Dog {
public:
    using Dog::Dog;   // inherit Dog's constructors (C++11)
};

void example7() {
    Dog d("Rex", "German Shepherd");
    // Animal constructor: Rex
    // Dog constructor: German Shepherd

    cout << "\n";
    Labrador lab("Buddy", "Labrador");
    // Animal constructor: Buddy
    // Dog constructor: Labrador
}


int main() {
    cout << "=== Example 1: Default Constructor ===\n";       example1();
    cout << "\n=== Example 2: Parameterized + Overloading ===\n"; example2();
    cout << "\n=== Example 3: Copy Constructor (Shallow vs Deep) ===\n"; example3();
    cout << "\n=== Example 4: Member Initializer List ===\n"; example4();
    cout << "\n=== Example 7: Constructor in Inheritance ===\n"; example7();
}
