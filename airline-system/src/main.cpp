// ============================================================
// main.cpp — SkyLink Airways Management System Entry Point
// OOP Concepts: Object creation, Polymorphism (creating derived types
//               through base pointers), Exception Handling (try-catch),
//               Input Validation, File Handling (save/load on start/exit)
// ============================================================

#include "Airline.h"
#include "DomesticFlight.h"
#include "InternationalFlight.h"
#include "CharterFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "FirstClassPassenger.h"
#include "Exceptions.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <limits>

// ---- INPUT VALIDATION HELPER FUNCTIONS ----
// These ensure the program never crashes from bad input

// Read an integer from cin with validation
// Checks cin.fail() (failbit) and clears the stream on error
int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            // failbit set — user entered non-numeric input
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard bad input
            std::cout << "Invalid input. Please enter a number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard rest of line
            return value;
        }
    }
}

// Read a double from cin with validation
double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Read a non-empty string from cin
std::string readString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Input cannot be empty. Try again.\n";
    }
}

// ============================================================
// MENU HANDLER FUNCTIONS
// ============================================================

// Handle adding a new flight (choose type D/I/C)
void handleAddFlight(Airline& airline) {
    std::cout << "\n--- Add Flight ---\n";
    std::cout << "Select flight type:\n";
    std::cout << "  D - Domestic\n";
    std::cout << "  I - International\n";
    std::cout << "  C - Charter\n";

    std::string type = readString("Enter type (D/I/C): ");

    // Common fields for all flight types
    std::string flightNumber = readString("Flight Number (e.g. SK101): ");
    std::string origin = readString("Origin city: ");
    std::string destination = readString("Destination city: ");
    std::string dateTime = readString("Departure (YYYY-MM-DD HH:MM): ");
    int totalSeats = readInt("Total seats: ");

    if (type == "D" || type == "d") {
        // Create DomesticFlight — demonstrates creating derived object
        double baseFare = readDouble("Base fare: ");
        double taxRate = readDouble("Tax rate (e.g. 0.05 for 5%): ");
        // new creates on heap — Airline takes ownership (Composition)
        airline.addFlight(new DomesticFlight(flightNumber, origin, destination,
                                            dateTime, totalSeats, totalSeats,
                                            baseFare, taxRate));
        std::cout << "Domestic flight " << flightNumber << " added successfully!\n";
    }
    else if (type == "I" || type == "i") {
        // Create InternationalFlight
        double baseFare = readDouble("Base fare: ");
        double intTax = readDouble("International tax rate (e.g. 0.12): ");
        std::string visaStr = readString("Visa required? (y/n): ");
        bool visaReq = (visaStr == "y" || visaStr == "Y");
        airline.addFlight(new InternationalFlight(flightNumber, origin, destination,
                                                  dateTime, totalSeats, totalSeats,
                                                  baseFare, intTax, visaReq));
        std::cout << "International flight " << flightNumber << " added successfully!\n";
    }
    else if (type == "C" || type == "c") {
        // Create CharterFlight
        double charterFee = readDouble("Total charter fee: ");
        std::string contractHolder = readString("Contract holder company: ");
        airline.addFlight(new CharterFlight(flightNumber, origin, destination,
                                            dateTime, totalSeats, totalSeats,
                                            charterFee, contractHolder));
        std::cout << "Charter flight " << flightNumber << " added successfully!\n";
    }
    else {
        std::cout << "Invalid flight type. Operation cancelled.\n";
    }
}

// Handle removing a flight
void handleRemoveFlight(Airline& airline) {
    std::string fn = readString("Enter flight number to remove: ");
    airline.removeFlight(fn);  // May throw FlightNotFoundException
}

// Handle searching for flights (by number / route / date)
void handleSearchFlight(Airline& airline) {
    std::cout << "\n--- Search Flight ---\n";
    std::cout << "  1. By flight number\n";
    std::cout << "  2. By route\n";
    std::cout << "  3. By date\n";

    int choice = readInt("Select search type: ");

    if (choice == 1) {
        std::string fn = readString("Enter flight number: ");
        Flight* f = airline.findFlight(fn);
        if (f) {
            f->displayDetails();  // Polymorphic call
        } else {
            std::cout << "Flight " << fn << " not found.\n";
        }
    }
    else if (choice == 2) {
        std::string origin = readString("Origin: ");
        std::string dest = readString("Destination: ");
        auto results = airline.searchByRoute(origin, dest);
        if (results.empty()) {
            std::cout << "No flights found for this route.\n";
        } else {
            std::cout << "\nFound " << results.size() << " flight(s):\n";
            for (Flight* f : results) {
                f->displayDetails();  // Polymorphic call
            }
        }
    }
    else if (choice == 3) {
        std::string date = readString("Date (YYYY-MM-DD): ");
        auto results = airline.searchByDate(date);
        if (results.empty()) {
            std::cout << "No flights found for this date.\n";
        } else {
            std::cout << "\nFound " << results.size() << " flight(s):\n";
            for (Flight* f : results) {
                f->displayDetails();
            }
        }
    }
    else {
        std::cout << "Invalid choice.\n";
    }
}

// Handle registering a new passenger (choose class E/B/F)
void handleRegisterPassenger(Airline& airline) {
    std::cout << "\n--- Register Passenger ---\n";
    std::cout << "Select passenger class:\n";
    std::cout << "  E - Economy\n";
    std::cout << "  B - Business\n";
    std::cout << "  F - First Class\n";

    std::string cls = readString("Enter class (E/B/F): ");
    std::string id = readString("Passenger ID (e.g. P001): ");
    std::string name = readString("Full name: ");
    std::string email = readString("Email: ");
    std::string phone = readString("Phone: ");

    if (cls == "E" || cls == "e") {
        airline.addPassenger(new EconomyPassenger(id, name, email, phone));
        std::cout << "Economy passenger " << id << " registered!\n";
    }
    else if (cls == "B" || cls == "b") {
        airline.addPassenger(new BusinessPassenger(id, name, email, phone));
        std::cout << "Business passenger " << id << " registered!\n";
    }
    else if (cls == "F" || cls == "f") {
        airline.addPassenger(new FirstClassPassenger(id, name, email, phone));
        std::cout << "First Class passenger " << id << " registered!\n";
    }
    else {
        std::cout << "Invalid passenger class. Operation cancelled.\n";
    }
}

// Handle removing a passenger
void handleRemovePassenger(Airline& airline) {
    std::string id = readString("Enter passenger ID to remove: ");
    airline.removePassenger(id);  // May throw PassengerNotFoundException
}

// ============================================================
// MAIN FUNCTION — Program Entry Point
// ============================================================
int main() {
    // Create the central Airline object — Composition (owns everything)
    Airline airline("data/airline_data.txt");

    // ---- FILE HANDLING: Load data on startup ----
    // Uses ifstream (input file stream) internally
    airline.loadFromFile();

    int mainChoice = -1;

    // Main menu loop — runs until user chooses 0 (exit)
    while (mainChoice != 0) {
        // Display menu
        std::cout << "\n\n===== SkyLink Airways Management System =====\n"
                  << "1. Flight Management\n"
                  << "2. Passenger Management\n"
                  << "3. Booking\n"
                  << "4. Reports\n"
                  << "0. Exit (saves data automatically)\n"
                  << "=============================================\n";

        mainChoice = readInt("Enter choice: ");

        // ---- EXCEPTION HANDLING ----
        // All operations wrapped in try-catch to prevent crashes
        try {
            switch (mainChoice) {
                case 1: {
                    // Flight Management submenu
                    std::cout << "\n--- Flight Management ---\n"
                              << "1.1 Add Flight\n"
                              << "1.2 Remove Flight\n"
                              << "1.3 Search Flight\n"
                              << "1.4 List All Flights\n";

                    std::string subChoice = readString("Enter choice (e.g. 1.1): ");

                    if (subChoice == "1.1") handleAddFlight(airline);
                    else if (subChoice == "1.2") handleRemoveFlight(airline);
                    else if (subChoice == "1.3") handleSearchFlight(airline);
                    else if (subChoice == "1.4") airline.listAllFlights();
                    else std::cout << "Invalid choice. Try again.\n";
                    break;
                }
                case 2: {
                    // Passenger Management submenu
                    std::cout << "\n--- Passenger Management ---\n"
                              << "2.1 Register Passenger\n"
                              << "2.2 Remove Passenger\n"
                              << "2.3 View Passenger Booking History\n"
                              << "2.4 List All Passengers\n";

                    std::string subChoice = readString("Enter choice (e.g. 2.1): ");

                    if (subChoice == "2.1") handleRegisterPassenger(airline);
                    else if (subChoice == "2.2") handleRemovePassenger(airline);
                    else if (subChoice == "2.3") {
                        std::string id = readString("Enter passenger ID: ");
                        airline.viewPassengerHistory(id);
                    }
                    else if (subChoice == "2.4") airline.listAllPassengers();
                    else std::cout << "Invalid choice. Try again.\n";
                    break;
                }
                case 3: {
                    // Booking submenu
                    std::cout << "\n--- Booking ---\n"
                              << "3.1 Book a Ticket\n"
                              << "3.2 Cancel a Ticket\n"
                              << "3.3 View Ticket Details\n";

                    std::string subChoice = readString("Enter choice (e.g. 3.1): ");

                    if (subChoice == "3.1") {
                        std::string pid = readString("Passenger ID: ");
                        std::string fn = readString("Flight Number: ");
                        airline.bookTicket(pid, fn);  // May throw exceptions
                    }
                    else if (subChoice == "3.2") {
                        std::string tid = readString("Ticket ID to cancel: ");
                        airline.cancelTicket(tid);  // May throw exceptions
                    }
                    else if (subChoice == "3.3") {
                        std::string tid = readString("Ticket ID: ");
                        airline.viewTicketDetails(tid);
                    }
                    else std::cout << "Invalid choice. Try again.\n";
                    break;
                }
                case 4: {
                    // Reports submenu
                    std::cout << "\n--- Reports ---\n"
                              << "4.1 Today's Departures\n"
                              << "4.2 Flight Occupancy Report\n"
                              << "4.3 Top 5 Revenue Flights This Month\n";

                    std::string subChoice = readString("Enter choice (e.g. 4.1): ");

                    if (subChoice == "4.1") airline.reportTodayDepartures();
                    else if (subChoice == "4.2") airline.reportOccupancy();
                    else if (subChoice == "4.3") airline.reportTopRevenueFlights();
                    else std::cout << "Invalid choice. Try again.\n";
                    break;
                }
                case 0:
                    // Exit — save data before quitting
                    break;
                default:
                    std::cout << "Invalid choice. Try again.\n";
                    break;
            }
        }
        catch (const FlightFullException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const FlightNotFoundException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const PassengerNotFoundException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const InvalidCancellationException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }
    }

    // ---- FILE HANDLING: Save data on exit ----
    // Uses ofstream (output file stream) internally
    std::cout << "\nSaving data...\n";
    airline.saveToFile();
    std::cout << "Thank you for using SkyLink Airways! Goodbye.\n";

    // Airline destructor called here — deletes all Flight* and Passenger* pointers
    return 0;
}
