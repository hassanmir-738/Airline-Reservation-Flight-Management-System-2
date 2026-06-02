 SkyLink Airways
Airline Reservation & Flight Management
System
COMPLETE AI CODING DOCUMENTATION
OOP (C++) — Individual Assignment  |  100 Marks
Hand this document to the AI coder exactly as-is.
This document contains every class, attribute, method, relationship,
file structure, and rule the AI needs to produce the complete project.
No extra features beyond what is listed here.
1. Project Overview
Language
Type
Files
Data persistence
Goal
C++17 (compile with: g++ -std=c++17 -Wall -Wextra)
Console-based application (no GUI)
Multiple .h + .cpp files + Makefile + README.md
Text file (save on exit, load on startup)
Manage flights, passengers, bookings, cancellations, reports for SkyLink Airways
1.1 What the Program Must Do (Summary)
•   Add / remove / search / list flights.
•   Register / remove / view history of passengers.
•   Book a seat (reject if full or duplicate booking).
•   Cancel a booking and compute refund by passenger class + days-before-departure.
•   Show reports: today's departures, occupancy %, top-5 revenue flights this month.
•   Save all data to file on exit; load on startup.
•   Show a console menu with full input validation.
2. Required File & Folder Structure
project/ 
first run) 
 Makefile 
 include/  
 CharterFlight.h  
BusinessPassenger.h  
Exceptions.h  
 Utils.h 
 README.md 
 Flight.h  
 Passenger.h  
 data/  
 FirstClassPassenger.h  
 src/ 
 InternationalFlight.cpp 
EconomyPassenger.cpp 
 airline_data.txt (auto-created on
 DomesticFlight.h  
 EconomyPassenger.h  
 Ticket.h  
 main.cpp 
 CharterFlight.cpp 
 BusinessPassenger.cpp 
 Flight.cpp 
 Passenger.cpp 
 InternationalFlight.h
 Airline.h  
 DomesticFlight.cpp
 FirstClassPassenger.cpp 
 Airline.cpp 
 Utils.cpp
Every .h file must have #pragma once (or traditional include guards). All .cpp files include their matching .h.
 Ticket.cpp
3. Class Hierarchy (Inheritance Tree)
[Abstract] Flight  DomesticFlight  InternationalFlight  CharterFlight [Abstract]
Passenger  EconomyPassenger  BusinessPassenger  FirstClassPassenger Ticket (links
one Passenger to one Flight) Airline (owns vectors of Flight*, Passenger*, Ticket)
Exceptions.h (FlightFullException, InvalidCancellationException, PassengerNotFoundException,
FlightNotFoundException) Utils.h (template search function)
4. Detailed Class Specifications
4.1 Flight (Abstract Base Class) — include/Flight.h + src/Flight.cpp
This is the root of the flight hierarchy. It cannot be instantiated directly.
Attributes (all private / protected)
flightNumber std::string — unique ID e.g. SK101
origin std::string — departure city
destination std::string — arrival city
departureDateTime std::string — format: YYYY-MM-DD HH:MM
totalSeats int — total capacity
availableSeats int — decremented on booking, incremented on cancel
Methods
Flight(…) constructor Initialise all attributes above via parameter list
virtual ~Flight() Virtual destructor (must be present)
getFlightNumber() const Returns flightNumber
getOrigin() const Returns origin
getDestination() const Returns destination
getDepartureDateTime() const Returns departureDateTime
getTotalSeats() const Returns totalSeats
getAvailableSeats() const Returns availableSeats
bookSeat() Decrements availableSeats by 1. Throws FlightFullException if 0.
cancelSeat() Increments availableSeats by 1 (max totalSeats).
isFull() const Returns true if availableSeats == 0
getOccupancyPct() const Returns double: (totalSeats-availableSeats)*100.0/totalSeats
[PURE VIRTUAL] calculateBaseFare() const Returns double — implemented by each derived class
[PURE VIRTUAL] displayDetails() constPrints all flight info to console — implemented by derived classes
[PURE VIRTUAL] getType() const Returns std::string e.g. 'Domestic', 'International', 'Charter'
operator<< (friend) Prints flightNumber, route, dateTime, seats, fare to ostream
saveToFile(ofstream&) const Writes all attributes to file in fixed order — implemented by derived
4.2 DomesticFlight — Derived from Flight
Extra attribute taxRate (double) — e.g. 0.05 (5%)
calculateBaseFare() Returns: baseFare * (1 + taxRate). baseFare is a fixed value passed at construction e.g. 5000.0
displayDetails() Prints all Flight fields + 'Type: Domestic' + taxRate
getType() Returns "Domestic"
Constructor DomesticFlight(flightNumber, origin, destination, dateTime, totalSeats, baseFare, taxRate)
saveToFile() Write: type tag 'D', then base fields, then taxRate, then baseFare
4.3 InternationalFlight — Derived from Flight
Extra attributes visaRequired (bool), internationalTax (double), baseFare (double)
calculateBaseFare() Returns: baseFare * (1 + internationalTax)
displayDetails() Prints all Flight fields + 'Type: International' + visa status + tax
getType() Returns "International"
Constructor InternationalFlight(flightNumber, origin, destination, dateTime, totalSeats, baseFare, internationalTax, visaRequired)
saveToFile() Write: type tag 'I', then base fields, then baseFare, internationalTax, visaRequired
4.4 CharterFlight — Derived from Flight
Extra attributes contractHolder (std::string), charterFee (double)
calculateBaseFare() Returns: charterFee / totalSeats  (per-seat cost)
displayDetails() Prints all Flight fields + 'Type: Charter' + contractHolder + charterFee
getType() Returns "Charter"
Constructor CharterFlight(flightNumber, origin, destination, dateTime, totalSeats, charterFee, contractHolder)
saveToFile() Write: type tag 'C', then base fields, then charterFee, contractHolder
4.5 Passenger (Abstract Base Class) — include/Passenger.h + src/Passenger.cpp
passengerID std::string — unique e.g. P001
name std::string
email std::string
phone std::string
bookingHistory std::vector<std::string> — stores ticket IDs
Methods
Passenger(…) constructor Initialise all attributes
virtual ~Passenger() Virtual destructor
getPassengerID() / getName() / getEmail() / getPhone() Getters
addToHistory(ticketID) Push ticketID into bookingHistory
removeFromHistory(ticketID) Erase ticketID from bookingHistory
getBookingHistory() const Returns const ref to bookingHistory vector
displayInfo() const Prints ID, name, email, phone, class, history
[PURE VIRTUAL] getBaggageAllowance() const Returns double (kg)
[PURE VIRTUAL] getLoyaltyMultiplier() const Returns double
[PURE VIRTUAL] getRefundPercentage(int daysBeforeDeparture) const Returns double 0.0–1.0
[PURE VIRTUAL] getPassengerClass() const Returns std::string
saveToFile(ofstream&) const Write all attributes — implemented by derived
4.6 EconomyPassenger — Derived from Passenger
getBaggageAllowance() Returns 20.0 (kg)
getLoyaltyMultiplier() Returns 1.0
getRefundPercentage(days) days >= 7: return 0.5 (50%), days >= 3: return 0.25, else: return 0.0
getPassengerClass() Returns "Economy"
saveToFile() Write type tag 'E', then all Passenger base fields
4.7 BusinessPassenger — Derived from Passenger
getBaggageAllowance() Returns 35.0 (kg)
getLoyaltyMultiplier() Returns 1.5
getRefundPercentage(days) days >= 7: return 0.75, days >= 3: return 0.5, else: return 0.25
getPassengerClass() Returns "Business"
saveToFile() Write type tag 'B', then all Passenger base fields
4.8 FirstClassPassenger — Derived from Passenger
getBaggageAllowance()
getLoyaltyMultiplier()
getRefundPercentage(days)
Returns 50.0 (kg)
Returns 2.0
days >= 7: return 1.0 (100%), days >= 3: return 0.75, else: return 0.5
getPassengerClass()
saveToFile()
Returns "FirstClass"
Write type tag 'F', then all Passenger base fields
4.9 Ticket — include/Ticket.h + src/Ticket.cpp
Links one Passenger to one Flight. Holds booking details.
ticketID std::string — unique e.g. T001, T002 (auto-generated by Airline)
passengerID std::string
flightNumber std::string
seatNumber std::string — e.g. '12A' (generate sequentially)
farePaid double — snapshot of calculateBaseFare() at booking time
status std::string — 'CONFIRMED' or 'CANCELLED'
bookingDate std::string — date ticket was created YYYY-MM-DD
Methods
Ticket(…) constructor Set all above fields
All getters getTicketID, getPassengerID, getFlightNumber, getSeatNumber, getFarePaid, getStatus, getBookingDate
setStatus(s) Set status to 'CONFIRMED' or 'CANCELLED'
isConfirmed() const Returns status == 'CONFIRMED'
displayTicket() const Print all fields neatly to console
operator== (friend) Returns true if ticketID == other.ticketID
operator<< (friend) Prints ticket summary to ostream
saveToFile(ofstream&) Write all 7 fields to file, one per line
loadFromFile(ifstream&) Static factory: read 7 lines, return Ticket object
4.10 Airline — include/Airline.h + src/Airline.cpp
Central manager class. Owns all flights, passengers, and tickets.
Attributes (all private)
flights std::vector&lt;Flight*&gt; — owns heap-allocated Flight objects
passengers std::vector&lt;Passenger*&gt; — owns heap-allocated Passenger objects
tickets std::vector&lt;Ticket&gt; — value objects
nextTicketID int — counter for auto-generating ticket IDs (start at 1)
dataFilePath std::string — path to persistence file
Methods — Flight Management
addFlight(Flight*) Append to flights vector
removeFlight(flightNumber) Find by number, delete pointer, erase from vector. Throws FlightNotFoundException if not found.
findFlight(flightNumber) Returns Flight* or nullptr
searchByRoute(origin, destination)Returns vector of matching Flight*
searchByDate(date) Returns vector of Flight* where date matches YYYY-MM-DD prefix of departureDateTime
listAllFlights() Calls displayDetails() on every flight via pointer (polymorphism)
Methods — Passenger Management
addPassenger(Passenger*)
Append to passengers vector
removePassenger(passengerID) Find, delete pointer, erase. Throws PassengerNotFoundException.
findPassenger(passengerID)
listAllPassengers()
Returns Passenger* or nullptr
viewPassengerHistory(passengerID)Find passenger, print each ticketID in bookingHistory with full ticket details
Calls displayInfo() on every passenger
Methods — Booking & Cancellation
bookTicket(passengerID, flightNumber)
cancelTicket(ticketID)
(1) Find passenger & flight — throw if not found. (2) Check if flight is full — throw FlightFullException. (3) Check if passenger already has CONFIRMED ticket on this flight — throw InvalidCancellationException. (4) Call flight->bookSeat(). (5) Generate ticketID, seatNumber, create Ticket. (6) Add ticket to tickets vector. (7) Add ticketID to passenger history. Returns Ticket.
(1) Find ticket — throw if not found. (2) Check status != CANCELLED already. (3) Compute daysBeforeDeparture from bookingDate to departure date. (4) Call passenger->getRefundPercentage(days). (5) Compute refundAmount = farePaid * refundPercentage. (6) Call flight->cancelSeat(). (7) Set ticket status = CANCELLED. (8) Print refund amount. Returns refundAmount.
Methods — Reports
reportTodayDepartures()
reportOccupancy()
reportTopRevenueFlights()
Get today's date (use system clock). Filter flights where departureDateTime starts with today's date. Print each.
For each flight print: flightNumber, route, getOccupancyPct()%.
For each confirmed ticket sum farePaid per flight for current month. Sort descending. Print top 5.
Methods — Persistence
saveToFile()
loadFromFile()
Open dataFilePath for writing. Write section markers [FLIGHTS], [PASSENGERS], [TICKETS]. For each item call its saveToFile(ofstream&). Handle file errors gracefully (print warning, don't crash).
Open dataFilePath for reading. If file doesn't exist, return silently. Read section by section. Reconstruct Flight* (check type tag D/I/C), Passenger* (tag E/B/F), Ticket objects. Set nextTicketID to max existing ID + 1.
Destructor
~Airline(): loop through flights vector and delete each pointer; loop through passengers and delete each pointer.
5. Exception Classes — include/Exceptions.h
Define all four in one header file. Each extends std::exception.
class FlightFullException : public std::exception { std::string msg; public:
FlightFullException(const std::string& flightNum) : msg("Flight " + flightNum + " is full.")
{} const char* what() const noexcept override { return msg.c_str(); } }; class
InvalidCancellationException : public std::exception { std::string msg; public:
InvalidCancellationException(const std::string& reason) : msg("Invalid cancellation: " +
reason) {} const char* what() const noexcept override { return msg.c_str(); } }; class
PassengerNotFoundException : public std::exception { std::string msg; public:
PassengerNotFoundException(const std::string& id) : msg("Passenger not found: " + id) {} const
char* what() const noexcept override { return msg.c_str(); } }; class FlightNotFoundException
: public std::exception { std::string msg; public: FlightNotFoundException(const std::string&
fn) : msg("Flight not found: " + fn) {} const char* what() const noexcept override { return
msg.c_str(); } };
6. Template Search Utility — include/Utils.h + src/Utils.cpp
Provide a generic search function template that works for both Flight* and Passenger* vectors.
// In Utils.h #pragma once #include #include template T* findByPredicate(const std::vector&
collection, std::function predicate) { for (T* item : collection) { if (predicate(item))
return item; } return nullptr; } // Usage example in Airline.cpp: // Flight* f =
findByPredicate(flights, // [&](Flight* fl){ return fl->getFlightNumber() == flightNumber; });
7. STL Usage Requirements
std::vector<Flight*> Primary container for flights in Airline
std::vector<Passenger*> Primary container for passengers in Airline
std::vector<Ticket> Primary container for tickets in Airline
std::vector<std::string> Used in Passenger::bookingHistory
std::map<std::string,double> Used in reportTopRevenueFlights() to accumulate revenue per flightNumber
std::sort Sort revenue map results to get top 5
std::find_if Find a ticket by ID in the tickets vector
8. Operator Overloading
operator<< for Flight friend ostream& operator<<(ostream& os, const Flight& f) — print flightNumber, route, dateTime, availableSeats/totalSeats, fare
operator<< for Ticket friend ostream& operator<<(ostream& os, const Ticket& t) — print ticketID, passenger, flight, seat, fare, status
operator== for Ticket friend bool operator==(const Ticket& a, const Ticket& b) — returns a.ticketID == b.ticketID
9. Console Menu Structure — src/main.cpp
The main() function creates one Airline object, calls loadFromFile(), runs the menu loop, and calls saveToFile() before
exit.
===== SkyLink Airways Management System ===== 1. Flight Management 1.1 Add Flight (choose
type: D/I/C) 1.2 Remove Flight 1.3 Search Flight (by number / route / date) 1.4 List All
Flights 2. Passenger Management 2.1 Register Passenger (choose class: E/B/F) 2.2 Remove
Passenger 2.3 View Passenger Booking History 2.4 List All Passengers 3. Booking 3.1 Book a
Ticket 3.2 Cancel a Ticket 3.3 View Ticket Details 4. Reports 4.1 Today's Departures 4.2
Flight Occupancy Report 4.3 Top 5 Revenue Flights This Month 0. Exit (saves data
automatically)
Input validation rule: if user enters invalid option, print 'Invalid choice. Try again.' and re-show the menu. If any
operation throws an exception, catch it, print the exception message, and return to menu without crashing.
10. File Persistence Format — data/airline_data.txt
Use plain text. Fields separated by newlines within each record. Records separated by '---'. Sections separated by
markers.
[FLIGHTS] D SK101 Karachi Lahore 2025-08-01 08:00 150 120 5000.0 0.05 --- I SK202 Islamabad
Dubai 2025-08-02 14:30 200 175 15000.0 0.12 1 --- C SK303 Lahore Quetta 2025-08-05 10:00 50 30
500000.0 AcmeCorp --- [PASSENGERS] E P001 Ali Khan ali@email.com 0300-1234567 --- B P002 Sara
Malik sara@email.com 0321-9876543 --- [TICKETS] T001 P001 SK101 12A 5250.0 CONFIRMED
2025-07-20 --
Loading rule: Read the type tag first (D/I/C for flights, E/B/F for passengers), then use it to construct the correct derived class.
11. Seat Number Generation
Generate seat numbers sequentially per flight. Track in Airline as a std::map<std::string, int> (flightNumber →
nextSeatIndex).
// Formula: row = (index / 6) + 1, col = 'A' + (index % 6) // Example: index=0 → "1A", index=5
→ "1F", index=6 → "2A" std::string generateSeat(int index) { int row = (index / 6) + 1; char
col = 'A' + (index % 6); return std::to_string(row) + col; }
12. Date Utility Functions — Utils.h
Add these free functions to Utils.h for use in Airline methods:
#include #include // Get today's date as "YYYY-MM-DD" std::string getTodayDate(); // Calculate
days between two "YYYY-MM-DD" strings (result can be negative) int daysBetween(const
std::string& from, const std::string& to); // Get current month as "YYYY-MM" prefix
std::string getCurrentMonthPrefix();
Implement using std::mktime and std::tm. Parse date strings manually (std::stoi on substrings).
13. Sample Data (10 Flights, 8 Passengers)
Pre-populate the data file with the following for demonstration:
Flights
ID Type From To Date/Time Seats Fare/Fee Extra
SK101 Domestic Karachi Lahore 2025-08-01 08:00 150 5000 Tax 5%
SK102 Domestic Lahore Islamabad 2025-08-01 09:30 120 4500 Tax 5%
SK201 International Islamabad Dubai 2025-08-02 14:30 200 15000 Tax 12%, Visa req
SK202 International Karachi London 2025-08-03 22:00 250 45000 Tax 15%, Visa req
SK203 International Lahore Istanbul 2025-08-04 16:00 180 30000 Tax 12%, No visa
SK301 Charter Islamabad Skardu 2025-08-05 07:00 50 500000 AcmeCorp
SK302 Charter Karachi Gwadar 2025-08-06 11:00 30 300000 OilCo Ltd
SK103 Domestic Peshawar Karachi 2025-08-07 13:00 100 6000 Tax 5%
SK204 International Islamabad Riyadh 2025-08-08 03:00 220 20000 Tax 12%, Visa req
SK104 Domestic Quetta Lahore 2025-08-09 15:00 90 5500 Tax 5%
Passengers
ID
P001
P002
P003
P004
P005
P006
P007
Name
Ali Khan
Sara Malik
Ahmed Raza
Fatima Noor
Usman Tariq
Zainab Ali
Email
ali@sky.com
sara@sky.com
ahmed@sky.com
fatima@sky.com
Phone
0300-1111111
0321-2222222
Class
Economy
Business
0333-3333333
0312-4444444
usman@sky.com
zainab@sky.com
Hassan Mir
P008
Amna Sheikh
hassan@sky.com
amna@sky.com
0345-5555555
0300-6666666
0321-7777777
0333-8888888
FirstClass
Economy
Business
Economy
FirstClass
Business
14. Makefile
CXX = g++ CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude SRCS = $(wildcard src/*.cpp) OBJS =
$(SRCS:src/%.cpp=build/%.o) TARGET = skylink all: $(TARGET) $(TARGET): $(OBJS) $(CXX)
$(CXXFLAGS) -o $@ $^ build/%.o: src/%.cpp @mkdir -p build $(CXX) $(CXXFLAGS) -c $< -o $@
clean: rm -rf build $(TARGET) run: all ./$(TARGET)
15. Hard Rules for the AI Coder
•   No extra features. Implement ONLY what is described in this document. No GUI, no networking, no database.
•   No raw new/delete inside methods — except in Airline::addFlight / addPassenger where pointers are passed
in, and Airline destructor where they are deleted.
•   No global variables. All state is inside the Airline object.
•   Every .h file must start with #pragma once.
•   All data members private (use protected only in Flight and Passenger for subclass access if absolutely
necessary).
•   Do not use system('cls') or system('clear'). Use plain newlines to separate menu sections.
•   Input validation: all console inputs must be validated. Never trust raw cin for numbers without checking failbit.
•   No hard-coded passenger or flight data inside source code. All sample data goes in airline_data.txt.
•   Comments: every method in every .cpp file must have at least one inline comment explaining non-obvious
logic.
•   Compile clean: zero warnings with g++ -std=c++17 -Wall -Wextra.
•   Memory: Airline destructor must delete all Flight* and Passenger* pointers. No leaks.
•   Exception safety: all exception throws must be caught in the menu loop in main.cpp. The program must never
crash from bad input.
16. Report & UML Notes (for the student to fill in)
The AI coder does NOT write the report — the student does. But the coder must generate a README.md with build
and run instructions.
README.md must contain:
•   How to build: make
•   How to run: ./skylink
•   How to clean: make clean
•   Compiler requirement: g++ with C++17
•   Data file location: data/airline_data.txt (auto-created on first run)
17. Quick Refund Reference Table
Passenger Class
Economy
Business
First Class
7+ days before
50%
3–6 days before
25%
< 3 days before
0%
75%
100%
50%
75%
25%
50%
End of AI Coding Documentation — SkyLink Airways OOP Assignment
Hand this PDF to the AI coder. No clarification needed — every detail is here.