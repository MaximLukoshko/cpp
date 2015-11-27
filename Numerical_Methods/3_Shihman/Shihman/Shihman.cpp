/*
 * Shihman.cpp
 *
 *  Created on: 21.09.2015
 *      Author: maximus
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "Shihman.h"
#include "Eiler/Eiler.h"
#include "NeutonForShihman/Neuton.h"

using namespace std;

ofstream fout("Result.txt");

double ArrFunkForShihman(DiffEq* ArrSourceEq, double* Uk1_, double* U_k,
		double* U_k1, double t, int i, double a0, double a1, double b0) {

	return U_k1[i] - a1 * Uk1_[i] - a0 * U_k[i] - b0 * ArrSourceEq[i](U_k1, t);
}

double CountEpsForShihman(double t_step, double t_step_prev,
		double t_step_prev_prev, double* U, double* U1, double* U1_,
		double* U2_, int NumberOfVariables) {
	double eps = 0;
	double max = 0;
	eps = (t_step * t_step * (t_step + t_step_prev) * (t_step + t_step_prev)
			/ (2 * t_step + t_step_prev));
	{
		double a = U1[0]
				/ (t_step * (t_step + t_step_prev)
						* (t_step + t_step_prev + t_step_prev_prev));
		double b = U[0]
				/ (t_step * t_step_prev * (t_step_prev + t_step_prev_prev));
		double c = U1_[0]
				/ (t_step_prev_prev * t_step_prev * (t_step_prev + t_step));
		double d = U2_[0]
				/ (t_step_prev * (t_step_prev + t_step_prev_prev)
						* (t_step_prev_prev + t_step_prev + t_step));
		eps *= (a - b + c - d);
	}
	max = fabs(eps);
	for (int i = 1; i < NumberOfVariables; i++) {
		eps = (t_step * t_step * (t_step + t_step_prev) * (t_step + t_step_prev)
				/ (2 * t_step + t_step_prev));
		{
			double a = U1[i]
					/ (t_step * (t_step + t_step_prev)
							* (t_step + t_step_prev + t_step_prev_prev));
			double b = U[i]
					/ (t_step * t_step_prev * (t_step_prev + t_step_prev_prev));
			double c = U1_[i]
					/ (t_step_prev_prev * t_step_prev * (t_step_prev + t_step));
			double d = U2_[i]
					/ (t_step_prev * (t_step_prev + t_step_prev_prev)
							* (t_step_prev_prev + t_step_prev + t_step));
			eps *= (a - b + c - d);
		}
		if (max < fabs(eps)) {
			max = fabs(eps);
		}
	}
	return max;
}

void ChooseStepForShihman(double& t_step, double eps_max, double eps) {
	if (fabs(eps_max) > eps) {
		t_step /= 2;
	} else if (fabs(eps_max) < eps / 4) {
		t_step *= 2;
	}
}

void ShiftDecisionsForShihman2(double* U, double* U1, int NumberOfEquations) {
	for (int i = 0; i < NumberOfEquations; ++i) {
		U[i] = U1[i];
	}
}

void ShiftDecisionsForShihman3(double* U1_, double* U, double* U1,
		int NumberOfEquations) {
	for (int i = 0; i < NumberOfEquations; ++i) {
		U1_[i] = U[i];
		U[i] = U1[i];
	}
}

double Count_a0(double t_step, double t_step_prev) {
	return (t_step + t_step_prev) * (t_step + t_step_prev)
			/ (t_step_prev * (2 * t_step + t_step_prev));
}

double Count_a1(double t_step, double t_step_prev) {
	return -t_step * t_step / (t_step_prev * (2 * t_step + t_step_prev));
}

double Count_b0(double t_step, double t_step_prev) {
	return t_step * (t_step + t_step_prev) / (2 * t_step + t_step_prev);
}

////////////////////////////////////////////////////////////////////////////

void Shihman(DiffEq* ArrDiffEq, int NumberOfEquations, double* U, double t,
		double T, double eps) {
	int max_iter = 10000, k = 0;
	double t_max_step = 0.1;
	double t_min_step = 0.0005;
	double t_step = 0.005;
	double t_step_prev = t_step;
	double t_step_prev_prev = t_step;
	double eps_max = 0;

	double* U1 = new double[NumberOfEquations];
	double* U1_ = new double[NumberOfEquations];
	double* U2_ = new double[NumberOfEquations];

//	Получаем три одинаковых вектора
	ShiftDecisionsForShihman2(U1, U, NumberOfEquations);
	ShiftDecisionsForShihman2(U1_, U, NumberOfEquations);
	ShiftDecisionsForShihman2(U2_, U, NumberOfEquations);

//	Делаем 2 первых шага интегрирования
	Eiler(ArrDiffEq, NumberOfEquations, U1_, U, t, t_step, eps);
	Eiler(ArrDiffEq, NumberOfEquations, U, U1, t, t_step, eps);
	t_step_prev = t_step;

	cout << setw(3) << "|" << setw(7) << "k" << setw(3) << "|" << setw(15)
			<< "U1" << setw(3) << "|" << setw(15) << "U2" << setw(3) << "|"
			<< setw(15) << "t" << setw(3) << "|" << "\n";
	cout
			<< "  |---------|-----------------|-----------------|-----------------|\n";

	fout << setw(3) << "|" << setw(7) << "k" << setw(3) << "|" << setw(15)
			<< "U1" << setw(3) << "|" << setw(15) << "U2" << setw(3) << "|"
			<< setw(15) << "t" << setw(3) << "|" << "\n";
	fout
			<< "  |---------|-----------------|-----------------|-----------------|\n";

	cout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15)
			<< U1_[0] << setw(3) << "|" << setw(15) << U1_[1] << setw(3) << "|"
			<< setw(15) << t << setw(3) << "|" << "\n";

	fout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15)
			<< U1_[0] << setw(3) << "|" << setw(15) << U1_[1] << setw(3) << "|"
			<< setw(15) << t << setw(3) << "|" << "\n";

	cout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15) << U[0]
			<< setw(3) << "|" << setw(15) << U[1] << setw(3) << "|" << setw(15)
			<< t << setw(3) << "|" << "\n";

	fout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15) << U[0]
			<< setw(3) << "|" << setw(15) << U[1] << setw(3) << "|" << setw(15)
			<< t << setw(3) << "|" << "\n";

	while ((t < T) && (k < max_iter)) {

		cout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15)
				<< U1[0] << setw(3) << "|" << setw(15) << U1[1] << setw(3)
				<< "|" << setw(15) << t << setw(3) << "|" << "\n";

		fout << setw(3) << "|" << setw(7) << k << setw(3) << "|" << setw(15)
				<< U1[0] << setw(3) << "|" << setw(15) << U1[1] << setw(3)
				<< "|" << setw(15) << t << setw(3) << "|" << "\n";

//		Вычисляем параметры для текущего шага
		double a0 = Count_a0(t_step, t_step_prev);
		double a1 = Count_a1(t_step, t_step_prev);
		double b0 = Count_b0(t_step, t_step_prev);

//		Считаем ошибку
		eps_max = CountEpsForShihman(t_step, t_step_prev, t_step_prev_prev, U,
				U1, U1_, U2_, NumberOfEquations);

//		Выбираем новый шаг
		t_step_prev_prev = t_step_prev;
		t_step_prev = t_step;
		ChooseStepForShihman(t_step, eps_max, eps);

		t_step = (t_step > t_max_step) ? t_max_step : t_step;
		t_step = (t_step < t_min_step) ? t_min_step : t_step;

		t = t + t_step;

//		Находим следующий вектор
		NeutonForShihman(ArrFunkForShihman, ArrDiffEq, NumberOfEquations, U1_,
				U1, U, NumberOfEquations, t, a0, a1, b0, eps, eps);

		ShiftDecisionsForShihman2(U2_, U1_, NumberOfEquations);
		ShiftDecisionsForShihman3(U1_, U, U1, NumberOfEquations);
		k++;
	}

	delete U1_;
	delete U1;
	delete U2_;
	fout.close();
}

