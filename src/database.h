#pragma once

#include "date.h"
#include "node.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <functional>

class Database {
public:
	Database(){}
	void Add(const Date& date, const std::string& event);
	int RemoveIf (const std::function<bool(const Date&, const std::string&)> predicate);
	std::vector<std::string> FindIf (const std::function<bool(const Date&, const std::string&)> predicate) const;
	void Print(std::ostream& os) const;
	std::string Last (const Date& date) const;
private:
	std::map<Date, std::set<std::string>> s_date_to_events;
	std::map<Date, std::vector<std::string>> v_date_to_events;
};
