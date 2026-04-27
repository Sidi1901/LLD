# Decorator Design Pattern

## Intent

Attach additional responsibilities to an object **dynamically**. Decorators provide a flexible alternative to subclassing for extending functionality.

Also known as: **Wrapper**.

---

## When to Use

- When you want to add behavior to individual objects without affecting others of the same class.
- When subclassing is impractical because it produces an explosion of subclasses for every combination of features.
- When responsibilities need to be added and removed at runtime.

---

## Problem Statement

Suppose you have a `Coffee` class and you want to support optional add-ons: milk, sugar, whip, etc. Without the pattern:

```cpp
class CoffeeWithMilk : public Coffee { /* ... */ };
class CoffeeWithMilkAndSugar : public Coffee { /* ... */ };
class CoffeeWithMilkAndSugarAndWhip : public Coffee { /* ... */ };
// Combinatorial explosion — one class per combination
```

With 4 add-ons, you need up to **2⁴ = 16 subclasses**. Adding a 5th add-on doubles it again.

---

## Structure

```
Component (Interface)
└── operation()

ConcreteComponent
└── operation()   ← base behavior

BaseDecorator
├── wrappee: Component*
└── operation()  ← delegates to wrappee

ConcreteDecoratorA / ConcreteDecoratorB
└── operation()  ← calls super, then adds own behavior
```

---

## Participants

| Participant            | Role |
|------------------------|------|
| **Component**          | Interface that both the concrete component and decorators implement |
| **ConcreteComponent**  | The base object being wrapped |
| **BaseDecorator**      | Holds a reference to a Component; delegates calls to it |
| **ConcreteDecorator**  | Adds behavior before/after delegating to the wrapped component |

---

## Example — Coffee Shop (C++)

### Component Interface

```cpp
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Coffee() = default;
};
```

### ConcreteComponent — SimpleCoffee

```cpp
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }
    double getCost() const override {
        return 1.00;
    }
};
```

### BaseDecorator

```cpp
class CoffeeDecorator : public Coffee {
protected:
    Coffee* wrappee;
public:
    explicit CoffeeDecorator(Coffee* c) : wrappee(c) {}

    std::string getDescription() const override {
        return wrappee->getDescription();
    }
    double getCost() const override {
        return wrappee->getCost();
    }
};
```

### ConcreteDecorators

```cpp
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    std::string getDescription() const override {
        return wrappee->getDescription() + ", Milk";
    }
    double getCost() const override {
        return wrappee->getCost() + 0.25;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}

    std::string getDescription() const override {
        return wrappee->getDescription() + ", Sugar";
    }
    double getCost() const override {
        return wrappee->getCost() + 0.10;
    }
};

class WhipDecorator : public CoffeeDecorator {
public:
    explicit WhipDecorator(Coffee* c) : CoffeeDecorator(c) {}

    std::string getDescription() const override {
        return wrappee->getDescription() + ", Whip";
    }
    double getCost() const override {
        return wrappee->getCost() + 0.50;
    }
};
```

### Client

```cpp
#include <iostream>

int main() {
    Coffee* coffee = new SimpleCoffee();
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << "\n";
    // Simple Coffee $1

    coffee = new MilkDecorator(coffee);
    coffee = new SugarDecorator(coffee);
    coffee = new WhipDecorator(coffee);

    std::cout << coffee->getDescription() << " $" << coffee->getCost() << "\n";
    // Simple Coffee, Milk, Sugar, Whip $1.85

    return 0;
}
```

---

## Class Diagram

```
┌───────────────────────┐
│      Coffee           │  (Interface)
├───────────────────────┤
│ + getDescription()    │
│ + getCost()           │
└───────────────────────┘
          △
          │ implements
   ┌──────┴──────────────────────────────┐
   │                                     │
┌──┴──────────────────┐   ┌─────────────┴──────────────┐
│   SimpleCoffee      │   │      CoffeeDecorator        │
├─────────────────────┤   ├────────────────────────────┤
│ + getDescription()  │   │ - wrappee: Coffee*          │
│ + getCost()         │   ├────────────────────────────┤
└─────────────────────┘   │ + getDescription()          │
                           │ + getCost()                 │
                           └─────────────────────────────┘
                                        △
                                        │ extends
                     ┌──────────────────┼──────────────────┐
                     │                  │                   │
              ┌──────┴──────┐  ┌────────┴──────┐  ┌────────┴──────┐
              │MilkDecorator│  │SugarDecorator │  │WhipDecorator  │
              └─────────────┘  └───────────────┘  └───────────────┘
```

---

## Advantages

- **Open/Closed Principle**: Add new behaviors without changing existing classes.
- **Single Responsibility**: Each decorator handles exactly one concern.
- **Runtime flexibility**: Wrap and unwrap decorators dynamically.
- **Avoids subclass explosion**: Compose behavior instead of inheriting it.

## Disadvantages

- **Many small objects**: Results in a system with lots of small, similarly-looking objects.
- **Order-dependent**: The order in which decorators are applied can matter.
- **Harder to debug**: Tracing through a chain of wrappers can be confusing.
- **Interface must match**: All decorators must implement the same interface as the component.

---

## Real-World Analogies

- **Clothing layers** — Each garment adds insulation; all still let you move (same interface).
- **Java I/O Streams** — `BufferedReader(new FileReader("file.txt"))` stacks behavior via wrapping.
- **HTTP middleware** — Each middleware wraps the next handler, adding logging, auth, etc.

---

## Decorator vs Inheritance

| | Inheritance | Decorator |
|--|-------------|-----------|
| **When** | Compile time | Runtime |
| **Flexibility** | Fixed combinations | Any combination |
| **Class count** | Grows exponentially | Grows linearly |
| **Coupling** | Tight (parent–child) | Loose (via interface) |

---

## Related Patterns

| Pattern | Relationship |
|---------|-------------|
| **Composite** | Both use recursive composition; Composite aggregates children, Decorator wraps exactly one |
| **Strategy** | Strategy changes the *algorithm*; Decorator changes the *skin* (adds to existing behavior) |
| **Proxy** | Proxy controls access; Decorator adds behavior — similar structure, different intent |
| **Chain of Responsibility** | Also chains objects; CoR passes a request until one handles it, Decorator always delegates |

---

## Example: Complete Implementation

See [Solution1.cpp](Solution1.cpp) and [Solution2.cpp](Solution2.cpp) for complete working examples.
