// ============================================================
// Airline.cpp — Implementation of the Airline Central Manager
// OOP Concepts: Composition (owns and manages all entities),
//               Destructor (memory cleanup), Polymorphism (virtual calls
//               through base pointers), File Handling (ifstream, ofstream,
//               ios::in, ios::out, ios::trunc, tellg, seekg),
//               Static member usage, Template usage,
//               Structures & Arrays of Structures (RevenueEntry),
//               Association (connecting passengers to flights via tickets)
// ============================================================

#include "Airline.h"
#include "Exceptions.h"
#include "Utils.h"
#include "DomesticFlight.h"
#include "InternationalFlight.h"
#include "CharterFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "FirstClassPassenger.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>

// ---- CONSTRUCTOR ----
// Parameterized constructor — initializes data file path and ticket counter
Airline::Airline(const std::string& dataFilePath)
    : nextTicketID(1), dataFilePath(dataFilePath) {
    // flights, passengers, tickets vectors start empty
    // Data will be loaded from file separately via loadFromFile()
}

// ---- DESTRUCTOR ----
// Demonstrates: Destructor, Memory Management
// MUST delete all heap-allocated pointers to prevent memory leaks
Airline::~Airline() {
    // Loop through flights vector and delete each Flight pointer
    for (Flight* f : flights) {
        delete f;  // Calls virtual destructor — proper cleanup for derived types
    }
    flights.clear();

    // Loop through passengers vector and delete each Passenger pointer
    for (Passenger* p : passengers) {
        delete p;  // Calls virtual destructor
    }
    passengers.clear();
    // tickets are value objects (not pointers) — automatically cleaned up
}

// ============================================================
// FLIGHT MANAGEMENT METHODS
// ============================================================

// Add a flight to the system — Airline takes ownership (Composition)
void Airline::addFlight(Flight* flight) {
    flights.push_back(flight);  // Append to flights vector
    // Initialize seat map for this flight based on booked seats
    int bookedSeats = flight->getTotalSeats() - flight->getAvailableSeats();
    seatMap[flight->getFlightNumber()] = bookedSeats;
}

// Remove a flight by flight number — deletes the pointer
void Airline::removeFlight(const std::string& flightNumber) {
    // Search for the flight in the vector
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        if ((*it)->getFlightNumber() == flightNumber) {
            delete *it;        // Free the heap-allocated Flight object
            flights.erase(it); // Remove from vector
            seatMap.erase(flightNumber);  // Remove seat tracking
            std::cout << "Flight " << flightNumber << " removed successfully.\n";
            return;
        }
    }
    // If not found, throw custom exception
    throw FlightNotFoundException(flightNumber);
}

// Find a flight by number — uses template search utility
// Demonstrates: Template function usage, Run-Time Polymorphism
Flight* Airline::findFlight(const std::string& flightNumber) {
    // Use the generic findByPredicate template from Utils.h
    return findByPredicate<Flight>(flights,
        [&](Flight* fl) { return fl->getFlightNumber() == flightNumber; });
}

// Search flights by route (origin and destination)
// Demonstrates: Function that returns vector of polymorphic pointers
std::vector<Flight*> Airline::searchByRoute(const std::string& origin,
                                             const std::string& destination) {
    std::vector<Flight*> results;
    for (Flight* f : flights) {
        // Compare origin and destination using getters (Encapsulation)
        if (f->getOrigin() == origin && f->getDestination() == destination) {
            results.push_back(f);
        }
    }
    return results;
}

// Search flights by date — matches YYYY-MM-DD prefix of departure datetime
std::vector<Flight*> Airline::searchByDate(const std::string& date) {
    std::vector<Flight*> results;
    for (Flight* f : flights) {
        // Check if departure datetime starts with the given date
        if (f->getDepartureDateTime().substr(0, 10) == date) {
            results.push_back(f);
        }
    }
    return results;
}

// List all flights — calls virtual displayDetails() on each
// Demonstrates: Run-Time Polymorphism — base pointer calls derived method
void Airline::listAllFlights() {
    if (flights.empty()) {
        std::cout << "\nNo flights registered in the system.\n";
        return;
    }
    std::cout << "\n========== All Flights (" << flights.size() << ") ==========\n";
    for (Flight* f : flights) {
        // Polymorphic call — displayDetails() is virtual
        // The correct derived version is called based on actual object type
        f->displayDetails();
    }
}

// ============================================================
// PASSENGER MANAGEMENT METHODS
// ============================================================

// Add a passenger — Airline takes ownership (Composition)
void Airline::addPassenger(Passenger* passenger) {
    passengers.push_back(passenger);  // Append to passengers vector
}

// Remove a passenger by ID
void Airline::removePassenger(const std::string& passengerID) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if ((*it)->getPassengerID() == passengerID) {
            delete *it;          // Free heap-allocated Passenger
            passengers.erase(it);
            std::cout << "Passenger " << passengerID << " removed successfully.\n";
            return;
        }
    }
    throw PassengerNotFoundException(passengerID);
}

// Find passenger by ID — uses template search
Passenger* Airline::findPassenger(const std::string& passengerID) {
    return findByPredicate<Passenger>(passengers,
        [&](Passenger* p) { return p->getPassengerID() == passengerID; });
}

// List all passengers — calls virtual displayInfo() on each
void Airline::listAllPassengers() {
    if (passengers.empty()) {
        std::cout << "\nNo passengers registered in the system.\n";
        return;
    }
    std::cout << "\n========== All Passengers (" << passengers.size() << ") ==========\n";
    for (Passenger* p : passengers) {
        p->displayInfo();  // Polymorphic call — shows class-specific info
    }
}

// View booking history for a specific passenger
void Airline::viewPassengerHistory(const std::string& passengerID) {
    Passenger* p = findPassenger(passengerID);
    if (!p) {
        throw PassengerNotFoundException(passengerID);
    }

    const auto& history = p->getBookingHistory();
    std::cout << "\n===== Booking History for " << p->getName()
              << " (" << passengerID << ") =====\n";

    if (history.empty()) {
        std::cout << "No bookings found.\n";
        return;
    }

    // Display full ticket details for each ticket in history
    for (const auto& tid : history) {
        // Search tickets vector for matching ticket ID
        for (const auto& t : tickets) {
            if (t.getTicketID() == tid) {
                t.displayTicket();  // Show full ticket info
                break;
            }
        }
    }
}

// ============================================================
// BOOKING & CANCELLATION METHODS
// ============================================================

// Book a ticket — connects a passenger to a flight
// Demonstrates: Association, Polymorphism, Exception Handling
Ticket Airline::bookTicket(const std::string& passengerID,
                           const std::string& flightNumber) {
    // Step 1: Find passenger — throw if not found
    Passenger* passenger = findPassenger(passengerID);
    if (!passenger) {
        throw PassengerNotFoundException(passengerID);
    }

    // Step 2: Find flight — throw if not found
    Flight* flight = findFlight(flightNumber);
    if (!flight) {
        throw FlightNotFoundException(flightNumber);
    }

    // Step 3: Check if flight is full — throws FlightFullException
    if (flight->isFull()) {
        throw FlightFullException(flightNumber);
    }

    // Step 4: Check for duplicate booking (same passenger, same flight, CONFIRMED)
    for (const auto& t : tickets) {
        if (t.getPassengerID() == passengerID &&
            t.getFlightNumber() == flightNumber &&
            t.isConfirmed()) {
            throw InvalidCancellationException(
                "Passenger " + passengerID + " already has a confirmed booking on flight " + flightNumber);
        }
    }

    // Step 5: Book the seat — calls virtual bookSeat() (Polymorphism)
    flight->bookSeat();

    // Step 6: Generate ticket ID (e.g. T001, T002, ...)
    std::string ticketID = "T" + std::to_string(nextTicketID);
    // Pad with zeros for consistent formatting
    while (ticketID.length() < 4) {
        ticketID = ticketID.substr(0, 1) + "0" + ticketID.substr(1);
    }
    nextTicketID++;

    // Step 7: Generate seat number using seat tracking map
    int seatIndex = seatMap[flightNumber];
    std::string seatNumber = generateSeat(seatIndex);
    seatMap[flightNumber]++;  // Increment for next booking

    // Step 8: Get fare using polymorphic calculateBaseFare()
    double fare = flight->calculateBaseFare();

    // Step 9: Get today's date for booking date
    std::string bookingDate = getTodayDate();

    // Step 10: Create ticket — Association (links Passenger to Flight)
    Ticket ticket(ticketID, passengerID, flightNumber, seatNumber,
                  fare, "CONFIRMED", bookingDate);

    // Step 11: Add ticket to system
    tickets.push_back(ticket);

    // Step 12: Add ticket to passenger's booking history (Aggregation)
    passenger->addToHistory(ticketID);

    std::cout << "\n*** Ticket booked successfully! ***\n";
    // Use operator<< (Operator Overloading + Friend Function)
    std::cout << ticket << "\n";

    return ticket;
}

// Cancel a ticket — compute refund based on passenger class and days before departure
// Demonstrates: Polymorphism, File pointer concept, Exception handling
double Airline::cancelTicket(const std::string& ticketID) {
    // Step 1: Find ticket using std::find_if (STL algorithm)
    auto it = std::find_if(tickets.begin(), tickets.end(),
        [&](const Ticket& t) { return t.getTicketID() == ticketID; });

    if (it == tickets.end()) {
        throw InvalidCancellationException("Ticket " + ticketID + " not found.");
    }

    // Step 2: Check if already cancelled
    if (!it->isConfirmed()) {
        throw InvalidCancellationException("Ticket " + ticketID + " is already cancelled.");
    }

    // Step 3: Find associated passenger and flight
    Passenger* passenger = findPassenger(it->getPassengerID());
    Flight* flight = findFlight(it->getFlightNumber());

    if (!passenger || !flight) {
        throw InvalidCancellationException("Associated passenger or flight not found.");
    }

    // Step 4: Compute days before departure
    std::string departureDate = flight->getDepartureDateTime().substr(0, 10);
    std::string bookingDate = it->getBookingDate();
    int daysBeforeDeparture = daysBetween(bookingDate, departureDate);

    // Step 5: Get refund percentage using polymorphic call
    // Each passenger class returns different refund rate (Run-Time Polymorphism)
    double refundPercentage = passenger->getRefundPercentage(daysBeforeDeparture);

    // Step 6: Compute refund amount
    double refundAmount = it->getFarePaid() * refundPercentage;

    // Step 7: Cancel the seat on the flight
    flight->cancelSeat();

    // Step 8: Set ticket status to CANCELLED
    it->setStatus("CANCELLED");

    // Step 9: Print refund details
    std::cout << "\n*** Ticket " << ticketID << " cancelled ***\n"
              << "Days before departure : " << daysBeforeDeparture << "\n"
              << "Passenger class       : " << passenger->getPassengerClass() << "\n"
              << "Refund percentage     : " << (refundPercentage * 100) << "%\n"
              << "Fare paid             : " << std::fixed << std::setprecision(2) << it->getFarePaid() << "\n"
              << "Refund amount         : " << std::fixed << std::setprecision(2) << refundAmount << "\n";

    return refundAmount;
}

// View details of a specific ticket
void Airline::viewTicketDetails(const std::string& ticketID) {
    for (const auto& t : tickets) {
        if (t.getTicketID() == ticketID) {
            t.displayTicket();
            return;
        }
    }
    std::cout << "Ticket " << ticketID << " not found.\n";
}

// ============================================================
// REPORT METHODS
// ============================================================

// Report: Today's departures — filters flights by today's date
void Airline::reportTodayDepartures() {
    std::string today = getTodayDate();  // Get system date
    std::cout << "\n===== Today's Departures (" << today << ") =====\n";

    bool found = false;
    for (Flight* f : flights) {
        // Check if flight's departure date matches today
        if (f->getDepartureDateTime().substr(0, 10) == today) {
            f->displayDetails();  // Polymorphic call
            found = true;
        }
    }

    if (!found) {
        std::cout << "No departures scheduled for today.\n";
    }
}

// Report: Occupancy percentage for all flights
void Airline::reportOccupancy() {
    std::cout << "\n===== Flight Occupancy Report =====\n";
    std::cout << std::left << std::setw(12) << "Flight"
              << std::setw(20) << "Route"
              << std::setw(15) << "Occupancy" << "\n";
    std::cout << std::string(47, '-') << "\n";

    for (Flight* f : flights) {
        // getOccupancyPct() returns percentage of booked seats
        std::cout << std::left << std::setw(12) << f->getFlightNumber()
                  << std::setw(20) << (f->getOrigin() + "->" + f->getDestination())
                  << std::fixed << std::setprecision(1) << f->getOccupancyPct() << "%\n";
    }
}

// Report: Top 5 revenue flights this month
// Demonstrates: Structures (RevenueEntry), Arrays of Structures, std::sort
void Airline::reportTopRevenueFlights() {
    std::string currentMonth = getCurrentMonthPrefix();  // e.g. "2025-08"

    // Use std::map to accumulate revenue per flight for current month
    std::map<std::string, double> revenueMap;

    for (const auto& t : tickets) {
        // Only count CONFIRMED tickets from the current month
        if (t.isConfirmed() && t.getBookingDate().substr(0, 7) == currentMonth) {
            revenueMap[t.getFlightNumber()] += t.getFarePaid();
        }
    }

    // ---- ARRAYS OF STRUCTURES (OOP Topic 1) ----
    // Convert map to array of RevenueEntry structures for sorting
    std::vector<RevenueEntry> entries;  // Vector of structures
    for (const auto& pair : revenueMap) {
        RevenueEntry entry;          // Create structure instance
        entry.flightNumber = pair.first;
        entry.revenue = pair.second;
        entries.push_back(entry);    // Add to array of structures
    }

    // Sort by revenue descending using std::sort
    std::sort(entries.begin(), entries.end(),
        [](const RevenueEntry& a, const RevenueEntry& b) {
            return a.revenue > b.revenue;  // Descending order
        });

    // Display top 5
    std::cout << "\n===== Top 5 Revenue Flights (Month: " << currentMonth << ") =====\n";
    std::cout << std::left << std::setw(5) << "Rank"
              << std::setw(15) << "Flight"
              << std::setw(15) << "Revenue" << "\n";
    std::cout << std::string(35, '-') << "\n";

    // ---- STRUCTURE POINTERS (OOP Topic 1) ----
    // Iterate using index, accessing structure members
    int count = std::min(static_cast<int>(entries.size()), 5);
    for (int i = 0; i < count; i++) {
        // Access structure members using dot notation
        RevenueEntry* entryPtr = &entries[i];  // Structure pointer
        std::cout << std::left << std::setw(5) << (i + 1)
                  << std::setw(15) << entryPtr->flightNumber   // Access via pointer
                  << std::fixed << std::setprecision(2) << entryPtr->revenue << "\n";
    }

    if (entries.empty()) {
        std::cout << "No revenue data for this month.\n";
    }
}

// ============================================================
// FILE HANDLING — PERSISTENCE
// Demonstrates: ofstream (output file stream), ifstream (input file stream),
//               ios::out, ios::in, ios::trunc, tellg(), seekg(),
//               File pointers, Stream operations
// ============================================================

// Save all data to file
// Uses: ofstream (output file stream), ios::out | ios::trunc
void Airline::saveToFile() {
    // Open file for writing — ios::out opens for output, ios::trunc clears existing content
    std::ofstream ofs(dataFilePath, std::ios::out | std::ios::trunc);

    if (!ofs.is_open()) {
        std::cerr << "Warning: Could not open file for writing: " << dataFilePath << "\n";
        return;  // Handle error gracefully — don't crash
    }

    // ---- Write FLIGHTS section ----
    ofs << "[FLIGHTS]\n";
    for (const Flight* f : flights) {
        f->saveToFile(ofs);  // Polymorphic call — each derived type writes its own format
        ofs << "---\n";      // Record separator
    }

    // ---- Write PASSENGERS section ----
    ofs << "[PASSENGERS]\n";
    for (const Passenger* p : passengers) {
        p->saveToFile(ofs);  // Polymorphic call
        ofs << "---\n";
    }

    // ---- Write TICKETS section ----
    ofs << "[TICKETS]\n";
    for (const Ticket& t : tickets) {
        t.saveToFile(ofs);
        ofs << "---\n";
    }

    ofs.close();  // Close the file stream — close() method
    std::cout << "Data saved successfully to " << dataFilePath << "\n";
}

// Load all data from file
// Uses: ifstream (input file stream), ios::in, tellg(), seekg()
void Airline::loadFromFile() {
    // Open file for reading — ifstream is input file stream
    std::ifstream ifs(dataFilePath, std::ios::in);

    if (!ifs.is_open()) {
        // File doesn't exist on first run — return silently
        return;
    }

    // ---- FILE POINTER: tellg() and seekg() demonstration ----
    // tellg() — get current read (get) pointer position
    std::streampos startPos = ifs.tellg();  // Should be 0 at start

    // seekg() — move read pointer to end to check file size
    ifs.seekg(0, std::ios::end);            // seekg with ios::end direction
    std::streampos fileSize = ifs.tellg();  // tellp equivalent for read

    // seekg() — move back to beginning for reading
    ifs.seekg(0, std::ios::beg);            // seekg with ios::beg direction

    // If file is empty, return
    if (fileSize == startPos) {
        ifs.close();
        return;
    }

    std::string line;
    std::string currentSection = "";

    while (std::getline(ifs, line)) {
        // Remove carriage return if present (Windows line endings)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Detect section markers
        if (line == "[FLIGHTS]") {
            currentSection = "FLIGHTS";
            continue;
        } else if (line == "[PASSENGERS]") {
            currentSection = "PASSENGERS";
            continue;
        } else if (line == "[TICKETS]") {
            currentSection = "TICKETS";
            continue;
        } else if (line == "---") {
            continue;  // Skip record separators
        }

        // ---- LOAD FLIGHTS ----
        if (currentSection == "FLIGHTS" && !line.empty()) {
            std::string typeTag = line;  // D, I, or C

            // Read common flight fields
            std::string flightNumber, origin, destination, dateTime;
            std::string seatsLine, availLine;
            std::getline(ifs, flightNumber);
            std::getline(ifs, origin);
            std::getline(ifs, destination);
            std::getline(ifs, dateTime);
            std::getline(ifs, seatsLine);
            std::getline(ifs, availLine);

            // Remove carriage returns
            if (!flightNumber.empty() && flightNumber.back() == '\r') flightNumber.pop_back();
            if (!origin.empty() && origin.back() == '\r') origin.pop_back();
            if (!destination.empty() && destination.back() == '\r') destination.pop_back();
            if (!dateTime.empty() && dateTime.back() == '\r') dateTime.pop_back();
            if (!seatsLine.empty() && seatsLine.back() == '\r') seatsLine.pop_back();
            if (!availLine.empty() && availLine.back() == '\r') availLine.pop_back();

            int totalSeats = std::stoi(seatsLine);
            int availableSeats = std::stoi(availLine);

            // Construct correct derived type based on type tag
            if (typeTag == "D") {
                // Domestic: read baseFare and taxRate
                std::string baseFareLine, taxRateLine;
                std::getline(ifs, baseFareLine);
                std::getline(ifs, taxRateLine);
                if (!baseFareLine.empty() && baseFareLine.back() == '\r') baseFareLine.pop_back();
                if (!taxRateLine.empty() && taxRateLine.back() == '\r') taxRateLine.pop_back();

                double baseFare = std::stod(baseFareLine);
                double taxRate = std::stod(taxRateLine);

                addFlight(new DomesticFlight(flightNumber, origin, destination,
                                            dateTime, totalSeats, availableSeats,
                                            baseFare, taxRate));
            }
            else if (typeTag == "I") {
                // International: read baseFare, internationalTax, visaRequired
                std::string baseFareLine, taxLine, visaLine;
                std::getline(ifs, baseFareLine);
                std::getline(ifs, taxLine);
                std::getline(ifs, visaLine);
                if (!baseFareLine.empty() && baseFareLine.back() == '\r') baseFareLine.pop_back();
                if (!taxLine.empty() && taxLine.back() == '\r') taxLine.pop_back();
                if (!visaLine.empty() && visaLine.back() == '\r') visaLine.pop_back();

                double baseFare = std::stod(baseFareLine);
                double intTax = std::stod(taxLine);
                bool visaReq = (visaLine == "1");

                addFlight(new InternationalFlight(flightNumber, origin, destination,
                                                  dateTime, totalSeats, availableSeats,
                                                  baseFare, intTax, visaReq));
            }
            else if (typeTag == "C") {
                // Charter: read charterFee, contractHolder
                std::string feeLine, holderLine;
                std::getline(ifs, feeLine);
                std::getline(ifs, holderLine);
                if (!feeLine.empty() && feeLine.back() == '\r') feeLine.pop_back();
                if (!holderLine.empty() && holderLine.back() == '\r') holderLine.pop_back();

                double charterFee = std::stod(feeLine);

                addFlight(new CharterFlight(flightNumber, origin, destination,
                                            dateTime, totalSeats, availableSeats,
                                            charterFee, holderLine));
            }
        }
        // ---- LOAD PASSENGERS ----
        else if (currentSection == "PASSENGERS" && !line.empty()) {
            std::string typeTag = line;  // E, B, or F

            std::string passengerID, name, email, phone, histCountLine;
            std::getline(ifs, passengerID);
            std::getline(ifs, name);
            std::getline(ifs, email);
            std::getline(ifs, phone);
            std::getline(ifs, histCountLine);

            if (!passengerID.empty() && passengerID.back() == '\r') passengerID.pop_back();
            if (!name.empty() && name.back() == '\r') name.pop_back();
            if (!email.empty() && email.back() == '\r') email.pop_back();
            if (!phone.empty() && phone.back() == '\r') phone.pop_back();
            if (!histCountLine.empty() && histCountLine.back() == '\r') histCountLine.pop_back();

            int histCount = std::stoi(histCountLine);

            // Read booking history entries
            std::vector<std::string> history;
            for (int i = 0; i < histCount; i++) {
                std::string tid;
                std::getline(ifs, tid);
                if (!tid.empty() && tid.back() == '\r') tid.pop_back();
                history.push_back(tid);
            }

            // Construct correct derived Passenger type
            Passenger* p = nullptr;
            if (typeTag == "E") {
                p = new EconomyPassenger(passengerID, name, email, phone);
            } else if (typeTag == "B") {
                p = new BusinessPassenger(passengerID, name, email, phone);
            } else if (typeTag == "F") {
                p = new FirstClassPassenger(passengerID, name, email, phone);
            }

            if (p) {
                // Restore booking history
                for (const auto& tid : history) {
                    p->addToHistory(tid);
                }
                addPassenger(p);
            }
        }
        // ---- LOAD TICKETS ----
        else if (currentSection == "TICKETS" && !line.empty()) {
            // First line is ticketID (already read as 'line')
            std::string ticketID = line;
            std::string passengerID, flightNumber, seatNumber;
            std::string fareLine, status, bookingDate;

            std::getline(ifs, passengerID);
            std::getline(ifs, flightNumber);
            std::getline(ifs, seatNumber);
            std::getline(ifs, fareLine);
            std::getline(ifs, status);
            std::getline(ifs, bookingDate);

            if (!ticketID.empty() && ticketID.back() == '\r') ticketID.pop_back();
            if (!passengerID.empty() && passengerID.back() == '\r') passengerID.pop_back();
            if (!flightNumber.empty() && flightNumber.back() == '\r') flightNumber.pop_back();
            if (!seatNumber.empty() && seatNumber.back() == '\r') seatNumber.pop_back();
            if (!fareLine.empty() && fareLine.back() == '\r') fareLine.pop_back();
            if (!status.empty() && status.back() == '\r') status.pop_back();
            if (!bookingDate.empty() && bookingDate.back() == '\r') bookingDate.pop_back();

            double farePaid = std::stod(fareLine);

            Ticket ticket(ticketID, passengerID, flightNumber, seatNumber,
                          farePaid, status, bookingDate);
            tickets.push_back(ticket);

            // Update nextTicketID to be max of existing IDs + 1
            // Extract number from ticket ID (e.g. "T003" -> 3)
            if (ticketID.length() > 1) {
                int idNum = std::stoi(ticketID.substr(1));
                if (idNum >= nextTicketID) {
                    nextTicketID = idNum + 1;  // Set next to max + 1
                }
            }

            // Update seat map for this flight
            if (seatMap.find(flightNumber) == seatMap.end()) {
                seatMap[flightNumber] = 0;
            }
            seatMap[flightNumber]++;
        }
    }

    ifs.close();  // Close input file stream
    std::cout << "Data loaded successfully from " << dataFilePath << "\n";
    std::cout << "  Flights: " << flights.size()
              << " | Passengers: " << passengers.size()
              << " | Tickets: " << tickets.size() << "\n";
}
