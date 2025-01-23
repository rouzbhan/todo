#include<iostream>
#include "tt.h"
#include "tasktree.h"
#include "fstream"

int main()
{
	std::vector<Node*> list = Read_and_extract();
	show(list);

	//std::vector<Node*> list = Read_and_extract(file);
	//show(list);
}