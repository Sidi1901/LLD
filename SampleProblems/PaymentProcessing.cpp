#include <iostream>
#include <string>
using namespace std;

// 🧾 Problem Statement: Payment Processing System

// Design a system where a user can pay using different payment methods.

// 🎯 Requirements
// A user should be able to choose a payment method at runtime:
//      Credit Card
//      UPI
//      PayPal
// Each payment method should have its own logic:
//      Credit Card → card number, CVV validation
//      UPI → UPI ID validation
//      PayPal → email-based processing
// The system should:
//      Allow switching payment method dynamically
//      Avoid if-else or switch for payment handling
//      Be easily extendable (e.g., add Crypto later)

class PaymentStrategy
{
protected:
    virtual void validate() = 0;

public:
    virtual void pay() = 0;
    virtual void refund() = 0;
    virtual ~PaymentStrategy() {}
};

class CreditCardPayment : public PaymentStrategy
{
    void validate() override
    {
        cout << "[Credit Card] Validating Card...\n";
    }
    void pay() override
    {
        validate();
        cout << "[Credit Card] Paying Using Credit Card \n";
    }
    void refund() override
    {
        cout << "[Credit Card] Refund Initiated...\n";
    }
};

class UPIPayment : public PaymentStrategy
{
    void validate() override
    {
        cout << "[UPI] Validating UPI...\n";
    }
    void pay() override
    {
        validate();
        cout << "[UPI] Paying Using UPI \n";
    }
    void refund() override
    {
        cout << "[UPI] Refund Initiated...\n";
    }
};

class PaypalPayment : public PaymentStrategy
{
    void validate() override
    {
        cout << "[Paypal] Validating Paypal...\n";
    }
    void pay() override
    {
        validate();
        cout << "[Paypal] Paying Using Paypal \n";
    }
    void refund() override
    {
        cout << "[Paypal] Refund Initiated...\n";
    }
};

class Payment
{
public:
    PaymentStrategy *strategy;
    Payment(PaymentStrategy *s) : strategy(s) {};
    void setPaymentStrategy(PaymentStrategy *s)
    {
        strategy = s;
    }
    void pay()
    {
        strategy->pay();
    }
    void refund()
    {
        strategy->refund();
    }
};

int main()
{
    Payment *p1 = new Payment(new CreditCardPayment());
    p1->pay();
    p1->setPaymentStrategy(new UPIPayment());
    p1->pay();
}