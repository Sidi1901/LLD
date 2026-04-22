# Low-Level Design (LLD) — Design Patterns in C++

A collection of Gang of Four (GoF) behavioral design patterns implemented in C++, with problem statements, solutions, and detailed explanations.

## Structure

Each pattern lives in its own directory containing:

| File | Purpose |
|------|---------|
| `Problem*.cpp` | Naive implementation that violates design principles |
| `Solution*.cpp` | Refactored implementation using the pattern |
| `<Pattern>.md` | Theory, structure, trade-offs, and real-world analogies |

## Patterns

### Behavioral

| Pattern | Intent | Key Concept |
|---------|--------|-------------|
| [Strategy](StrategyDesignPattern/) | Define a family of algorithms and make them interchangeable at runtime | Context holds a `Strategy*`; swap without touching the client |
| [Observer](ObserverDesignPattern/) | Notify dependents automatically when a subject's state changes | Subject maintains an observer list; calls `update()` on all on change |

## Building & Running

No build system is configured — compile individual files directly with g++:

```bash
g++ -std=c++17 -o out StrategyDesignPattern/Solution2.cpp && ./out
g++ -std=c++17 -o out ObserverDesignPattern/Solution2.cpp && ./out
```

## Learning Path

Start with `Problem*.cpp` to see what goes wrong without the pattern, then read `Solution*.cpp` alongside the pattern's `.md` file for the full picture.
