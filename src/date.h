#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Date {
public:
	Date (const int& new_year, const int& new_month, const int& new_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

Date ParseDate(std::istream& is);

std::ostream& operator<< (std::ostream& stream, const Date& date);
string DateToString (const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
