//============================================================================
// Name        : Z_8_6.cpp
// Author      : Maxim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CTree/CTree.h"
#include <iostream>
using namespace std;

int main() {
	CTree<short> my_tree(5);
	my_tree.enter(10);
	my_tree.print_ascending();
	my_tree.print();
	my_tree.delete_leaves();
	my_tree.print_ascending();
	my_tree.print();
	cout << "finished" << endl; // prints !!!Hello World!!!
	return 0;
}
