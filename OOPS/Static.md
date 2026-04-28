# Static in C++

## 1. Static Data Members

A `static` data member belongs to the **class itself**, not to any individual object. There is exactly **one copy** shared across all instances.

Key points:
- Must be **defined** outside the class body (except for `inline static` in C++17).
- Initialized to zero by default if no explicit initializer.
- Accessed via Scope Resolution Operator

See Example 1

## 2. Static Member Functions

A `static` member function belongs to the class, not to an object. It has **no `this` pointer** and can only access other static members directly.

```cpp
class Counter {
    static int count;
public:
    static int getCount() { return count; }   // no 'this'
};
```

---

## 3. Static Local Variables

A `static` local variable inside a function is initialized **once** on first call and retains its value across all subsequent calls (its lifetime is the entire program).

```cpp
void increment() {
    static int x = 0;   // initialized only the first time this line is reached
    ++x;
    std::cout << x << '\n';
}

increment();  // prints 1
increment();  // prints 2
increment();  // prints 3
```

Key points:
- Stored in the **data segment**, not on the stack.
- Thread-safe initialization guaranteed since C++11.
- Useful for counters, caches, or the Singleton pattern.

