#include <iostream>
#include <string>
using namespace std;

// virtual tells the compiler to use runtime polymorphism (dynamic dispatch) instead of resolving the method call at compile time.

// Without virtual:

// DrivingStrategy* d = new NormalDrivingStrategy();
// d->drive(); // calls DrivingStrategy::drive() — wrong!
// The compiler sees the pointer type (DrivingStrategy*) and calls the base class version.

// With virtual:

// DrivingStrategy* d = new NormalDrivingStrategy();
// d->drive(); // calls NormalDrivingStrategy::drive() — correct!
// At runtime, it checks the actual object type and calls the overridden version.

// In short: virtual enables overriding to actually work when calling through a base class pointer/reference. Without it, override is meaningless and won't even compile.

class DrivingStrategy
{
public:
    // This method contains the logic for driving mode.
    // If we want to change the driving behavior, we only need to modify this method.
    virtual void drive()
    {
        cout << "Driving smoothly on city roads — comfort mode\n";
    }
};

class NormalDrivingStrategy : public DrivingStrategy
{
public:
    void drive() override
    {
        cout << "[Normal] Driving smoothly on city roads — comfort mode\n";
    }
};

class SpecialDrivingStrategy : public DrivingStrategy
{
public:
    void drive() override
    {
        // Aggressive driving logic
        cout << "[Special] Driving aggressively — high speed, sharp turns\n";
    }
};

class Vehicle
{
public:
    DrivingStrategy *strategy;                   // Pointer to the current driving strategy
    Vehicle(DrivingStrategy *s) : strategy(s) {} // Constructor to set the initial strategy
    void setStrategy(DrivingStrategy *s)         // Method to change the strategy at runtime
    {
        strategy = s;
    }
};

int main()
{
    Vehicle *v1 = new Vehicle(new NormalDrivingStrategy());
    Vehicle *v2 = new Vehicle(new SpecialDrivingStrategy());

    v1->strategy->drive(); // Output: [Normal] Driving smoothly on city roads — comfort mode
    v2->strategy->drive(); // Output: [Special] Driving aggressively — high speed, sharp turns

    v1->setStrategy(new SpecialDrivingStrategy()); // Switching strategy at runtime
    v1->strategy->drive();                         // Output: [Special] Driving aggressively — high speed, sharp turns

    delete v1;
    delete v2;
    return 0;
}