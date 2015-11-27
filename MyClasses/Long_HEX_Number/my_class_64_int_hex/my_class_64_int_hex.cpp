/*
 * my_class_64_int_hex.cpp
 *
 *  Created on: 30.03.2015
 *      Author: maximus
 */

#include "my_class_64_int_hex.h"


//////////////////////////CONSTRUCNORS//////////////////////////

C_64_int_hex::C_64_int_hex()
	{
		short i=0;
		while(i<num_razryadov)
		{
			m_cifra[i]=0;
			i++;
		}
		clear_Dec();
	};

C_64_int_hex::C_64_int_hex(int k)
	{
		short i=0;
		while(i<64)
		{
			m_cifra[i]=k%16;
			k=k/16;
			i++;
		}
		clear_Dec();
		to_Dec();
	};

C_64_int_hex::C_64_int_hex(C_64_int_hex* C64)
	{
		short i=0;
		while(i<64)
		{
			m_cifra[i]=C64->m_cifra[i];
			i++;
		}
		clear_Dec();
		to_Dec();
	};





//////////////////////////OPERATORS//////////////////////////

void operator >>(istream& f, C_64_int_hex* T)
{
	cout<<endl;
	short i=0;
	while(i<64)
	{
		T->m_cifra[i]=0;
		i++;
	}
	i=0;
	while(i<num_razryadov)
	{
		char ch;
		f.get(ch);
		if(ch!='\n')
		{
			T->m_cifra[i]=static_cast<int>(ch)-48;
			if(T->m_cifra[i]>9)
			{
				T->m_cifra[i]-=7;
				if(T->m_cifra[i]>15)
				{
					T->m_cifra[i]=0;
					i--;
				}
			}
			else if (T->m_cifra[i]<0)
			{
				T->m_cifra[i]=0;
				i--;
			}
		}
		else
		{
			break;
		}
		i++;
	}

	short k=0;
	while(k<i/2)
	{
		swap(T->m_cifra[k], T->m_cifra[i-1-k]);
		k++;
	}
	T->C_64_int_hex::to_Dec();
};



void operator <<(ostream& f, C_64_int_hex* T)
{
	short i=num_razryadov-1;
	while((T->m_cifra[i]==0)&&(i>=1))
		{
		//	cout<<" ";
			i--;
		}
	if((i==0)&&(T->m_cifra[i]==0))
		{
			f<<0;

		}
	else
		{
			while(i>=0)
			{
				if(T->m_cifra[i]<10)
				{
					f<<(static_cast<char>(T->m_cifra[i]+48));
				}
				else
				{
					f<<(static_cast<char>(T->m_cifra[i]+55));
				}
				i--;
			}
		}
};

char C_64_int_hex::operator [](const short i)
{
	short cif;
	cif=m_cifra[0];
	if(i<0)
	{
		cif=m_cifra[0];
	}
	else if(i>=num_razryadov)
	{
		cif=m_cifra[num_razryadov-1];
	}
	else
	{
		cif=m_cifra[i];
	}
	char sign = '\0';
	if(m_cifra[i]<10)
	{
		sign=static_cast<char>(m_cifra[i]+48);
	}
	else
	{
		sign=static_cast<char>(m_cifra[i]+55);
	}
	return sign;
}

C_64_int_hex& C_64_int_hex::operator = (const C_64_int_hex& B)
{
	short i=0;
	while(i<num_razryadov)
	{
		m_cifra[i]=B.m_cifra[i];
		m_cifra_dec[i]=B.m_cifra_dec[i];
		i++;
	}
	while(i<num_razryadov)
	{
		m_cifra_dec[i]=B.m_cifra_dec[i];
		i++;
	}
	return *this;
}





C_64_int_hex operator * (C_64_int_hex A,C_64_int_hex B)
{
	C_64_int_hex C(0);

	for(short i=0;i<num_razryadov;i++)
	{
		for(short j=0;j<num_razryadov;j++)
		{
			short proizv=A.m_cifra[i]*B.m_cifra[j];
			C.m_cifra[i+j]+=proizv%16;
			proizv/=16;
			if(C.m_cifra[i+j]>15)
			{
				C.m_cifra[i+j]%=16;
				proizv++;
			}
			if(proizv>0)
			{
				short k=1;
				while((proizv>0)&&(i+j+k<num_razryadov))
				{
					C.m_cifra[i+j+k]+=proizv%16;
					proizv/=16;
					if(C.m_cifra[i+j+k]>15)
					{
						C.m_cifra[i+j+k]%=16;
						proizv++;
					}
					k++;
				}
			}
		}
	}
	C.C_64_int_hex::to_Dec();

	cout<<"entered"<<endl;
	return C;
}


//////////////////////////METHODS//////////////////////////

void C_64_int_hex::to_Dec()
{
	short pow_16=1;
	for(short i=0;i<num_razryadov;i++)
		{
			short proizv=m_cifra[i]*pow_16;
			short k=0;
			while((proizv>0)&&(k<num_razryadov))
			{
				m_cifra_dec[k]+=proizv%10;
				proizv/=10;
				if(m_cifra_dec[k]>9)
				{
					m_cifra_dec[k]%=10;
					proizv++;
				}
				k++;
			}
			pow_16*=16;
		}
}

void C_64_int_hex::Dec()
{
	to_Dec();
}

void C_64_int_hex::clear_Dec()
{
	{
		for(short k=num_razryadov_dec-1; k>=0; k--)
		{
			m_cifra_dec[k]=0;
		}
	}
}

void C_64_int_hex::show_Dec()
{
	for(short k=num_razryadov_dec-1; k>=0; k--)
	{
		cout<<m_cifra_dec[k];
	}
}
