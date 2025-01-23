#pragma once
#include "tt.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
//void Main_program();
class Node {
private:
	friend void append(Task&, Node*&);
	Task data;
	Node* left, * right, * parent;
public:
	Node(Task d):
		data(d) {
		left = right = parent = nullptr;
	}
	void set_father(Node* dad) {
		parent = dad;
	}
	void set_left(Node* l) {
		left = l;
	}
	void set_right(Node* r) {
		right = r;
	}
	Node* get_father() const {
		return parent;
	}
	Node* get_left() const {
		return left;
	}
	Node* get_right() const {
		return right;
	}
	Task get_data() const {
		return data;
	}
};

void append(Task & Data,Node *& root) {
	if (!root) {
		root = new Node(Data);
		return;
	}
	else {
		Node** ptr =&root->left;
		if (!ptr) {
			*ptr = new Node(Data);
			root->set_left(*ptr);
			return;
		}
		while (*ptr) {
			ptr = &((*ptr)->right);
		}

		*ptr = new Node(Data);
		(*ptr)->set_father(root);
	}
}
int left(int i) { return (i << 1) + 1; }

int right(int i) { return (i << 1) + 2; }

int parent(int i) { return i >> 1; }


void write_to_info(std::vector<Node*>& list) {
	std::ofstream file("info.txt");
	for (auto data : list) {
		if (data->get_left() == nullptr) {
			file << data->get_data().Name() << ", " << data->get_data().Description() << ", " << data->get_data().Date() << ", "
				<< data->get_data().Hours() << ":" << data->get_data().Minutes() << ", " << data->get_data().Status() << std::endl;
		}
		else {
			auto ptr = data->get_left();
			while (ptr) {
				file << "+" << ptr->get_data().Name() << ", " << ptr->get_data().Description() << ", " << ptr->get_data().Date() << ", "
					<< ptr->get_data().Hours() << ":" << ptr->get_data().Minutes() << ", " << ptr->get_data().Status() << std::endl;
				ptr = ptr->get_right();
			}
		}
		file.close();
	}
}



void max_heapify(std::vector<Node*>& tasks, int i) {
	int largest;
	int n = tasks.size();
	int l = left(i);
	int r = right(i);
	if (l < n && tasks[l]->get_data().get_total() > tasks[i]->get_data().get_total()) {
		largest = l;
	}
	else largest = i;
	if (r < n && tasks[r]->get_data().get_total() > tasks[largest]->get_data().get_total()) {
		largest = r;
	}
	if (largest != i) {
		std::swap(tasks[i], tasks[largest]);
		max_heapify(tasks, largest);
	}
}

void build_max_heap(std::vector<Node*>& tasks, int n) {
	for (int i = n; i >= 0; i--) {
		max_heapify(tasks, i);
	}
}

void heapSort(std::vector<Node* >& tasks) {
	int n = tasks.size();
	build_max_heap(tasks, n);
	for (int i = n - 1; i >= 1; i--) {
		std::swap(tasks[0], tasks[i]);
		n -= 1;
		max_heapify(tasks, 0);
	}
}

std::vector<Node*>  Read_and_extract() {
	std::ifstream file("info.txt");
	std::vector<Node*> list;
	std::string s;
	while (std::getline(file, s)) {
		if (s.find("+") != std::string::npos) {
			std::string name, des, status, date, time;
			name = s.substr(1, s.find(',')-1);
			s.erase(0, s.find(',')+1);
			des = s.substr(0, s.find(',') );
			s.erase(0, s.find(',')+1);
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+1);
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+1);
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+1);
			int hours = stoi(time.substr(0, time.find(':') + 1));
			time.erase(0, time.find(':') + 1);
			int min = stoi(time);
			std::cout << date;
			std::cout << name << des << hours << min << status;
			
			Task  data(name, des, date, hours, min, status);
			append(data, list[list.size() - 1]);

		}
		else {
			std::string name, des, status, date, time;
			//s.erase('+');
			name = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 1);
			des = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 1);
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 1);
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 1);
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 1);
			int hours = stoi(time.substr(0, time.find(':') + 1));
			time.erase(0, time.find(':') + 1);
			int min = stoi(time);
			std::cout << date;
			std::cout << name << des << hours << min << status;

			Task  data(name, des, date, hours, min, status);
			Node* node = new Node(data);
			list.push_back(node);
		}

	}
	std::string name, des, status, date, time;
	
	
	return list;

}

void organize(std::vector<Node*>& list) {
	heapSort(list);
}
void show(std::vector<Node*>& list) {

	std::system("cls");
	int j = 0;
	for (auto i : list) {
		std::cout <<j<<"_" << " Name : " << i->get_data().Name() << std::endl;
		j++;
	}
	
}

void show_subtasks(Node* root) {
	std::system("cls");
	std::cout << "task : " << root->get_data().Name() << std::endl;
	Node* ptr = root->get_left();
	int i = 0;
	if (!ptr) {
		std::cout << "\t\t\t" << "No subtasks yet!\n";
		return;
	}
	while (ptr) {
		std::cout <<"\t\t\t" << i << "-" << "Name: " << ptr->get_data().Name() << std::endl;
		i++;
		ptr = ptr->get_right();
	}
}

void add_Task(std::vector<Node*>& list,std::string command) {
	std::system("cls");

	std::string name, des, date, status;
	int hour, min;
	
	command.erase(0, 9);
	name = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 1);
	des = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 1);
	date = command.substr(0, 10);
	command.erase(0, 10);
	hour = stoi(command.substr(0, command.find(':')));
	command.erase(0, command.find(':') + 1);
	min = stoi(command.substr(0, command.find(',')));
	command.erase(0, command.find(',') + 1);
	status = command;
	Task data(name, des, date, hour, min, status);

	Node* node = new Node(data);
	list.push_back(node);
	organize(list);
	std::cout << "Task Added!" << std::endl;
	Sleep(5);
	std::system("cls");
	write_to_info(list);
	
	


	}

void add_sub_Task(std::vector<Node*>& list, std::string command) {
	std::system("cls");

	std::string name, des, date, status;
	int hour, min;

	command.erase(0, 11);
	name = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 2);
	des = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 2);
	date = command.substr(0, 10);
	command.erase(0, 11);
	hour = stoi(command.substr(0, command.find(':')));
	command.erase(0, command.find(':') + 1);
	min = stoi(command.substr(0, command.find(',')));
	command.erase(0, command.find(',') + 2);
	status = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 2);
	std::string father = command;
	
	Task data(name, des, date, hour, min, status);
	for (auto & ptr : list) {
		if (ptr->get_data().Name() == father) {
			append(data, ptr);
			break;
		}
	}
	write_to_info(list);
	std::cout << "SubTask added!" << std::endl;
	Sleep(5);
	

	
}