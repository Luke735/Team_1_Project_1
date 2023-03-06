#ifndef DATE_H
#define DATE_H

#include <iostream>

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

    bool operator <= (const Date&);
    bool operator == (const Date&);
    bool isValid() const;

    friend ostream& operator << (ostream&, const Date&);
private:
    int day;
    int month;
    int year;
};
#endif
