#pragma once
#include "Vehicle.h"
#include "ParkingSpot.h"
#include <chrono>

class Ticket
{
public:
    double entryTime;
    Vehicle *vehicle;
    ParkingSpot *spot;
    Ticket(Vehicle *v, ParkingSpot *s) : vehicle(v), spot(s)
    {
        // YYYY-MM-DD HH:MM:SS
        entryTime = std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    }
};