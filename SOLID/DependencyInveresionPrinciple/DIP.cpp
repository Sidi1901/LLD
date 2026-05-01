#include <iostream>
#include <string>
using namespace std;

// 🔔 Problem Statement: Notification System

// Design a system that sends notifications to users.

// ❌ DIP Violation — high-level module depends directly on low-level module:
//      NotificationService directly creates and uses EmailSender
//      Switching to SMS or Push requires modifying NotificationService

// ✅ DIP Fix — both high and low level modules depend on an abstraction:
//      Introduce INotifier interface
//      NotificationService depends on INotifier, not on any concrete sender
//      Concrete senders (Email, SMS, Push) depend on INotifier too
//      Swap any sender without touching NotificationService

// ─────────────────────────────────────────────
// ❌ BAD: high-level module depends directly on a low-level concrete class
// ─────────────────────────────────────────────

class BadEmailSender
{
public:
    void sendEmail(const string &message)
    {
        cout << "[Email] Sending: " << message << "\n";
    }
};

class BadNotificationService
{
    BadEmailSender sender; // ❌ hardwired to EmailSender — cannot swap without editing this class

public:
    void notify(const string &message)
    {
        sender.sendEmail(message);
    }
};

// ─────────────────────────────────────────────
// ✅ GOOD: both levels depend on an abstraction
// ─────────────────────────────────────────────

class INotifier
{
public:
    virtual void send(const string &message) = 0;
    virtual ~INotifier() {}
};

// Low-level modules depend on the abstraction
class EmailNotifier : public INotifier
{
public:
    void send(const string &message) override
    {
        cout << "[Email] " << message << "\n";
    }
};

class SMSNotifier : public INotifier
{
public:
    void send(const string &message) override
    {
        cout << "[SMS] " << message << "\n";
    }
};

class PushNotifier : public INotifier
{
public:
    void send(const string &message) override
    {
        cout << "[Push] " << message << "\n";
    }
};

// High-level module depends on the abstraction — not on any concrete sender
class NotificationService
{
    INotifier &notifier; // ✅ depends on interface, not implementation

public:
    NotificationService(INotifier &notifier) : notifier(notifier) {}

    void notify(const string &message)
    {
        notifier.send(message);
    }
};

int main()
{
    cout << "--- ❌ DIP Violation ---\n";
    BadNotificationService badService;
    badService.notify("Your order has been placed.");
    // ❌ to switch to SMS, we must go into BadNotificationService and change it

    cout << "\n--- ✅ DIP Compliant ---\n";
    EmailNotifier email;
    NotificationService emailService(email);
    emailService.notify("Your order has been placed.");

    SMSNotifier sms;
    NotificationService smsService(sms);
    smsService.notify("Your order has been placed.");

    PushNotifier push;
    NotificationService pushService(push);
    pushService.notify("Your order has been placed.");
    // ✅ NotificationService never changed — only the injected notifier differs

    return 0;
}
