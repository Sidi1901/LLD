# Virtual Functions, Multiple Inheritance Ambiguity, and the Diamond Problem

## 1. Ambiguity in Multiple Inheritance

When a class inherits from two or more base classes that define a method with the **same name**, the compiler cannot determine which version to call. This is a **name ambiguity** and is a compile-time error.

```
class Flyable  { void describe(); };
class Swimmable{ void describe(); };
class Duck : public Flyable, public Swimmable {};

Duck d;
d.describe();           // ERROR: ambiguous — Flyable::describe or Swimmable::describe?
d.Flyable::describe();  // OK: explicit scope resolution
```

**Fix options:**
1. Use explicit scope resolution at the call site: `d.Flyable::describe()`.
2. Override in the derived class and delegate to the specific bases from there (cleaner).

---

## 2. Hybrid Inheritance and the Diamond Problem

Hybrid inheritance combines multiple inheritance types. The classic pattern is:

```
         Animal
        /       \
      Dog        Cat        ← both inherit from Animal
        \       /
         Hybrid             ← inherits from Dog and Cat
```

### The Problem — duplicate subobjects

Without any extra keyword, `Hybrid` contains **two completely separate copies** of `Animal`:
- One through `Dog` → `Dog::Animal`
- One through `Cat` → `Cat::Animal`

Consequences:
- Any access to `Animal` members through `Hybrid` is **ambiguous** (compiler error).
- The `Animal` constructor runs **twice**, wasting memory and breaking "is-a" semantics.
- You are forced to qualify every call: `Dog::speak()` vs `Cat::speak()` — two different objects.

### The Fix — `virtual` Inheritance

Mark the inheritance of the shared base as `virtual` in **both** intermediate classes:

```cpp
class Dog : virtual public Animal { ... };
class Cat : virtual public Animal { ... };
class Hybrid : public Dog, public Cat { ... };
```

- Only **one shared `Animal` subobject** exists inside `Hybrid`.
- The **most-derived class** (`Hybrid`) is responsible for constructing that single copy directly.
  Dog's and Cat's `Animal` constructors are ignored at runtime.
- Ambiguity disappears — `Hybrid::name` refers to exactly one thing.

```cpp
// most-derived class must list the virtual base in its initializer list
Hybrid(const std::string& n) : Animal(n), Dog(n), Cat(n) {}
```

> The `virtual` keyword in `virtual public Animal` has **nothing to do with virtual functions**.
> It controls the **object layout**, telling the linker to merge duplicate base subobjects into one.

---

## 3. Virtual Functions

### The Problem — Static Dispatch

When you call a method through a **base-class pointer or reference**, C++ by default uses the **declared (static) type** of the pointer to pick the function at **compile time**. This is called **static dispatch** or early binding.

```cpp
Shape* s = new Circle(5);
s->area();   // calls Shape::area() — WRONG, ignores that s actually points to a Circle
```

The override in `Circle` is completely bypassed. The compiler bound `Shape::area` at compile time.

### The Solution — `virtual` and Dynamic Dispatch

Adding `virtual` to the base class method tells the compiler to resolve the call at **runtime** based on the **actual object type**:

```cpp
class Shape {
    virtual double area() const;   // virtual = resolve at runtime
};

Shape* s = new Circle(5);
s->area();   // calls Circle::area() — CORRECT
```

This is **dynamic dispatch** (or late binding / runtime polymorphism).

### How It Works — The vtable

Every class with at least one virtual function gets a hidden **vtable** (virtual dispatch table) — an array of function pointers, one slot per virtual method.

Every **object** of such a class stores a hidden **vptr** (virtual pointer) as its first member, pointing to its class's vtable.

When `s->area()` executes:
1. CPU reads `s`'s vptr.
2. Follows it to the vtable.
3. Jumps to the function pointer at the `area` slot — the correct derived version.

```
 Circle object in memory:
 ┌─────────┬──────────────┐
 │  vptr ──┼──► Circle vtable ──► Circle::area
 │  radius │               └──► Shape::~Shape (or Circle's)
 └─────────┴──────────────┘
```

### Why Do We Need Virtual Functions?

Without virtual functions you cannot write **generic code** that works with any derived type:

```cpp
// Without virtual: you'd need one function per shape type — not extensible.
// With virtual: one function drives every current and future shape.
void printArea(Shape* s) {
    s->printArea();   // dispatches correctly to Circle, Rectangle, Triangle, ...
}
```

This enables the **Open/Closed Principle**: add new shapes without touching existing code.

### Virtual Destructors

If a class has any virtual function, its **destructor must also be virtual**:

```cpp
virtual ~Shape() = default;
```

Without it, `delete basePtr` only calls `Shape::~Shape()` — the derived destructor is skipped, leaking any resources the derived class owns.

### The `override` Keyword

Use `override` in derived classes so the compiler verifies the signature matches the base:

```cpp
double area() const override;   // compile error if base has no matching virtual
```

Catches typos and argument-type mismatches that would silently create a new unrelated function.

### Pure Virtual Functions and Abstract Classes

A pure virtual function (`= 0`) has no implementation in the base class and forces every concrete derived class to provide one:

```cpp
class Shape {
    virtual double area() const = 0;   // pure virtual
};
// Shape s;  ← COMPILE ERROR: cannot instantiate an abstract class
```

This is how C++ models interfaces.

### Key Rules at a Glance

| Rule | Reason |
|------|--------|
| Declare destructor `virtual` in any base class | Prevents resource leaks when deleting through a base pointer |
| Use `override` in derived classes | Compiler catches signature mismatches |
| Pure virtual (`= 0`) makes a class abstract | Forces derived classes to implement the contract |
| Most-derived class drives virtual base constructors | Ensures exactly one shared subobject in diamond hierarchies |
| `virtual` in inheritance ≠ virtual functions | Different features; one controls layout, the other controls dispatch |

See `Virtual_functions.cpp` for working examples of all three concepts.
