/*
 * CLinear_list.h
 *
 *  Created on: 07.04.2015
 *      Author: maximus
 */

#pragma once
#ifndef CLINEAR_LIST_H_
#define CLINEAR_LIST_H_

#include <iostream>
#include <iomanip>
using namespace std;

typedef short counter;

template <typename T=short>
class CLinear_list
{
private:
	struct Node
	{
		T id;
		counter pos;
		Node* next_guy;
		Node* previous_guy;
	};

	Node* m_first_element;
	Node* m_last_element;
	counter m_number_of_elements;
public:

	CLinear_list();
	CLinear_list(const counter& , short = 0);
	~CLinear_list();

	T operator [](counter);

	void print(ostream& =cout);
	void enter(istream& =cin);
	void add_element(T);
	void delete_element(T);
	T find_element(T, ostream& = cout);
	void erase(CLinear_list<T> &);
	counter get_number_of_elements();
};

/////////////////////////////////////////CONSTRUCTORS/////////////////////////////////////////

template<class T>
CLinear_list<T>::CLinear_list()
{
	m_first_element=new Node;
	m_first_element->next_guy=NULL;
	m_first_element->id=0;
	m_last_element=m_first_element;
	m_first_element->pos=1;
	m_number_of_elements=1;
}

template<class T>
CLinear_list<T>::CLinear_list(const counter &n, short x)
{
	m_number_of_elements=0;
	if(n>0)
	{
		m_first_element=new Node;
		m_first_element->id=static_cast<T>(x);
		m_first_element->previous_guy=NULL;
		m_first_element->pos=1;
		Node* now_node=m_first_element;
		for(counter i=1;i<n;i++)
		{
			Node* prev_node=now_node;
			now_node->next_guy=new Node;
			now_node=now_node->next_guy;
			now_node->previous_guy=prev_node;
			now_node->next_guy=NULL;
			now_node->id=static_cast<T>(x);
			now_node->pos=i+1;
		}
		m_last_element=now_node;
		m_number_of_elements=n;
	}
}

template<class T>
CLinear_list<T>::~CLinear_list()
{
	for(counter i=0;i<m_number_of_elements;i++)
	{
		Node* prev_node=m_first_element;
		if(m_first_element->next_guy)
		{
			m_first_element=m_first_element->next_guy;
		}
		delete prev_node;
	}
	m_first_element=NULL;
	m_last_element=NULL;
	cout<<"\nDestructed\n\n";
}

/////////////////////////////////////////METHODS/////////////////////////////////////////

template<class T>
void CLinear_list<T>::print(ostream& f)
{
	f<<"\n\nYour list:\n";
	Node* temp=m_first_element;
	while(temp)
	{
		f<<setw(5)<<temp->pos;
		temp=temp->next_guy;
	}
	f<<endl;

	temp=m_first_element;
	while(temp)
	{
		f<<setw(5)<<temp->id;
		temp=temp->next_guy;
	}
	f<<endl<<endl;
}

template<class T>
void CLinear_list<T>::enter(istream& f)
{
	cout<<"\nEnter your list ("<<m_number_of_elements<<" elements)\n";
	Node* temp=m_first_element;
	while(temp)
	{
		f>>temp->id;
		temp=temp->next_guy;
	}
}

template<class T>
void CLinear_list<T>::add_element(T x)
{
	Node* prev_node=m_last_element;
	m_last_element->next_guy=new Node;
	m_last_element=m_last_element->next_guy;
	m_last_element->previous_guy=prev_node;
	m_last_element->next_guy=NULL;
	m_last_element->id=x;
	m_number_of_elements++;
	m_last_element->pos=m_number_of_elements;
}

template <class T>
void CLinear_list<T>::delete_element(T pos)
{
	if((pos>0)&&(pos<=m_number_of_elements))
	{
		if(pos==1)
		{
			Node* temp=m_first_element;
			m_first_element=m_first_element->next_guy;
			m_first_element->previous_guy=NULL;
			delete temp;
			temp=m_first_element;
			counter temp_pos=0;
			while(temp)
			{
				temp_pos++;
				temp->pos=temp_pos;
				temp=temp->next_guy;
			}
		}
		else
		{
			Node* now_elem=m_first_element->next_guy;
			Node* prev_elem=m_first_element;
			while(now_elem->pos<pos)
			{
				prev_elem=prev_elem->next_guy;
				now_elem=now_elem->next_guy;
			}
				if(now_elem==m_last_element)
				{
					m_last_element=prev_elem;
					m_last_element->next_guy=NULL;
					delete now_elem;
				}
				else
				{
					prev_elem->next_guy=now_elem->next_guy;
					Node* next_node=prev_elem->next_guy;
					next_node->previous_guy=prev_elem;
					delete now_elem;
				}
				counter temp_pos=prev_elem->pos;
				prev_elem=prev_elem->next_guy;
				while(prev_elem)
				{
					temp_pos++;
					prev_elem->pos=temp_pos;
					prev_elem=prev_elem->next_guy;
				}
		}
				m_number_of_elements--;
	}
	else
	{
		cout<<"\n\nERROR while deleting. Check position\n";
	}
}
template <class T>
T CLinear_list<T>::find_element(T x, ostream& f)
{
	Node* now_elem=m_first_element;
	counter n=0;
	f<<"Your element "<<x;
	while(now_elem)
	{
		if(now_elem->id==x)
		{
			n++;
			if(n==1)
			{
				f<<" is placed at positions: ";
			}
			f<<setw(5)<<now_elem->pos;
		}
		now_elem=now_elem->next_guy;
	}
	if(n==0)
	{
		f<<" was not found\n";
	}
}

template <class T>
void CLinear_list<T>::erase(CLinear_list<T> &L1)
{
	Node* now_elem_L=m_first_element;
	Node* now_elem_L1=L1.m_first_element;
	Node* begining_of_deleting=NULL;
	while(now_elem_L!=NULL)
	{
		begining_of_deleting=NULL;
		now_elem_L1=L1.m_first_element;
		bool del=true;
		bool first=true;
		while(now_elem_L1)
		{
			if(!now_elem_L)			//L закончился
			{
				del=false;
				break;
			}
			else if(now_elem_L->id==now_elem_L1->id)
			{
				if(first)
				{
					begining_of_deleting=now_elem_L;
					first=false;
				}
				now_elem_L=now_elem_L->next_guy;
				now_elem_L1=now_elem_L1->next_guy;
			}
			else
			{
				del=false;
				break;
			}
		}
		if(del)
		{
			for(counter i=0;i<L1.m_number_of_elements;i++)
			{
				Node* temp=begining_of_deleting;
				begining_of_deleting=begining_of_deleting->next_guy;
				this->delete_element(temp->pos);
			}
		}
		if(!del)
		{
			if(begining_of_deleting)
			{
				now_elem_L=begining_of_deleting;
			}
			now_elem_L=now_elem_L->next_guy;
		}
	}
}

template<class T>
counter CLinear_list<T>::get_number_of_elements()
{
	return m_number_of_elements;
}

/////////////////////////////////////////OPERATORS/////////////////////////////////////////
template <class T>
T CLinear_list<T>::operator [](counter i)
{
	Node* element=m_first_element;
	counter k=1;
	for(;(k<=m_number_of_elements)&&(element->pos!=i);k++)
	{
		element=element->next_guy;
	}
	if(k==m_number_of_elements+1)
	{
		cout<<"\n\nERROR while getting access to element at "<<i<<" position\n";
		element=m_first_element;
	}
	return element->id;
}

#endif /* CLINEAR_LIST_H_ */
