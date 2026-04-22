#include <bits/stdc++.h>
using namespace std;

class Observer
{
public:
    virtual void update(const string &productName, int stock) = 0;
    virtual ~Observer() = default;
};

class Observable
{
public:
    virtual void addObserver(Observer *obs) = 0;
    virtual void removeObserver(Observer *obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Observable() = default;
};

class EmailObserver : public Observer
{
    string email;

public:
    EmailObserver(const string &email) : email(email) {}
    void update(const string &productName, int stock) override
    {
        cout << "[Email -> " << email << "] " << productName
             << " is back in stock! Available: " << stock << "\n";
    }
};

class MobileObserver : public Observer
{
    string phoneNumber;

public:
    MobileObserver(const string &phoneNumber) : phoneNumber(phoneNumber) {}
    void update(const string &productName, int stock) override
    {
        cout << "[Mobile -> " << phoneNumber << "] " << productName
             << " is back in stock! Available: " << stock << "\n";
    }
};

class NotificationObserver : public Observer
{
    string username;

public:
    NotificationObserver(const string &username) : username(username) {}
    void update(const string &productName, int stock) override
    {
        cout << "[Notification -> " << username << "] " << productName
             << " is back in stock! Available: " << stock << "\n";
    }
};

class IPhoneStockObservable : public Observable
{
    vector<Observer *> observers;
    string productName;
    int stock = 0; // Initial stock is 0 (out of stock)

public:
    IPhoneStockObservable(const string &productName) : productName(productName) {}

    void addObserver(Observer *obs) override
    {
        observers.push_back(obs);
    }

    void removeObserver(Observer *obs) override
    {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override
    {
        for (Observer *obs : observers)
            obs->update(productName, stock);
    }

    void setStock(int newStock)
    {
        bool wasOutOfStock = (stock == 0);
        stock = newStock;
        if (wasOutOfStock && stock > 0)
            notifyObservers();
    }

    int getStock() const { return stock; }
};

int main()
{
    IPhoneStockObservable iphone16("iPhone 16");

    EmailObserver email1("alice@gmail.com");
    EmailObserver email2("bob@gmail.com");
    MobileObserver mobile1("+91-9876543210");
    NotificationObserver notif1("charlie_app");

    iphone16.addObserver(&email1);
    iphone16.addObserver(&email2);
    iphone16.addObserver(&mobile1);
    iphone16.addObserver(&notif1);

    cout << "Setting stock to 0 (no notification expected):\n";
    iphone16.setStock(0);

    cout << "\nSetting stock to 10 (all observers notified):\n";
    iphone16.setStock(10);

    cout << "\nSetting stock to 5 (already in stock, no notification):\n";
    iphone16.setStock(5);

    cout << "\nRemoving mobile observer, setting stock to 0 then 3:\n";
    iphone16.removeObserver(&mobile1);
    iphone16.setStock(0);
    iphone16.setStock(3);

    return 0;
}
