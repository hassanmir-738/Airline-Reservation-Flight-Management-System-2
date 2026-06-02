#pragma once
// ============================================================
// InternationalFlight.h — Derived from Flight (Single Inheritance)
// OOP Concepts: Single Inheritance, Encapsulation,
//               Function Overriding, Constructor
// ============================================================

#include "Flight.h"
#include <string>
#include <fstream>

// InternationalFlight inherits from Flight — Single Inheritance
class InternationalFlight : public Flight {
private:
    double baseFare;           // Base ticket price (e.g. 15000.0)
    double internationalTax;   // International tax rate (e.g. 0.12 for 12%)
    bool visaRequired;         // Whether passengers need a visa

public:
    // Parameterized constructor
    InternationalFlight(const std::string& flightNumber, const std::string& origin,
                        const std::string& destination, const std::string& dateTime,
                        int totalSeats, int availableSeats,
                        double baseFare, double internationalTax, bool visaRequired);

    // ---- FUNCTION OVERRIDING ----
    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;

    // ---- FILE HANDLING ----
    void saveToFile(std::ofstream& ofs) const override;
};
