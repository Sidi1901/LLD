# Low-Level Design (LLD) — Design Patterns in C++

A collection of Gang of Four (GoF) design patterns implemented in C++, with problem statements, solutions, and detailed explanations.

## Structure

Each pattern lives in its own directory containing:

| File | Purpose |
|------|---------|
| `Problem*.cpp` | Naive implementation that violates design principles |
| `Solution*.cpp` | Refactored implementation using the pattern |
| `<Pattern>.md` | Theory, structure, trade-offs, and real-world analogies |

## Patterns

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

## Building & Running

No build system is configured — compile individual files directly with g++:

```bash
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/SimpleFactory/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/FactoryMethod/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/FactoryDesignPattern/AbstractFactory/Solution1.cpp && ./out
g++ -std=c++17 -o out Patterns/DecoratorDesignPattern/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/StrategyDesignPattern/Solution2.cpp && ./out
g++ -std=c++17 -o out Patterns/ObserverDesignPattern/Solution2.cpp && ./out
```

## Learning Path

Start with `Problem*.cpp` to see what goes wrong without the pattern, then read `Solution*.cpp` alongside the pattern's `.md` file for the full picture.
