//============================================================================
// Name        : 1_Gaus.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include "Gaus/Gaus.h"

using namespace std;

int main() {
	double** A=NULL;
	double* B=NULL;
	int n=0;
	double* X=NULL;
	double d=0.0;

	n=3;
	A=new double* [n];
	for(int k=0;k<n;k++)
	{
		A[k]=new double[n];
	}
	B=new double [n];

	/////////////////////////////////////////////

	A[0][0]=8.64;
	A[0][1]=1.71;
	A[0][2]=5.42;
	A[1][0]=-6.39;
	A[1][1]=4.25;
	A[1][2]=1.84;
	A[2][0]=4.21;
	A[2][1]=7.92;
	A[2][2]=-3.41;

	B[0]=10.21;
	B[1]=3.41;
	B[2]=12.29;

	/////////////////////////////////////////////

	Gaus(A,B,n,X,d);

	cout<<"\nDecision:\n";
	for(int k=0;k<n;k++)
	{
		cout<<setw(11)<<X[k]<<"\n";
	}
	cout<<"Error: "<<d<<"\n";

	return 0;
}
