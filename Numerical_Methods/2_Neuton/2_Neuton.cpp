//============================================================================
// Name        : 2_Neuton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <math.h>
#include "Neuton/Neuton.h"

using namespace std;


/*double func1(double* X)
{
	return X[0]*X[0]+X[1]*X[1]-25;
}

double func2(double* X)
{
	return 3*X[0]*X[0]-4*X[1]*X[1]-12;
}*/

/*
double func1(double* X)
{
	return X[0]*X[0]*X[1]*X[1]-3*X[0]*X[0]-6*X[1]*X[1]+8;
}

double func2(double* X)
{
	return X[0]*X[0]*X[0]*X[0]-9*X[1]+2;
}
*/

/*
double func1(double* X)
{
	return X[0]-X[1]-6*log(X[0])-1;
}

double func2(double* X)
{
	return X[0]-3*X[1]-6*log(X[1])-2;
}
*/

double func1(double* X)
{
	return sin(X[0])-X[1]-1.32;
}

double func2(double* X)
{
	return cos(X[1])-X[0]+0.85;
}


int main() {
	const int num=2;
	Func ArrFunc[num]={func1,func2};

	double* X = new double[num];
	X[0]=0.5;
	X[1]=0.2;

	double eps1=1e-15;
	double eps2=1e-15;

	Neuton(ArrFunc,2,X,2,eps1,eps2);

	cout<<"Your decision:\n"<<X[0]<<"\n"<<X[1]<<"\n";

	delete X;
	X=NULL;

	return 0;
}
