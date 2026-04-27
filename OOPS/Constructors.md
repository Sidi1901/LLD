### Constructor
A special member function automatically called when an object is created. Same name as the class, no return type (not even void). Used to initialize object state.

### Types of Constructors

#### 1. Default Constructor
No parameters (or all parameters have defaults). Called when you create an object without arguments.
- Compiler auto-generates one if you define NO constructor at all.
- If you define ANY constructor, the compiler NO longer generates a default one — you must write it explicitly if you need it.

See Example no.1 in Constructor.cpp

#### 2. Parameterized Constructor
Takes arguments to initialize members with specific values.

See Example no.2 in Constructor.cpp

#### 3. Copy Constructor
Creates a new object as a copy of an existing one.
Signature: `ClassName(const ClassName& other)`

Copy can do two types of copies :- 

**Shallow Copy (default)** : Compiler-generated copy constructor copies each member bit-by-bit. If a member is a raw pointer, both objects point to the same heap memory — dangerous (double-free, dangling pointer).
**Deep Copy (user-defined)** : Allocate new memory and copy the actual content. Both objects own their own data independently.

When is the copy constructor called?
1. `MyClass b = a;` (copy initialization)
2. `MyClass b(a);` (direct copy)
3. Passing an object by value to a function
4. Returning an object by value from a function

See Example no.3 in Constructor.cpp

### Member Initializer List
Preferred way to initialize members — runs BEFORE the constructor body. Required for:
- `const` members (can only be assigned once)
- Reference members
- Members with no default constructor
- Base class constructors

Syntax: `ClassName(int x) : member1(x), member2(0) { }`

Order of initialization follows declaration order in the class, NOT the initializer list order.

See Example no.4 in Constructor.cpp

### Constructor Overloading
Multiple constructors with different parameter lists in the same class. The compiler picks the best match at call site.

See Example no.2 in Constructor.cpp (Car has both default and parameterized)



### Constructor in Inheritance
When a derived object is created:
1. Base class constructor runs first
2. Member initializer list runs
3. Derived constructor body runs

Destructor order is exactly reversed.

You must forward constructor arguments to the base via the initializer list:
`Derived(int x) : Base(x) { }`

Using `using Base::Base;` (C++11) inherits all base constructors into the derived class.

See Example no.7 in Constructor.cpp
