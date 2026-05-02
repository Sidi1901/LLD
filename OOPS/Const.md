### const Keyword in OOPs

The `const` keyword is a compile-time contract: it tells the compiler (and other developers) that something will NOT be modified. Used in three main ways in OOPs: **const member functions**, **const objects**, and **const data members**.

Three types one should know
1) Const Object
2) Const member function
3) Const data members

---

### 1. const Member Functions

A member function marked `const` promises it will NOT modify any data member of the object.

Syntax: `returnType functionName() const { }`

- Can be called on both const and non-const objects.
- A non-const function can only be called on non-const objects.
- Inside a const function, `this` is of type `const ClassName*` — so any write to a member is a compile error.

See Example 1 in Const.cpp

---

### 2. const Objects

A const object is an object whose state cannot be modified after initialization.

An object declared `const` can ONLY call const member functions.

```cpp
const BankAccount acc(1000);
acc.getBalance();    // OK   — const function
acc.deposit(500);    // ERROR — non-const function
```

See Example 2 in Const.cpp

---

### 3. const Data Members

A data member declared `const` must be initialized in the **member initializer list** — it can never be assigned after construction.

```cpp
class Circle {
    const double PI = 3.14159;  // inline init OK (C++11)
    const int id;               // MUST use initializer list
public:
    Circle(int i) : id(i) {}
};
```

See Example 3 in Const.cpp

---


### 4. Why const Correctness Matters

- **Compile-time safety** — bugs caught at compile time, not runtime.


### 5. LLD Tips

**1. Getters must always be const.**
Every getter that only reads state should be `const`. If it isn't, you cannot pass the object as `const&` to other functions — your whole const-correctness chain breaks.

**2. Apply Command-Query Separation (CQS) using const.**
- **Query** = reads state, returns data → mark `const`
- **Command** = changes state, returns void → non-const
This makes intent clear at the function signature level — a core LLD principle.

**3. const in interfaces (abstract classes / pure virtuals).**
Pure virtual functions that are conceptually queries should be declared const in the base interface. This forces all derived classes to honour the read-only contract.

```cpp
class Shape {
public:
    virtual double area() const = 0;   // all shapes must implement read-only area()
};
```

See Example 4 in Const.cpp


Note: A non-const object can call both const and non-const member functions