#include<iostream>
#include "tt.h"
#include "tasktree.h"
#include "fstream"

int main()
{
	std::vector<Node*> list = Read_and_extract();
	show(list);
	Sleep(5);
	std::string command;
	
	show_subtasks(list[0]);
	Sleep(100);
}