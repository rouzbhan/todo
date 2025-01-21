#pragma once
#include "tt.h"

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
