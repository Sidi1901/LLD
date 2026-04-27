### Copying Objects
Two mechanisms exist for copying an object from another already-constructed object.

---

#### 1. Copy Constructor
Creates a **new** object initialised from an existing one.
Signature: `ClassName(const ClassName& other)`

Called when:
- `MyClass b = a;` or `MyClass b(a);`
- Passing an object **by value** to a function
- Returning an object **by value** from a function

See Example 1 in Copy_objects.cpp

---

#### 2. Copy Assignment Operator
Copies into an **already-existing** object.
Signature: `ClassName& operator=(const ClassName& other)`

Called when:
- `b = a;`  (both `b` and `a` already exist)

See Example 2 in Copy_objects.cpp

---

#### Shallow vs Deep Copy
Shallow (compiler default) | Deep (user-defined)
Pointers :- In Shallow, both objects share the same heap block. In Deep, each object owns its own heap block 

See Example 3 in Copy_objects.cpp


### The Rule of Three (LLD critical)
If a class needs **any one** of these, it almost certainly needs **all three**:
1. Destructor
2. Copy Constructor
3. Copy Assignment Operator

*Reason*: needing a custom destructor usually means the class manages a resource (heap memory, file handle, socket). The compiler-generated copy and assignment will do a shallow copy of that resource, causing double-free or resource leaks.

---


### The Rule of Zero (preferred LLD pattern)
Design classes so they own **no raw resources directly**. Use `std::unique_ptr`, `std::shared_ptr`, `std::string`, `std::vector`, etc.
- Compiler-generated copy/move/destructor all do the right thing automatically.
- Zero hand-written special member functions = zero bugs from forgetting one.

