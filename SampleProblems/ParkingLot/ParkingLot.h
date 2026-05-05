#pragma once
#include "ParkingEntrance.h"
#include "ParkingManagerFactory.h"
#include "ParkingExit.h"

class ParkingLot
{
    ParkingEntrance entrance;
    ParkingExit exit;
    ParkingSpotStrategy *strategy;
    ParkingSpotManager *twoWheelerMgr;
    ParkingSpotManager *fourWheelerMgr;

public:
    ParkingLot() : exit(new HourlyPricingStrategy())
    {
        strategy = new FirstAvailableSpotStrategy();

        TwoWheelerParkingManagerFactory twoFactory;
        FourWheelerParkingManagerFactory fourFactory;

        twoWheelerMgr = twoFactory.createParkingManager(strategy);
        fourWheelerMgr = fourFactory.createParkingManager(strategy);

        entrance.registerManager(VehicleType::TwoWheeler, twoWheelerMgr);
        entrance.registerManager(VehicleType::FourWheeler, fourWheelerMgr);
    }

    void addTwoWheelerSpot() { twoWheelerMgr->addSpot(new TwoWheelerParkingSpot()); }
    void addFourWheelerSpot() { fourWheelerMgr->addSpot(new FourWheelerParkingSpot()); }

    // Change strategy for all vehicle types at once
    void setStrategy(ParkingSpotStrategy *newStrategy)
    {
        twoWheelerMgr->setStrategy(newStrategy);
        fourWheelerMgr->setStrategy(newStrategy);
    }

    // Change strategy for a specific vehicle type only
    void setStrategy(VehicleType vehicleType, ParkingSpotStrategy *newStrategy)
    {
        if (vehicleType == VehicleType::TwoWheeler)
            twoWheelerMgr->setStrategy(newStrategy);
        else if (vehicleType == VehicleType::FourWheeler)
            fourWheelerMgr->setStrategy(newStrategy);
    }

    Ticket *vehicleEntry(Vehicle *vehicle) { return entrance.vehicleEntry(vehicle); }

    Receipt vehicleExit(Ticket *ticket) { return exit.vehicleExit(ticket); }

    void setPricingStrategy(PricingStrategy *newStrategy) { exit.setPricingStrategy(newStrategy); }
};
