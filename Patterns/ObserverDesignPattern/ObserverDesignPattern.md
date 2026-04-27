# Observer Design Pattern

## Intent

Define a one-to-many dependency between objects so that when one object (the **Subject**) changes state, all its dependents (**Observers**) are notified and updated automatically.

Also known as: **Publish-Subscribe**, **Event Listener**.

---

## When to Use

- When a change in one object requires updating others, and you don't know how many objects need to change.
- When an object should notify other objects without making assumptions about who those objects are.
- Implementing distributed event-handling systems.

---

## Structure

```
Subject (Observable)
├── attach(observer)
├── detach(observer)
└── notify()

Observer (Interface)
└── update(data)

ConcreteSubject
├── state
└── getState()

ConcreteObserver
└── update(data)  ← reacts to Subject's state change
```

---

## Participants

| Participant          | Role                                                                 |
| -------------------- | -------------------------------------------------------------------- |
| **Subject**          | Maintains a list of observers; provides attach/detach/notify methods |
| **Observer**         | Interface with an `update()` method                                  |
| **ConcreteSubject**  | Holds state; calls `notify()` when state changes                     |
| **ConcreteObserver** | Implements `update()`; reacts to Subject's changes                   |

---

## Example — Stock Price Alert (C++)

### Observer Interface

```cpp
class Observer {
public:
    virtual void update(const std::string& stockName, double price) = 0;
    virtual ~Observer() = default;
};
```

### Subject Interface

```cpp
class Subject {
public:
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};
```

### ConcreteSubject — StockMarket

```cpp
#include <vector>
#include <algorithm>
#include <string>

class StockMarket : public Subject {
    std::vector<Observer*> observers;
    std::string stockName;
    double price = 0.0;

public:
    void setStockPrice(const std::string& name, double p) {
        stockName = name;
        price = p;
        notifyObservers();
    }

    void attach(Observer* o) override { observers.push_back(o); }

    void detach(Observer* o) override {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notifyObservers() override {
        for (Observer* o : observers)
            o->update(stockName, price);
    }
};
```

### ConcreteObserver — MobileApp

```cpp
#include <iostream>

class MobileApp : public Observer {
    std::string userId;
public:
    explicit MobileApp(std::string id) : userId(std::move(id)) {}

    void update(const std::string& stockName, double price) override {
        std::cout << "[MobileApp - " << userId << "] Alert: "
                  << stockName << " is now $" << price << "\n";
    }
};
```

### ConcreteObserver — EmailAlert

```cpp
class EmailAlert : public Observer {
    std::string email;
public:
    explicit EmailAlert(std::string e) : email(std::move(e)) {}

    void update(const std::string& stockName, double price) override {
        std::cout << "[Email - " << email << "] "
                  << stockName << " price changed to $" << price << "\n";
    }
};
```

### Client

```cpp
int main() {
    StockMarket market;

    MobileApp app("user_42");
    EmailAlert emailAlert("trader@example.com");

    market.attach(&app);
    market.attach(&emailAlert);

    market.setStockPrice("AAPL", 189.50);
    // [MobileApp - user_42] Alert: AAPL is now $189.5
    // [Email - trader@example.com] AAPL price changed to $189.5

    market.detach(&emailAlert);
    market.setStockPrice("AAPL", 192.00);
    // [MobileApp - user_42] Alert: AAPL is now $192

    return 0;
}
```

---

## Push vs Pull Model

| Model    | Description                                           | Trade-off                                                      |
| -------- | ----------------------------------------------------- | -------------------------------------------------------------- |
| **Push** | Subject sends data in `update(data)`                  | Observer gets data it may not need                             |
| **Pull** | Observer calls `subject.getState()` inside `update()` | Observer controls what it fetches; tighter coupling to Subject |

---

## Advantages

- **Loose coupling** — Subject knows nothing about Observer internals.
- **Open/Closed** — Add new observers without changing the Subject.
- **Broadcast communication** — One change fans out to many listeners.

## Disadvantages

- **Unexpected updates** — Observers may be notified in an unpredictable order.
- **Memory leaks** — Forgotten `detach()` calls keep observers alive (lapsed listener problem).
- **Cascading updates** — One notify can trigger a chain of updates across observers.

---

## Real-World Analogies

- **YouTube subscriptions** — Channel (Subject) notifies all subscribers (Observers) on new upload.
- **Event listeners in UI** — Button click notifies registered click handlers.
- **Redux store** — Components subscribe to state; re-render on change.

---

## Related Patterns

| Pattern                 | Relationship                                                              |
| ----------------------- | ------------------------------------------------------------------------- |
| **Mediator**            | Mediator centralizes communication; Observer distributes it               |
| **Event Bus / Pub-Sub** | Decoupled variant — observers subscribe to topic, not to Subject directly |
| **Strategy**            | Often used together; observers can swap behavior strategies               |
