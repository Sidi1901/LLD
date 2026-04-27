## Function Overloading

Same function name, different parameter list (type, number, or order of params). Return type alone does NOT differentiate overloads.

#### How the compiler resolves it
- Checked **at compile time** → compile-time polymorphism
- Compiler picks the best match based on argument types
- Ambiguous calls (e.g., passing `int` when both `float` and `double` versions exist) cause a compile error
- Default values can be set in funtion parameters.

#### Rules
- Must differ in parameter type, count, or order
- Return type alone is NOT enough to overload
- Default arguments can cause ambiguity — be careful

#### LLD Relevance (IMPORTANT)


**Constructors are the most common overloading in LLD**
```cpp
class Logger {
public:
    Logger();                            // default — logs to stdout
    Logger(const string& filePath);      // logs to file
    Logger(const string& filePath, int level); // with log level
};
```
Used heavily in **Builder** and **Factory** patterns to create objects with varying configurations.

**Operator overloading is a subset** — same concept applied to operators (`+`, `==`, `<<`).

#### When to use in design
- When behavior is the same but inputs vary (e.g., `area(int r)` vs `area(int l, int w)`)
- Constructors with optional context (dependency injection)
- Utility/helper classes with multiple input formats (e.g., parsing strings, ints, enums)

See in Example 1

#### Pitfalls
- Too many overloads → harder to read; consider named methods or a parameter object instead
- Avoid overloads that differ only in `int` vs `long` — silent implicit conversions cause bugs

See in Example 2
