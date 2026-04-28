# Method Overriding

Method overriding means a derived class provides its own implementation of a method that already exists in the base class, using the **same name, same parameters, and same return type**.

## Compile-time vs Runtime Overriding

### Without `virtual` — Compile-time (Static) Dispatch

If the base class method is **not** virtual, the compiler binds the call at compile time based on the **declared type** of the pointer or reference, not the actual object.

See Example 1

Make sure A class has the function show otherwise

This is **method hiding**, not true overriding. The derived version is silently ignored.

### With `virtual` — Runtime (Dynamic) Dispatch

Marking the base method `virtual` tells the compiler to defer the call to runtime:

See Example 2

The `virtual` keyword on the base class method is what enables true overriding.

## Rules for Valid Overriding

1. Same function name Must match exactly
2. Same parameter list Type, order, and count must match
3. Base method must be `virtual` Without it, you get hiding, not overriding
4. Use `override` in derived class Not required but strongly recommended 

## The `override` and `final` Keyword

`override` asks the compiler to verify that the signature actually matches a `virtual` method in the base class
`final` on a method prevents any further derived class from overriding it. 

```cpp
class Dog : public Animal {
public:
    void speek() override final;   // COMPILE ERROR: no matching virtual in Animal — catches typo
};
```
`final` can also be applied to an entire class to prevent inheritance altogether.

Without `override`, a typo silently introduces a new, unrelated method instead of overriding.


## Calling the Base Class Version

Inside an override, you can still call the base implementation explicitly:

```cpp
void Dog::speak() override {
    Animal::speak();             // call base version first
    std::cout << "Dog barks\n";
}
```

Useful when the derived class wants to extend rather than fully replace base behavior.


## Overriding vs Hiding

- **Hiding**: Base method is not `virtual` — derived method silently replaces the base version only for the derived type's static calls. 
- Child defines same function → it hides base version
- Call is decided by pointer type, not object type
- With virtual, it's the real overriding.
- If derived defines same function → hides base version
- If derived does NOT define it → base version is used
- Without virtual → depends on pointer type (static binding) Thus it's a static polymorphism

Base* obj = new Derived();
obj->show();  // Base::show in case without virtual

Base* obj = new Derived();
obj->show();  // Derived::show in case of virtual 
              // depends on object type. Resolved at runtime. Hence dynamic polymorphism


## Virtual Destructor Requirement

Whenever you override methods in a hierarchy, the base destructor **must** be virtual:

```cpp
virtual ~Animal() = default;
```

Without it, `delete animalPtr` (where the actual object is a `Dog`) skips `Dog::~Dog()`, leaking any resources `Dog` owns.

## Common LLD Pitfalls

- Forgetting `virtual` on the base method: you get hiding, bugs are silent and hard to trace.
- Forgetting `virtual ~Base()`: resource leaks when deleting through a base pointer.
- Not using `override`: typos or signature mismatches create new methods instead of overrides.
- Overriding without calling `Base::method()` when the base has important setup or teardown logic.
- Violating LSP: the override changes semantics rather than specializing them — callers relying on the base contract break silently.


