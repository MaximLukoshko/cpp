/*
 * Eiler.h
 *
 *  Created on: 14.09.2015
 *      Author: maximus
 */

#pragma once
#ifndef EILER_H_
#define EILER_H_

typedef double (*DiffEq)(double* U, double t);

void Eiler(DiffEq* ArrDiffEq, int NumberOfEquations, double* U, double* U1,
		double &t_o, double &t_step, double eps);

#endif /* EILER_H_ */
