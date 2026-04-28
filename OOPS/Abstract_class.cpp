#include <iostream>

// --------------------------------------------------------------------------------
// Example 1: Abstract class with a pure virtual function plus a normal function.
// --------------------------------------------------------------------------------
class Animal {
public:
    virtual void speak() const = 0; // pure virtual function

    void info() const {
        std::cout << "This is an animal." << std::endl;
    }

    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog says: Woof!" << std::endl;
    }
};

// --------------------------------------------------------------------------------
// Example 2: Interface-style abstract class (pure contract).
// --------------------------------------------------------------------------------
class IShape {
public:
    virtual double area() const = 0;
    virtual ~IShape() = default;
};

class Circle : public IShape {
public:
    explicit Circle(double radius) : radius_(radius) {}

    double area() const override {
        return 3.14159265358979323846 * radius_ * radius_;
    }

private:
    double radius_;
};

int main() {
    std::cout << "Example 1: Abstract class with normal member function and pure virtual function" << std::endl;

    Dog dog;
    dog.speak();
    dog.info();

    std::cout << std::endl;
    std::cout << "Example 2: Interface-style abstract class (pure contract)" << std::endl;

    Circle circle(2.5);
    std::cout << "Circle area: " << circle.area() << std::endl;

    // Animal animal; // Uncommenting this line will fail to compile because Animal is abstract.
    // IShape shape;   // This will also fail because IShape is an interface with no implementation.

    return 0;
}
