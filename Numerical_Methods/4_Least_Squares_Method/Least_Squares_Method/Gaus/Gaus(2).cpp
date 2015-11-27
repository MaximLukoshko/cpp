/*
 * Gaus.cpp
 *
 *  Created on: 10.09.2015
 *      Author: maximus
 */
#include "Gaus.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;


class CMatrix
{
private:

	double* *m_Matrix;	//Матрица системы

	int m_num_lines;
	int m_num_columns;
	double* m_solution;	//Указатель на столбец-решение

	void Create_help_number(int i, double num, double* &p);
	void Clear_column(int i);								//Провернуть один шаг Гаусса
	void add_columns(int num_of_additional_columns);		//Добавть колонку в конец

	void Set();							//Ввести матрицу
	void Print();						//Вывести матрицу
	void Choose_main_element(int i);	//Выбрать главный элемент
	void Transform_to_up_triangle();	//Привести к треугольному виду
	void Solve_system();				//Решить систему
	void Check_decision(double &d);		//Оценить погрешность

public:

	CMatrix(int num_lines, int num_columns, double** A, double* B);
	CMatrix(int num_lines, int num_columns);
	~CMatrix();

	double* return_solution(double &d);	//Выдать ответ


};

///////////////////////////////////////////CONSTRUCTORS///////////////////////////////////////////////////////

CMatrix::CMatrix(int num_lines, int num_columns)
{
	m_num_lines=num_lines;
	m_num_columns=num_columns;

	m_Matrix=new double*[m_num_lines];
	for(int i=0;i<m_num_lines;i++)
	{
		m_Matrix[i]=new double[num_columns];
	}
}

CMatrix::CMatrix(int num_lines, int num_columns, double** A, double* B)
{
	m_num_lines=num_lines;
	m_num_columns=num_columns;
	m_solution=NULL;

	m_Matrix=new double*[m_num_lines];
	for(int i=0;i<m_num_lines;i++)
	{
		m_Matrix[i]=new double[num_columns];
		for(int j=0;j<m_num_columns;j++)
		{
			m_Matrix[i][j]=A[i][j];
		}
	}

	this->add_columns(1);					//Добавить и заполнить столбец правой части
	for(int k=0;k<m_num_lines;k++)			//
	{										//
		m_Matrix[k][m_num_columns-1]=B[k];	//
	}										//

	//this->Print();
}

CMatrix::~CMatrix()
{
	for(int i=0;i<m_num_lines;i++)
	{
		delete []m_Matrix[i];
	}
	delete []m_Matrix;
	m_Matrix=NULL;
	//cout<<"\n\nDestructed\n";
	m_num_columns--;
}


double skalyar(double** array1,double* array2, int number_line, int number_col, int number)
{					//Скалярное произведение
	double sum=0;
	for(int k=0; k<number; k++)
	{
		sum+=array1[number_line][k]*array2[k];
	}
	return sum;
}


///////////////////////////////////////////METHODS///////////////////////////////////////////////////////



void CMatrix::add_columns(int num_of_additional_columns)
{
	for(int i=0;i<m_num_lines;i++)
	{
		double* temp=new double[m_num_columns+num_of_additional_columns];
		for(int j=0;j<m_num_columns;j++)
		{
			temp[j]=m_Matrix[i][j];
		}
		delete []m_Matrix[i];
		m_Matrix[i]=temp;
	}
	m_num_columns+=num_of_additional_columns;
}


void CMatrix::Print(){
	cout<<"Your System: "<<"\n";
	for(int i=0;i<m_num_lines;i++)
	{
		for(int j=0; j<m_num_columns-1;j++)
		{
			cout<<setw(11)<<m_Matrix[i][j];
		}
		cout<<setw(11)<<"|"<<setw(11)<<m_Matrix[i][m_num_columns-1];
		cout<<"\n";
	}
}

void CMatrix::Set(){
	cout<<"Enter Matrix "<< " ("<<m_num_lines<<", "<<m_num_columns<<")\n";
	for(int i=0;i<m_num_lines;i++)
	{
		for(int j=0; j<m_num_columns;j++)
		{
			cin>>m_Matrix[i][j];
		}
	}

}

void CMatrix::Choose_main_element(int i){
	double max=fabs(m_Matrix[i][i]);
	int i_max=i;
	for(int k=i;k<m_num_lines;k++){
		if(fabs(m_Matrix[k][i])>max){
			max=fabs(m_Matrix[k][i]);
			i_max=k;
		}
		//cout<<max<<" "<<i_max<<endl;
		swap(m_Matrix[i], m_Matrix[i_max]);
	}

	for(int k=m_num_columns-1;k>=0;k--){		//Делаем главный элемент единицей
		m_Matrix[i][k]/=m_Matrix[i][i];
	}
}

void CMatrix::Create_help_number(int i, double num, double* &p){
	for(int k=0;k<m_num_columns;k++){
		p[k]=m_Matrix[i][k]*num;
	}
	//cout<<endl;
}

void CMatrix::Clear_column(int i){
	for(int k=i+1;k<m_num_lines;k++){
		double* p=new double[m_num_columns];

		Create_help_number(i,m_Matrix[k][i],p);

		for(int l=i;l<m_num_columns;l++){
			m_Matrix[k][l]-=p[l];
		}
		delete[] p;
		p=NULL;
	}
}

void CMatrix::Transform_to_up_triangle(){
	for(int k=0;k<m_num_lines;k++)
	{
		Choose_main_element(k);
		Clear_column(k);
	}
}

void CMatrix::Solve_system()	//Находит вектор-столбец решений
{
	double* p=NULL;
	p=new double[m_num_columns-1];
	for(int k=m_num_columns-2;k>=0;k--)
	{
		p[k]=m_Matrix[k][m_num_columns-1];
		for(int i=k+1;i<m_num_columns-1;i++)
		{
			p[k]-=m_Matrix[k][i]*p[i];
		}

		//Округляем до трёх знаков после запятой
	//	p[k]=(static_cast<int>((p[k])*1000+0.5))/1000.0;
	}

	m_solution=p;
}

void CMatrix::Check_decision(double &d)
{
	double* fluct = new double[m_num_lines];
	int k=0;
	fluct[k]=skalyar(m_Matrix,m_solution,k,0,m_num_lines)-m_Matrix[k][m_num_columns-1];
	double max=fabs(fluct[k]);
	k++;

	for(;k<m_num_lines;k++)
	{
		fluct[k]=skalyar(m_Matrix,m_solution,k,0,m_num_lines)-m_Matrix[k][m_num_columns-1];
		if(fabs(fluct[k])>max)
		{
			max=fabs(fluct[k]);
		}
	}
	delete fluct;
	d=max;
}

double* CMatrix::return_solution(double &d)
{
	this->Transform_to_up_triangle();
	this->Solve_system();
	this->Check_decision(d);
	return m_solution;
}




///////////////////////////////////////////////////////////////////////


void Gaus(double** A,double* B, unsigned int n, double* &X, double &d)
{
	if((A!=NULL)&&(B!=NULL))
	{
		CMatrix* System=new CMatrix(n, n, A, B);
		X=System->return_solution(d);
		delete System;
		System=NULL;
	}
	else
	{
		cout<<"\n\nERROR: Check source of data\n";
	}
}

