#pragma once
// ============================================================
// Flight.h — Abstract Base Class for all Flight types
// OOP Concepts: Abstract Class, Pure Virtual Functions,
//               Encapsulation (protected/private members),
//               Virtual Destructor, Friend Function (operator<<),
//               Run-Time Polymorphism
// ============================================================

#include <string>
#include <iostream>
#include <fstream>

class Flight {
protected:
    // Protected attributes — accessible by derived classes for saveToFile/displayDetails
    std::string flightNumber;       // Unique ID e.g. SK101
    std::string origin;             // Departure city
    std::string destination;        // Arrival city
    std::string departureDateTime;  // Format: YYYY-MM-DD HH:MM
    int totalSeats;                 // Total capacity of the flight
    int availableSeats;             // Seats still available (decremented on booking)

public:
    // ---- PARAMETERIZED CONSTRUCTOR ----
    // Initializes all base attributes via parameter list
    Flight(const std::string& flightNumber, const std::string& origin,
           const std::string& destination, const std::string& departureDateTime,
           int totalSeats, int availableSeats);

    // ---- VIRTUAL DESTRUCTOR ----
    // Must be virtual so derived class destructors are called properly
    virtual ~Flight();

    // ---- ENCAPSULATION: GETTERS ----
    // All data members are protected; accessed only through these const getters
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureDateTime() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;

    // ---- BOOKING OPERATIONS ----
    // bookSeat: decrements availableSeats, throws FlightFullException if 0
    void bookSeat();
    // cancelSeat: increments availableSeats (max = totalSeats)
    void cancelSeat();

    // ---- UTILITY METHODS ----
    // Returns true if no seats available
    bool isFull() const;
    // Returns occupancy as percentage
    double getOccupancyPct() const;

    // ---- PURE VIRTUAL FUNCTIONS (Abstract Class) ----
    // These make Flight an abstract class — cannot be instantiated directly
    // Each derived class MUST override these (Run-Time Polymorphism)
    virtual double calculateBaseFare() const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string getType() const = 0;

    // ---- VIRTUAL FILE I/O ----
    // Virtual so derived classes can write their extra fields
    virtual void saveToFile(std::ofstream& ofs) const = 0;

    // ---- FRIEND FUNCTION (Operator Overloading) ----
    // Friend has access to private/protected members for output formatting
    friend std::ostream& operator<<(std::ostream& os, const Flight& f);
};
