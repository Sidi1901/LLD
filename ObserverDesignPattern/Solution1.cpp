#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ObserverInterface
{
public:
    virtual void update() = 0; // Pure virtual function to be implemented by concrete observers
};

class ObservableInterface
{
public:
    virtual void addObserver(class ObserverInterface *observer) = 0;    // Pure virtual function to add an observer
    virtual void removeObserver(class ObserverInterface *observer) = 0; // Pure virtual function to remove an observer
    virtual void notifyObservers() = 0;                                 // Pure virtual function to notify all observers of a change
};

class WeatherStation : public ObservableInterface
{
    int temperature;                       // Example of a state that observers might be interested in,
    vector<ObserverInterface *> observers; // List of observers subscribed to this weather station

public:
    WeatherStation() : temperature(0) {}
    void setTemperature(int temp)
    {
        temperature = temp;
        notifyObservers();
    }
    void addObserver(ObserverInterface *observer) override
    {
        observers.push_back(observer);
    }
    void removeObserver(ObserverInterface *observer) override
    {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }
    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }
    int getTemperature() const
    {
        return temperature;
    }
};

class WeatherDisplay : public ObserverInterface
{
    WeatherStation &station; // Reference to the weather station being observed
public:
    WeatherDisplay(WeatherStation &ws) : station(ws)
    {
        station.addObserver(this); // Register itself as an observer to the weather station
    }
    void update() override
    {
        cout << "Weather Display: Temperature updated to " << station.getTemperature() << " degrees.\n"; // Get the updated temperature from the weather station and display it
    }
};

int main()
{
    WeatherStation station;          // Create a weather station
    WeatherDisplay display(station); // Create a weather display that observes the weather station

    station.setTemperature(25); // Update the temperature, which will trigger the display to update
    station.setTemperature(30); // Update the temperature again, demonstrating that the observer is notified of changes

    return 0;
}