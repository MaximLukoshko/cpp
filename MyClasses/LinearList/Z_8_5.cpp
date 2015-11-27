//============================================================================
// Name        : Z_8_5.cpp
// Author      : Maxim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CLinear_list/CLinear_list.h"

#include <iostream>
using namespace std;

int main() {
	CLinear_list<counter> *list_L;
	list_L = new CLinear_list<counter>(5);

	list_L->enter();
	list_L->print();
	{
		counter num=list_L->get_number_of_elements();
		counter* array_af_amounts = new counter[(num)/2];


		array_af_amounts[0]=(*list_L)[1]+(*list_L)[num];
		counter min_k=1;
		counter min=array_af_amounts[0];
		cout<<endl<<endl;
		for(counter k=2,i=num;k<(num)/2; k++,i--)
		{
			array_af_amounts[k-1]=(*list_L)[k]+(*list_L)[i];
			if(min>array_af_amounts[k-1])
			{
				min=array_af_amounts[k-1];
				min_k=k+1;
			}
		}

		cout<<"The smallest amount is "<<min<<". It is the amount of "<<min_k<<" pair\n"<<endl;

		delete array_af_amounts;
	}


	delete list_L;
	cout<<"\nFinished\n";
	return 0;
}
