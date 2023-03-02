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

std::ostream& operator << (std::ostream& os, const Date& date) {
    os << std::setw(2) << std::setfill('0') << date.day << "/";
    os << std::setw(2) << std::setfill('0') << date.month << "/";
    os << std::setw(4) << std::setfill('0') << date.year;
    return os;
}
