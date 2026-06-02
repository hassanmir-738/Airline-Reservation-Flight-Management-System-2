// ============================================================
// InternationalFlight.cpp — Implementation of InternationalFlight
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor chaining, File Handling (ofstream)
// ============================================================

#include "InternationalFlight.h"
#include <iostream>

// Constructor — initializes base Flight and international-specific fields
InternationalFlight::InternationalFlight(const std::string& flightNumber,
                                         const std::string& origin,
                                         const std::string& destination,
                                         const std::string& dateTime,
                                         int totalSeats, int availableSeats,
                                         double baseFare, double internationalTax,
                                         bool visaRequired)
    : Flight(flightNumber, origin, destination, dateTime, totalSeats, availableSeats),
      baseFare(baseFare), internationalTax(internationalTax), visaRequired(visaRequired) {
    // Base constructor handles common fields; derived handles its own
}

// Function Overriding — international fare includes international tax
double InternationalFlight::calculateBaseFare() const {
    return baseFare * (1 + internationalTax);  // e.g. 15000 * 1.12 = 16800
}

// Function Overriding — prints all info including visa and international tax
void InternationalFlight::displayDetails() const {
    std::cout << "\n===== International Flight Details =====\n"
              << "Flight Number     : " << flightNumber << "\n"
              << "Type              : International\n"
              << "Route             : " << origin << " -> " << destination << "\n"
              << "Departure         : " << departureDateTime << "\n"
              << "Total Seats       : " << totalSeats << "\n"
              << "Available         : " << availableSeats << "\n"
              << "Base Fare         : " << baseFare << "\n"
              << "International Tax : " << (internationalTax * 100) << "%\n"
              << "Final Fare        : " << calculateBaseFare() << "\n"
              << "Visa Required     : " << (visaRequired ? "Yes" : "No") << "\n"
              << "========================================\n";
}

// Function Overriding — type identifier
std::string InternationalFlight::getType() const {
    return "International";
}

// File Handling — writes to output stream with type tag 'I'
void InternationalFlight::saveToFile(std::ofstream& ofs) const {
    ofs << "I" << "\n"
        << flightNumber << "\n"
        << origin << "\n"
        << destination << "\n"
        << departureDateTime << "\n"
        << totalSeats << "\n"
        << availableSeats << "\n"
        << baseFare << "\n"
        << internationalTax << "\n"
        << visaRequired << "\n";   // 1 for true, 0 for false
}
