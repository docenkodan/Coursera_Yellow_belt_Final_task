#include "database.h"

#include <algorithm>

void Database::Add(const Date& date, const string& event) {
	auto p = s_date_to_events[date].insert(event);
	if (p.second) {
		v_date_to_events[date].push_back(event);
	}
}

int Database::RemoveIf (const function<bool(const Date&, const string&)> predicate) {
	int n = 0;
	auto current = find_if(v_date_to_events.begin(), v_date_to_events.end(),
			[predicate](const auto& p) {
		const Date& date = p.first;
		auto it = find_if(p.second.begin(), p.second.end(),
				[predicate, date](const string& event){
			return predicate(date,event);
		});
		return it != p.second.end();
	});
	while (current != v_date_to_events.end()) {
		const Date& date = (*current).first;
		vector<string>& events = (*current).second;
		if (predicate(date,"")) {
			n += v_date_to_events[date].size();
			v_date_to_events.erase(date);
			s_date_to_events.erase(date);
		} else {
			auto it = stable_partition(events.begin(), events.end(),
					[date, predicate](const string& event){
				return !predicate(date,event);
			});
			if (it != events.end()) {
				n += events.end() - it;
				if (it == events.begin()) {
					v_date_to_events.erase(date);
					s_date_to_events.erase(date);
				} else {
					events.erase(it, events.end());
					set<string> new_events (events.begin(), events.end());
					s_date_to_events[date] = new_events;
				}
			}
		}
		current = find_if(v_date_to_events.upper_bound(date), v_date_to_events.end(),
				[predicate](const auto& p) {
			Date date = p.first;
			auto it = find_if(p.second.begin(), p.second.end(),
					[predicate, date](const string& event){
				return predicate(date,event);
			});
			return it != p.second.end();
		});
	}
	return n;
}

vector<string> Database::FindIf (const function<bool(const Date&, const string&)> predicate) const {
	vector<string> result;
	for (const auto& p : v_date_to_events) {
		if (predicate(p.first, "")) {
			for (size_t i = 0; i < p.second.size(); ++i) {
				result.push_back(DateToString(p.first) + ' ' + p.second[i]);
			}
		} else {
			auto it = find_if(p.second.begin(), p.second.end(),
					[predicate, p](const string& event) {
				return predicate(p.first, event);
			});
			while(it != p.second.end()) {
				result.push_back(DateToString(p.first) + ' ' + *it);
				it = find_if(++it, p.second.end(),
						[predicate, p](const string& event) {
					return predicate(p.first, event);
				});
			}
		}
	}
	return result;
}

void Database::Print(ostream& os) const {
	for (const auto& i : v_date_to_events) {
		for (const auto& event : i.second) {
			os << i.first << " " << event << endl;
		}
	}
}

string Database::Last (const Date& date) const {
	auto it = v_date_to_events.upper_bound(date);
	if (it == v_date_to_events.begin()) {
		throw invalid_argument ("No entries");
	}
	--it;
	return DateToString((*it).first) + " " + (*it).second.back();
}

