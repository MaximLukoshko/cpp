//============================================================================
// Name        : 5_Integration.cpp
// Author      : Maxim Lukoshko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include "IntegrateSimpson/IntegrateSimpson.h"

using namespace std;

double function(double x, double y) {
	return (x * x) / (1 + y * y);
}

int main() {
	double startX = 0;
	double finishX = 4;

	double startY = 1;
	double finishY = 2;

	double eps = 1e-6;

	cout << "Your integral:" << setw(14)
			<< IntegrateSimpson(function, startX, finishX, startY, finishY, eps)
			<< "\n";
	return 0;
}
