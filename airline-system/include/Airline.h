#pragma once
// ============================================================
// Airline.h — Central Manager Class (Composition Pattern)
// OOP Concepts: Composition (owns Flight*, Passenger*, Ticket objects),
//               Encapsulation (all private members),
//               Static Member (nextTicketID),
//               Association (manages relationships between entities),
//               Destructor (frees all heap-allocated memory)
// ============================================================

#include <string>
#include <vector>
#include <map>
#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"

class Airline {
private:
    // ---- COMPOSITION ----
    // Airline OWNS these objects — responsible for their lifetime
    // When Airline is destroyed, all Flight* and Passenger* are deleted
    std::vector<Flight*> flights;           // Heap-allocated Flight objects
    std::vector<Passenger*> passengers;     // Heap-allocated Passenger objects
    std::vector<Ticket> tickets;            // Value objects (not pointers)

    // ---- STATIC-LIKE MEMBER ----
    // Counter for auto-generating unique ticket IDs (T001, T002, ...)
    int nextTicketID;

    // File path for data persistence
    std::string dataFilePath;

    // Seat tracking — maps flight number to next seat index
    std::map<std::string, int> seatMap;

public:
    // ---- CONSTRUCTOR ----
    // Parameterized constructor — takes data file path
    Airline(const std::string& dataFilePath);

    // ---- DESTRUCTOR ----
    // MUST delete all Flight* and Passenger* pointers to prevent memory leaks
    // Demonstrates: Destructor, memory management
    ~Airline();

    // ---- FLIGHT MANAGEMENT ----
    void addFlight(Flight* flight);
    void removeFlight(const std::string& flightNumber);
    Flight* findFlight(const std::string& flightNumber);
    std::vector<Flight*> searchByRoute(const std::string& origin,
                                       const std::string& destination);
    std::vector<Flight*> searchByDate(const std::string& date);
    void listAllFlights();

    // ---- PASSENGER MANAGEMENT ----
    void addPassenger(Passenger* passenger);
    void removePassenger(const std::string& passengerID);
    Passenger* findPassenger(const std::string& passengerID);
    void listAllPassengers();
    void viewPassengerHistory(const std::string& passengerID);

    // ---- BOOKING & CANCELLATION ----
    Ticket bookTicket(const std::string& passengerID,
                      const std::string& flightNumber);
    double cancelTicket(const std::string& ticketID);
    void viewTicketDetails(const std::string& ticketID);

    // ---- REPORTS ----
    void reportTodayDepartures();
    void reportOccupancy();
    void reportTopRevenueFlights();

    // ---- FILE HANDLING (Persistence) ----
    // saveToFile uses ofstream (output file stream) with ios::out
    // loadFromFile uses ifstream (input file stream) with ios::in
    void saveToFile();
    void loadFromFile();
};
