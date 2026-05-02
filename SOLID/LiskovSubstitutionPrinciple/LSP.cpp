#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 🐦 Problem Statement: Bird Simulation System

// Design a system that models different types of birds.

// ❌ LSP Violation — a subclass breaks the contract of its parent:
//      Penguin IS-A Bird, but cannot fly → overriding fly() to throw breaks caller expectations
//      Any code that treats a Penguin as a Bird and calls fly() will crash or behave wrongly

// ✅ LSP Fix — subtypes must be substitutable for their base type:
//      Split Bird into FlyingBird and NonFlyingBird
//      Only birds that can truly fly inherit FlyingBird
//      Callers that need flying birds ask for FlyingBird — no surprises

// ─────────────────────────────────────────────
// ❌ BAD: violates LSP — Penguin breaks the Bird contract
// ─────────────────────────────────────────────

class BadBird
{
public:
    virtual void fly() const
    {
        cout << "Flying!\n";
    }
    virtual string name() const = 0;
    virtual ~BadBird() {}
};

class BadEagle : public BadBird
{
public:
    string name() const override { return "Eagle"; }
};

class BadPenguin : public BadBird
{
public:
    string name() const override { return "Penguin"; }

    void fly() const override
    {
        // ❌ Penguin cannot fly — throws to signal this, breaking caller assumptions
        throw runtime_error("Penguins can't fly!");
    }
};

void makeBirdFly(const BadBird &bird)
{
    // ❌ Caller assumes every BadBird can fly — Penguin will blow this up
    bird.fly();
}

// ─────────────────────────────────────────────
// ✅ GOOD: subtypes honour their base type's contract
// ─────────────────────────────────────────────

class Bird
{
public:
    virtual string name() const = 0;
    virtual string describe() const = 0;
    virtual ~Bird() {}
};

class FlyingBird : public Bird
{
public:
    virtual void fly() const = 0;
};

class NonFlyingBird : public Bird {};

class Eagle : public FlyingBird
{
public:
    string name() const override { return "Eagle"; }
    string describe() const override { return "Eagle — soars at high altitude"; }
    void fly() const override { cout << name() << " is flying!\n"; }
};

class Sparrow : public FlyingBird
{
public:
    string name() const override { return "Sparrow"; }
    string describe() const override { return "Sparrow — quick short-distance flier"; }
    void fly() const override { cout << name() << " is flying!\n"; }
};

class Penguin : public NonFlyingBird
{
public:
    string name() const override { return "Penguin"; }
    string describe() const override { return "Penguin — expert swimmer, cannot fly"; }
    void swim() const { cout << name() << " is swimming!\n"; }
};

// ✅ This function works correctly for ALL FlyingBirds — no exceptions, no surprises
void makeBirdFly(const FlyingBird &bird)
{
    bird.fly();
}

int main()
{
    cout << "--- ❌ LSP Violation ---\n";
    BadEagle badEagle;
    BadPenguin badPenguin;
    makeBirdFly(badEagle); // ✅ works
    try
    {
        makeBirdFly(badPenguin); // ❌ crashes — Penguin broke the contract
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    cout << "\n--- ✅ LSP Compliant ---\n";
    vector<FlyingBird *> fliers = {new Eagle(), new Sparrow()};
    for (auto *b : fliers)
    {
        makeBirdFly(*b); // ✅ every FlyingBird can actually fly — substitution holds
        delete b;
    }

    Penguin penguin;
    cout << penguin.describe() << "\n";
    penguin.swim(); // ✅ Penguin exposes only what it can truly do

    return 0;
}
