// ============================================================
// Ticket.cpp — Implementation of Ticket class
// OOP Concepts: Constructor Overloading (default, parameterized, copy),
//               Encapsulation (getters/setter), Friend Functions,
//               Operator Overloading (== and <<),
//               Static Function (loadFromFile),
//               File Handling (ifstream reading, ofstream writing)
// ============================================================

#include "Ticket.h"
#include <iomanip>

// ---- DEFAULT CONSTRUCTOR ----
// Creates an empty ticket — needed for std::vector operations
Ticket::Ticket()
    : ticketID(""), passengerID(""), flightNumber(""),
      seatNumber(""), farePaid(0.0), status(""), bookingDate("") {
    // All fields initialized to empty/zero defaults
}

// ---- PARAMETERIZED CONSTRUCTOR ----
// Creates a fully-specified ticket with all fields
Ticket::Ticket(const std::string& ticketID, const std::string& passengerID,
               const std::string& flightNumber, const std::string& seatNumber,
               double farePaid, const std::string& status,
               const std::string& bookingDate)
    : ticketID(ticketID), passengerID(passengerID), flightNumber(flightNumber),
      seatNumber(seatNumber), farePaid(farePaid), status(status),
      bookingDate(bookingDate) {
    // All fields set via initializer list
}

// ---- COPY CONSTRUCTOR ----
// Demonstrates Constructor Overloading — creates ticket by copying another
Ticket::Ticket(const Ticket& other)
    : ticketID(other.ticketID), passengerID(other.passengerID),
      flightNumber(other.flightNumber), seatNumber(other.seatNumber),
      farePaid(other.farePaid), status(other.status),
      bookingDate(other.bookingDate) {
    // Deep copy of all fields from the other ticket
}

// ---- ENCAPSULATION: Getters ----
std::string Ticket::getTicketID() const { return ticketID; }
std::string Ticket::getPassengerID() const { return passengerID; }
std::string Ticket::getFlightNumber() const { return flightNumber; }
std::string Ticket::getSeatNumber() const { return seatNumber; }
double Ticket::getFarePaid() const { return farePaid; }
std::string Ticket::getStatus() const { return status; }
std::string Ticket::getBookingDate() const { return bookingDate; }

// ---- SETTER ----
// Set ticket status to "CONFIRMED" or "CANCELLED"
void Ticket::setStatus(const std::string& s) {
    status = s;  // Allows controlled modification of status only
}

// Check if ticket is still active
bool Ticket::isConfirmed() const {
    return status == "CONFIRMED";  // Returns true only for confirmed tickets
}

// Display all ticket information neatly formatted
void Ticket::displayTicket() const {
    std::cout << "\n----- Ticket Details -----\n"
              << "Ticket ID    : " << ticketID << "\n"
              << "Passenger ID : " << passengerID << "\n"
              << "Flight       : " << flightNumber << "\n"
              << "Seat         : " << seatNumber << "\n"
              << "Fare Paid    : " << std::fixed << std::setprecision(2) << farePaid << "\n"
              << "Status       : " << status << "\n"
              << "Booking Date : " << bookingDate << "\n"
              << "--------------------------\n";
}

// ---- FRIEND FUNCTION: operator== (Operator Overloading) ----
// Compares two tickets by their ticket ID
// Friend function has access to private ticketID member
bool operator==(const Ticket& a, const Ticket& b) {
    return a.ticketID == b.ticketID;  // Tickets are equal if IDs match
}

// ---- FRIEND FUNCTION: operator<< (Operator Overloading) ----
// Outputs ticket summary to stream — friend has access to all private members
std::ostream& operator<<(std::ostream& os, const Ticket& t) {
    os << "Ticket[" << t.ticketID << "] "
       << "Passenger: " << t.passengerID
       << " | Flight: " << t.flightNumber
       << " | Seat: " << t.seatNumber
       << " | Fare: " << std::fixed << std::setprecision(2) << t.farePaid
       << " | Status: " << t.status;
    return os;  // Return stream for chaining
}

// ---- FILE HANDLING: Save (ofstream — output file stream) ----
// Writes all 7 fields to file, one per line
// Uses ios::out mode (set when opening in Airline)
void Ticket::saveToFile(std::ofstream& ofs) const {
    ofs << ticketID << "\n"
        << passengerID << "\n"
        << flightNumber << "\n"
        << seatNumber << "\n"
        << farePaid << "\n"
        << status << "\n"
        << bookingDate << "\n";
}

// ---- STATIC FUNCTION: loadFromFile (ifstream — input file stream) ----
// Static factory method — reads 7 lines from file and constructs a Ticket
// Demonstrates: Static function + File Handling (ifstream reading)
Ticket Ticket::loadFromFile(std::ifstream& ifs) {
    std::string ticketID, passengerID, flightNumber, seatNumber;
    std::string status, bookingDate, fareLine;
    double farePaid;

    // Read each field from file (ifstream — input file stream for reading)
    std::getline(ifs, ticketID);
    std::getline(ifs, passengerID);
    std::getline(ifs, flightNumber);
    std::getline(ifs, seatNumber);
    std::getline(ifs, fareLine);
    std::getline(ifs, status);
    std::getline(ifs, bookingDate);

    // Remove carriage returns if present (Windows line endings support)
    if (!ticketID.empty() && ticketID.back() == '\r') ticketID.pop_back();
    if (!passengerID.empty() && passengerID.back() == '\r') passengerID.pop_back();
    if (!flightNumber.empty() && flightNumber.back() == '\r') flightNumber.pop_back();
    if (!seatNumber.empty() && seatNumber.back() == '\r') seatNumber.pop_back();
    if (!fareLine.empty() && fareLine.back() == '\r') fareLine.pop_back();
    if (!status.empty() && status.back() == '\r') status.pop_back();
    if (!bookingDate.empty() && bookingDate.back() == '\r') bookingDate.pop_back();

    farePaid = std::stod(fareLine);  // Convert string to double

    // Construct and return a new Ticket object
    return Ticket(ticketID, passengerID, flightNumber, seatNumber,
                  farePaid, status, bookingDate);
}
