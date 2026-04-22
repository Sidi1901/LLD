# Strategy Design Pattern

## Overview

The **Strategy Design Pattern** is a behavioral design pattern that defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from clients that use it.

## Problem Statement

When you have multiple ways to perform a task and need to choose between them at runtime, the traditional approach leads to:

- **Tight coupling** between the client and algorithm implementations
- **Difficult maintenance** when adding new algorithms
- **Violation of Open/Closed Principle** (classes should be open for extension, closed for modification)
- **Proliferation of conditional logic** in the client code

### Example Problem

Consider a payment system that supports multiple payment methods:

```cpp
class PaymentProcessor {
    void processPayment(double amount, string method) {
        if (method == "Credit Card") {
            // Credit card logic
        } else if (method == "Debit Card") {
            // Debit card logic
        } else if (method == "PayPal") {
            // PayPal logic
        } else if (method == "Bitcoin") {
            // Bitcoin logic
        }
        // Hard to maintain, violates OCP
    }
};
```

## Solution

The Strategy Pattern solves this by:

1. **Defining an interface** for all supported algorithms
2. **Encapsulating each algorithm** in separate strategy classes
3. **Making strategies interchangeable** at runtime
4. **Eliminating conditional logic** from the client

## Key Components

### 1. **Strategy Interface**

Declares the common interface for all supported algorithms.

```cpp
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() {}
    virtual bool pay(double amount) = 0;
    virtual void processRefund(double amount) = 0;
};
```

### 2. **Concrete Strategies**

Implement the strategy interface with specific algorithms.

```cpp
class CreditCardStrategy : public PaymentStrategy {
public:
    bool pay(double amount) override {
        cout << "Processing payment of $" << amount << " via Credit Card\n";
        return true;
    }

    void processRefund(double amount) override {
        cout << "Credit card refund: $" << amount << "\n";
    }
};

class PayPalStrategy : public PaymentStrategy {
public:
    bool pay(double amount) override {
        cout << "Processing payment of $" << amount << " via PayPal\n";
        return true;
    }

    void processRefund(double amount) override {
        cout << "PayPal refund: $" << amount << "\n";
    }
};
```

### 3. **Context**

Uses a strategy object to execute an algorithm.

```cpp
class PaymentProcessor {
private:
    PaymentStrategy* strategy;

public:
    PaymentProcessor(PaymentStrategy* s) : strategy(s) {}

    void setStrategy(PaymentStrategy* s) {
        strategy = s;
    }

    bool processPayment(double amount) {
        return strategy->pay(amount);
    }

    void refund(double amount) {
        strategy->processRefund(amount);
    }
};
```

### 4. **Client**

Creates concrete strategies and passes them to the context.

```cpp
int main() {
    // Choose payment method at runtime
    PaymentProcessor processor(new CreditCardStrategy());
    processor.processPayment(100.0);

    // Switch strategy at runtime
    processor.setStrategy(new PayPalStrategy());
    processor.processPayment(50.0);

    return 0;
}
```

## Class Diagram

```
┌──────────────────────────┐
│    PaymentProcessor      │
├──────────────────────────┤
│ - strategy: Strategy     │
├──────────────────────────┤
│ + setStrategy()          │
│ + processPayment()       │
│ + refund()               │
└──────────────────────────┘
           │
           │ uses
           ▼
┌──────────────────────────┐
│   PaymentStrategy        │ (Interface)
├──────────────────────────┤
│ + pay()                  │
│ + processRefund()        │
└──────────────────────────┘
           △
           │ implements
    ┌──────┴─────────┬────────────────┐
    │                │                │
┌───┴────────────┐ ┌─┴────────────┐ ┌┴──────────────┐
│CreditCardStrat │ │PayPalStrategy │ │BitcoinStrategy│
├────────────────┤ ├───────────────┤ ├───────────────┤
│+ pay()         │ │+ pay()        │ │+ pay()        │
│+ processRefund │ │+ processRefund│ │+ processRefund│
└────────────────┘ └───────────────┘ └───────────────┘
```

## Advantages

✅ **Open/Closed Principle**: Easy to add new strategies without modifying existing code  
✅ **Run-time Selection**: Algorithms can be selected at runtime  
✅ **Loose Coupling**: Client is independent of concrete strategy implementations  
✅ **Easy Testing**: Each strategy can be tested in isolation  
✅ **Eliminates Conditionals**: No need for long if-else chains  
✅ **Reusability**: Strategies can be reused across different clients

## Disadvantages

❌ **Increased Complexity**: More classes to maintain  
❌ **Overhead**: Small overhead for strategy objects and method calls  
❌ **Not Ideal for Few Algorithms**: Adds complexity if only 1-2 strategies exist  
❌ **Client Must Know Strategies**: Client needs to be aware of different strategy options

## When to Use

Use the Strategy Pattern when:

- 🎯 You have multiple algorithms for a specific task
- 🎯 You need to choose between algorithms at runtime
- 🎯 You want to avoid conditional statements for algorithm selection
- 🎯 You expect new algorithms to be added in the future
- 🎯 Different algorithms have different performance characteristics
- 🎯 You need to encapsulate algorithms that should be independent of clients

### Avoid when:

- ❌ You have only 1-2 simple algorithms
- ❌ Algorithms are rarely used or changed
- ❌ You want to keep the codebase minimal

## Real-World Examples

### 1. **Sorting Algorithms**

```cpp
class SortingStrategy {
public:
    virtual void sort(vector<int>& arr) = 0;
};

class QuickSortStrategy : public SortingStrategy { /* ... */ };
class MergeSortStrategy : public SortingStrategy { /* ... */ };
```

### 2. **Compression Algorithms**

Compress files using different algorithms (ZIP, RAR, 7Z) interchangeably.

### 3. **Route Navigation**

Choose between driving, walking, or public transit routes based on user preference.

### 4. **Authentication Methods**

Support multiple authentication strategies: OAuth, JWT, API Key, Azure AD.

### 5. **Logging Strategies**

Log to console, file, or remote server based on configuration.

## Comparison with Other Patterns

| Pattern                     | Purpose                                   | Key Difference                        |
| --------------------------- | ----------------------------------------- | ------------------------------------- |
| **Strategy**                | Choose algorithm at runtime               | Encapsulates different algorithms     |
| **Template Method**         | Define algorithm skeleton in parent class | Subclasses implement specific steps   |
| **State**                   | Change behavior based on state            | Object's behavior changes with state  |
| **Decorator**               | Add responsibility dynamically            | Wraps objects to add features         |
| **Chain of Responsibility** | Pass request through chain                | Handlers process request sequentially |

## Best Practices

1. **Use Small, Focused Strategies**: Each strategy should do one thing well
2. **Prefer Composition**: Use strategy composition for complex behavior
3. **Document Strategy Contracts**: Clearly document what each strategy does
4. **Consider Performance**: Cache strategies if creation is expensive
5. **Use Factory Pattern**: Create a factory to instantiate strategies
6. **Immutable Strategies**: Consider making strategies stateless and immutable
7. **Version Your Strategies**: Consider versioning when strategies evolve

## Implementation Considerations

### Memory Management

- Use `std::unique_ptr` to manage strategy lifetime automatically
- Consider strategy pooling for frequently created strategies

### Thread Safety

- Ensure strategies are thread-safe if used in multi-threaded context
- Use thread-local strategies if needed

### Configuration

- Store strategy configuration separately from behavior
- Use dependency injection to provide strategies

## Example: Complete Implementation

See `Solution1.cpp` and `Solution2.cpp` for a complete working example with multiple payment strategies.

## Conclusion

The Strategy Pattern is powerful for managing multiple algorithms and making code more flexible and maintainable. It's particularly useful when:

- Algorithms vary and may change frequently
- You want to eliminate conditional logic
- You need to support different implementations of the same task
- You want to follow SOLID principles (especially Open/Closed Principle)

By encapsulating algorithms as interchangeable strategies, you make your code more extensible, testable, and easier to maintain.
