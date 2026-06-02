# ✈️ SkyLink Airways Management System

A console-based airline management system built in **C++17**, designed to demonstrate core Object-Oriented Programming principles including inheritance, polymorphism, encapsulation, composition, and file persistence.

---

## 📋 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Data Persistence](#data-persistence)
- [Exception Handling](#exception-handling)

---

## ✨ Features

- **Flight Management** — Add, remove, search, and list Domestic, International, and Charter flights
- **Passenger Management** — Register Economy, Business, and First Class passengers with full profiles
- **Ticket Booking & Cancellation** — Book tickets with auto-generated IDs; cancel with dynamic refund calculation
- **Search & Filters** — Search flights by route or departure date
- **Reports** — View today's departures, flight occupancy stats, and top revenue flights
- **Data Persistence** — All data is automatically saved to and loaded from a file on every run

---

## 📁 Project Structure

```
airline-system/
├── include/                    # Header files
│   ├── Airline.h               # Core manager class
│   ├── Flight.h                # Abstract base class for flights
│   ├── DomesticFlight.h        # Domestic flight (base fare + tax)
│   ├── InternationalFlight.h   # International flight (visa, intl. tax)
│   ├── CharterFlight.h         # Charter flight (contract holder, flat fee)
│   ├── Passenger.h             # Abstract base class for passengers
│   ├── EconomyPassenger.h      # Economy class passenger
│   ├── BusinessPassenger.h     # Business class passenger
│   ├── FirstClassPassenger.h   # First class passenger
│   ├── Ticket.h                # Ticket entity
│   ├── Exceptions.h            # Custom exception classes
│   └── Utils.h                 # Utility helpers
├── src/                        # Source files
│   ├── main.cpp                # Entry point & menu system
│   ├── Airline.cpp
│   ├── Flight.cpp
│   ├── DomesticFlight.cpp
│   ├── InternationalFlight.cpp
│   ├── CharterFlight.cpp
│   ├── Passenger.cpp
│   ├── EconomyPassenger.cpp
│   ├── BusinessPassenger.cpp
│   ├── FirstClassPassenger.cpp
│   ├── Ticket.cpp
│   └── Utils.cpp
├── data/
│   └── airline_data.txt        # Persistent data store
├── build/                      # Compiled object files (auto-generated)
├── Makefile
└── skylink.exe                 # Pre-built Windows executable
```

---

## 🧠 OOP Concepts Demonstrated

| Concept | Where Applied |
|---|---|
| **Abstract Classes** | `Flight`, `Passenger` (pure virtual functions) |
| **Hierarchical Inheritance** | `Flight` → `DomesticFlight`, `InternationalFlight`, `CharterFlight` |
| **Hierarchical Inheritance** | `Passenger` → `EconomyPassenger`, `BusinessPassenger`, `FirstClassPassenger` |
| **Run-Time Polymorphism** | `calculateBaseFare()`, `displayDetails()`, `getType()` via base pointers |
| **Composition** | `Airline` owns and manages `Flight*` and `Passenger*` objects |
| **Aggregation** | `Passenger` holds a history of ticket IDs (does not own `Ticket` objects) |
| **Encapsulation** | All data members private/protected; accessed via getters |
| **Custom Exceptions** | `FlightFullException`, `PassengerNotFoundException`, `InvalidCancellationException`, `FlightNotFoundException` |
| **Operator Overloading** | `operator<<` for `Flight` output (friend function) |
| **Virtual Destructor** | `~Flight()`, `~Passenger()` to ensure correct polymorphic cleanup |
| **File I/O** | `saveToFile()` / `loadFromFile()` with `ofstream` / `ifstream` |

---

## 🚀 Getting Started

### Prerequisites

- **g++** with C++17 support (`g++ --version`)
- **make** (Linux/macOS) or MinGW (Windows)

### Build & Run

```bash
# Clone or extract the project
cd airline-system

# Build
make

# Run
make run
```

### Windows (pre-built)

A pre-built executable is included for Windows:

```cmd
skylink.exe
```

### Clean Build Artifacts

```bash
make clean
```

---

## 🖥️ Usage

On launch, the system loads saved data from `data/airline_data.txt` and presents an interactive menu:

```
===== SkyLink Airways =====
1. Flight Management
2. Passenger Management
3. Booking & Cancellation
4. Reports
0. Exit
```

**Flight types when adding a flight:**
- `D` — Domestic (base fare + tax rate)
- `I` — International (base fare + international tax + visa requirement)
- `C` — Charter (flat charter fee + contract holder name)

**Passenger classes when registering:**
- `E` — Economy
- `B` — Business
- `F` — First Class

---

## 💾 Data Persistence

All flights, passengers, and tickets are saved automatically to `data/airline_data.txt` on exit and reloaded on startup. The file uses a structured plain-text format with `---` as record separators and `[FLIGHTS]`, `[PASSENGERS]`, `[TICKETS]` as section headers.

---

## ⚠️ Exception Handling

The system uses custom exceptions (all inheriting from `std::exception`) to handle error cases gracefully without crashing:

| Exception | Trigger |
|---|---|
| `FlightFullException` | Booking on a flight with no available seats |
| `FlightNotFoundException` | Looking up a non-existent flight number |
| `PassengerNotFoundException` | Looking up a non-existent passenger ID |
| `InvalidCancellationException` | Cancelling a ticket that cannot be cancelled |

All exceptions are caught in `main.cpp` and displayed as user-friendly messages.
