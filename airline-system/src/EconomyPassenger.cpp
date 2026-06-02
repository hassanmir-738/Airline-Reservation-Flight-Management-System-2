// ============================================================
// EconomyPassenger.cpp — Implementation of EconomyPassenger
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor chaining, File Handling
// ============================================================

#include "EconomyPassenger.h"

// Constructor — delegates to base Passenger constructor
EconomyPassenger::EconomyPassenger(const std::string& passengerID,
                                   const std::string& name,
                                   const std::string& email,
                                   const std::string& phone)
    : Passenger(passengerID, name, email, phone) {
    // Economy passengers have the basic benefits
}

// Function Overriding — economy class gets 20kg baggage
double EconomyPassenger::getBaggageAllowance() const {
    return 20.0;  // 20 kg baggage allowance
}

// Function Overriding — no loyalty multiplier for economy
double EconomyPassenger::getLoyaltyMultiplier() const {
    return 1.0;  // Base multiplier (no bonus)
}

// Function Overriding — economy refund policy (least generous)
// 7+ days: 50%, 3-6 days: 25%, <3 days: 0%
double EconomyPassenger::getRefundPercentage(int daysBeforeDeparture) const {
    if (daysBeforeDeparture >= 7) {
        return 0.5;   // 50% refund if cancelled 7+ days before
    } else if (daysBeforeDeparture >= 3) {
        return 0.25;  // 25% refund for 3-6 days before
    } else {
        return 0.0;   // No refund for less than 3 days
    }
}

// Function Overriding — returns class identifier string
std::string EconomyPassenger::getPassengerClass() const {
    return "Economy";
}

// File Handling — writes economy passenger data with type tag 'E'
void EconomyPassenger::saveToFile(std::ofstream& ofs) const {
    ofs << "E" << "\n"             // Type tag for loading
        << passengerID << "\n"
        << name << "\n"
        << email << "\n"
        << phone << "\n"
        << bookingHistory.size() << "\n";  // Number of tickets in history
    // Write each ticket ID in booking history
    for (const auto& tid : bookingHistory) {
        ofs << tid << "\n";
    }
}
