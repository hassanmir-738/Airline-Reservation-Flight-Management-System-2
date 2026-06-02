#pragma once
// ============================================================
// DomesticFlight.h — Derived from Flight (Single Inheritance)
// OOP Concepts: Single Inheritance, Function Overriding,
//               Encapsulation (private members), Constructor
// ============================================================

#include "Flight.h"
#include <string>
#include <fstream>

// DomesticFlight inherits from Flight — Single Inheritance
class DomesticFlight : public Flight {
private:
    double baseFare;   // Base ticket price (e.g. 5000.0)
    double taxRate;    // Tax rate as decimal (e.g. 0.05 for 5%)

public:
    // Parameterized constructor — calls base Flight constructor
    DomesticFlight(const std::string& flightNumber, const std::string& origin,
                   const std::string& destination, const std::string& dateTime,
                   int totalSeats, int availableSeats,
                   double baseFare, double taxRate);

    // ---- FUNCTION OVERRIDING (Run-Time Polymorphism) ----
    // Override pure virtual functions from Flight base class
    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;

    // ---- FILE HANDLING ----
    // Writes domestic-specific data to file
    void saveToFile(std::ofstream& ofs) const override;
};
