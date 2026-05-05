/*
🧩 Problem: Dynamic Pricing Engine for an E-commerce Platform
📖 Context

You’re building the pricing module for an e-commerce checkout system.

Different types of discounts can be applied to the cart:

Seasonal Discount (e.g., 10% off)
Coupon Discount (flat ₹500 off)
Premium User Discount (%20 off)
Flash Sale Discount (time-based dynamic pricing) (optional for pratice)

EXPECTED ANSWER
================

double cartTotal = 2000;

PricingEngine engine;

DiscountStrategy* strategy = new CouponDiscount();
double finalPrice = engine.calculatePrice(cartTotal, strategy);

cout << "Final Price: " << finalPrice << endl;
*/

/*
classes
PricingEngine // concrete class
DiscountStrategy // interface
CouponDiscount  // concrete class
SeasonalDiscount // concrete class
PremiumUserDisount // concrete class
FlashSaleDiscount // concrete class
*/
#include <bits/stdc++.h>

using namespace std;

class DiscountStrategy{
    public:
    virtual double calculateDiscount(double cartTotal) = 0;
    virtual ~DiscountStrategy() = default;
};

class CouponDiscount : public DiscountStrategy{
    
    public:
        double calculateDiscount(double cartTotal) override{
            return 500;
        }

};

class SeasonalDiscount : public DiscountStrategy{
    public:
        double calculateDiscount(double cartTotal) override{
            return cartTotal/10;
        }
};

class PremiumUserDisount : public DiscountStrategy{
    public:
        double calculateDiscount(double cartTotal) override{
            return cartTotal/5;
        }
};

class PricingEngine{

    public:

    double calculatePrice(double cartTotal, DiscountStrategy *strategy){
        return cartTotal - strategy->calculateDiscount(cartTotal);
    }
};


//Client code

int main(){
    double cartTotal = 2000;

    PricingEngine engine;

    DiscountStrategy* strategy = new CouponDiscount();
    double finalPrice = engine.calculatePrice(cartTotal, strategy);

    cout << "Final Price: " << finalPrice << endl;
}






