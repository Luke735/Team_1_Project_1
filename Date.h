#pragma once
#ifndef DATE_H
#define DATE_H

using namespace std;

class Date {
public:
    //Constructors
    Date();
    //Class member functions
    void set_day(int day);
    void set_month(int month);
    void set_year(int year);
    int get_day();
    int get_month();
    int get_year();
private:
    int day;
    int month;
    int year;
};
#endif
