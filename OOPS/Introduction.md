### OOP (Object-Oriented Programming)
A paradigm where you design software using objects (data + behavior) instead of just functions.

### Procedural vs OOP
1. In Procedural, Data and functions are separate | Data and behavior are bundled into objects |
2. In Procedural, Functions operate on global/passed data | Methods operate on the object's own data |
3. In Procedural, Hard to model real-world entities | Maps naturally to real-world entities |
4. In Procedural, Example are C, C++ | In OOPs, Examples are C++, Java, Python 

### Pillars of OOP
1. Encapsulation : Wrap data + methods together, hide internal details => Control access, reduce bugs
2. Abstraction : Show only essential features, hide complexity => User doesn't care how, only what
3. Inheritance : Reuse code using "is-a" relationship => Promotes reuse
4. Polymorphism : Define behaviour at compile time & runtime. Same interface, different behavior.

For example, setters and getters enable encapsulation.

### Access Modifiers
1. Private : Accessible only inside the class
2. Public : Accessible everywhere
3. Protected : Accessible in Class itself and Derived (child) classes

### Class and Object
Class is a blueprint of objects. Object is an instance of class. It's the object that takes memory and is initialised with values.

Class has attributes (states/fields/properties) and methods (functions/behavior).

See Example no.1 in Introduction.cpp

### Ways to Initialise an object

1. Stack (automatic) allocation
Object lives on the stack and is destroyed when it goes out of scope.
```cpp
Car c;                        // default constructor
Car c("Toyota", 120);         // parameterized constructor
Car c2 = c;                   // copy initialization
```

2. Heap allocation using `new`
Object lives on the heap; you must `delete` it manually (or use a smart pointer).
```cpp
Car* c = new Car();           // default constructor, returns pointer
Car* c = new Car("Toyota", 120);
delete c;                     // must free manually
```


### Some Keywords

#### this
`this` is an implicit pointer available inside every non-static member function. It points to the object on which the method was called. Useful to resolve name conflicts between parameters and members, and to return the current object.

class Student{
    name string;
    foo(Student obj){
        print(){
            .....
        }
    }
}

let's say foo(Student ob){print(this.name)}  // foo is a function accepting object

obj.foo(obj2) // here this refers this obj.So, obj's name is called not obj2.

See Example no.2 in Introduction.cpp

#### friend
A `friend` function or class is granted access to private/protected members of the class it is declared friend of. Friendship is not inherited and not mutual.

There is 1. Friend function and 2. Friend class

See Example no.3 in Introduction.cpp


#### mutable
A `mutable` member can be modified even inside a `const` method. Useful for caching or logging inside logically-const operations.

See Example no.4 in Introduction.cpp

### inline functions
Hint to the compiler to replace the function call with the function body directly, avoiding call overhead. Commonly used for small, frequently called methods defined inside the class body (implicitly inline).

See Example no.5 in Introduction.cpp

#### Initializer List in Constructor
Syntax: `ClassName(params) : member1(val1), member2(val2) { }`

Runs before the constructor body. Preferred over assignment inside the body because:
- **Required** for `const` members, reference members, and base class constructors.
- **More efficient** — directly constructs members instead of default-constructing then assigning.

```cpp
class Point {
    const int x;   // const — must use initializer list
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}   // correct
};
```

See Example no.6 in Introduction.cpp
