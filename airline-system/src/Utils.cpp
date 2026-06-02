// ============================================================
// Utils.cpp — Implementation of Utility Functions
// OOP Concepts: File Pointer operations (tellg, seekg concepts),
//               Structure usage, Date manipulation
// ============================================================

#include "Utils.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>

// Get today's date formatted as "YYYY-MM-DD"
// Uses system clock via std::time and std::localtime
std::string getTodayDate() {
    // Get current time from system clock
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Format using string stream with zero-padding
    std::ostringstream oss;
    oss << (1900 + localTime->tm_year) << "-"
        << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-"
        << std::setw(2) << std::setfill('0') << localTime->tm_mday;
    return oss.str();
}

// Calculate the number of days between two date strings
// Parses "YYYY-MM-DD" format manually using std::stoi on substrings
int daysBetween(const std::string& from, const std::string& to) {
    // Parse 'from' date — extract year, month, day using substring operations
    int fromYear = std::stoi(from.substr(0, 4));
    int fromMonth = std::stoi(from.substr(5, 2));
    int fromDay = std::stoi(from.substr(8, 2));

    // Parse 'to' date similarly
    int toYear = std::stoi(to.substr(0, 4));
    int toMonth = std::stoi(to.substr(5, 2));
    int toDay = std::stoi(to.substr(8, 2));

    // Build std::tm structures for mktime conversion
    std::tm fromTm = {};
    fromTm.tm_year = fromYear - 1900;  // tm_year is years since 1900
    fromTm.tm_mon = fromMonth - 1;     // tm_mon is 0-based
    fromTm.tm_mday = fromDay;

    std::tm toTm = {};
    toTm.tm_year = toYear - 1900;
    toTm.tm_mon = toMonth - 1;
    toTm.tm_mday = toDay;

    // Convert to time_t and compute difference in seconds, then convert to days
    std::time_t fromTime = std::mktime(&fromTm);
    std::time_t toTime = std::mktime(&toTm);

    // difftime returns seconds; divide by 86400 to get days and round to nearest whole day
    double diffSeconds = std::difftime(toTime, fromTime);
    return static_cast<int>(std::round(diffSeconds / 86400.0));
}

// Get current month prefix as "YYYY-MM" for filtering tickets by month
std::string getCurrentMonthPrefix() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Build "YYYY-MM" string
    std::ostringstream oss;
    oss << (1900 + localTime->tm_year) << "-"
        << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon);
    return oss.str();
}

// Generate seat number from sequential index
// Formula: row = (index / 6) + 1, col = 'A' + (index % 6)
// Example: index=0 -> "1A", index=5 -> "1F", index=6 -> "2A"
std::string generateSeat(int index) {
    int row = (index / 6) + 1;          // 6 seats per row (A-F)
    char col = 'A' + (index % 6);       // Column letter A through F
    return std::to_string(row) + col;   // Concatenate e.g. "1A"
}
