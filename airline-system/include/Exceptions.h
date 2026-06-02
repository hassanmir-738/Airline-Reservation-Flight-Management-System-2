#pragma once
// ============================================================
// Exceptions.h — Custom Exception Classes for SkyLink Airways
// OOP Concepts: Single Inheritance (from std::exception),
//               Encapsulation (private msg), Function Overriding (what()),
//               Parameterized Constructors
// ============================================================

#include <exception>
#include <string>

// Exception thrown when trying to book a seat on a full flight
class FlightFullException : public std::exception {
private:
    std::string msg;  // Encapsulated error message

public:
    // Parameterized constructor — takes flight number to build message
    FlightFullException(const std::string& flightNum)
        : msg("Flight " + flightNum + " is full.") {}

    // Function overriding — overrides std::exception::what()
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Exception thrown for invalid cancellation attempts
class InvalidCancellationException : public std::exception {
private:
    std::string msg;

public:
    InvalidCancellationException(const std::string& reason)
        : msg("Invalid cancellation: " + reason) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Exception thrown when a passenger ID is not found
class PassengerNotFoundException : public std::exception {
private:
    std::string msg;

public:
    PassengerNotFoundException(const std::string& id)
        : msg("Passenger not found: " + id) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Exception thrown when a flight number is not found
class FlightNotFoundException : public std::exception {
private:
    std::string msg;

public:
    FlightNotFoundException(const std::string& fn)
        : msg("Flight not found: " + fn) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};
