## Operator Overloading

Define custom behavior for built-in operators (`+`, `==`, `<`, `<<`, etc.) when applied to user-defined types. Same operator, new meaning for your class.

#### How it works
1. Resolved **at compile time** → compile-time polymorphism (like function overloading)
2. You write a function named `operator<symbol>` and the compiler calls it when the operator is used
3. Can be defined as a **member function** or a **friend (non-member) function**

See in Example 1 and 2


#### Rules
- Cannot create new operators — only overload existing ones
- Cannot overload: `::`, `.`, `.*`, `?:`, `sizeof`
- At least one operand must be a user-defined type (no overloading `int + int`)
- Overloading `=`, `[]`, `()`, `->` **must** be member functions
- `<<` and `>>` are almost always friend functions

#### LLD Relevance

Used in patterns like **Strategy** (comparing costs), **Iterator** (advancing with `++`), and anywhere objects represent measurable quantities.

#### Pitfalls
- Overloading `+` without overloading `+=` is inconsistent — do both
- Don't overload operators with surprising semantics (`+` doing subtraction)
- Avoid overloading `&&`, `||` — short-circuit evaluation breaks with overloaded versions
- `==` overloaded means you should also overload `!=` for consistency
