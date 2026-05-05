#pragma once
#include <string>

enum class VehicleType
{
    TwoWheeler,
    FourWheeler,
    HeavyVehicle
};

class Vehicle
{
public:
    std::string vehicleNumber;
    Vehicle(std::string number) : vehicleNumber(number) {}

    virtual VehicleType getType() const = 0;
    virtual ~Vehicle() {}
};

class TwoWheeler : public Vehicle
{
public:
    TwoWheeler(std::string number) : Vehicle(number) {}
    VehicleType getType() const override { return VehicleType::TwoWheeler; }
};

class FourWheeler : public Vehicle
{
public:
    FourWheeler(std::string number) : Vehicle(number) {}
    VehicleType getType() const override { return VehicleType::FourWheeler; }
};