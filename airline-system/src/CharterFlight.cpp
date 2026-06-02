// ============================================================
// CharterFlight.cpp — Implementation of CharterFlight
// OOP Concepts: Single Inheritance, Function Overriding,
//               Constructor chaining, File Handling (ofstream)
// ============================================================

#include "CharterFlight.h"
#include <iostream>

// Constructor — calls base Flight constructor, then initializes charter-specific fields
CharterFlight::CharterFlight(const std::string& flightNumber, const std::string& origin,
                             const std::string& destination, const std::string& dateTime,
                             int totalSeats, int availableSeats,
                             double charterFee, const std::string& contractHolder)
    : Flight(flightNumber, origin, destination, dateTime, totalSeats, availableSeats),
      contractHolder(contractHolder), charterFee(charterFee) {
    // Charter flights have a total fee divided among seats
}

// Function Overriding — per-seat cost is total charter fee divided by total seats
double CharterFlight::calculateBaseFare() const {
    // Avoid division by zero
    if (totalSeats == 0) return 0.0;
    return charterFee / totalSeats;  // e.g. 500000 / 50 = 10000 per seat
}

// Function Overriding — display charter-specific information
void CharterFlight::displayDetails() const {
    std::cout << "\n===== Charter Flight Details =====\n"
              << "Flight Number    : " << flightNumber << "\n"
              << "Type             : Charter\n"
              << "Route            : " << origin << " -> " << destination << "\n"
              << "Departure        : " << departureDateTime << "\n"
              << "Total Seats      : " << totalSeats << "\n"
              << "Available        : " << availableSeats << "\n"
              << "Charter Fee      : " << charterFee << "\n"
              << "Per-Seat Cost    : " << calculateBaseFare() << "\n"
              << "Contract Holder  : " << contractHolder << "\n"
              << "=================================\n";
}

// Function Overriding — type identifier
std::string CharterFlight::getType() const {
    return "Charter";
}

// File Handling — writes to output stream with type tag 'C'
void CharterFlight::saveToFile(std::ofstream& ofs) const {
    ofs << "C" << "\n"
        << flightNumber << "\n"
        << origin << "\n"
        << destination << "\n"
        << departureDateTime << "\n"
        << totalSeats << "\n"
        << availableSeats << "\n"
        << charterFee << "\n"
        << contractHolder << "\n";
}
