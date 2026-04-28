#include <iostream>
#include <string>

// ============================================================================
// SECTION 1 : Ambiguity in Multiple Inheritance
// ============================================================================
// When two base classes define a method with the same name, the compiler
// cannot pick one — accessing it through the derived class is an error.

class Flyable {
public:
    void describe() const { std::cout << "I can fly\n"; }
};

class Swimmable {
public:
    void describe() const { std::cout << "I can swim\n"; }
};

class Duck : public Flyable, public Swimmable {
public:
    // Without this override, duck.describe() is a compile error (ambiguous).
    // Resolution: override in Duck and delegate via explicit scope.
    void describe() const {
        Flyable::describe();
        Swimmable::describe();
        std::cout << "I am a Duck — I do both!\n";
    }
};

// ============================================================================
// SECTION 2a : Diamond Problem — WITHOUT virtual inheritance (the problem)
// ============================================================================
//
//            Animal_NV
//           /         \
//        Dog_NV      Cat_NV
//           \         /
//           Hybrid_NV
//
// Hybrid_NV ends up with TWO separate Animal_NV subobjects.
// Any direct access to Animal_NV members through Hybrid_NV is ambiguous.

class Animal_NV {
public:
    std::string name;
    Animal_NV(const std::string& n) : name(n) {
        std::cout << "Animal_NV ctor: " << n << '\n';
    }
    void speak() const { std::cout << name << " says something\n"; }
};

class Dog_NV : public Animal_NV {
public:
    Dog_NV(const std::string& n) : Animal_NV(n) {
        std::cout << "Dog_NV ctor\n";
    }
};

class Cat_NV : public Animal_NV {
public:
    Cat_NV(const std::string& n) : Animal_NV(n) {
        std::cout << "Cat_NV ctor\n";
    }
};

class Hybrid_NV : public Dog_NV, public Cat_NV {
public:
    Hybrid_NV(const std::string& n) : Dog_NV(n), Cat_NV(n) {}

    void demonstrate() const {
        // speak();           // COMPILE ERROR: ambiguous — Dog_NV::speak or Cat_NV::speak?
        Dog_NV::speak();     // forced explicit qualification — two different copies
        Cat_NV::speak();
    }
};

// ============================================================================
// SECTION 2b : Diamond Problem — WITH virtual inheritance (the fix)
// ============================================================================
//
//            Animal
//           /       \
//          Dog      Cat          <- virtual public Animal
//           \       /
//            Hybrid
//
// virtual inheritance tells the compiler: merge duplicate Animal subobjects
// into ONE shared copy. Hybrid drives that single Animal constructor directly.

class Animal {
public:
    std::string name;
    Animal(const std::string& n) : name(n) {
        std::cout << "Animal ctor: " << n << '\n';
    }
    void speak() const { std::cout << name << " says something\n"; }
};

class Dog : virtual public Animal {
public:
    Dog(const std::string& n) : Animal(n) {
        std::cout << "Dog ctor\n";
    }
    void bark() const { std::cout << name << " barks\n"; }
};

class Cat : virtual public Animal {
public:
    Cat(const std::string& n) : Animal(n) {
        std::cout << "Cat ctor\n";
    }
    void meow() const { std::cout << name << " meows\n"; }
};

class Hybrid : public Dog, public Cat {
public:
    // Most-derived class must initialize the virtual base directly.
    // Dog's and Cat's Animal constructors are skipped by the runtime.
    Hybrid(const std::string& n) : Animal(n), Dog(n), Cat(n) {
        std::cout << "Hybrid ctor\n";
    }

    void demonstrate() const {
        speak();   // unambiguous — one Animal
        bark();
        meow();
    }
};

// ============================================================================
// SECTION 3 : Virtual Functions — need, mechanism, and runtime dispatch
// ============================================================================
//
// WITHOUT virtual: the compiler uses the static type (pointer type) to bind
//   the method call at compile time — always calls the base version.
//
// WITH virtual: a vtable (array of function pointers) is built per class.
//   Every object stores a vptr to its class's vtable. At runtime the CPU
//   follows vptr -> vtable -> correct override. This is dynamic dispatch.

class Shape {
public:
    virtual ~Shape() = default;  // virtual destructor prevents resource leaks

    virtual double area() const { return 0.0; }

    void printArea() const {
        // area() here is dispatched dynamically — calls the derived override,
        // not Shape::area(), even though printArea() lives in Shape.
        std::cout << "Area = " << area() << '\n';
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
};

// Demonstrates static dispatch (no virtual) vs dynamic dispatch (virtual).
class BaseNoVirtual {
public:
    void greet() const { std::cout << "BaseNoVirtual::greet\n"; }
};

class DerivedNoVirtual : public BaseNoVirtual {
public:
    void greet() const { std::cout << "DerivedNoVirtual::greet\n"; }
};

class BaseVirtual {
public:
    virtual ~BaseVirtual() = default;
    virtual void greet() const { std::cout << "BaseVirtual::greet\n"; }
};

class DerivedVirtual : public BaseVirtual {
public:
    void greet() const override { std::cout << "DerivedVirtual::greet\n"; }
};

// ============================================================================
// main
// ============================================================================

int main() {
    // ── Section 1: multiple-inheritance name ambiguity ──
    std::cout << "=== Multiple Inheritance Ambiguity ===\n";
    Duck duck;
    duck.describe();
    // duck.Flyable::describe();  // explicit scope also works if needed

    // ── Section 2a: diamond without virtual inheritance ──
    std::cout << "\n=== Diamond Problem — WITHOUT virtual inheritance ===\n";
    Hybrid_NV hnv("Beastie");
    hnv.demonstrate();   // two Animal_NV copies, explicit scoping mandatory

    // ── Section 2b: diamond with virtual inheritance ──
    std::cout << "\n=== Diamond Problem — WITH virtual inheritance ===\n";
    Hybrid h("Max");
    h.demonstrate();     // one Animal, no ambiguity

    // ── Section 3a: static dispatch vs dynamic dispatch ──
    std::cout << "\n=== Static Dispatch (no virtual) ===\n";
    BaseNoVirtual* p1 = new DerivedNoVirtual();
    p1->greet();   // prints BaseNoVirtual::greet — compile-time binding ignores real type
    delete p1;

    std::cout << "\n=== Dynamic Dispatch (virtual) ===\n";
    BaseVirtual* p2 = new DerivedVirtual();
    p2->greet();   // prints DerivedVirtual::greet — runtime binding uses real type
    delete p2;

    // ── Section 3b: polymorphic shape array ──
    std::cout << "\n=== Virtual Functions — polymorphic shapes ===\n";
    Shape* shapes[] = { new Circle(5.0), new Rectangle(4.0, 6.0) };
    for (Shape* s : shapes) {
        s->printArea();  // calls correct derived area() via vtable
        delete s;        // virtual destructor ensures correct cleanup
    }

    return 0;
}
