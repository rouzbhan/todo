#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "tt.h"
#include "tasktree.h"

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
	build_max_heap(tasks,n);
	for (int i = n - 1; i >= 1; i--) {
		std::swap(tasks[0], tasks[i]);
		n -= 1;
		max_heapify(tasks, 0);
	}
}

