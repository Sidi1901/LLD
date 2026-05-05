#pragma once
#include "ParkingSpotManager.h"

class ParkingManagerFactory
{
public:
    virtual ParkingSpotManager *createParkingManager(ParkingSpotStrategy *strategy) = 0;
    virtual ~ParkingManagerFactory() = default;
};

class TwoWheelerParkingManagerFactory : public ParkingManagerFactory
{
public:
    ParkingSpotManager *createParkingManager(ParkingSpotStrategy *strategy) override
    {
        // Implementation for creating a two-wheeler parking manager
        return new TwoWheelerSpotManager(strategy);
    }
};

class FourWheelerParkingManagerFactory : public ParkingManagerFactory
{
public:
    ParkingSpotManager *createParkingManager(ParkingSpotStrategy *strategy) override
    {
        // Implementation for creating a four-wheeler parking manager
        return new FourWheelerSpotManager(strategy);
    }
};