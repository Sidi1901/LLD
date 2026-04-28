# Inheritance

Inheritance is a relationship where one class (derived) reuses and extends another class (base).
The derived class inherits members from the base class and can add new behavior, reuse existing behavior, or override virtual functions.

## Key Concepts

### Base class vs Derived class
- Base class: defines common behavior and state that multiple derived classes can share.
- Derived class: extends the base class and can add new members, override functions, or specialize behavior.
- Inheritance models an "is-a" relationship: a `Derived` object is also a `Base` object.

### Why use inheritance?
- Reuse code without copying it.
- Model hierarchical relationships in a natural way.
- Enable polymorphism through virtual functions.
- Separate common behavior into a shared base class.

## Types of inheritance

1. Single inheritance
   - One derived class inherits from one base class.
   - Example: `class Dog : public Animal`.

2. Multilevel inheritance
   - A class derives from a class that is already derived from another class.
   - Example: `class Puppy : public Dog`, where `Dog` inherits from `Animal`.

3. Multiple inheritance
   - A class inherits from more than one base class.
   - Example: `class SmartPhone : public Phone, public Camera`.

4. Hierarchical inheritance
   - Multiple derived classes inherit from the same base class.
   - Example: `class Car : public Vehicle` and `class Bike : public Vehicle`.

5. Hybrid inheritance
   - A combination of two or more types of inheritance.
   - It can include single, multiple, and multilevel inheritance in one design.

## Access specifiers in inheritance

Inheritance also changes how base class members are accessible in the derived class:

1. Public inheritance
   - Most common form.
   - `public` members stay `public` in the derived class.
   - `protected` members stay `protected`.
   - `private` members are not accessible directly by the derived class.

2. Protected inheritance
   - `public` and `protected` members of the base class become `protected` in the derived class.
   - The derived class can use them, but they are not exposed as public.

3. Private inheritance
   - `public` and `protected` members of the base class become `private` in the derived class.
   - Useful when implementing one class in terms of another without exposing the base class interface.

## Constructor and destructor order

When a derived object is created:
1. Base class constructor runs first.
2. Derived class constructor runs next.

When an object is destroyed, the order is reversed:
1. Derived class destructor runs first.
2. Base class destructor runs next.

Use member initializer lists to forward arguments to base class constructors:

```cpp
Derived(int x) : Base(x) {
    // Derived class initialization
}
```

## Example

Inheritance lets the derived class reuse base class members while specializing behavior.
A base class pointer can refer to a derived class object and call overridden virtual methods.

See `Inheritance.cpp` for a working example.
