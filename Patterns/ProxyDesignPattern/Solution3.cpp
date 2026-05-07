#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

// Logging Proxy — intercept every call to the real object and record it
// transparently. The client and the real object are unaware of the logging.
// Example: a payment service where every transaction must be audited.

class PaymentService
{
public:
    virtual bool pay(const string &recipient, double amount) = 0;
    virtual double getBalance() = 0;
    virtual ~PaymentService() = default;
};

class RealPaymentService : public PaymentService
{
    double balance;

public:
    RealPaymentService(double initialBalance) : balance(initialBalance) {}

    bool pay(const string &recipient, double amount) override
    {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }

    double getBalance() override
    {
        return balance;
    }
};

// ─── Logger helper ────────────────────────────────────────────────────────────

static string timestamp()
{
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    char buf[20];
    strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));
    return string(buf);
}

// ─── Logging Proxy ────────────────────────────────────────────────────────────

class LoggingPaymentProxy : public PaymentService
{
    PaymentService *real;

    void log(const string &msg) const
    {
        cout << "[" << timestamp() << "] " << msg << "\n";
    }

public:
    LoggingPaymentProxy(PaymentService *service) : real(service) {}

    bool pay(const string &recipient, double amount) override
    {
        log("pay() called — recipient: " + recipient +
            ", amount: $" + to_string(amount));

        bool result = real->pay(recipient, amount);

        log("pay() returned — " + string(result ? "SUCCESS" : "FAILED (insufficient funds)") +
            " | new balance: $" + to_string(real->getBalance()));

        return result;
    }

    double getBalance() override
    {
        log("getBalance() called");
        double balance = real->getBalance();
        log("getBalance() returned $" + to_string(balance));
        return balance;
    }

    ~LoggingPaymentProxy()
    {
        delete real;
    }
};

int main()
{
    PaymentService *service = new LoggingPaymentProxy(
        new RealPaymentService(500.0)
    );

    service->getBalance();
    service->pay("Alice", 120.0);
    service->pay("Bob", 450.0);   // should fail — insufficient funds
    service->pay("Carol", 300.0);
    service->getBalance();

    delete service;
    return 0;
}

/*
Why a proxy instead of editing RealPaymentService directly?

1. Open/Closed — RealPaymentService is closed for modification.
   Add logging by wrapping, not by editing.

2. Single Responsibility — the real object handles payments;
   the proxy handles audit logging. They change for different reasons.

3. Stackable — you can chain proxies:
       client → LoggingProxy → CachingProxy → RealService
   Each layer adds one concern without knowing about the others.

4. Toggle logging at runtime — swap the proxy in/out without touching
   any other code.
*/
