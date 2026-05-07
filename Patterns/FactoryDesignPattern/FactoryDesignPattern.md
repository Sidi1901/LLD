# Factory Design Pattern

## Overview

The **Factory Design Pattern** is a creational design pattern that provides an interface for creating objects without specifying their exact concrete class. It delegates the instantiation logic to subclasses or a dedicated factory, decoupling the client from the objects it creates.

There are three closely related variants:

| Variant              | Description                                          |
| -------------------- | ---------------------------------------------------- |
| **Simple Factory**   | A single class/method creates objects based on input |
| **Factory Method**   | Subclasses decide which class to instantiate         |
| **Abstract Factory** | Creates families of related objects                  |

---

## The Gang of Four (GoF) design patterns are 23 classic, proven software design solutions to common, recurring problems in object-oriented programming, documented in the 1994 book Design Patterns: Elements of Reusable Object-Oriented Software by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides. These patterns improve code reusability, maintainability, and scalability by providing standardized templates for structuring objects and classes.

---

## Problem Statement

When client code directly instantiates objects using `new`, it creates tight coupling:

- **Hard to extend**: Adding a new type requires modifying client code
- **Violates Open/Closed Principle**: Classes should be open for extension, closed for modification
- **Scattered creation logic**: Object creation spread across the codebase is hard to maintain
- **Difficult testing**: Hard to inject mock/test objects

### Example Problem

```cpp
class NotificationService {
    void sendNotification(string type, string message) {
        if (type == "Email") {
            EmailNotification* n = new EmailNotification();
            n->send(message);
        } else if (type == "SMS") {
            SMSNotification* n = new SMSNotification();
            n->send(message);
        } else if (type == "Push") {
            PushNotification* n = new PushNotification();
            n->send(message);
        }
        // Every new type requires modifying this method — violates OCP
    }
};
```

---

## Solution

The Factory Pattern solves this by:

1. **Defining a product interface** for all objects to be created
2. **Centralizing creation logic** in a factory class or method
3. **Letting subclasses or configuration** decide which concrete product to instantiate
4. **Shielding the client** from knowing concrete types

---

## Variant 1: Simple Factory

Not a formal GoF pattern, but widely used. A single static method creates objects based on a parameter.
Centralized creation logic (usually if-else or switch)
Easy to use
❌ Violates Open/Closed Principle (adding new type → modify factory)

```cpp
class Notification {
public:
    virtual ~Notification() {}
    virtual void send(const string& message) = 0;
};

class EmailNotification : public Notification {
public:
    void send(const string& message) override {
        cout << "[Email] " << message << "\n";
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& message) override {
        cout << "[SMS] " << message << "\n";
    }
};

class PushNotification : public Notification {
public:
    void send(const string& message) override {
        cout << "[Push] " << message << "\n";
    }
};

// Simple Factory
class NotificationFactory {
public:
    static Notification* create(const string& type) {
        if (type == "Email") return new EmailNotification();
        if (type == "SMS")   return new SMSNotification();
        if (type == "Push")  return new PushNotification();
        throw invalid_argument("Unknown notification type: " + type);
    }
};

// Client
int main() {
    Notification* n = NotificationFactory::create("Email");
    n->send("Hello, World!");
    delete n;
}
```

---

## Variant 2: Factory Method (GoF)

Defines an interface for creating an object, but lets subclasses decide which class to instantiate. The factory method is declared in a base creator class and overridden by subclasses.
👉 Idea: Delegate object creation to subclasses
Instead of one factory deciding everything, each subclass decides what to create.
No if-else
Follows Open/Closed Principle ✅
Uses polymorphism
More scalable

### Key Components

#### 1. Product Interface

```cpp
class Transport {
public:
    virtual ~Transport() {}
    virtual void deliver() = 0;
};
```

#### 2. Concrete Products

```cpp
class Truck : public Transport {
public:
    void deliver() override {
        cout << "Delivering by road in a Truck\n";
    }
};

class Ship : public Transport {
public:
    void deliver() override {
        cout << "Delivering by sea in a Ship\n";
    }
};
```

#### 3. Creator (Abstract)

Declares the factory method that subclasses must implement.

```cpp
class Logistics {
public:
    virtual ~Logistics() {}
    virtual Transport* createTransport() = 0;  // factory method

    void planDelivery() {
        Transport* t = createTransport();
        t->deliver();
        delete t;
    }
};
```

#### 4. Concrete Creators

```cpp
class RoadLogistics : public Logistics {
public:
    Transport* createTransport() override {
        return new Truck();
    }
};

class SeaLogistics : public Logistics {
public:
    Transport* createTransport() override {
        return new Ship();
    }
};
```

#### 5. Client

```cpp
int main() {
    Logistics* logistics = new RoadLogistics();
    logistics->planDelivery();  // Delivering by road in a Truck

    delete logistics;
    logistics = new SeaLogistics();
    logistics->planDelivery();  // Delivering by sea in a Ship

    delete logistics;
}
```

| Aspect        | Simple Factory        | Factory Method          |
| ------------- | --------------------- | ----------------------- |
| Type          | Not official pattern  | GoF pattern             |
| Logic         | Centralized (if-else) | Delegated to subclasses |
| Extensibility | Modify factory        | Add new subclass        |
| Complexity    | Simple                | More structured         |
| OCP           | Violates              | Follows                 |

#### 🧠 When to use what?

##### Use Simple Factory

→ when object types are few and unlikely to change


---

## Variant 3: Abstract Factory

Creates **families of related objects** without specifying their concrete classes. Think of it as a factory of factories.

See solution 1

```cpp
// Abstract products
// Button and checkbox are family of related product (Notice in definition 'families of related products')
class Button {
public:
    virtual void render() = 0;
};

class Checkbox {
public:
    virtual void render() = 0;
};

// Concrete Factories
// Windows Factory has two factory createButton factory and create check box factory (Notice in definition factoy of factories)
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override { return new WindowsButton(); }
    Checkbox* createCheckbox() override { return new WindowsCheckbox(); }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    Checkbox* createCheckbox() override { return new MacCheckbox(); }
};

// Client — works with any factory through the abstract interface
class Application {
    GUIFactory* factory;
    Button* button;
public:
    Application(GUIFactory* f) : factory(f) {
        button = factory->createButton();
    }
    void render() { button->render(); }
};
```

---

## Class Diagram (Factory Method)

```
┌──────────────────────────┐
│       Logistics          │  (Abstract Creator)
├──────────────────────────┤
│ + createTransport()      │  ◄── factory method
│ + planDelivery()         │
└──────────────────────────┘
           △
           │ inherits
    ┌──────┴──────────────┐
    │                     │
┌───┴──────────────┐ ┌────┴─────────────┐
│  RoadLogistics   │ │  SeaLogistics    │
├──────────────────┤ ├──────────────────┤
│+createTransport()│ │+createTransport()│
└──────────────────┘ └──────────────────┘
    │ creates               │ creates
    ▼                       ▼
┌──────────┐         ┌──────────┐
│  Truck   │         │  Ship    │
├──────────┤         ├──────────┤
│+deliver()│         │+deliver()│
└──────────┘         └──────────┘
    │                     │
    └──────────┬──────────┘
               △
               │ implements
    ┌──────────┴──────────┐
    │      Transport      │  (Product Interface)
    ├─────────────────────┤
    │ + deliver()         │
    └─────────────────────┘
```

---

## Advantages

✅ **Open/Closed Principle**: Add new products by adding new creator subclasses, no modification needed  
✅ **Single Responsibility**: Creation logic lives in one place  
✅ **Loose Coupling**: Client depends on the product interface, not concrete classes  
✅ **Easy Testing**: Inject mock factories/products in tests  
✅ **Consistency**: Abstract Factory ensures related objects are always used together

## Disadvantages

❌ **Increased Complexity**: More classes and interfaces to maintain  
❌ **Parallel Hierarchies**: Every new product requires a new creator subclass  
❌ **Abstract Factory is Rigid**: Adding a new product type to an existing abstract factory requires changing the factory interface and all implementations

---

## When to Use

Use the Factory Pattern when:

- 🎯 You don't know ahead of time what class you need to instantiate
- 🎯 You want to provide a library/framework where users can extend components
- 🎯 You need to reuse existing objects or manage a pool of objects
- 🎯 You want object creation centralized and consistent across the codebase
- 🎯 You need to create families of related objects (Abstract Factory)

### Avoid when:

- ❌ You only ever create one type of object — a factory adds unnecessary indirection
- ❌ The object creation logic is trivial and unlikely to change

---

## Real-World Examples

### 1. Database Drivers

```cpp
class DBConnection {
public:
    virtual void connect(const string& url) = 0;
    virtual void query(const string& sql) = 0;
};

class MySQLConnection : public DBConnection { /* ... */ };
class PostgresConnection : public DBConnection { /* ... */ };

class DBConnectionFactory {
public:
    static DBConnection* create(const string& driver) {
        if (driver == "mysql")    return new MySQLConnection();
        if (driver == "postgres") return new PostgresConnection();
        throw runtime_error("Unknown driver");
    }
};
```

### 2. UI Theming (Abstract Factory)

Creating consistent sets of themed UI widgets across Windows, Mac, and Linux.

### 3. Document Parsers

A document editor that supports multiple formats (PDF, DOCX, HTML) — each format has its own parser created by the factory.

### 4. Game Enemy Spawning

Different game levels use different factories to spawn different types of enemies with a consistent interface.

---

## Comparison with Other Patterns

| Pattern              | Purpose                                | Key Difference                                      |
| -------------------- | -------------------------------------- | --------------------------------------------------- |
| **Simple Factory**   | Centralize object creation             | Not a formal GoF pattern; uses a static method      |
| **Factory Method**   | Let subclasses decide what to create   | One product type, multiple creator subclasses       |
| **Abstract Factory** | Create families of related products    | Multiple product types, grouped into families       |
| **Builder**          | Construct complex objects step by step | Focuses on construction process, not type selection |
| **Prototype**        | Clone existing objects                 | Creates via copying, not via a factory              |
| **Strategy**         | Choose algorithm at runtime            | Encapsulates behavior, not object creation          |

---

## Best Practices

1. **Return the interface type**, not the concrete type, from all factory methods
2. **Use `unique_ptr`** in modern C++ to avoid memory leaks from factory-created objects
3. **Register products** with the factory at startup to avoid modifying the factory class for each new type (self-registering factories)
4. **Keep factories stateless** where possible for thread safety
5. **Prefer Factory Method over Simple Factory** when you expect many new product types — it scales better with OCP
6. **Combine with Strategy** when the factory decides not just what to create but also how it behaves

---

## Self-Registering Factory (Advanced)

Eliminates the need to modify the factory when adding new types:

```cpp
class ShapeFactory {
    using Creator = function<Shape*()>;
    static map<string, Creator>& registry() {
        static map<string, Creator> r;
        return r;
    }
public:
    static void registerShape(const string& name, Creator creator) {
        registry()[name] = creator;
    }
    static Shape* create(const string& name) {
        auto it = registry().find(name);
        if (it == registry().end()) throw runtime_error("Unknown shape: " + name);
        return it->second();
    }
};

// Each concrete class registers itself — factory never needs modification
struct CircleRegistrar {
    CircleRegistrar() {
        ShapeFactory::registerShape("Circle", []() { return new Circle(); });
    }
} circleRegistrar;
```

---

## Conclusion

The Factory Design Pattern is one of the most commonly used creational patterns. Use **Simple Factory** for straightforward centralization, **Factory Method** when subclasses should control creation, and **Abstract Factory** when your system needs to work with multiple families of related objects. All three promote loose coupling, testability, and adherence to the Open/Closed Principle.
