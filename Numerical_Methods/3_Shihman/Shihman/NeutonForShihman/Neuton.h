/*
 * Neuton.h
 *
 *  Created on: 13.09.2015
 *      Author: maximus
 */

#pragma once
#ifndef NEUTON_H_
#define NEUTON_H_

#include "Gaus/Gaus.h"

#define deltaX 1e-9;

typedef double (*DiffEq)(double* U, double t);
typedef double (*Func)(DiffEq* ArrSourceEq, double* Uk1_, double* U_k,
		double* U_k1, double t, int i, double a0, double a1, double b0);

void NeutonForShihman(Func func, DiffEq* ArrSourceEq, int NumberOfEquations,
		double* PreviousApproximationConstInThisMethod,
		double* InitialApproximation,
		double* LastApproximationConstInThisMethod, int NumberOfVariables,
		double t, double a0, double a1, double b0, double eps1, double eps2);

#endif /* NEUTON_H_ */
