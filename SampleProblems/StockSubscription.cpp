#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// 🎯 Requirements
// There is a Stock (e.g., Apple, Google).
// Users can:
//      Subscribe to a price
//      Unsubscribe from a price
// Whenever price price changes:
//      All subscribed users should be notified automatically
// Different types of observers:
//      Mobile App User (gets push notification)
//      Email User (gets email)
//      Web Dashboard (updates UI)
// The system should:
//      Support multiple stocks
//      Allow dynamic subscription/unsubscription
//      Avoid tight coupling between Stock and Users

class ObserverInterface
{
public:
    virtual void update(const string &productName, double price) = 0;
    virtual ~ObserverInterface() = default;
};

class SubjectInterface
{
public:
    virtual void subscribe(ObserverInterface *o) = 0;
    virtual void unsubscribe(ObserverInterface *o) = 0;
    virtual void notify() = 0;
    virtual ~SubjectInterface() = default;
};

class MobileAppObserver : public ObserverInterface
{
private:
    string user;

public:
    MobileAppObserver(const string &u) : user(u) {};
    void update(const string &productName, double price) override
    {
        cout << "[Updating mobile user]: " << user << " : " << productName << " - " << price << endl;
    }
};

class EmailUserObserver : public ObserverInterface
{
private:
    string email;

public:
    EmailUserObserver(const string &e) : email(e) {};
    void update(const string &productName, double price) override
    {
        cout << "[Updating Email user]: " << email << " : " << productName << " - " << price << endl;
    }
};

class WebDashboardObserver : public ObserverInterface
{
private:
    string user;

public:
    WebDashboardObserver(const string &u) : user(u) {};
    void update(const string &productName, double price) override
    {
        cout << "[Updating Webdashboard user]: " << user << " : " << productName << " - " << price << endl;
    }
};

class StockObservable : public SubjectInterface
{
private:
    string productName;
    double price;
    // vector<ObserverInterface *> subscribers;
    unordered_map<ObserverInterface *, bool> subscribers;

public:
    StockObservable(const string &p, double pr) : productName(p), price(pr) {};
    void subscribe(ObserverInterface *newObserver) override
    {
        subscribers[newObserver] = true;
    }

    void unsubscribe(ObserverInterface *obs) override
    {
        subscribers.erase(obs);
    }

    void notify() override
    {
        for (auto x : subscribers)
        {
            x.first->update(productName, price);
        }
    }

    void updateStock(int newStock)
    {
        price = newStock;
        notify();
    }
};

int main()
{
    StockObservable appleStock("Apple", 34.23);
    StockObservable bananaStock("Banana", 12.35);

    MobileAppObserver *o1 = new MobileAppObserver("Adarsh");
    appleStock.subscribe(o1);

    WebDashboardObserver *o2 = new WebDashboardObserver("Siddhi");
    bananaStock.subscribe(o2);

    EmailUserObserver *o3 = new EmailUserObserver("john@example.com");
    appleStock.subscribe(o3);

    // Simulate price updates
    appleStock.updateStock(35.00);
    bananaStock.updateStock(13.00);

    cout << "\n--- After Unsubscription ---\n";

    // Unsubscribe a user and update price again
    appleStock.unsubscribe(o1);
    appleStock.updateStock(36.00);

    delete o1;
    delete o2;
    delete o3;
}