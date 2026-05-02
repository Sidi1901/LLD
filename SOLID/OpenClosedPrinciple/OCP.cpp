#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 🛒 Problem Statement: Discount System for an E-Commerce Platform

// Design a system that calculates discounts for different customer types.

// ❌ OCP Violation — every new customer type forces you to modify existing code:
//      Adding "Student" discount → edit DiscountCalculator → risk breaking existing logic

// ✅ OCP Fix — open for extension, closed for modification:
//      Define a DiscountStrategy interface
//      Each customer type is a new class (extension), not an edit

// ─────────────────────────────────────────────
// ❌ BAD: violates OCP — must modify this class to add any new discount type
// ─────────────────────────────────────────────

class BadDiscountCalculator
{
public:
    double calculate(const string &customerType, double price)
    {
        if (customerType == "Regular")
            return price;
        else if (customerType == "Premium")
            return price * 0.80; // 20% off
        else if (customerType == "VIP")
            return price * 0.60; // 40% off
        // ❌ Adding "Student" → must come in here and edit this method
        return price;
    }
};

// ─────────────────────────────────────────────
// ✅ GOOD: open for extension, closed for modification
// ─────────────────────────────────────────────

class DiscountStrategy
{
public:
    virtual double apply(double price) const = 0;
    virtual string label() const = 0;
    virtual ~DiscountStrategy() {}
};

class RegularDiscount : public DiscountStrategy
{
public:
    double apply(double price) const override { return price; }
    string label() const override { return "Regular (0% off)"; }
};

class PremiumDiscount : public DiscountStrategy
{
public:
    double apply(double price) const override { return price * 0.80; }
    string label() const override { return "Premium (20% off)"; }
};

class VIPDiscount : public DiscountStrategy
{
public:
    double apply(double price) const override { return price * 0.60; }
    string label() const override { return "VIP (40% off)"; }
};

// ✅ New requirement: Student discount — zero modification to existing classes
class StudentDiscount : public DiscountStrategy
{
public:
    double apply(double price) const override { return price * 0.85; }
    string label() const override { return "Student (15% off)"; }
};

// The calculator never changes — it works with any DiscountStrategy
class DiscountCalculator
{
public:
    double calculate(const DiscountStrategy &strategy, double price)
    {
        return strategy.apply(price);
    }
};

int main()
{
    double basePrice = 100.0;

    cout << "--- ❌ OCP Violation ---\n";
    BadDiscountCalculator bad;
    cout << "Regular : $" << bad.calculate("Regular", basePrice) << "\n";
    cout << "Premium : $" << bad.calculate("Premium", basePrice) << "\n";
    cout << "VIP     : $" << bad.calculate("VIP", basePrice) << "\n";

    cout << "\n--- ✅ OCP Compliant ---\n";
    DiscountCalculator calc;
    vector<DiscountStrategy *> strategies = {
        new RegularDiscount(),
        new PremiumDiscount(),
        new VIPDiscount(),
        new StudentDiscount()
    };

    for (auto *s : strategies)
    {
        cout << s->label() << " → $" << calc.calculate(*s, basePrice) << "\n";
        delete s;
    }

    return 0;
}
