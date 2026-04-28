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
    virtual Notification *createNotification() = 0; // Pure virtual function to be implemented by concrete factories
    void sendNotification(const string &message)
    {
        Notification *notification = createNotification(); // Create a notification using the factory method
        notification->send(message);                       // Send the notification
        delete notification;                               // Clean up memory
    }
};

class EmailNotificationFactory : public NotificationFactory
{
public:
    Notification *createNotification() override
    {
        return new EmailNotification();
    }
};

class SMSNotificationFactory : public NotificationFactory
{
public:
    Notification *createNotification() override
    {
        return new SMSNotification();
    }
};

class PushNotificationFactory : public NotificationFactory
{
public:
    Notification *createNotification() override
    {
        return new PushNotification();
    }
};

int main()
{
    NotificationFactory *factory1 = new EmailNotificationFactory();
    factory1->sendNotification("Hello via Email!");

    NotificationFactory *factory2 = new SMSNotificationFactory();
    factory2->sendNotification("Hello via SMS!");

    NotificationFactory *factory3 = new PushNotificationFactory();
    Notification *notification3 = factory3->createNotification();
    notification3->send("Hello via Push Notification!");

    delete factory1;
    delete factory2;
    delete notification3;
    delete factory3;

    return 0;
}
