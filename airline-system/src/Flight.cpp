// ============================================================
// Flight.cpp — Implementation of the Flight Abstract Base Class
// OOP Concepts: Constructor implementation, Encapsulation (getters),
//               Friend Function implementation, Exception throwing
// ============================================================

#include "Flight.h"
#include "Exceptions.h"

// Parameterized constructor — initializes all base flight attributes
Flight::Flight(const std::string& flightNumber, const std::string& origin,
               const std::string& destination, const std::string& departureDateTime,
               int totalSeats, int availableSeats)
    : flightNumber(flightNumber), origin(origin), destination(destination),
      departureDateTime(departureDateTime), totalSeats(totalSeats),
      availableSeats(availableSeats) {
    // All members initialized via initializer list for efficiency
}

// Virtual destructor — ensures proper cleanup when deleting through base pointer
Flight::~Flight() {
    // Base class has no dynamic memory to free
    // But virtual destructor ensures derived destructors are called
}

// ---- ENCAPSULATION: Getter implementations ----
// Each getter returns the value of a protected member
std::string Flight::getFlightNumber() const { return flightNumber; }
std::string Flight::getOrigin() const { return origin; }
std::string Flight::getDestination() const { return destination; }
std::string Flight::getDepartureDateTime() const { return departureDateTime; }
int Flight::getTotalSeats() const { return totalSeats; }
int Flight::getAvailableSeats() const { return availableSeats; }

// Book a seat on the flight — decrements available count
void Flight::bookSeat() {
    // Check if flight is full before booking
    if (availableSeats <= 0) {
        throw FlightFullException(flightNumber);  // Throw custom exception
    }
    availableSeats--;  // Decrement available seats by 1
}

// Cancel a seat — increments available count back up
void Flight::cancelSeat() {
    // Ensure we don't exceed total capacity
    if (availableSeats < totalSeats) {
        availableSeats++;  // Increment available seats by 1
    }
}

// Check if all seats are taken
bool Flight::isFull() const {
    return availableSeats == 0;  // True when no seats left
}

// Calculate occupancy percentage for reports
double Flight::getOccupancyPct() const {
    // Formula: booked seats / total seats * 100
    return (totalSeats - availableSeats) * 100.0 / totalSeats;
}

// ---- FRIEND FUNCTION: operator<< ----
// This is a friend, not a member — has access to protected members
// Demonstrates: Operator Overloading + Friend Function
std::ostream& operator<<(std::ostream& os, const Flight& f) {
    os << "Flight: " << f.flightNumber
       << " | Route: " << f.origin << " -> " << f.destination
       << " | DateTime: " << f.departureDateTime
       << " | Seats: " << f.availableSeats << "/" << f.totalSeats
       << " | Fare: " << f.calculateBaseFare();
    return os;  // Return stream for chaining
}
