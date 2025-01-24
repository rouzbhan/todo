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
	friend void edit_Task(std::vector<Node*>& list, std::string& name);
	friend void edit_subtask(std::vector<Node*>& list, std::string& command);
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
void add_Task(std::vector<Node*>& list, std::string command);
void add_sub_Task(std::vector<Node*>& list, std::string command);

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


void delete_node(std::vector<Node*>& list) {
	int it = 0;
	while (it < list.size()) {
		if (list[it]->get_data().Status() == "done") {
			list.erase(std::find(list.begin(),list.end(),list[it]));
			continue;
		}
		it++;
	}

}



void write_to_info(std::vector<Node*>& list) {
	std::ofstream file("info.txt");
	for (auto data : list) {
		if (data->get_left() == nullptr) {
			file << data->get_data().Name() << ", " << data->get_data().Description() << ", " << data->get_data().Date() << ", "
				<< data->get_data().Hours() << ":" << data->get_data().Minutes() << ", " << data->get_data().Status() << std::endl;
		}
		else {
			file << data->get_data().Name() << ", " << data->get_data().Description() << ", " << data->get_data().Date() << ", "
				<< data->get_data().Hours() << ":" << data->get_data().Minutes() << ", " << data->get_data().Status() << std::endl;
			auto ptr = data->get_left();
			while (ptr) {
				file << "+" << ptr->get_data().Name() << ", " << ptr->get_data().Description() << ", " << ptr->get_data().Date() << ", "
					<< ptr->get_data().Hours() << ":" << ptr->get_data().Minutes() << ", " << ptr->get_data().Status() << std::endl;
				ptr = ptr->get_right();
			}
		}
	}
	file.close();

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
	for (int i = n - 1; i > 1; i--) {
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
			s.erase(0, s.find(',')+2);
			des = s.substr(0, s.find(',') );
			s.erase(0, s.find(',')+2);
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+2);
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+2);
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(',')+2);
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
			s.erase(0, s.find(',') + 2);
			des = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 2);
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 2);
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 2);
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(',') + 2);
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
	
	
	
	system("cls");
	int width = 100, height = list.size()+25;
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, 9);
	for (int i = 0; i < width;i++) {
		std::cout << ((i % 2 == 0) ? '-' : ' ');
	}
	int it = 0;
	std::cout << std::endl;
	for (int i = 0;i < height - 2;i++) {
		int j = 0;
		while (j < width) {
			if (j == 0 || j == width - 1) {
				std::cout << "|";
				j++;
			}
			else if (j == 3 && it < list.size()) {
				SetConsoleTextAttribute(hconsole, 6);
				std::cout <<it + 1 << "-";
				SetConsoleTextAttribute(hconsole, 4);
				std::cout << list[it]->get_data().Name() << "-" << list[it]->get_data().Date() << "-" << list[i]->get_data().Hours() << ":" <<
					list[it]->get_data().Minutes();
				j += (9 + list[it]->get_data().Name().size() + list[it]->get_data().Date().size());
				SetConsoleTextAttribute(hconsole, 9);
				it++;
			}
			else {
				std::cout << " ";
				j++;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < width;i++) {
		std::cout << ((i % 2 == 0) ? '-' : ' ');
	}
	SetConsoleTextAttribute(hconsole, 6);
	std::cout << std::endl << "command: ";
	SetConsoleTextAttribute(hconsole, 7);
	std::string command;
	int g = getchar();
	std::getline(std::cin,command);
	if (command.find("add task") != std::string::npos) {
		add_Task(list, command);
	}
	else if (command.find("add subtask") != std::string::npos) {
		add_sub_Task(list, command);
	}
	else if (command.find("edit task") != std::string::npos) {
		edit_Task(list, command);
	}
	else if (command.find("edit subtask") != std::string::npos) {
		edit_subtask(list, command);
	}
	
	else if (command.find("exit") != std::string::npos) {
		return;
	}
	SetConsoleTextAttribute(hconsole, 7);
	
	show(list);

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
	date = command.substr(0, 11);
	command.erase(0, 12);
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
	Sleep(5000);
	

	
}

bool is_done(Node* node) {
	if (node->get_data().Status() == "done") {
		return true;
	}
	auto ptr = node->get_left();
	int done_counter = 0, num = 0;
	while (ptr) {
		if (ptr->get_data().Status() == "done") {
			done_counter++;
		}
		num++;
	}
	if (done_counter == num) return true;
	return false;
}
Node* find_Task(std::vector<Node*>& list, std::string& name) {
	for (auto& node : list) {
		if (node->get_data().Name() == name) {
			return node;
		}
	}
	return nullptr;
}

void edit_Task(std::vector<Node*>& list, std::string& command) {
	std::system("cls");
	command.erase(0, 10);
	auto task = find_Task(list, command);
	if (task) {
		std::cout << "which aspect of the command do you want to change?\n" <<
			"1-name\n2-description\n3-date\n4-time\n5-status\n";
		std::string choice;
		std::getline(std::cin, choice);
		
		system("cls");
		if (choice == "1") {
			std::cout << "enter the new Name:\n";
			std::string name;
			std::getline(std::cin, name);
			task->get_data().set_name(name);
			system("cls");
			std::cout << "Name successfully changed!\n";
			Sleep(3000);

		}
		else if (choice == "2") {
			std::cout << "enter the new description:\n";
			std::string des;
			std::getline(std::cin.ignore('\n'), des);
			task->data.set_description(des);
			system("cls");
			std::cout << "description successfully changed!\n";
			Sleep(3000);
		}
		else if (choice == "3") {
			std::cout << "enter the new Date:\n";
			std::string date;
			std::cin >> date;
			task->data.set_date(date);
			task->data.calculate_total();
			system("cls");
			std::cout << "Date successfully changed\n";
			organize(list);
			Sleep(3000);
		}
		else if (choice == "4") {
		
			std::cout << "enter the new time:\n";
			std::string time;
			std::getline(std::cin, time);
			task->data.set_hours(time.substr(0, time.find(':')));
			task->data.set_minutes(time.substr(time.find(':') + 1, 3));
			task->data.calculate_total();
			organize(list);
			system("cls");
			std::cout << "time successfully changed!\n";
			Sleep(3000);

		}
		else if (choice == "5") {
			std::cout << "changing status to done....";
			Sleep(5000);
			task->data.set_status("done");
			system("cls");
			std::cout << "status successfully changed to done!\n";
			delete_node(list);
			organize(list);
			Sleep(3000);
		}
		else throw std::exception("this choice is not available!\n");
		write_to_info(list);
	}
	else {
		throw std::exception("couldn't find the task!\n");
	}
}
void edit_subtask(std::vector<Node*>& list, std::string & command ) {
	command.erase(0, 13);
	std::string subname = command.substr(0, command.find(','));
	command.erase(0, command.find(',') + 2);
	auto task = find_Task(list, command);
	if (task) {
		if (!task->left) {
			throw std::exception("this task does not have any subtasks!\n");
			Sleep(3000);
		}
		Node** ptr = &(task->left);
		while (ptr && (*ptr)->data.Name() != subname) {
			
			ptr = &((*ptr)->left);
		}
		std::cout << "which aspect of the subtask do you want to change?\n" <<
			"1-name\n2-description\n3-date\n4-time\n5-status\n";
		std::string choice;
		std::getline(std::cin, choice);

		system("cls");
		if (choice == "1") {
			std::cout << "enter the new Name:\n";
			std::string name;
			std::getline(std::cin, name);
			(*ptr)->data.set_name(name);
			system("cls");
			std::cout << "Name successfully changed!\n";
			Sleep(3000);

		}
		else if (choice == "2") {
			std::cout << "enter the new description:\n";
			std::string des;
			std::getline(std::cin.ignore('\n'), des);
			(*ptr)->data.set_description(des);
			system("cls");
			std::cout << "description successfully changed!\n";
			Sleep(3000);
		}
		else if (choice == "3") {
			std::cout << "enter the new Date:\n";
			std::string date;
			std::cin >> date;
			(*ptr)->data.set_date(date);
			(*ptr)->data.calculate_total();
			system("cls");
			std::cout << "Date successfully changed\n";
			organize(list);
			Sleep(3000);
		}
		else if (choice == "4") {

			std::cout << "enter the new time:\n";
			std::string time;
			std::getline(std::cin, time);
			(*ptr)->data.set_hours(time.substr(0, time.find(':')));
			(*ptr)->data.set_minutes(time.substr(time.find(':') + 1, 3));
			(*ptr)->data.calculate_total();
			organize(list);
			system("cls");
			std::cout << "time successfully changed!\n";
			Sleep(3000);

		}
		else if (choice == "5") {
			std::cout << "changing status to done....";
			Sleep(5000);
			(*ptr)->data.set_status("done");
			system("cls");
			std::cout << "status successfully changed to done!\n";
			if (is_done(task)) {
				delete_node(list);
				organize(list);
			}
			
			Sleep(3000);
		}
		else throw std::exception("this choice is not available!\n");
		write_to_info(list);
	}
	else throw std::exception("there is no such task\n");
}



void help() {
	system("cls");
	int width=100,  height = 25;
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, 9);
	int g = getchar();
	for (int i = 0; i < width;i++) {
		std::cout << ((i % 2 == 0) ? '-' : ' ');
	}
	std::cout << std::endl;
	for (int i = 0;i < height - 2;i++) {
		int j = 0;
		while(j < width){
			if (j == 0 || j == width - 1) {
				std::cout << "|";
				j++;
			}
			else {
				if (i == 1 && j == 45) {
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "COMMANDS";
					SetConsoleTextAttribute(hconsole, 9);
					j += 8;
				}
				else if (i == 3 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "1-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"add task (Name, description, date, time, status)";
					j += 50;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (j == 3 && i == 4) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "2-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"add subtask (Name, description, date, time, status, Task Name)";
					j += 64;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (i == 5 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "3-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"edit task (Name of Task)";
					j += 26;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (i == 6 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "4-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"view tasks";
					j += 12;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (i == 7 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "5-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"view task info (name of task)";
					j += 31;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (i == 8 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "6-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"show subtasks (name of task)";
					j += 30;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else if (i == 9 && j == 3) {
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "7-";
					SetConsoleTextAttribute(hconsole, 7);
					std::cout <<
						"show subtask info (name of subtask)";
					j += 37;
					SetConsoleTextAttribute(hconsole, 9);
				}
				else {
					std::cout << " ";
					j++;
				}
			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width;i++) {
		std::cout << ((i % 2 == 0) ? '-' : ' ');
	}
	SetConsoleTextAttribute(hconsole, 7);

	std::cout << std::endl << std::endl;
	std::cout << "press enter to return";
	int ent = getchar();
	return;
	
}
void to_do_list(std::vector<Node*>& list) {

}


void Main() {
	std::vector<Node*> list = Read_and_extract();
	while (true) {
		std::cout << "\n\n\n\t\t\t\t\t1-to do list";
		std::cout << "\n\n\n\t\t\t\t\t2-help\n";
		char c;
		std::cin >> c;
		switch (c)
		{
		case ('1'):
			show(list);
			system("cls");
			break;
		case('2'):
			help();
			system("cls");
			break;
		default:
			break;
		}

	}
}