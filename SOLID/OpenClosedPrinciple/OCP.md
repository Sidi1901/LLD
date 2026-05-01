# Open/Closed Principle (OCP)

> **"Software entities should be open for extension, but closed for modification."**
> — Bertrand Meyer / Robert C. Martin

## What It Means

Once a class is written and tested, you should be able to **add new behaviour by adding new code** — not by editing the existing class. Editing existing code risks breaking things that already work.

---

## The Problem (OCP Violation)

A `BadDiscountCalculator` uses `if/else` to handle customer types:

```cpp
if (customerType == "Regular") ...
else if (customerType == "Premium") ...
else if (customerType == "VIP") ...
```

Every new customer type (e.g. Student, Employee, Seasonal) requires **modifying** this method — violating OCP and risking regressions in existing discount logic.

---

## The Fix (OCP Applied)

Define a `DiscountStrategy` interface. Each customer type is a **new class** — no existing code is touched:

`RegularDiscount` | 0% off 
`PremiumDiscount` | 20% off
`VIPDiscount` | 40% off
`StudentDiscount` | 15% off — added with zero changes to existing code 
`DiscountCalculator` never changes — it works with **any** `DiscountStrategy`.

---

## Key Takeaway

OCP is typically achieved through **abstraction** (interfaces / abstract classes) and **polymorphism**. The goal is to push variability into new subclasses rather than into `if/else` branches inside existing ones.

### A quick test:
> *"To add a new case, do I have to edit an existing class?"*

If yes — OCP is likely being violated.
