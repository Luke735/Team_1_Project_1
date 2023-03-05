#include "Date.h"
#include <iostream>
#include <iomanip>

Date::Date() {
    day = 0;
    month = 0;
    year = 0;
}

void Date::set_day(int day) { this->day = day; }

void Date::set_month(int month) { this->month = month; }

void Date::set_year(int year) { this->year = year; }

int Date::get_day() { return this->day; }

int Date::get_month() { return this->month; }

int Date::get_year() { return this->year; }

bool Date:: operator <= (const Date& other) {
    if (this->year < other.year) { return true; }
    else if (this->year > other.year) { return false; }
    else if (this->year == other.year) {
        if (this->month < other.month) { return true; }
        else if (this->month > other.month) { return false; }
        else if (this->month == other.month) {
            if (this->day < other.day) { return true; }
            else if (this->day > other.day) { return false; }
            else { return true; }
        }
    }
}

bool Date:: operator == (const Date& other) {
    if ((this->get_day() == other.day) && (this->get_month() == other.month) && (this->get_year() == other.year)) { return true; }
    else { return false; }
}

std::ostream& operator << (std::ostream& os, const Date& date) {
    os << std::setw(2) << std::setfill('0') << date.day << "/";
    os << std::setw(2) << std::setfill('0') << date.month << "/";
    os << std::setw(4) << std::setfill('0') << date.year;
    return os;
}

bool Date::isValid() const {
    if (year < 0) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        if (day > 29) {
            return false;
        }
        if ((year % 4 != 0 || year % 100 == 0) && year % 400 != 0 && day > 28) {
            return false;
        }
    }
    return true;
}
