### Polymorphism

Polymorphism means "many forms." In object-oriented programming, it allows one interface to represent multiple underlying forms (data types or classes).

#### Compile-time Polymorphism
Compile-time polymorphism is resolved during compilation. Common forms include:

- Function overloading: multiple functions with the same name but different parameters.
- Operator overloading: defining custom behavior for operators like `+`, `-`, `<<`, etc.
- Templates: generic code that works with multiple data types.
- Method/function overriding without `virtual`: when a derived class defines a method with the same name as the base class, but calls depend on the static type.

#### Runtime Polymorphism (MOST IMPORTANT)
Runtime polymorphism is resolved during program execution. In C++, this is typically achieved using:

- Virtual functions i.e Method/function overriding with `virtual`
- Base class pointers or references to derived objects
- Dynamic dispatch through the virtual table (vtable)

This allows one pointer or reference type to call the appropriate derived-class implementation at runtime.

#### Why it matters
- Makes code extensible and easier to maintain.
- Enables writing functions that work with base class interfaces while using derived-class behavior.
- Supports runtime behavior selection based on actual object type.

#### Key distinction
- Compile-time polymorphism: chosen by the compiler.
- Runtime polymorphism: chosen by the program at runtime using virtual dispatch.

#### Common LLD pitfalls
- Overusing inheritance for polymorphism when composition + an interface would be cleaner and more flexible.
- Forgetting `virtual` destructors in base classes — leads to resource leaks when deleting through a base pointer.
- Deep inheritance hierarchies that violate LSP**; prefer flat hierarchies with delegation.

Checkout LLD concepts in SOLD folder
