# SkyLink Airways — Airline Reservation & Flight Management System

## OOP (C++) Individual Assignment

A console-based airline management system built in C++17 demonstrating core OOP concepts including:
- **Inheritance** (Single, Hierarchical) — Flight & Passenger class hierarchies
- **Polymorphism** (Compile-time & Run-time) — Virtual functions, Operator overloading
- **Encapsulation** — Private/protected members with getters/setters
- **Abstraction** — Abstract base classes with pure virtual functions
- **Composition & Aggregation** — Airline owns Flight/Passenger objects
- **File Handling** — ifstream, ofstream, file pointers (tellg, seekg)
- **Exception Handling** — Custom exception classes
- **Friend Functions** — operator<< and operator==
- **Static Functions** — Ticket::loadFromFile()
- **Templates** — Generic search utility

## How to Build

```bash
make
```

## How to Run

```bash
./skylink
```

## How to Clean

```bash
make clean
```

## Compiler Requirement

- **g++** with C++17 support
- Compile flags: `-std=c++17 -Wall -Wextra`

## Data File

- Location: `data/airline_data.txt`
- Auto-created on first run
- Pre-populated with 10 flights and 8 passengers for demonstration

## Project Structure

```
airline-system/
├── Makefile
├── README.md
├── data/
│   └── airline_data.txt
├── include/
│   ├── Flight.h              (Abstract base class)
│   ├── DomesticFlight.h
│   ├── InternationalFlight.h
│   ├── CharterFlight.h
│   ├── Passenger.h            (Abstract base class)
│   ├── EconomyPassenger.h
│   ├── BusinessPassenger.h
│   ├── FirstClassPassenger.h
│   ├── Ticket.h
│   ├── Airline.h              (Central manager — Composition)
│   ├── Exceptions.h
│   └── Utils.h
└── src/
    ├── main.cpp
    ├── Flight.cpp
    ├── DomesticFlight.cpp
    ├── InternationalFlight.cpp
    ├── CharterFlight.cpp
    ├── Passenger.cpp
    ├── EconomyPassenger.cpp
    ├── BusinessPassenger.cpp
    ├── FirstClassPassenger.cpp
    ├── Ticket.cpp
    ├── Airline.cpp
    └── Utils.cpp
```
