// ============================================================
// FirstClassPassenger.cpp — Implementation of FirstClassPassenger
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor chaining, File Handling
// ============================================================

#include "FirstClassPassenger.h"

// Constructor — delegates to base Passenger constructor
FirstClassPassenger::FirstClassPassenger(const std::string& passengerID,
                                         const std::string& name,
                                         const std::string& email,
                                         const std::string& phone)
    : Passenger(passengerID, name, email, phone) {
    // First class passengers get premium benefits
}

// Function Overriding — first class gets maximum 50kg baggage
double FirstClassPassenger::getBaggageAllowance() const {
    return 50.0;  // 50 kg baggage allowance — highest tier
}

// Function Overriding — 2.0x loyalty multiplier (double points)
double FirstClassPassenger::getLoyaltyMultiplier() const {
    return 2.0;  // Double loyalty points
}

// Function Overriding — first class refund policy (most generous)
// 7+ days: 100%, 3-6 days: 75%, <3 days: 50%
double FirstClassPassenger::getRefundPercentage(int daysBeforeDeparture) const {
    if (daysBeforeDeparture >= 7) {
        return 1.0;   // 100% full refund for 7+ days
    } else if (daysBeforeDeparture >= 3) {
        return 0.75;  // 75% refund for 3-6 days
    } else {
        return 0.5;   // 50% refund even for last-minute cancellation
    }
}

// Function Overriding — returns class identifier
std::string FirstClassPassenger::getPassengerClass() const {
    return "FirstClass";
}

// File Handling — writes first class passenger data with type tag 'F'
void FirstClassPassenger::saveToFile(std::ofstream& ofs) const {
    ofs << "F" << "\n"
        << passengerID << "\n"
        << name << "\n"
        << email << "\n"
        << phone << "\n"
        << bookingHistory.size() << "\n";
    for (const auto& tid : bookingHistory) {
        ofs << tid << "\n";
    }
}
