#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : Static Data Members ─────────────────────────────────────────
//-------------------------------------------------------------------------------
class Student {
private:
    string name;
    static int count;   // shared across all objects

public:
    Student(string n) : name(n) { count++; }
    ~Student() { count--; }

    static int getCount() { return count; }   // static fn to access static member

    void display() const {
        cout << "Student: " << name << "\n";
    }
};

int Student::count = 0;   // definition outside class

void example1() {
    cout << "Count: " << Student::count << "\n";   // 0

    Student s1("Alice");
    Student s2("Bob");
    cout << "Count: " << Student::getCount() << "\n";   // 2

    {
        Student s3("Charlie");
        cout << "Count: " << Student::getCount() << "\n";   // 3
    }   // s3 destroyed here

    cout << "Count: " << Student::getCount() << "\n";   // 2
}

int main() {
    cout << "=== Example 1: Static Data Members ===\n"; example1();
}
