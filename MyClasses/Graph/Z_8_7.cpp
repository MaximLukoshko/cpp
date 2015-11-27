//============================================================================
// Name        : Z_8_7.cpp
// Author      : Maxim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CGraph/CGraph.h"
#include <iostream>
using namespace std;

int main() {

	CGraph<short,short>* temp = new CGraph<short,short>;

	temp->Zapolnit();

	temp->find_source();
	temp->find_drain();
	temp->add_vertice();
	temp->delete_vertice(1);
	temp->print();
	temp->find_source();
	temp->find_drain();
	delete temp;
	return 0;
}
