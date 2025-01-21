#pragma once

#include <string>

class SubTask {
private:
	friend void build_Tree(std::vector &, Node * );
	
	std::string name;

	std::string description;

	std::string date;

	std::string status;

	int hours, minutes;

	Task* father;

	SubTask* right_sibling;

	unsigned int total;




public:
	SubTask(std::string n, std::string des, std::string d, int h, int m, std::string s, Task*& p) :
		name(n), description(des), date(d), hours(h), minutes(m), status(s)
	{
		total = std::stoi(date.substr(0, date.find('/'))) * 365 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, date.find('/'))) * 30 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, date.length()) * 24 * 60;

		total = total + hours * 60 + minutes;

		father = p;

		right_sibling = nullptr;
	}


};
class Task {
private:
	std::string name;

	std::string description;

	std::string date;

	std::string status;

	int hours, minutes;

	SubTask* left_child;
	int total;
public:
	Task(std::string n, std::string des, std::string d, int h, int m, std::string s) :
		name(n), description(des), date(d), hours(h), minutes(m), status(s)
	{
		total = std::stoi(date.substr(0, date.find('/'))) * 365 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, date.find('/'))) * 30 * 24 * 60;

		date.erase(0, date.find('/'));

		total += std::stoi(date.substr(0, date.length()) * 24 * 60;

		total = total + hours * 60 + minutes;

		left_child = nullptr;

	};