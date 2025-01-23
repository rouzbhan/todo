
#pragma once

#include <string>
#include <vector>



class Task {
private:

	

	std::string name;

	std::string description;

	std::string date;

	std::string status;

	int hours, minutes;

	
	int total;
public:
	Task(std::string n, std::string des, std::string d, int h, int m, std::string s) :
		name(n), description(des), date(d), hours(h), minutes(m), status(s)
	{
		total = std::stoi(d.substr(0, d.find('/'))) * 365 * 24 * 60;

		d.erase(0, d.find('/')+1);

		total += std::stoi(d.substr(0, d.find('/'))) * 30 * 24 * 60;

		d.erase(0, d.find('/')+1);

		total += std::stoi(d.substr(0, 2)) * 24 * 60;

		total = total + hours * 60 + minutes;

		
	}
	int get_total() const {
		return total;
	}
	std::string Name() const {
		return name;
	}
	std::string Description()const {
		return description;
	}
	std::string Date() const {
		return date;
	}
	std::string Status() const {
		return status;
	}
	int Hours() const {
		return hours;
	}
	int Minutes() const {

		return minutes;
	}
	void set_name(std::string name) {
		this->name = name;
	}
	void set_description(std::string des) {
		this->description = des;
	}
	void set_date(std::string d) {
		this->date = d;
	}
	void set_hours(std::string h){
		hours = stoi(h);
	}
	void set_minutes(std::string m) {
		minutes = stoi(m);
	}
	void set_status(std::string s) {
		status = s;
	}
	void calculate_total() {
		total = std::stoi(date.substr(0, date.find('/'))) * 365 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, date.find('/'))) * 30 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, 2)) * 24 * 60;

		total = total + hours * 60 + minutes;

	}
	};


