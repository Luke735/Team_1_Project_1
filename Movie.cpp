#include "Movie.h"
#include <iostream>

Movie::Movie(string name, Date release_date, string description, Date recieve_date, bool status) {
	this->release_date = release_date;
	this->recieve_date = recieve_date;
	this->name = name;
	this->description = description;
	this->status = status;
}

void Movie::set_name(string name) { this->name = name; }

void Movie::set_description(string description) { this->description = description; }

void Movie::set_status(bool status) { this->status = status; }

void Movie::set_release_date(int day, int month, int year) {
	release_date.set_day(day);
	release_date.set_month(month);
	release_date.set_year(year);
}

void Movie::set_recieve_date(int day, int month, int year) {
	recieve_date.set_day(day);
	recieve_date.set_month(month);
	recieve_date.set_year(year);
}

string Movie::get_name() { return name; }

string Movie::get_description() { return description; }

bool Movie::get_status() { return status; }

Date Movie::get_release_date() { return release_date; }

Date Movie::get_recieve_date() { return recieve_date; }

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
	os << "Name " << movie.name << std::endl;
	os << "Receive date: " << movie.recieve_date << std::endl;
	os << "Release date: " << movie.release_date << std::endl;
	os << "Description: " << movie.description << std::endl;
	os << "Status " << movie.status << std::endl;
	return os;
}
