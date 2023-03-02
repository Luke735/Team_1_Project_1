#include "Date.h"

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
