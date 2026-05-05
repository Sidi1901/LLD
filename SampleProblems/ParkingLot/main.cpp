#include <iostream>
#include <windows.h>
#include "ParkingLot.h"

void printTicket(Ticket *ticket)
{
    if (!ticket)
    {
        std::cout << "  [DENIED] No available spot.\n";
        return;
    }
    std::cout << "  [TICKET] Vehicle: " << ticket->vehicle->vehicleNumber
              << " | Spot ID: " << ticket->spot->getId()
              << " | Price/hr: " << ticket->spot->pricePerHour << "\n";
}

void printReceipt(const Receipt &r)
{
    std::cout << "  [RECEIPT] Vehicle: " << r.vehicleNumber
              << " | Spot: " << r.spotId
              << " | Hours: " << r.hours
              << " | Total: Rs." << r.totalCost << "\n";
}

int main()
{
    ParkingLot lot;
    lot.addTwoWheelerSpot();
    lot.addTwoWheelerSpot();
    lot.addFourWheelerSpot();
    lot.addFourWheelerSpot();

    // Test 1: Normal entry and exit (hourly pricing)
    std::cout << "=== Test 1: Entry and exit with hourly pricing ===\n";
    Ticket *t1 = lot.vehicleEntry(new TwoWheeler("MH01AB1111"));
    printTicket(t1);
    Sleep(1000 * 2); // Simulate 2 seconds of parking
    Receipt r1 = lot.vehicleExit(t1);
    printReceipt(r1);

    Ticket *t2 = lot.vehicleEntry(new FourWheeler("MH02CD3333"));
    printTicket(t2);
    Sleep(1000 * 5); // Simulate 5 seconds of parking
    Receipt r2 = lot.vehicleExit(t2);
    printReceipt(r2);

    // Test 2: Lot full
    std::cout << "\n=== Test 2: Lot full (two-wheeler) ===\n";
    Ticket *t3 = lot.vehicleEntry(new TwoWheeler("MH01AB2222"));
    printTicket(t3);
    Ticket *t4 = lot.vehicleEntry(new TwoWheeler("MH01AB3333")); // spot freed after t1 exit
    printTicket(t4);
    Ticket *t5 = lot.vehicleEntry(new TwoWheeler("MH01AB9999")); // should be denied
    printTicket(t5);

    // Test 3: Swap to flat rate pricing at runtime
    std::cout << "\n=== Test 3: Exit with flat rate pricing (Rs.50) ===\n";
    lot.setPricingStrategy(new FlatRatePricingStrategy(50.0));
    Receipt r4 = lot.vehicleExit(t3);
    printReceipt(r4);

    // Test 4: Swap to minimum 1 hour pricing
    std::cout << "\n=== Test 4: Exit with minimum 1-hour pricing ===\n";
    lot.setPricingStrategy(new MinimumOneHourPricingStrategy());
    Ticket *t6 = lot.vehicleEntry(new FourWheeler("MH04GH8888"));
    printTicket(t6);
    Sleep(1000 * 3); // Simulate 3 seconds of parking
    Receipt r6 = lot.vehicleExit(t6);
    printReceipt(r6);

    // Test 5: Unknown vehicle type
    std::cout << "\n=== Test 5: Unknown vehicle type ===\n";
    class HeavyVehicle : public Vehicle
    {
    public:
        HeavyVehicle(std::string n) : Vehicle(n) {}
        VehicleType getType() const override { return VehicleType::HeavyVehicle; }
    };
    Ticket *t7 = lot.vehicleEntry(new HeavyVehicle("MH03EF7777"));
    printTicket(t7);

    return 0;
}
