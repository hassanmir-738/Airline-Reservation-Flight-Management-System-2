#pragma once
// ============================================================
// Utils.h — Utility Functions, Templates & Structures
// OOP Concepts: Structures, Arrays of Structures, Structure Pointers,
//               Template Functions, File Pointer concepts
// ============================================================

#include <string>
#include <vector>
#include <functional>
#include <ctime>

// ---- STRUCTURE (OOP Topic 1) ----
// Structure to hold revenue data for report generation
// Demonstrates: Structures, used in arrays of structures for sorting
struct RevenueEntry {
    std::string flightNumber;  // Flight identifier
    double revenue;            // Total revenue for this flight
};

// ---- TEMPLATE FUNCTION ----
// Generic search function that works for both Flight* and Passenger* vectors
// Demonstrates: Templates, generic programming
template <typename T>
T* findByPredicate(const std::vector<T*>& collection,
                   std::function<bool(T*)> predicate) {
    // Iterate through collection and return first match
    for (T* item : collection) {
        if (predicate(item))
            return item;
    }
    return nullptr;  // Return nullptr if no match found
}

// ---- DATE UTILITY FUNCTIONS ----
// Get today's date as "YYYY-MM-DD" string
std::string getTodayDate();

// Calculate days between two "YYYY-MM-DD" strings (result can be negative)
int daysBetween(const std::string& from, const std::string& to);

// Get current month as "YYYY-MM" prefix for filtering
std::string getCurrentMonthPrefix();

// ---- SEAT GENERATION ----
// Generate seat number from sequential index (e.g., 0 -> "1A", 5 -> "1F", 6 -> "2A")
std::string generateSeat(int index);
