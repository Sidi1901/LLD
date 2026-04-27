#include <iostream>
#include <string>
using namespace std;

class RouteStrategy
{
public:
    // it is a pure virtual function, so this class is abstract and cannot be instantiated.
    // It defines the interface for all route strategies.
    virtual void buildRoute(const string &from, const string &to) = 0;
};

class DrivingStrategy : public RouteStrategy
{
public:
    void buildRoute(const string &from, const string &to) override
    {
        cout << "[Driving]  fastest road route from "
             << from << " to " << to << "\n";
    }
};

class WalkingStrategy : public RouteStrategy
{
public:
    void buildRoute(const string &from, const string &to) override
    {
        cout << "[Walking]  shortest footpath from "
             << from << " to " << to << "\n";
    }
};

class CyclingStrategy : public RouteStrategy
{
public:
    void buildRoute(const string &from, const string &to) override
    {
        cout << "[Cycling]  bike-friendly route from "
             << from << " to " << to << "\n";
    }
};

class Navigator
{
public:
    RouteStrategy *strategy;                     // Pointer to the current route strategy
    Navigator(RouteStrategy *s) : strategy(s) {} // Constructor to set the initial strategy
    // Navigator(RouteStrategy *s){
    //     strategy = s;
    // }
    void setStrategy(RouteStrategy *s) // Method to change the strategy at runtime
    {
        strategy = s;
    }
    void buildRoute(const string &from, const string &to)
    {
        strategy->buildRoute(from, to);
    }
};

int main()
{
    Navigator nav1(new DrivingStrategy());
    nav1.buildRoute("Home", "Office");

    Navigator nav2(new WalkingStrategy());
    nav2.buildRoute("Hotel", "Museum");

    nav2.setStrategy(new DrivingStrategy()); // Switching strategy at runtime
    nav2.buildRoute("Hotel", "Museum");

    Navigator nav3(new CyclingStrategy());
    nav3.buildRoute("Park", "Beach");
}