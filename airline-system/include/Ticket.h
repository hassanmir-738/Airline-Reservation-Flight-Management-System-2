#pragma once
// ============================================================
// Ticket.h — Links one Passenger to one Flight (Association)
// OOP Concepts: Association (links Passenger to Flight by ID),
//               Encapsulation (all private members),
//               Friend Functions (operator<< and operator==),
//               Operator Overloading, Static Function (loadFromFile),
//               Constructor Overloading (parameterized + copy)
// ============================================================

#include <string>
#include <iostream>
#include <fstream>

class Ticket {
private:
    // ---- ENCAPSULATION: All members private ----
    std::string ticketID;       // Unique e.g. T001, T002 (auto-generated)
    std::string passengerID;    // Links to Passenger (Association)
    std::string flightNumber;   // Links to Flight (Association)
    std::string seatNumber;     // e.g. "12A" (generated sequentially)
    double farePaid;            // Snapshot of fare at booking time
    std::string status;         // "CONFIRMED" or "CANCELLED"
    std::string bookingDate;    // Date ticket was created YYYY-MM-DD

public:
    // ---- PARAMETERIZED CONSTRUCTOR ----
    Ticket(const std::string& ticketID, const std::string& passengerID,
           const std::string& flightNumber, const std::string& seatNumber,
           double farePaid, const std::string& status,
           const std::string& bookingDate);

    // ---- COPY CONSTRUCTOR (Constructor Overloading) ----
    // Demonstrates having multiple constructors — copy constructor
    Ticket(const Ticket& other);

    // ---- DEFAULT CONSTRUCTOR ----
    // Needed for vector operations
    Ticket();

    // ---- ENCAPSULATION: GETTERS ----
    std::string getTicketID() const;
    std::string getPassengerID() const;
    std::string getFlightNumber() const;
    std::string getSeatNumber() const;
    double getFarePaid() const;
    std::string getStatus() const;
    std::string getBookingDate() const;

    // ---- SETTER ----
    void setStatus(const std::string& s);

    // ---- UTILITY ----
    bool isConfirmed() const;
    void displayTicket() const;

    // ---- FRIEND FUNCTIONS (Operator Overloading) ----
    // Friends have access to private members for formatting/comparison
    friend bool operator==(const Ticket& a, const Ticket& b);
    friend std::ostream& operator<<(std::ostream& os, const Ticket& t);

    // ---- FILE HANDLING ----
    void saveToFile(std::ofstream& ofs) const;

    // ---- STATIC FUNCTION ----
    // Static factory method — creates Ticket from file data
    // Demonstrates: Static member function
    static Ticket loadFromFile(std::ifstream& ifs);
};
