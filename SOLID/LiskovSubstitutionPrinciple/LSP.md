# Liskov Substitution Principle (LSP)

> **"Objects of a subclass should be replaceable with objects of the parent class without breaking the program."**
> — Barbara Liskov / Robert C. Martin

## What It Means

If `S` is a subtype of `T`, then anywhere you use a `T`, you should be able to drop in an `S` and everything still works correctly — no exceptions thrown, no empty overrides, no broken behaviour.

---

## The Problem (LSP Violation)

`BadPenguin` inherits `BadBird`, which has a `fly()` method. But a penguin can't fly — so the override throws:

```cpp
void fly() const override {
    throw runtime_error("Penguins can't fly!");
}
```

Any function that accepts a `BadBird&` and calls `fly()` will **crash** when given a `Penguin`. The subclass broke the promise its parent made.

This is the LSP violation: the caller trusted the contract of `BadBird`, but the subclass silently violated it.

---

## The Fix (LSP Applied)

Split `Bird` into two separate hierarchies based on **what is actually true**:

`FlyingBird` & `NonFlyingBird` classes

| `Eagle` | `FlyingBird` | `fly()` |
| `Sparrow` | `FlyingBird` | `fly()` |
| `Penguin` | `NonFlyingBird` | `swim()` |

`makeBirdFly(const FlyingBird&)` now works for **every type passed to it** — no exceptions, no surprises. Substitution holds.

---

## Key Takeaway

LSP is about **honouring contracts**. A subclass must fulfil every promise the base class makes — not just inherit its interface.

### Common LSP violation smells:
- Overriding a method to **throw** ("not supported")
- Overriding a method to **do nothing**
- Adding **preconditions** in a subclass that the parent didn't have

### A quick test:
> *"If I swap this subclass in for its parent, does anything break or behave unexpectedly?"*

If yes — LSP is being violated.

### Comming back to LSP definition
If Sparrow is a subtype of FlyingBird, then everywhere the code expects a FlyingBird, you should be able to silently swap in a Sparrow and:

No exception is thrown
No wrong/empty behaviour happens
The caller's expectations are fully met.

void makeBirdFly(const FlyingBird &bird)  // written for FlyingBird (parent) <-The function expects the parent

However,
Sparrow s;
makeBirdFly(s);  // passing Sparrow (subclass)
