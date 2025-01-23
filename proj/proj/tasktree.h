#pragma once
#include "tt.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
class Node {
private:
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

void append(Task Data,Node * root) {
	if (!root) {
		root = new Node(Data);
		return;
	}
	else {
		Node* ptr = root->get_left();
		while (ptr) {
			ptr = ptr->get_right();
		}

		ptr = new Node(Data);
		ptr->set_father(root);
	}
}
int left(int i) { return (i << 1) + 1; }

int right(int i) { return (i << 1) + 2; }

int parent(int i) { return i >> 1; }



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
		if (s.find("+") == std::string::npos) {
			std::string name, des, status, date, time;
			s.erase('+');
			name = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			des = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			std::string d = date.substr(0, 9);
			date.erase(0, 9);
			int hours = stoi(date.substr(0, date.find(':')));
			date.erase(0, date.find(':'));
			int min = stoi(date);
			Task data(name, des, date, hours, min, status);
			append(data, list[list.size() - 1]);

		}
		else {
			std::string name, des, status, date, time;
			
			name = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			des = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			date = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			time = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			status = s.substr(0, s.find(','));
			s.erase(0, s.find(','));
			std::string d = date.substr(0, 9);
			date.erase(0, 9);
			int hours = stoi(date.substr(0, date.find(':')));
			date.erase(0, date.find(':'));
			int min = stoi(date);
			Task data(name, des, date, hours, min, status);
			Node* node = new Node(data);
			list.push_back(node);
		}

	}
	std::string name, des, status, date, time;
	
	name = s.substr(0, s.find(','));
	s.erase(0, s.find(','));
	des = s.substr(0, s.find(','));
	s.erase(0, s.find(','));
	date = s.substr(0, s.find(','));
	s.erase(0, s.find(','));
	time = s.substr(0, s.find(','));
	s.erase(0, s.find(','));
	status = s.substr(0, s.find(','));
	s.erase(0, s.find(','));
	std::string d = date.substr(0, 9);
	date.erase(0, 9);
	int hours = stoi(date.substr(0, date.find(':')));
	date.erase(0, date.find(':'));
	int min = stoi(date);
	Task data(name, des, date, hours, min, status);
	Node* node = new Node(data);
	list.push_back(node);
	return list;

}

void organize(std::vector<Node*>& list) {
	heapSort(list);
}
void show(std::vector<Node*>& list) {
	std::system("cls");
	for (auto i : list) {
		std::cout << "Name : " << i->get_data().Name() << std::endl;
	}
}
