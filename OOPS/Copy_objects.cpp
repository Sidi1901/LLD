#include <iostream>
#include <string>
using namespace std;

//-------------------------------------------------------------------------
// ── Example 1 : Copy Constructor ────────────────────────────────────────
//-------------------------------------------------------------------------
class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    Point(const Point& other) : x(other.x), y(other.y) {
        cout << "Copy constructor called\n";
    }

    void print(const string& label) const {
        cout << label << " -> (" << x << ", " << y << ")\n";
    }
};

void example1() {
    cout << "=== Example 1 : Copy Constructor ===\n";

    Point a(1, 2);
    Point b = a;      // copy constructor
    Point c(a);       // copy constructor (explicit form)

    a.x = 99;
    cout << "After a.x = 99:\n";
    a.print("a"); b.print("b"); c.print("c");
}


//-------------------------------------------------------------------------
// ── Example 2 : Copy Assignment Operator ────────────────────────────────
//-------------------------------------------------------------------------

class Rectangle {
public:
    int width, height;

    Rectangle(int w, int h) : width(w), height(h) {}

    Rectangle& operator=(const Rectangle& other) {
        cout << "Copy assignment called\n";
        width  = other.width;
        height = other.height;
        return *this;
    }

    void print(const string& label) const {
        cout << label << " -> " << width << " x " << height << "\n";
    }
};

void example2() {
    cout << "\n=== Example 2 : Copy Assignment Operator ===\n";

    Rectangle r1(4, 5);
    Rectangle r2(1, 1);

    r2 = r1;

    r1.width = 99;
    cout << "After r1.width = 99:\n";
    r1.print("r1"); r2.print("r2");
}

//-------------------------------------------------------------------------
// ── Example 3 : Shallow Copy vs Deep Copy ────────────────────────────────────
// Both classes wrap a single heap int.
// ShallowBox lets the compiler copy the pointer (both objects share it).
// DeepBox allocates a new int so each object is independent.
//-------------------------------------------------------------------------
class ShallowBox {
public:
    int* data;
    ShallowBox(int v) : data(new int(v)) {}
    // compiler copy: copies the pointer, not the int it points to
    // Compiler-generated copy constructor and assignment operator do a shallow copy
};

class DeepBox {
public:
    int* data;
    DeepBox(int v)              : data(new int(v)) {}
    DeepBox(const DeepBox& o)   : data(new int(*o.data)) {}  // new int for each copy
    ~DeepBox()                  { delete data; }

    // DeepBox(const DeepBox& o) is our own copy constructor that performs a deep copy by allocating a new int and copying the value from the original object. The destructor ensures that the allocated memory is properly released when a DeepBox object goes out of scope.
};

void example3() {
    cout << "\n=== Example 3 : Shallow vs Deep Copy ===\n";

    cout << "-- Shallow --\n";
    ShallowBox a(10);
    ShallowBox b = a;                     // compiler copies the pointer
    cout << "a.data=" << a.data << "  b.data=" << b.data << "  (same address)\n";
    *a.data = 99;
    cout << "After *a.data=99 : a=" << *a.data << "  b=" << *b.data << "\n";
    delete a.data;                        // only delete once – they share the same block

    cout << "\n-- Deep --\n";
    DeepBox x(10);
    DeepBox y = x;                        // deep copy constructor allocates new int
    cout << "x.data=" << x.data << "  y.data=" << y.data << "  (different addresses)\n";
    *x.data = 99;
    cout << "After *x.data=99 : x=" << *x.data << "  y=" << *y.data << "\n";
}

int main() {
    example1();
    example2();
    example3();
    return 0;
}
