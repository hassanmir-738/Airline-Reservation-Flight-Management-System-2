#pragma once
// ============================================================
// CharterFlight.h — Derived from Flight (Single Inheritance)
// OOP Concepts: Single Inheritance, Encapsulation,
//               Function Overriding, Constructor
// ============================================================

#include "Flight.h"
#include <string>
#include <fstream>

// CharterFlight inherits from Flight — Single Inheritance
// Part of Hierarchical Inheritance (Flight -> Domestic / International / Charter)
class CharterFlight : public Flight {
private:
    std::string contractHolder;  // Company that chartered the flight
    double charterFee;           // Total charter fee for the whole plane

public:
    // Parameterized constructor
    CharterFlight(const std::string& flightNumber, const std::string& origin,
                  const std::string& destination, const std::string& dateTime,
                  int totalSeats, int availableSeats,
                  double charterFee, const std::string& contractHolder);

    // ---- FUNCTION OVERRIDING ----
    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;

    // ---- FILE HANDLING ----
    void saveToFile(std::ofstream& ofs) const override;
};
