#pragma once
#include "ParkingSpot.h"
#include <vector>

class ParkingSpotStrategy
{
public:
    virtual ParkingSpot *findAvailableSpot(std::vector<ParkingSpot *> &spots) = 0;
    virtual ~ParkingSpotStrategy() {}
};

class FirstAvailableSpotStrategy : public ParkingSpotStrategy
{
public:
    ParkingSpot *findAvailableSpot(std::vector<ParkingSpot *> &spots) override
    {
        for (auto spot : spots)
        {
            if (!spot->isOccupied)
                return spot;
        }
        return nullptr;
    }
};

class ParkingSpotManager
{
protected:
    std::vector<ParkingSpot *> spots;
    ParkingSpotStrategy *strategy;

public:
    ParkingSpotManager(ParkingSpotStrategy *strategy) : strategy(strategy) {}

    void addSpot(ParkingSpot *spot) { spots.push_back(spot); }

    virtual ParkingSpot *findAndPark(Vehicle *vehicle)
    {
        ParkingSpot *spot = strategy->findAvailableSpot(spots);
        if (spot)
            spot->ParkVehicle(vehicle);
        return spot;
    }

    void setStrategy(ParkingSpotStrategy *newStrategy) { strategy = newStrategy; }

    virtual ~ParkingSpotManager() {}
};

class TwoWheelerSpotManager : public ParkingSpotManager
{
public:
    TwoWheelerSpotManager(ParkingSpotStrategy *strategy) : ParkingSpotManager(strategy) {}
};

class FourWheelerSpotManager : public ParkingSpotManager
{
public:
    FourWheelerSpotManager(ParkingSpotStrategy *strategy) : ParkingSpotManager(strategy) {}
};
