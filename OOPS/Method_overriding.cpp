#include <iostream>

// ============================================================================
// EXAMPLE 1 : Without virtual — Method Hiding (Static / Compile-time Dispatch)
// ============================================================================
// The base class A has show(). B defines its own show() — this hides A::show().
// The call is decided by the pointer TYPE, not the actual object type.

class A {
public:
    void show() { std::cout << "A::show()\n"; }
};

class B : public A {
public:
    void show() { std::cout << "B::show()\n"; }  // hides A::show, does NOT override
};

// ============================================================================
// EXAMPLE 2 : With virtual — True Overriding (Dynamic / Runtime Dispatch)
// ============================================================================
// Marking show() virtual in the base class tells the compiler to resolve
// the call at runtime based on the actual object type, not the pointer type.

class Base {
public:
    virtual void show() { std::cout << "Base::show()\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void show() override { std::cout << "Derived::show()\n"; }
};

// ============================================================================
// main
// ============================================================================

int main() {
    std::cout << "--- Example 1: Without virtual (hiding) ---\n";
    A* obj1 = new B();
    obj1->show();   // prints A::show() — pointer type is A*, so A::show is called
    B* obj2 = new B();
    obj2->show();   // prints B::show() — pointer type is B*, so B::show is called
    delete obj1;
    delete obj2;

    std::cout << "\n--- Example 2: With virtual (overriding) ---\n";
    Base* obj3 = new Derived();
    obj3->show();   // prints Derived::show() — resolved at runtime from actual object
    delete obj3;

    return 0;
}
