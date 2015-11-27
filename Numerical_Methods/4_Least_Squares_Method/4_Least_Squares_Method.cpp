//============================================================================
// Name        : 4_Least_Squares_Method.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Least_Squares_Method/Least_Squares_Method.h"

using namespace std;

int main() {
	ifstream fin("data.txt");

	double* X;
	double* Y;
	int NumberOfPoints;
	int PolynomialDegree;
	double* PolynomialCoefficients;
	double eps = 1e-9;

	fin >> NumberOfPoints;
	fin >> PolynomialDegree;

	X = new double[NumberOfPoints];
	Y = new double[NumberOfPoints];

	PolynomialCoefficients = new double[PolynomialDegree + 1];

	for (int i = 0; i < NumberOfPoints; ++i) {
		fin >> X[i];
		fin >> Y[i];
		cout /*<< "I'm here\n" << NumberOfPoints */<< endl << X[i] << "   " << Y[i];
	}
	fin.close();

	Least_Squares_Method(X, Y, NumberOfPoints, PolynomialDegree,
			PolynomialCoefficients, eps);

	ofstream fout("Coefficient.txt");
	for (int i = 0; i < PolynomialDegree + 1; ++i) {
		fout << PolynomialCoefficients[i] << endl;
	}
	fout.close();

	delete[] X;
	delete[] Y;

	return 0;
}
