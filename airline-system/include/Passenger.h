#pragma once
// ============================================================
// Passenger.h — Abstract Base Class for all Passenger types
// OOP Concepts: Abstract Class, Pure Virtual Functions,
//               Encapsulation (protected members), Virtual Destructor,
//               Aggregation (bookingHistory vector of ticket IDs)
// ============================================================

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Passenger {
protected:
    // Protected attributes — accessible by derived classes
    std::string passengerID;    // Unique ID e.g. P001
    std::string name;           // Full name
    std::string email;          // Email address
    std::string phone;          // Phone number

    // ---- AGGREGATION ----
    // bookingHistory aggregates ticket IDs (strings) — Passenger doesn't own Tickets,
    // just holds references to them via their IDs
    std::vector<std::string> bookingHistory;

public:
    // ---- PARAMETERIZED CONSTRUCTOR ----
    Passenger(const std::string& passengerID, const std::string& name,
              const std::string& email, const std::string& phone);

    // ---- VIRTUAL DESTRUCTOR ----
    virtual ~Passenger();

    // ---- ENCAPSULATION: GETTERS ----
    std::string getPassengerID() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;

    // ---- BOOKING HISTORY MANAGEMENT (Aggregation) ----
    void addToHistory(const std::string& ticketID);
    void removeFromHistory(const std::string& ticketID);
    const std::vector<std::string>& getBookingHistory() const;

    // ---- DISPLAY ----
    void displayInfo() const;

    // ---- PURE VIRTUAL FUNCTIONS (Abstract Class) ----
    // Each derived passenger class provides its own implementation
    virtual double getBaggageAllowance() const = 0;
    virtual double getLoyaltyMultiplier() const = 0;
    virtual double getRefundPercentage(int daysBeforeDeparture) const = 0;
    virtual std::string getPassengerClass() const = 0;

    // ---- VIRTUAL FILE I/O ----
    virtual void saveToFile(std::ofstream& ofs) const = 0;
};
