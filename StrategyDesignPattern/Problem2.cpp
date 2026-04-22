// PROBLEM: Code Repetition Without Strategy Pattern
//
// Sports and OffRoading vehicles share identical aggressive drive logic,
// but since each class overrides drive() independently, the same code
// is duplicated in two places.
//
// If the aggressive driving logic changes (e.g., add turbo boost),
// we must update it in BOTH SportVehicle and OffRoadVehicle — easy to miss,
// easy to diverge. Strategy Pattern fixes this by extracting the behaviour
// into a separate object that can be shared and swapped.

#include <iostream>

class Vehicle
{
public:
    virtual void drive() = 0;
    virtual ~Vehicle() = default;
};

class PassengerVehicle : public Vehicle
{
public:
    void drive() override
    {
        std::cout << "Driving smoothly on city roads — comfort mode\n";
    }
};

// --- CODE REPETITION STARTS HERE ---

class SportVehicle : public Vehicle
{
public:
    void drive() override
    {
        // Aggressive driving logic
        std::cout << "Driving aggressively — high speed, sharp turns\n";
    }
};

class OffRoadVehicle : public Vehicle
{
public:
    void drive() override
    {
        // Exact same aggressive driving logic copied here
        std::cout << "Driving aggressively — high speed, sharp turns\n";
    }
};

// --- CODE REPETITION ENDS HERE ---
// Any change to aggressive driving must be made in both classes above.

int main()
{
    Vehicle *v1 = new PassengerVehicle();
    Vehicle *v2 = new SportVehicle();
    Vehicle *v3 = new OffRoadVehicle();

    v1->drive();
    v2->drive();
    v3->drive();

    delete v1;
    delete v2;
    delete v3;
    return 0;
}
