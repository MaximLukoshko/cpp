/*
 * Least_Squares_Method.h
 *
 *  Created on: 20.10.2015
 *      Author: maximus
 */

#pragma once
#ifndef LEAST_SQUARES_METHOD_H_
#define LEAST_SQUARES_METHOD_H_

#include "Gaus/Gaus.h"

void Least_Squares_Method(double* X, double* Y, int NumberOfPoints,
		int PolinomialDegree, double* &PolynomialCoefficients, double eps);

#endif /* LEAST_SQUARES_METHOD_H_ */
