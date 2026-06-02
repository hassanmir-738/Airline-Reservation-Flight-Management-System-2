// ============================================================
// Passenger.cpp — Implementation of the Passenger Abstract Base Class
// OOP Concepts: Constructor implementation, Encapsulation (getters),
//               Aggregation (booking history management),
//               Virtual destructor
// ============================================================

#include "Passenger.h"
#include <algorithm>  // for std::find and std::remove

// Parameterized constructor — initializes all base passenger attributes
Passenger::Passenger(const std::string& passengerID, const std::string& name,
                     const std::string& email, const std::string& phone)
    : passengerID(passengerID), name(name), email(email), phone(phone) {
    // bookingHistory starts empty — populated as tickets are booked
}

// Virtual destructor — ensures proper cleanup in inheritance hierarchy
Passenger::~Passenger() {
    // No dynamic memory in base class
}

// ---- ENCAPSULATION: Getter implementations ----
std::string Passenger::getPassengerID() const { return passengerID; }
std::string Passenger::getName() const { return name; }
std::string Passenger::getEmail() const { return email; }
std::string Passenger::getPhone() const { return phone; }

// ---- AGGREGATION: Booking history management ----
// Add a ticket ID to the passenger's booking history
void Passenger::addToHistory(const std::string& ticketID) {
    bookingHistory.push_back(ticketID);  // Append to vector
}

// Remove a ticket ID from history (used on cancellation)
void Passenger::removeFromHistory(const std::string& ticketID) {
    // Use erase-remove idiom to find and remove the ticket ID
    auto it = std::find(bookingHistory.begin(), bookingHistory.end(), ticketID);
    if (it != bookingHistory.end()) {
        bookingHistory.erase(it);  // Remove first occurrence
    }
}

// Return const reference to booking history — prevents modification from outside
const std::vector<std::string>& Passenger::getBookingHistory() const {
    return bookingHistory;
}

// Display all passenger information to console
void Passenger::displayInfo() const {
    std::cout << "\n----- Passenger Info -----\n"
              << "ID    : " << passengerID << "\n"
              << "Name  : " << name << "\n"
              << "Email : " << email << "\n"
              << "Phone : " << phone << "\n"
              << "Class : " << getPassengerClass() << "\n"  // Calls virtual method
              << "Booking History: ";
    if (bookingHistory.empty()) {
        std::cout << "None";
    } else {
        // Print all ticket IDs in history
        for (size_t i = 0; i < bookingHistory.size(); i++) {
            std::cout << bookingHistory[i];
            if (i < bookingHistory.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n-------------------------\n";
}
