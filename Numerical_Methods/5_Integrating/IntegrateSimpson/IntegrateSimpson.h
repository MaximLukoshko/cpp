/*
 * IntegrateSimpson.h
 *
 *  Created on: 29.10.2015
 *      Author: maximus
 */

#pragma once
#ifndef INTEGRATESIMPSON_H_
#define INTEGRATESIMPSON_H_

typedef double (*Function)(double, double);

double IntegrateSimpson(Function IntegratingFunction, double StartX,
		double FinishX, double StartY, double FinishY, double eps);

#endif /* INTEGRATESIMPSON_H_ */
