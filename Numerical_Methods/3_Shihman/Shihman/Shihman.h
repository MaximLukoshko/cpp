/*
 * Shihman.h
 *
 *  Created on: 21.09.2015
 *      Author: maximus
 */

#pragma once
#ifndef SHIHMAN_H_
#define SHIHMAN_H_

typedef double (*DiffEq)(double* U, double t);

void Shihman(DiffEq* ArrDiffEq, int NumberOfEquations, double* U, double t_o,
		double T, double eps);

#endif /* SHIHMAN_H_ */
