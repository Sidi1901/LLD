#include <iostream>
#include <string>
using namespace std;

class Notification
{
public:
    virtual void send(const string &message) = 0; // Pure virtual function to be implemented by concrete notification types
};

class EmailNotification : public Notification
{
public:
    void send(const string &message) override
    {
        cout << "Sending email: " << message << "\n";
    }
};

class SMSNotification : public Notification
{
public:
    void send(const string &message) override
    {
        cout << "Sending SMS: " << message << "\n";
    }
};

class PushNotification : public Notification
{
public:
    void send(const string &message) override
    {
        cout << "Sending push notification: " << message << "\n";
    }
};

class NotificationFactory
{
public:
    // static means we can call this method without creating an instance of NotificationFactory. It belongs to the class, not to any object.
    static Notification *createNotification(const string &type)
    {
        if (type == "email")
        {
            return new EmailNotification();
        }
        else if (type == "sms")
        {
            return new SMSNotification();
        }
        else if (type == "push")
        {
            return new PushNotification();
        }
        return nullptr;
    }
};

int main()
{
    Notification *n1 = NotificationFactory::createNotification("email");
    n1->send("Hello via Email!");

    Notification *n2 = NotificationFactory::createNotification("sms");
    n2->send("Hello via SMS!");

    Notification *n3 = NotificationFactory::createNotification("push");
    n3->send("Hello via Push Notification!");

    delete n1;
    delete n2;
    delete n3;
    return 0;
}