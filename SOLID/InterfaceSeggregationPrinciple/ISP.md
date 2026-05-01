# Interface Segregation Principle (ISP)

> **"A class should not be forced to implement interfaces it does not use."**
> — Robert C. Martin

## What It Means

Don't create one large interface that covers everything. Instead, split it into small, focused interfaces so that a class only implements what it actually supports.

---

## The Problem (ISP Violation)

A `BadMachine` interface forces every machine to implement `print()`, `scan()`, and `fax()`:

```cpp
class BadMachine {
    virtual void print(...) = 0;
    virtual void scan(...)  = 0;  // ❌ what if the machine can't scan?
    virtual void fax(...)   = 0;  // ❌ what if the machine can't fax?
};
```

A `BadPrinter` that can only print is **forced** to implement `scan()` and `fax()` — so it throws:

```cpp
void scan(...) override { throw runtime_error("Printer cannot scan!"); }
```

This is the ISP violation: the class is implementing a contract it **cannot honour**.

---

## The Fix (ISP Applied)

Split the fat interface into three focused ones:

| Interface | Responsibility |
|---|---|
| `IPrinter` | `print()` |
| `IScanner` | `scan()` |
| `IFax` | `fax()` |

Each class implements only what it truly supports:

| Class | Implements |
|---|---|
| `SimplePrinter` | `IPrinter` only |
| `SimpleScanner` | `IScanner` only |
| `AllInOne` | `IPrinter` + `IScanner` + `IFax` |

No empty methods. No throwing overrides. Every implemented method is genuine.

---

## Key Takeaway

ISP is about keeping interfaces **narrow and honest**. A fat interface forces unrelated responsibilities onto classes that don't need them — creating false contracts and brittle code.

### ISP violation smells:
- Overriding a method to throw `"not supported"`
- Leaving an override empty with a `// not applicable` comment
- A class implementing an interface but only using 1 of its 5 methods

### A quick test:
> *"Does this class use every method of the interface it implements?"*

If no — the interface is too broad and needs to be split.
