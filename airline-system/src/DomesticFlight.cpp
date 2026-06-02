// ============================================================
// DomesticFlight.cpp — Implementation of DomesticFlight
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor calling base constructor,
//               File Handling (ofstream writing)
// ============================================================

#include "DomesticFlight.h"
#include <iostream>

// Constructor — uses initializer list to call base Flight constructor first
// Demonstrates: Constructor chaining in inheritance
DomesticFlight::DomesticFlight(const std::string& flightNumber, const std::string& origin,
                               const std::string& destination, const std::string& dateTime,
                               int totalSeats, int availableSeats,
                               double baseFare, double taxRate)
    : Flight(flightNumber, origin, destination, dateTime, totalSeats, availableSeats),
      baseFare(baseFare), taxRate(taxRate) {
    // Base class constructor initializes common fields
    // Derived class initializes its own extra fields
}

// Function Overriding — provides domestic-specific fare calculation
// Returns base fare plus tax
double DomesticFlight::calculateBaseFare() const {
    return baseFare * (1 + taxRate);  // e.g. 5000 * 1.05 = 5250
}

// Function Overriding — displays all flight details including domestic-specific info
void DomesticFlight::displayDetails() const {
    std::cout << "\n===== Domestic Flight Details =====\n"
              << "Flight Number : " << flightNumber << "\n"
              << "Type          : Domestic\n"
              << "Route         : " << origin << " -> " << destination << "\n"
              << "Departure     : " << departureDateTime << "\n"
              << "Total Seats   : " << totalSeats << "\n"
              << "Available     : " << availableSeats << "\n"
              << "Base Fare     : " << baseFare << "\n"
              << "Tax Rate      : " << (taxRate * 100) << "%\n"
              << "Final Fare    : " << calculateBaseFare() << "\n"
              << "==================================\n";
}

// Function Overriding — returns type string for identification
std::string DomesticFlight::getType() const {
    return "Domestic";
}

// File Handling — writes domestic flight data to output file stream
// Format: type tag 'D', then base fields, then taxRate, then baseFare
void DomesticFlight::saveToFile(std::ofstream& ofs) const {
    ofs << "D" << "\n"                    // Type tag for loading
        << flightNumber << "\n"
        << origin << "\n"
        << destination << "\n"
        << departureDateTime << "\n"
        << totalSeats << "\n"
        << availableSeats << "\n"
        << baseFare << "\n"
        << taxRate << "\n";
}
