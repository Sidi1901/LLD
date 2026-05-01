# Single Responsibility Principle (SRP)

> **"A class should have only one reason to change."**
> — Robert C. Martin

## What It Means

A class should do **one thing** and do it well. If a class handles multiple concerns, a change to any one of them can break or force rewrites of unrelated logic.

---

## The Problem (SRP Violation)

Imagine a `BadInvoice` class that:
- Stores invoice data
- Calculates the total
- Prints the invoice to the console
- Saves the invoice to a file

This class has **three reasons to change**:
1. The display format changes → modify `BadInvoice`
2. The storage backend changes → modify `BadInvoice`
3. The pricing logic changes → modify `BadInvoice`

Each change risks breaking the other two responsibilities.

---

## The Fix (SRP Applied)

Split into focused classes, each with **one reason to change**:

| Class | Responsibility | Changes when... |
|---|---|---|
| `Invoice` | Data + business logic (total) | Pricing rules change |
| `InvoicePrinter` | Display / formatting | Output format changes |
| `InvoiceStorage` | Persistence (file, DB) | Storage backend changes |

---

## Key Takeaway

SRP is not about having only one method — it's about having only **one axis of change**. A class can have many methods as long as they all serve a single, cohesive purpose.

### A quick test:
> *"Can I describe what this class does without using the word 'and'?"*

If you need "and", the class probably has more than one responsibility.
