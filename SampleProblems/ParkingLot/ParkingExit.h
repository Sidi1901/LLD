#pragma once
#include "Ticket.h"
#include <chrono>

// Strategy: how to calculate cost — swap for flat rate, surge pricing, etc.
class PricingStrategy
{
public:
    virtual double calculateCost(double hours, double pricePerHour) = 0;
    virtual ~PricingStrategy() {}
};

class HourlyPricingStrategy : public PricingStrategy
{
public:
    double calculateCost(double hours, double pricePerHour) override
    {
        return hours * pricePerHour;
    }
};

class FlatRatePricingStrategy : public PricingStrategy
{
    double flatRate;

public:
    FlatRatePricingStrategy(double rate) : flatRate(rate) {}
    double calculateCost(double hours, double pricePerHour) override
    {
        return flatRate;
    }
};

// Minimum 1 hour, then hourly after that
class MinimumOneHourPricingStrategy : public PricingStrategy
{
public:
    double calculateCost(double hours, double pricePerHour) override
    {
        return (hours < 1.0 ? 1.0 : hours) * pricePerHour;
    }
};

struct Receipt
{
    std::string vehicleNumber;
    int spotId;
    double entryTime;
    double exitTime;
    double hours;
    double totalCost;
};

class ParkingExit
{
    PricingStrategy *pricingStrategy;

public:
    ParkingExit(PricingStrategy *strategy) : pricingStrategy(strategy) {}

    void setPricingStrategy(PricingStrategy *strategy) { pricingStrategy = strategy; }

    Receipt vehicleExit(Ticket *ticket)
    {
        double exitTime = std::chrono::duration_cast<std::chrono::seconds>(
                              std::chrono::system_clock::now().time_since_epoch())
                              .count();

        double hours = (exitTime - ticket->entryTime) / 3600.0;
        double cost = pricingStrategy->calculateCost(hours, ticket->spot->pricePerHour);

        ticket->spot->RemoveVehicle();

        return {ticket->vehicle->vehicleNumber,
                ticket->spot->getId(),
                ticket->entryTime,
                exitTime,
                hours,
                cost};
    }
};
