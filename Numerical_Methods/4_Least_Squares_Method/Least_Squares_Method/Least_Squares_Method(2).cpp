/*
 * Least_Squares_Method.cpp
 *
 *  Created on: 20.10.2015
 *      Author: maximus
 */

#include "Least_Squares_Method.h"

void Least_Squares_Method(double* X, double* Y, int NumberOfPoints,
		int PolynomialDegree, double* &PolynomialCoefficients, double eps) {

	double* SumPowerX = new double[PolynomialDegree * 2 + 2];
	double* SumYPowerX = new double[PolynomialDegree + 1];

	{
		double* PowerX = new double[NumberOfPoints];
		for (int i = 0; i < NumberOfPoints; ++i) {
			PowerX[i] = 1;
		}

		for (int var = 0; var < PolynomialDegree + 1; ++var) {
			SumPowerX[var] = 0;
			SumYPowerX[var] = 0;

			for (int i = 0; i < NumberOfPoints; ++i) {
				SumPowerX[var] += PowerX[i];
				SumYPowerX[var] += PowerX[i] * Y[i];
				PowerX[i] *= X[i];
			}
		}

		for (int var = PolynomialDegree + 1; var < PolynomialDegree * 2 + 1;
				++var) {

			SumPowerX[var] = 0;

			for (int i = 0; i < NumberOfPoints; ++i) {
				SumPowerX[var] += PowerX[i];
				PowerX[i] *= X[i];
			}
		}
	}
	{

		double* *MatrixForGauss = new double*[PolynomialDegree + 1];
		for (int i = 0; i < PolynomialDegree + 1; ++i) {
			MatrixForGauss[i] = new double[PolynomialDegree + 1];
			for (int j = 0; j < PolynomialDegree + 1; ++j) {
				MatrixForGauss[i][j] = SumPowerX[i+j];
			}
		}

		Gaus(MatrixForGauss, SumYPowerX, PolynomialDegree + 1,
				PolynomialCoefficients, eps);

		for (int i = 0; i < PolynomialDegree; ++i) {
			delete[] MatrixForGauss[i];
		}
		delete[] MatrixForGauss;
	}

	delete[] SumPowerX;
	delete[] SumYPowerX;
}

