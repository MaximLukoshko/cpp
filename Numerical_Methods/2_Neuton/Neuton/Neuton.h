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

typedef double (*Func)(double*);

void Neuton(Func* funk, int NumberOfEquations, double* InitialApproximation, int NumberOfVariables, double eps1, double eps2);


#endif /* NEUTON_H_ */
