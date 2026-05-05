#pragma once
#include "Vehicle.h"

class ParkingSpot
{
private:
    static int nextId; // shared counter across all instances
    int id;            // unique ID per instance

public:
    bool isOccupied;
    double pricePerHour;
    Vehicle *parkedVehicle;

    ParkingSpot(double price) : pricePerHour(price)
    {
        id = ++nextId;
        isOccupied = false;
    }

    int getId()
    {
        return id;
    }
    void ParkVehicle(Vehicle *vehicle)
    {
        isOccupied = true;
        parkedVehicle = vehicle;
    }

    void RemoveVehicle()
    {
        isOccupied = false;
        parkedVehicle = nullptr;
    }
};

int ParkingSpot::nextId = 0;

class TwoWheelerParkingSpot : public ParkingSpot
{
public:
    TwoWheelerParkingSpot() : ParkingSpot(10.0) {}
};

class FourWheelerParkingSpot : public ParkingSpot
{
public:
    FourWheelerParkingSpot() : ParkingSpot(20.0) {}
};