/*🧩 Problem: Notification System
📖 Context

You are building a notification system that can send messages via different channels:

Email
SMS
Push Notification

EXPECTED CLIENT CODE
====================

NotificationFactory factory1 = new EmailNotificationFactory();
factory1->sendNotification("Hello via Email!");

NotificationFactoryfactory2 = new SMSNotificationFactory();
factory2->sendNotification("Hello via SMS!");
*/


#include <bits/stdc++.h>

using namespace std;

class Notification{
    public:
    virtual void send() = 0;
    virtual ~Notification() = default;
};

class Email : public Notification{
    public:
    void send() override {
        cout<<"Email is sent"<<endl;
    }
};

class SMS : public Notification{
    void send() override {
        cout<<"SMS is sent"<<endl;
    }
};

class PushNotifiction : public Notification{
    void send() override {
        cout<<"Pushed Notifiction"<<endl;
    }
};

class NotificationFactory{
    public:

    virtual Notification* createNotification() = 0;

    void sendNotification(){
        Notification* n1 = createNotification();
        n1->send();
        delete n1;
    }

    virtual ~NotificationFactory() = default; 
};

class EmailFactory : public NotificationFactory{
    
    public:
    Notification* createNotification(){
        return new Email();
    }

};

class SMSFactory : public NotificationFactory{
    Notification* createNotification(){
        return new SMS();
    }
};

class PushNotifictionFactory : public NotificationFactory{
    Notification* createNotification(){
        return new PushNotifiction();
    }

};


int main(){
    NotificationFactory *email = new EmailFactory();
    email->sendNotification();
};




