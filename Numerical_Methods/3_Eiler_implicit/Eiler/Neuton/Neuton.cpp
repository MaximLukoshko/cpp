/*
 * Neuton.cpp
 *
 *  Created on: 13.09.2015
 *      Author: maximus
 */

#include "Neuton.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

//typedef double (*Func)(DiffEq* ArrSourceEq, double* U_k, double* U_k1,
//		double tau, double t, int i);

//Вычисляем вектор невязки
void CountResidualVector(Func func, int NumberOfEquations, DiffEq* ArrSourceEq,
		double* Approximation, double* LastApproximationConstInThisMethod,
		double t, double tau, double* ResidualVector) {
	for (int k = 0; k < NumberOfEquations; k++) {
		ResidualVector[k] = -func(ArrSourceEq,
				LastApproximationConstInThisMethod, Approximation, tau, t, k);
	}
}

//Вычисляем матрицу Якоби
void CountMatrixJakobi(double** Jakobi, Func funk, int NumberOfEquations,
		DiffEq* ArrSourceEq, double* Approximation,
		double* LastApproximationConstInThisMethod, double t, double tau,
		double* ResidualVector) {
	for (int i = 0; i < NumberOfEquations; i++) {
		for (int j = 0; j < NumberOfEquations; j++) {
			Approximation[j] += deltaX;
			Jakobi[i][j] = funk(ArrSourceEq, LastApproximationConstInThisMethod,
					Approximation, tau, t, i);
			Approximation[j] -= deltaX;
			Jakobi[i][j] -= funk(ArrSourceEq,
					LastApproximationConstInThisMethod, Approximation, tau, t,
					i);
			Jakobi[i][j] /= deltaX;
		}
	}
}

//Делаем следующее приближение
void NextApproximation(double** Jakobi, double* Approximation,
		int NumberOfEquations, double* ResidualVector, int NumberOfVariables) {
	double* CorrectionX = NULL;
	double d = 0;

	Gaus(Jakobi, ResidualVector, NumberOfEquations, CorrectionX, d);

	for (int k = 0; k < NumberOfVariables; k++) {
		Approximation[k] += CorrectionX[k];
	}
	delete CorrectionX;
}

double CountDelta1(double* ResidualVector, int NumberOfVariables) {
	double max = ResidualVector[0];

	for (int k = 1; k < NumberOfVariables; k++) {
		if (fabs(ResidualVector[k]) > max) {
			max = fabs(ResidualVector[k]);
		}
	}

	return max;
}

double CountDelta2(double* PreviousApproximation, double* NowApproximation,
		int NumberOfVariables) {
	double* helper = new double[NumberOfVariables];
	for (int k = 0; k < NumberOfVariables; k++) {
		if (NowApproximation[k] <= 1) {
			helper[k] = fabs(NowApproximation[k] - PreviousApproximation[k]);
		} else {
			helper[k] = fabs(
					(NowApproximation[k] - PreviousApproximation[k])
							/ NowApproximation[k]);
		}
	}
	double max = helper[0];

	for (int k = 1; k < NumberOfVariables; k++) {
		if (helper[k] > max) {
			max = helper[k];
		}
	}

	delete helper;

	return max;
}

void Neuton(Func func, DiffEq* ArrSourceEq, int NumberOfEquations,
		double* InitialApproximation,
		double* LastApproximationConstInThisMethod, int NumberOfVariables,
		double t, double tau, double eps1, double eps2) {

	double* ResidualVector = new double[NumberOfEquations];
	double* PreviousApproximation = new double[NumberOfVariables];
	double** Jakobi = new double*[NumberOfEquations];
	for (int i = 0; i < NumberOfEquations; i++) {
		Jakobi[i] = new double[NumberOfVariables];
	}

	int NIT = 100; //Максимальное число итераций
	int k = 1;
	double delta1;
	double delta2;
	bool go = true;

	while (go) {
		CountResidualVector(func, NumberOfEquations, ArrSourceEq,
				InitialApproximation, LastApproximationConstInThisMethod, t,
				tau, ResidualVector);
		CountMatrixJakobi(Jakobi, func, NumberOfEquations, ArrSourceEq,
				InitialApproximation, LastApproximationConstInThisMethod, t,
				tau, ResidualVector);
		for (int i = 0; i < NumberOfVariables; i++) {
			PreviousApproximation[i] = InitialApproximation[i];
		}
		NextApproximation(Jakobi, InitialApproximation, NumberOfEquations,
				ResidualVector, NumberOfVariables);

		delta1 = CountDelta1(ResidualVector, NumberOfVariables);
		delta2 = CountDelta2(PreviousApproximation, InitialApproximation,
				NumberOfVariables);

//		cout << "|" << setw(5) << k << setw(2) << "|" << setw(15) << delta1
//				<< setw(2) << "|" << setw(15) << delta2 << setw(2) << "|"
//				<< "\n";

		if ((delta1 - eps1 < 0) && (delta2 - eps2 < 0)) {
			go = false;
		}

		if (k > NIT) {
			go = false;
		}
		k++;
	}

	delete PreviousApproximation;
	delete ResidualVector;
	for (int i = 0; i < NumberOfEquations; i++) {
		delete Jakobi[i];
	}
	delete Jakobi;
}
