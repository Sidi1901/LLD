#include <iostream>
#include <string>
using namespace std;

class Coffee
{
public:
    virtual void make() = 0;             // Pure virtual function to be implemented by concrete coffee types
    virtual string getDescription() = 0; // Pure virtual function to get the description of the coffee
    virtual double getCost() = 0;        // Pure virtual function to get the cost of the coffee
};

class SimpleCoffee : public Coffee
{
public:
    void make() override
    {
        cout << "Making simple coffee\n";
    }
    string getDescription() override
    {
        return "Simple Coffee";
    }
    double getCost() override
    {
        return 2.0;
    }
};

class BaseDecorator : public Coffee
{
protected:
    Coffee *wrappedCoffee; // Pointer to the coffee being decorated
public:
    BaseDecorator(Coffee *c) : wrappedCoffee(c) {} // Constructor to set the coffee being decorated
    // void make() override
    // {
    //     wrappedCoffee->make(); // Delegate the make call to the wrapped coffee
    // }
    // string getDescription() override
    // {
    //     return wrappedCoffee->getDescription(); // Delegate the getDescription call to the wrapped coffee
    // }
    // double getCost() override
    // {
    //     return wrappedCoffee->getCost(); // Delegate the getCost call to the wrapped coffee
    // }
};

class MilkDecorator : public BaseDecorator
{
public:
    MilkDecorator(Coffee *c) : BaseDecorator(c) {} // Constructor to set the coffee being decorated
    void make() override
    {
        wrappedCoffee->make();
        // BaseDecorator::make();   // Call the base make method to make the original coffee
        cout << "Adding milk\n"; // Add milk to the coffee
    }
    string getDescription() override
    {
        return wrappedCoffee->getDescription() + ", Milk"; // Add milk to the description
    }
    double getCost() override
    {
        return wrappedCoffee->getCost() + 0.5; // Add the cost of milk to the original cost
    }
};

class SugarDecorator : public BaseDecorator
{
public:
    SugarDecorator(Coffee *c) : BaseDecorator(c) {} // Constructor to set the coffee being decorated
    void make() override
    {
        wrappedCoffee->make();
        // BaseDecorator::make();    // Call the base make method to make the original coffee
        cout << "Adding sugar\n"; // Add sugar to the coffee
    }
    string getDescription() override
    {
        return wrappedCoffee->getDescription() + ", Sugar"; // Add sugar to the description
    }
    double getCost() override
    {
        return wrappedCoffee->getCost() + 0.2; // Add the cost of sugar to the original cost
    }
};

class WhippedCreamDecorator : public BaseDecorator
{
public:
    WhippedCreamDecorator(Coffee *c) : BaseDecorator(c) {} // Constructor to set the coffee being decorated
    void make() override
    {
        wrappedCoffee->make();
        // BaseDecorator::make();            // Call the base make method to make the original coffee
        cout << "Adding whipped cream\n"; // Add whipped cream to the coffee
    }
    string getDescription() override
    {
        return wrappedCoffee->getDescription() + ", Whipped Cream"; // Add whipped cream to the description
    }
    double getCost() override
    {
        return wrappedCoffee->getCost() + 0.3; // Add the cost of whipped cream to the original cost
    }
};

int main()
{
    Coffee *myCoffee = new SimpleCoffee(); // Create a simple coffee
    myCoffee->make();
    cout << "Description: " << myCoffee->getDescription() << "\n"; // Output: Description: Simple Coffee
    cout << "Cost: $" << myCoffee->getCost() << "\n";              // Output: Cost: $2.0

    myCoffee = new MilkDecorator(myCoffee); // Decorate with milk
    myCoffee->make();
    cout << "Description: " << myCoffee->getDescription() << "\n"; // Output: Description: Simple Coffee, Milk
    cout << "Cost: $" << myCoffee->getCost() << "\n";              // Output: Cost: $2.5

    myCoffee = new SugarDecorator(myCoffee); // Decorate with sugar
    myCoffee->make();
    cout << "Description: " << myCoffee->getDescription() << "\n"; // Output: Description: Simple Coffee, Milk, Sugar
    cout << "Cost: $" << myCoffee->getCost() << "\n";              // Output: Cost: $2.7

    myCoffee = new WhippedCreamDecorator(myCoffee); // Decorate with whipped cream
    myCoffee->make();
    cout << "Description: " << myCoffee->getDescription() << "\n"; // Output: Description: Simple Coffee, Milk, Sugar, Whipped Cream
    cout << "Cost: $" << myCoffee->getCost() << "\n";              // Output: Cost: $3.0

    Coffee *anotherCoffee = new WhippedCreamDecorator(new MilkDecorator(new SimpleCoffee())); // Create another coffee with multiple decorators
    anotherCoffee->make();
    cout << "Description: " << anotherCoffee->getDescription() << "\n"; // Output: Description: Simple Coffee, Milk, Whipped Cream
    cout << "Cost: $" << anotherCoffee->getCost() << "\n";              // Output: Cost: $2.8

    delete myCoffee;      // Clean up memory
    delete anotherCoffee; // Clean up memory
    return 0;
}