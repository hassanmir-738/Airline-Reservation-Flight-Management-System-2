#pragma once
// ============================================================
// EconomyPassenger.h — Derived from Passenger (Single Inheritance)
// OOP Concepts: Single Inheritance, Function Overriding,
//               Hierarchical Inheritance (part of Passenger hierarchy)
// ============================================================

#include "Passenger.h"

// EconomyPassenger — lowest tier with basic benefits
class EconomyPassenger : public Passenger {
public:
    // Constructor — calls base Passenger constructor
    EconomyPassenger(const std::string& passengerID, const std::string& name,
                     const std::string& email, const std::string& phone);

    // ---- FUNCTION OVERRIDING ----
    double getBaggageAllowance() const override;
    double getLoyaltyMultiplier() const override;
    double getRefundPercentage(int daysBeforeDeparture) const override;
    std::string getPassengerClass() const override;

    // ---- FILE HANDLING ----
    void saveToFile(std::ofstream& ofs) const override;
};
