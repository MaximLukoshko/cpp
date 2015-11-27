/*
 * my_class_64_int_hex.h
 *
 *  Created on: 23.03.2015
 *      Author: maximus
 */

#pragma once
#ifndef MY_CLASS_64_INT_HEX_H_
#define MY_CLASS_64_INT_HEX_H_
#include <iostream>
using namespace std;

const short num_razryadov=64;
const short num_razryadov_dec=100;
class C_64_int_hex
{
private:

	short m_cifra[num_razryadov];
	short m_cifra_dec[num_razryadov_dec];
	void clear_Dec();
	void Dec();
	void to_Dec();

public:
	C_64_int_hex();

	C_64_int_hex(int k);

	C_64_int_hex(C_64_int_hex* C64);

	~C_64_int_hex(){cout<<endl<<endl<<endl<<"Destructed"<<endl;};

	void show_Dec();

	friend void operator >>(istream& f, C_64_int_hex* T);
	friend void operator <<(ostream& f, C_64_int_hex* T);
	friend C_64_int_hex operator * (C_64_int_hex A,C_64_int_hex B);
	C_64_int_hex& operator = (const C_64_int_hex& B);
	char operator [](const short i);
};


#endif /* MY_CLASS_64_INT_HEX_H_ */
