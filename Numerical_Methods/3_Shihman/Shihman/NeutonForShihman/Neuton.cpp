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

//Вычисляем вектор невязки
void CountResidualVectorForShihman(Func func, int NumberOfEquations,
		DiffEq* ArrSourceEq, double* PreviousApproximationConstInThisMethod,
		double* Approximation, double* LastApproximationConstInThisMethod,
		double t, double* ResidualVector, double a0, double a1, double b0) {
	for (int k = 0; k < NumberOfEquations; k++) {
		ResidualVector[k] = -func(ArrSourceEq,
				PreviousApproximationConstInThisMethod,
				LastApproximationConstInThisMethod, Approximation, t, k, a0, a1,
				b0);
	}
}

//Вычисляем матрицу Якоби
void CountMatrixJakobiForShihman(double** Jakobi, Func funk,
		int NumberOfEquations, DiffEq* ArrSourceEq, double* Approximation,
		double* PreviousApproximationConstInThisMethod,
		double* LastApproximationConstInThisMethod, double t,
		double* ResidualVector, double a0, double a1, double b0) {
	for (int i = 0; i < NumberOfEquations; i++) {
		for (int j = 0; j < NumberOfEquations; j++) {
			Approximation[j] += deltaX;
			Jakobi[i][j] = funk(ArrSourceEq,
					PreviousApproximationConstInThisMethod,
					LastApproximationConstInThisMethod, Approximation, t, i, a0,
					a1, b0);
			Approximation[j] -= deltaX;
			Jakobi[i][j] -= funk(ArrSourceEq,
					PreviousApproximationConstInThisMethod,
					LastApproximationConstInThisMethod, Approximation, t, i, a0,
					a1, b0);
			Jakobi[i][j] /= deltaX;
		}
	}
}

//Делаем следующее приближение
void NextApproximationForShihman(double** Jakobi, double* Approximation,
		int NumberOfEquations, double* ResidualVector, int NumberOfVariables) {
	double* CorrectionX = NULL;
	double d = 0;

	Gaus(Jakobi, ResidualVector, NumberOfEquations, CorrectionX, d);

	for (int k = 0; k < NumberOfVariables; k++) {
		Approximation[k] += CorrectionX[k];
	}
	delete CorrectionX;
}

double CountDelta1ForShihman(double* ResidualVector, int NumberOfVariables) {
	double max = ResidualVector[0];

	for (int k = 1; k < NumberOfVariables; k++) {
		if (fabs(ResidualVector[k]) > max) {
			max = fabs(ResidualVector[k]);
		}
	}

	return max;
}

double CountDelta2ForShihman(double* PreviousApproximation,
		double* NowApproximation, int NumberOfVariables) {
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

void NeutonForShihman(Func func, DiffEq* ArrSourceEq, int NumberOfEquations,
		double* PreviousApproximationConstInThisMethod,
		double* InitialApproximation,
		double* LastApproximationConstInThisMethod, int NumberOfVariables,
		double t, double a0, double a1, double b0, double eps1, double eps2) {

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
		CountResidualVectorForShihman(func, NumberOfEquations, ArrSourceEq,
				PreviousApproximationConstInThisMethod, InitialApproximation,
				LastApproximationConstInThisMethod, t, ResidualVector, a0, a1,
				b0);
		CountMatrixJakobiForShihman(Jakobi, func, NumberOfEquations,
				ArrSourceEq, InitialApproximation,
				PreviousApproximationConstInThisMethod,
				LastApproximationConstInThisMethod, t, ResidualVector, a0, a1,
				b0);
		for (int i = 0; i < NumberOfVariables; i++) {
			PreviousApproximation[i] = InitialApproximation[i];
		}
		NextApproximationForShihman(Jakobi, InitialApproximation,
				NumberOfEquations, ResidualVector, NumberOfVariables);

		delta1 = CountDelta1ForShihman(ResidualVector, NumberOfVariables);
		delta2 = CountDelta2ForShihman(PreviousApproximation,
				InitialApproximation, NumberOfVariables);

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
