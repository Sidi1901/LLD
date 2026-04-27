#include <iostream>
#include <string>
using namespace std;

// Component interface
class Pizza
{
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~Pizza() = default;
};

// ConcreteComponent
class PlainPizza : public Pizza
{
public:
    string getDescription() override { return "Plain Pizza"; }
    double getCost() override { return 5.00; }
};

// BaseDecorator
class ToppingDecorator : public Pizza
{
protected:
    Pizza *wrappee;

public:
    ToppingDecorator(Pizza *p) : wrappee(p) {}
};

// ConcreteDecorators
class CheeseTopping : public ToppingDecorator
{
public:
    CheeseTopping(Pizza *p) : ToppingDecorator(p) {}

    string getDescription() override { return wrappee->getDescription() + ", Cheese"; }
    double getCost() override { return wrappee->getCost() + 1.50; }
};

class PepperoniTopping : public ToppingDecorator
{
public:
    PepperoniTopping(Pizza *p) : ToppingDecorator(p) {}

    string getDescription() override { return wrappee->getDescription() + ", Pepperoni"; }
    double getCost() override { return wrappee->getCost() + 2.00; }
};

class OlivesTopping : public ToppingDecorator
{
public:
    OlivesTopping(Pizza *p) : ToppingDecorator(p) {}

    string getDescription() override { return wrappee->getDescription() + ", Olives"; }
    double getCost() override { return wrappee->getCost() + 1.00; }
};

class MushroomTopping : public ToppingDecorator
{
public:
    MushroomTopping(Pizza *p) : ToppingDecorator(p) {}

    string getDescription() override { return wrappee->getDescription() + ", Mushrooms"; }
    double getCost() override { return wrappee->getCost() + 1.25; }
};

int main()
{
    // Plain pizza
    Pizza *pizza = new PlainPizza();
    cout << pizza->getDescription() << " -> $" << pizza->getCost() << "\n";
    // Plain Pizza -> $5

    // Cheese pizza
    pizza = new CheeseTopping(new PlainPizza());
    cout << pizza->getDescription() << " -> $" << pizza->getCost() << "\n";
    // Plain Pizza, Cheese -> $6.5

    // Pepperoni + Cheese pizza
    pizza = new PepperoniTopping(new CheeseTopping(new PlainPizza()));
    cout << pizza->getDescription() << " -> $" << pizza->getCost() << "\n";
    // Plain Pizza, Cheese, Pepperoni -> $8.5

    // The works: Cheese + Pepperoni + Olives + Mushrooms
    pizza = new MushroomTopping(
        new OlivesTopping(
            new PepperoniTopping(
                new CheeseTopping(
                    new PlainPizza()))));
    cout << pizza->getDescription() << " -> $" << pizza->getCost() << "\n";
    // Plain Pizza, Cheese, Pepperoni, Olives, Mushrooms -> $10.75

    return 0;
}
