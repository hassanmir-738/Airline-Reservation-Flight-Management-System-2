// ============================================================
// BusinessPassenger.cpp — Implementation of BusinessPassenger
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor chaining, File Handling
// ============================================================

#include "BusinessPassenger.h"

// Constructor — delegates to base Passenger constructor
BusinessPassenger::BusinessPassenger(const std::string& passengerID,
                                     const std::string& name,
                                     const std::string& email,
                                     const std::string& phone)
    : Passenger(passengerID, name, email, phone) {
    // Business passengers get enhanced benefits
}

// Function Overriding — business class gets 35kg baggage
double BusinessPassenger::getBaggageAllowance() const {
    return 35.0;  // 35 kg baggage allowance
}

// Function Overriding — 1.5x loyalty multiplier
double BusinessPassenger::getLoyaltyMultiplier() const {
    return 1.5;  // 50% bonus loyalty points
}

// Function Overriding — business refund policy (moderate)
// 7+ days: 75%, 3-6 days: 50%, <3 days: 25%
double BusinessPassenger::getRefundPercentage(int daysBeforeDeparture) const {
    if (daysBeforeDeparture >= 7) {
        return 0.75;  // 75% refund for 7+ days
    } else if (daysBeforeDeparture >= 3) {
        return 0.5;   // 50% refund for 3-6 days
    } else {
        return 0.25;  // 25% refund for less than 3 days
    }
}

// Function Overriding — returns class identifier
std::string BusinessPassenger::getPassengerClass() const {
    return "Business";
}

// File Handling — writes business passenger data with type tag 'B'
void BusinessPassenger::saveToFile(std::ofstream& ofs) const {
    ofs << "B" << "\n"
        << passengerID << "\n"
        << name << "\n"
        << email << "\n"
        << phone << "\n"
        << bookingHistory.size() << "\n";
    for (const auto& tid : bookingHistory) {
        ofs << tid << "\n";
    }
}
