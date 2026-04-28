# Low-Level Design (LLD) — Design Patterns in C++

A collection of Gang of Four (GoF) design patterns implemented in C++, with problem statements, solutions, and detailed explanations. Also includes OOP fundamentals and end-to-end sample problems.

## Structure

Each pattern lives in its own directory containing:

| File | Purpose |
|------|---------|
| `Problem*.cpp` | Naive implementation that violates design principles |
| `Solution*.cpp` | Refactored implementation using the pattern |
| `<Pattern>.md` | Theory, structure, trade-offs, and real-world analogies |

---

## OOP Fundamentals

Core C++ OOP concepts, each with a `.cpp` file and a companion `.md` explanation.

| Topic | Source | Notes |
|-------|--------|-------|
| [Introduction](OOPS/Introduction.md) | [Introduction.cpp](OOPS/Introduction.cpp) | Classes, objects, encapsulation basics |
| [Constructors](OOPS/Constructors.md) | [Constructor.cpp](OOPS/Constructor.cpp) | Default, parameterized, copy constructors |
| [Destructors](OOPS/Destructor.md) | [Destructor.cpp](OOPS/Destructor.cpp) | RAII and resource cleanup |
| [Copy Objects](OOPS/Copy_objects.md) | [Copy_objects.cpp](OOPS/Copy_objects.cpp) | Shallow vs deep copy |
| [Static](OOPS/Static.md) | [Static.cpp](OOPS/Static.cpp) | Static members and methods |
| [Const](OOPS/Const.md) | [Const.cpp](OOPS/Const.cpp) | `const` correctness |
| [Inheritance](OOPS/Inheritance.md) | [Inheritance.cpp](OOPS/Inheritance.cpp) | Single, multi-level, and multiple inheritance |
| [Function Overloading](OOPS/Function_overloading.md) | [Function_overloading.cpp](OOPS/Function_overloading.cpp) | Compile-time polymorphism |
| [Operator Overloading](OOPS/Operator_overloading.md) | [Operator_overloading.cpp](OOPS/Operator_overloading.cpp) | Custom operators |
| [Virtual Functions](OOPS/Virtual_functions.md) | [Virtual_functions.cpp](OOPS/Virtual_functions.cpp) | vtable, dynamic dispatch |
| [Abstract Classes](OOPS/Abstract_Class.md) | [Abstract_class.cpp](OOPS/Abstract_class.cpp) | Pure virtual functions and interfaces |
| [Method Overriding](OOPS/Method_overriding.md) | [Method_overriding.cpp](OOPS/Method_overriding.cpp) | Runtime polymorphism |
| [Polymorphism](OOPS/Polymorphism.md) | — | Unified overview of compile- and run-time polymorphism |

---

## Design Patterns

### Creational

| Pattern | Intent | Key Concept |
|---------|--------|-------------|
| [Simple Factory](Patterns/FactoryDesignPattern/SimpleFactory/) | Centralize object creation in a single static method | One factory class with an if-else/switch; easy but violates OCP |
| [Factory Method](Patterns/FactoryDesignPattern/FactoryMethod/) | Let subclasses decide which class to instantiate | Abstract creator declares the factory method; concrete creators override it |
| [Abstract Factory](Patterns/FactoryDesignPattern/AbstractFactory/) | Create families of related objects without specifying concrete classes | Factory of factories; guarantees product families stay consistent |

See [FactoryDesignPattern.md](Patterns/FactoryDesignPattern/FactoryDesignPattern.md) for a unified explanation of all three variants.

### Structural

| Pattern | Intent | Key Concept |
|---------|--------|-------------|
| [Decorator](Patterns/DecoratorDesignPattern/) | Attach additional responsibilities to an object dynamically | Wrapper classes implement the same interface and delegate to the wrapped object |

### Behavioral

| Pattern | Intent | Key Concept |
|---------|--------|-------------|
| [Strategy](Patterns/StrategyDesignPattern/) | Define a family of algorithms and make them interchangeable at runtime | Context holds a `Strategy*`; swap without touching the client |
| [Observer](Patterns/ObserverDesignPattern/) | Notify dependents automatically when a subject's state changes | Subject maintains an observer list; calls `update()` on all on change |

---

## Sample Problems

End-to-end design exercises that combine multiple patterns and OOP concepts.

| Problem | Patterns Used |
|---------|--------------|
| [Payment Processing](SampleProblems/PaymentProcessing.cpp) | Strategy — interchangeable payment methods |
| [Stock Subscription](SampleProblems/StockSubscription.cpp) | Observer — notify subscribers on price change |
| [Delivery Logistics](SampleProblems/DeliveryLogistic.cpp) | Factory Method — create delivery agents by type |

---

## Building & Running

No build system is configured — compile individual files directly with g++:

```bash
# Patterns
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/SimpleFactory/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/FactoryMethod/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/AbstractFactory/Solution1.cpp && ./out
g++ -std=c++17 -o out Patterns/DecoratorDesignPattern/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/StrategyDesignPattern/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/ObserverDesignPattern/Solution2.cpp && ./out

# Sample Problems
g++ -std=c++17 -o out SampleProblems/PaymentProcessing.cpp && ./out
g++ -std=c++17 -o out SampleProblems/StockSubscription.cpp && ./out
g++ -std=c++17 -o out SampleProblems/DeliveryLogistic.cpp && ./out
```

## Learning Path

1. Read through **OOP Fundamentals** in order if you need a C++ refresher.
2. For each pattern, start with `Problem*.cpp` to see what goes wrong without it.
3. Read `Solution*.cpp` alongside the pattern's `.md` file for the full picture.
4. Tackle **Sample Problems** to apply multiple patterns together.
