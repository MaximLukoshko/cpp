//============================================================================
// Name        : Z_8_1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "my_class_64_int_hex/my_class_64_int_hex.h"

#include <iostream>
using namespace std;

int main() {
	C_64_int_hex* _1 = new C_64_int_hex();
	C_64_int_hex* _2 = new C_64_int_hex();
	C_64_int_hex* _3 = new C_64_int_hex();
	cout<<_1;


	/*cin>>_1;
	cin>>_1;
	cin>>_2;
	cout<<endl;
	cout<<(*_1)[0]<<endl;
	(*_3)=(*_1)*(*_2);
	cout<<_3;
	cout<<endl;
	(*_3).show_Dec();
	cout<<endl;
	cout<<_3;
	cout<<endl<<"entered"<<endl;*/

	delete _3;
	delete _1;
	delete _2;

	cout<<"finished"<<endl;
	return 0;
}
