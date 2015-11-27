//============================================================================
// Name        : 3_Eiler_implicit.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include "Eiler/Eiler.h"
using namespace std;

double funk1(double* U, double t) {
	double check = 1e-9;
	if (fabs(t) < check) {
		t = check;
	}
	return -U[0] * U[1] + sin(t) / t;
}

double funk2(double* U, double t) {
	return -U[1] * U[1] + 3 * t / (1 + t * t);
}

int main() {
	DiffEq ArrDiffEq[] = { funk1, funk2 };
	double U[] = { 0, -0.412 };
	double t = 0, T = 1, eps = 0.001;
	Eiler(ArrDiffEq, 2, U, t, T, eps);

	cout<<"\nHello, I work till the end\n";
	return 0;
}

