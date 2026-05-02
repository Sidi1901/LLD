# Dependency Inversion Principle (DIP)

> **"High-level modules should not depend on low-level modules. Both should depend on abstractions."**
> — Robert C. Martin


## What It Means

Two rules:
1. High-level modules (business logic) must not depend directly on low-level modules (concrete implementations).
2. Both should depend on an **abstraction** (interface / abstract class).

The dependency arrow gets **inverted** — instead of the high-level class reaching down to create a concrete low-level object, both point toward an interface in the middle.

---

## The Problem (DIP Violation)

`BadNotificationService` directly owns a `BadEmailSender`:

```cpp
class BadNotificationService {
    BadEmailSender sender; // ❌ hardwired concrete dependency
public:
    void notify(...) { sender.sendEmail(...); }
};
```

To switch to SMS, you must **open and modify** `BadNotificationService`. The high-level class is tightly coupled to a low-level detail.

---

## The Fix (DIP Applied)

Introduce an `INotifier` abstraction. Both levels depend on it:

```
NotificationService  →  INotifier  ←  EmailNotifier
                                   ←  SMSNotifier
                                   ←  PushNotifier
```

`NotificationService` receives its dependency from the outside (**dependency injection**):

```cpp
class NotificationService {
    INotifier &notifier; // depends on abstraction
public:
    NotificationService(INotifier &notifier) : notifier(notifier) {}
};
```

Swap `EmailNotifier` for `SMSNotifier` — `NotificationService` never changes.

---

## Key Takeaway

DIP is about **who controls the dependency**. In the bad version, `BadNotificationService` creates and owns `BadEmailSender` — it controls it. In the good version, the dependency is **passed in from outside** — the caller controls it.

It's not about inverting who calls who — NotificationService still calls send(). It's about inverting who owns the contract. Before, EmailSender owned its own interface. After, the abstraction INotifier owns it, and EmailSender must confirm to it

### DIP violation smells:
- A class uses `new ConcreteClass()` inside itself
- A high-level class imports or includes a low-level concrete class directly
- Switching an implementation requires editing business logic

### A quick test:
> *"If I want to swap the implementation this class uses, do I have to edit the class itself?"*

If yes — DIP is being violated.
