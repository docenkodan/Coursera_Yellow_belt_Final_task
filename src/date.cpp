#include "date.h"

#include <iomanip>

using namespace std;

Date::Date (const int& new_year, const int& new_month,
		const int& new_day) {
	year = new_year;
	if (new_month >= 1 && new_month <= 12) {
		month = new_month;
	} else {
		throw logic_error("Month value is invalid: " +
				to_string(new_month));
	}
	if (new_day >= 1 && new_day <= 31) {
			day = new_day;
	} else {
		throw logic_error("Day value is invalid: " +
				to_string(new_day));
	}
}
int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}


Date ParseDate (istream& is) {
	if (is.peek() == ' ') {
		is.get();
	}
	string date;
	getline(is, date, ' ');
	istringstream date_stream(date);
	int year = 0, month = 0, day = 0;
	char c1, c2;
	date_stream >> year >> c1 >> month >> c2 >> day;
	if (date_stream && c1 == '-' && c2 == '-' && date_stream.eof()) {
		return Date(year, month, day);
	}
	throw logic_error("Wrong date format: " + date);
}

ostream& operator<< (ostream& stream, const Date& date){
	stream << setfill('0') << setw(4) << date.GetYear() << "-" <<
			setw(2) << date.GetMonth() << "-" <<
			setw(2) << date.GetDay();
	return stream;
}

string DateToString (const Date& date) {
	stringstream stream;
	stream << date;
	string s;
	getline(stream, s);
	return s;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() < rhs.GetYear();
	if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() < rhs.GetMonth();
	return lhs.GetDay() < rhs.GetDay();
}

bool operator>(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() > rhs.GetYear();
	if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() > rhs.GetMonth();
	return lhs.GetDay() > rhs.GetDay();
}

bool operator!=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() != rhs.GetYear();
	if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() != rhs.GetMonth();
	return lhs.GetDay() != rhs.GetDay();
}
