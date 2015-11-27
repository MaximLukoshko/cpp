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
#include "Neuton/Neuton.h"

using namespace std;

double ArrFunk(DiffEq* ArrSourceEq, double* U_k, double* U_k1, double tau,
		double t, int i) {

	return U_k1[i] - U_k[i] - tau * ArrSourceEq[i](U_k1, t);
}

double CountEps(double t_step, double t_prev_step, double* U_k, double* U_k1,
		int NumberOfVariables) {
	double eps = 0;
	double max = 0;
	eps =
			(t_step / (t_prev_step + t_step))
					* (U_k1[0] - U_k[0]
							- ((t_step / t_prev_step) * (U_k[0] - U_k1[0])));
	max = fabs(eps);
	for (int i = 1; i < NumberOfVariables; i++) {
		eps = (t_step / (t_prev_step + t_step))
				* (U_k1[i] - U_k[i]
						- ((t_step / t_prev_step) * (U_k[i] - U_k1[i])));
		if (max < fabs(eps)) {
			max = fabs(eps);
		}
	}
	return max;
}

void ChooseStep(double& t_step, double eps_max, double eps) {
	if (fabs(eps_max) > eps) {
		t_step /= 2;
	} else if (fabs(eps_max) < eps / 4) {
		t_step *= 2;
	}
}

void ShiftDecisions(double* U, double* U1, int NumberOfEquations) {
	for (int i = 0; i < NumberOfEquations; ++i) {
		U[i] = U1[i];
	}
}

////////////////////////////////////////////////////////////////////////////

void Eiler(DiffEq* ArrDiffEq, int NumberOfEquations, double* U, double* U1,
		double &t, double &t_step, double eps) {

	double t_max_step = 0.1;
	double t_min_step = 0.001;

	double t_step_prev = t_step;
	double eps_max = 0;

	Neuton(ArrFunk, ArrDiffEq, NumberOfEquations, U1, U, NumberOfEquations, t,
			t_step, eps, eps);

	eps_max = CountEps(t_step, t_step_prev, U, U1, NumberOfEquations);

	t_step_prev = t_step;
	ChooseStep(t_step, eps_max, eps);
	t_step = (t_step > t_max_step) ? t_max_step : t_step;
	t_step = (t_step < t_min_step) ? t_min_step : t_step;

	t = t + t_step;

}

