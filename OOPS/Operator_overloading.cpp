#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : + and == operators (member functions) ────────────────────────
//-------------------------------------------------------------------------------

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point& other) {
        return Point(x + other.x, y + other.y);
    }

    bool operator==(const Point& other) {
        return x == other.x && y == other.y;
    }
};


//-------------------------------------------------------------------------------
// ── Example 2 : < and += operators  ──────────────────────────────────────────
//-------------------------------------------------------------------------------

class Money {
public:
    int cents;
    Money(int cents) : cents(cents) {}

    bool operator<(const Money& other) { return cents < other.cents; }

    Money& operator+=(const Money& other) {
        cents += other.cents;
        return *this;
    }

    Money operator+(const Money& other) {
        return Money(cents + other.cents);
    }
};

//-------------------------------------------------------------------------------
// ── main ──────────────────────────────────────────────────────────────────────
//-------------------------------------------------------------------------------

int main() {
    cout << "=== Example 1: + and == on Point ===\n";
    Point a(1, 2), b(3, 4);
    Point c = a + b;
    cout << "a + b = (" << c.x << ", " << c.y << ")\n";   // (4, 6)

    Point d(1, 2);
    cout << "a == d: " << (a == d ? "true" : "false") << "\n"; // true
    cout << "a == b: " << (a == b ? "true" : "false") << "\n"; // false

    cout << "\n=== Example 2: <, +, += on Money ===\n";
    Money price(500), tax(50);
    Money total = price + tax;
    cout << "price + tax = " << total.cents << " cents\n";  // 550

    price += tax;
    cout << "price after += tax: " << price.cents << " cents\n"; // 550

    cout << "price < total: " << (price < total ? "true" : "false") << "\n"; // false

    return 0;
}
