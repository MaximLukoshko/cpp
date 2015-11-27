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
typedef double (*Func)(DiffEq* ArrSourceEq, double* Uk, double* Uk1, double tau,
		double t, int i);

void Neuton(Func func, DiffEq* ArrSourceEq, int NumberOfEquations,
		double* InitialApproximation,
		double* LastApproximationConstInThisMethod, int NumberOfVariables,
		double t, double tau, double eps1, double eps2);

#endif /* NEUTON_H_ */
