#include <iostream>
#include <string>
using namespace std;

// ── Example 1 : Class and Object ────────────────────────────────────────────
class Car {
private:
    string brand;
    int speed;

public:
    // setter
    void setBrand(string b) { brand = b; }
    void setSpeed(int s)    { speed = s; }

    // getter
    string getBrand() { return brand; }
    int    getSpeed() { return speed; }

    void display() {
        cout << brand << " going at " << speed << " km/h\n";
    }
};

void example1() {
    Car c;           // c is an object (instance) of class Car
    c.setBrand("Toyota");
    c.setSpeed(120);
    c.display();     // Toyota going at 120 km/h
}



//-------------------------------------------------------------------------------
// ── Example 2 : this pointer ─────────────────────────────────────────────────
//-------------------------------------------------------------------------------
class Counter {
private:
    int count;

public:
    Counter(int count) {
        this->count = count;   // disambiguate member vs parameter
    }

    // return *this to allow method chaining
    Counter& increment() {
        count++;
        return *this;
    }

    void print() { cout << "Count: " << count << "\n"; }
};

void example2() {
    Counter c(0);
    c.increment().increment().increment();  // chaining via *this
    c.print();   // Count: 3
}


//-------------------------------------------------------------------------------
// ── Example 3 : friend ───────────────────────────────────────────────────────
// ...............................................................................
// Friend Function Example 
class Box {
private:
    double volume;

public:
    Box(double v) : volume(v) {}

    // grant free function access to private members
    friend void printVolume(const Box& b);
};

void printVolume(const Box& b) {
    cout << "Volume: " << b.volume << "\n";   // direct private access
}

void example3() {
    Box b(42.5);
    printVolume(b);   // Volume: 42.5
}

// Friend Class Example 
class A {
private:
    int x = 10;

    friend class B;
};

class B {
public:
    void show(A a) {
        cout << a.x; // allowed
    }
};



//-------------------------------------------------------------------------------
// ── Example 4 : mutable ──────────────────────────────────────────────────────
// -------------------------------------------------------------------------------
class Logger {
private:
    string data;
    mutable int accessCount;   // modified in const method — OK because of mutable

public:
    Logger(string d) : data(d), accessCount(0) {}

    string getData() const {
        accessCount++;         // allowed even though method is const
        return data;
    }

    int getAccessCount() const { return accessCount; }
};

void example4() {
    Logger log("hello");
    cout << log.getData() << "\n";   // hello
    cout << log.getData() << "\n";   // hello
    cout << "Accessed " << log.getAccessCount() << " times\n";   // 2
}

//-------------------------------------------------------------------------------
// ── Example 5 : inline functions ─────────────────────────────────────────────
//-------------------------------------------------------------------------------
class MathHelper {
public:
    // defined inside class body => implicitly inline
    int square(int x) { return x * x; }

    // explicit inline outside class
    inline int cube(int x) { return x * x * x; }
};

void example5() {
    MathHelper m;
    cout << "Square of 4: " << m.square(4) << "\n";   // 16
    cout << "Cube   of 3: " << m.cube(3)   << "\n";   // 27
}


int main() {
    cout << "=== Example 1: Class and Object ===\n"; example1();
    cout << "\n=== Example 2: this pointer ===\n";   example2();
    cout << "\n=== Example 3: friend ===\n";          example3();
    cout << "\n=== Example 4: mutable ===\n";         example4();
    cout << "\n=== Example 5: inline ===\n";          example5();
}
