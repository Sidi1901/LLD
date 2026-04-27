### Destructor
A special member function called automatically when an object's lifetime ends. Syntax: `~ClassName()`. No parameters, no return type, only one per class (cannot be overloaded). Used to release resources the object owns.

When is a destructor called?
- Stack object goes out of scope (end of block / function return)
- `delete` is called on a heap-allocated object
- End of program for global/static objects

See Example no.1 in Destructor.cpp

---

### Destructor Order in Inheritance
Destruction is the exact reverse of construction:
1. Derived destructor body runs
2. Member destructors run (reverse declaration order)
3. Base destructor body runs

See Example no.2 in Destructor.cpp

---

### Virtual Destructor ⭐ (Critical for LLD)
If a base class pointer holds a derived object and the destructor is **not virtual**, only the base destructor runs on `delete` — the derived destructor is skipped, causing a resource leak.

**Rule: any class meant to be inherited should have a `virtual` destructor.**

```cpp
Base* b = new Derived();
delete b;   // without virtual ~Base(), Derived::~Derived() never runs
```

**Always declare `virtual ~Base()` in any base class** — even if the body is empty. Forgetting this is a common memory leak in polymorphic hierarchies (e.g., Strategy, Observer, Abstract Factory patterns).

See Example no.3 in Destructor.cpp

