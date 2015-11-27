/*
 * Eiler.cpp
 *
 *  Created on: 14.09.2015
 *      Author: maximus
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "Eiler.h"
using namespace std;

ofstream fout("Result.txt");

//void CountVector_dU(DiffEq* func, int NumberOfEquations, double* U, double t,
//		double* dU) {
//	for (int k = 0; k < NumberOfEquations; k++) {
//		dU[k] = func[k](U, t);
//	}
//}

void CalculateStep(DiffEq* ArrDiffEq, int NumberOfEquations, double* U,
		double t, double& t_step, double t_max_step, double eps) {
	double t_i = eps / (fabs(ArrDiffEq[0](U, t) + eps / t_max_step));
	double min = fabs(t_i);
	for (int k = 1; k < NumberOfEquations; k++) {
		t_i = eps / (fabs(ArrDiffEq[k](U, t)) + eps / t_max_step);
		if (fabs(t_i) < min) {
			min = fabs(t_i);
		}
	}
	t_step = min;
//	cout << "t_step: " << t_step << "\n";
}

void GoToNextStep(DiffEq* ArrDiffEq, int NumberOfEquations, double* U,
		double& t, double t_step) {
	double* incrementU = new double[NumberOfEquations];

	for (int k = 0; k < NumberOfEquations; k++) {
		incrementU[k] = t_step * ArrDiffEq[k](U, t);
		U[k] += incrementU[k];
	}
	t += t_step;
	delete incrementU;
}
////////////////////////////////////////////////////////////////////////////

void Eiler(DiffEq* ArrDiffEq, int NumberOfEquations, double* U, double t,
		double T, double eps) {
	int max_iter = 10000, k = 0;
	double t_max_step = 0.1;
	double t_step = 0;
	double* dU = new double[NumberOfEquations];

	cout << setw(3) << "|" << setw(6) << "k" << setw(3) << "|" << setw(15)
			<< "U1" << setw(3) << "|" << setw(15) << "U2" << setw(3) << "|"
			<< setw(15) << "t" << setw(3) << "|" << "\n";
	cout
			<< "  |--------|-----------------|-----------------|-----------------|\n";

	fout << setw(3) << "|" << setw(6) << "k" << setw(3) << "|" << setw(15)
			<< "U1" << setw(3) << "|" << setw(15) << "U2" << setw(3) << "|"
			<< setw(15) << "t" << setw(3) << "|" << "\n";
	fout
			<< "  |--------|-----------------|-----------------|-----------------|\n";

	while ((t < T) && (k < max_iter)) {
//		CountVector_dU(ArrDiffEq, NumberOfEquations, U, t, dU);
		CalculateStep(ArrDiffEq, NumberOfEquations, U, t, t_step, t_max_step,
				eps);
		GoToNextStep(ArrDiffEq, NumberOfEquations, U, t, t_step);

		k++;

		cout << setw(3) << "|" << setw(6) << k << setw(3) << "|" << setw(15)
				<< U[0] << setw(3) << "|" << setw(15) << U[1] << setw(3) << "|"
				<< setw(15) << t << setw(3) << "|" << "\n";
		fout << setw(3) << "|" << setw(6) << k << setw(3) << "|" << setw(15)
				<< U[0] << setw(3) << "|" << setw(15) << U[1] << setw(3) << "|"
				<< setw(15) << t << setw(3) << "|" << "\n";
	}

	delete dU;
	fout.close();
}
