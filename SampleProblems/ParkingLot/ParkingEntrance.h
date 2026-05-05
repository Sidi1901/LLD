#pragma once
#include "Ticket.h"
#include "ParkingSpotManager.h"
#include <map>

class ParkingEntrance
{
    std::map<VehicleType, ParkingSpotManager *> managers;

public:
    void registerManager(VehicleType vehicleType, ParkingSpotManager *manager)
    {
        managers[vehicleType] = manager;
    }

    // Returns a Ticket on success, nullptr if no manager or no spot available
    Ticket *vehicleEntry(Vehicle *vehicle)
    {
        auto it = managers.find(vehicle->getType());
        if (it == managers.end())
            return nullptr;

        ParkingSpot *spot = it->second->findAndPark(vehicle);
        if (!spot)
            return nullptr;

        return new Ticket(vehicle, spot);
    }
};
