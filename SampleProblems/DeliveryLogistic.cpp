#include <iostream>
#include <string>
using namespace std;

// 🧾 Problem Statement: Logistics Delivery System
// Design a system for a logistics company that delivers packages using different transport methods.

// 🎯 Requirements
// The system should support multiple delivery types:
//      Road Delivery (Truck)
//      Sea Delivery (Ship)
//      Air Delivery (Airplane)
// Each delivery type has:
//      Its own way of transporting
//      Its own cost calculation logic
// The client code should:
//      Not know which concrete class is being used
//      Only work with a common interface
// The system should:
//      Be easily extendable (e.g., Drone delivery later)
//      Avoid if-else or switch for object creation

class TransportInterface
{
public:
    virtual void deliver() = 0;
    virtual double getCost() = 0;
};

class RoadTransport : public TransportInterface
{
public:
    void deliver() override
    {
        cout << "[Truck Delivery]" << endl;
    }
    double getCost() override
    {
        return 20.44;
    }
};

class SeaTransport : public TransportInterface
{
public:
    void deliver() override
    {
        cout << "[Ship Delivery]" << endl;
    }
    double getCost() override
    {
        return 87.455;
    }
};

class AirTransport : public TransportInterface
{
public:
    void deliver() override
    {
        cout << "[Airplane Delivery]" << endl;
    }
    double getCost() override
    {
        return 98.435;
    }
};

class TransportFactory
{
public:
    virtual TransportInterface *getTransport() = 0;
    void deliverPackage()
    {
        TransportInterface *transport = getTransport();
        transport->deliver();
        cout << "Cost: $" << transport->getCost() << endl;
        delete transport; // Clean up
    }
};

class RoadTransportFactory : public TransportFactory
{
public:
    TransportInterface *getTransport() override
    {
        return new RoadTransport();
    }
};

class SeaTransportFactory : public TransportFactory
{
public:
    TransportInterface *getTransport() override
    {
        return new SeaTransport();
    }
};

class AirTransportFactory : public TransportFactory
{
public:
    TransportInterface *getTransport() override
    {
        return new AirTransport();
    }
};

int main()
{
    TransportFactory *f1 = new RoadTransportFactory();
    f1->deliverPackage();

    TransportFactory *f2 = new SeaTransportFactory();
    f2->deliverPackage();

    TransportFactory *f3 = new AirTransportFactory();
    f3->deliverPackage();

    delete f1;
    delete f2;
    delete f3;

    return 0;
}