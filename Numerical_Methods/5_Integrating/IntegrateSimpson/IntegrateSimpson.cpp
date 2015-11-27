/*
 * IntegrateSimpson.cpp
 *
 *  Created on: 29.10.2015
 *      Author: maximus
 */

#include "IntegrateSimpson.h"
#include <math.h>
#include <iostream>

using namespace std;

double i_j_converter(double StartX, double stepX, int i) {
	return StartX + stepX * i;
}


double count_Integral_n(Function IntegratingFunction, double StartX,
		double FinishX, double stepX, int N, double StartY, double FinishY,
		double stepY, double M) {

	double Integral_n = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			Integral_n += IntegratingFunction(
					i_j_converter(StartX, stepX, 2 * i),
					i_j_converter(StartY, stepY, 2 * j));
			Integral_n += 4
					* IntegratingFunction(
							i_j_converter(StartX, stepX, 2 * i + 1),
							i_j_converter(StartY, stepY, 2 * j));
			Integral_n += IntegratingFunction(
					i_j_converter(StartX, stepX, 2 * i + 2),
					i_j_converter(StartY, stepY, 2 * j));
			Integral_n += 4
					* IntegratingFunction(i_j_converter(StartX, stepX, 2 * i),
							i_j_converter(StartY, stepY, 2 * j + 1));
			Integral_n += 16
					* IntegratingFunction(
							i_j_converter(StartX, stepX, 2 * i + 1),
							i_j_converter(StartY, stepY, 2 * j + 1));
			Integral_n += 4
					* IntegratingFunction(
							i_j_converter(StartX, stepX, 2 * i + 2),
							i_j_converter(StartY, stepY, 2 * j + 1));
			Integral_n += IntegratingFunction(
					i_j_converter(StartX, stepX, 2 * i),
					i_j_converter(StartY, stepY, 2 * j + 2));
			Integral_n += 4
					* IntegratingFunction(
							i_j_converter(StartX, stepX, 2 * i + 1),
							i_j_converter(StartY, stepY, 2 * j + 2));
			Integral_n += IntegratingFunction(
					i_j_converter(StartX, stepX, 2 * i + 2),
					i_j_converter(StartY, stepY, 2 * j + 2));
		}
	}

	Integral_n *= stepX * stepY / 9;

	return Integral_n;
}

double IntegrateSimpson(Function IntegratingFunction, double StartX,
		double FinishX, double StartY, double FinishY, double eps) {

	const int MAX_ITER = 10;

	int N = 4;
	int M = N * (FinishY - StartY) / (FinishX - StartX);

	double stepX = (FinishX - StartX) / (2 * N);
	double stepY = (FinishY - StartY) / (2 * M);

	double Integral_n;
	double Integral_2n;

	{
		Integral_n = count_Integral_n(IntegratingFunction, StartX, FinishX,
				stepX, N, StartY, FinishY, stepY, M);

		N *= 2;
		M *= 2;
		stepX = (FinishX - StartX) / (2 * N);
		stepY = (FinishY - StartY) / (2 * M);

		Integral_2n = count_Integral_n(IntegratingFunction, StartX, FinishX,
				stepX, N, StartY, FinishY, stepY, M);
	}

	{
		int i = 0;
		while ((fabs(Integral_n - Integral_2n) > eps) && (i < MAX_ITER)) {
			Integral_n = Integral_2n;
			N *= 2;
			M *= 2;
			stepX = (FinishX - StartX) / (2 * N);
			stepY = (FinishY - StartY) / (2 * M);
			Integral_2n = count_Integral_n(IntegratingFunction, StartX, FinishX,
					stepX, N, StartY, FinishY, stepY, M);
			i++;
		}

		if (i == MAX_ITER) {
			cout << "\n\nError while integrating(\n";
		}
	}

	return Integral_n;

}

