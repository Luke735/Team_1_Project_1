#pragma once
#ifndef MOVIE_H
#define MOVIE_H
#include "Date.h"
#include <string>

using namespace std;

class Movie {
public:
	//Constructors
	Movie(string, Date, string, Date, bool status);

	//Class member functions
	void set_name(string);
	void set_release_date(int, int, int);
	void set_recieve_date(int, int, int);
	void set_description(string);
	void set_status(bool);

	string get_name();
	string get_description();
	bool get_status();
	Date get_release_date();
	Date get_recieve_date();
private:
	Date release_date, recieve_date;
	string name, description;
	bool status;
};
#endif
