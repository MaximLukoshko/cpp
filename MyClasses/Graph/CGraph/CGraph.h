/*
 * CGraph.h
 *
 *  Created on: 13.04.2015
 *      Author: maximus
 */
#pragma once
#ifndef CGRAPH_H_
#define CGRAPH_H_

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

template<class T, typename counter>
class CGraph
{
private:
	struct list_smezhnyh_vershin
	{
		int nomer_vershiny;
		list_smezhnyh_vershin* next_guy;
		list_smezhnyh_vershin* previous_guy;
	};

	struct list_vershin
	{
		int nomer_vershiny;
		T info_field;
		short* dostigimiye_vershiny;
		list_smezhnyh_vershin* l_sm_v;
		list_vershin* next_guy;
		list_vershin* previous_guy;
	};

	list_vershin* m_nachalo_spiska;
	list_vershin* m_konec_spiska;

	short m_num_of_vertices;
	short m_last_element;

	//Проверяет, можно ли вершину с заданным номером сделать смежной текущей
	bool checker(list_smezhnyh_vershin* vershiny, short nomer_ustanavlivaemoy_vershiny);
	bool checker(list_vershin* vershiny, short nomer_ustanavlivaemoy_vershiny);
	bool checker(short* vershiny, short nomer_ustanavlivaemoy_vershiny, short nomer_tekuschey_vershiny, short num_versh);

	//Решение поставленной задачи
	short calculate_number_vershin_s_kotoryh_ona_dostizhima(list_vershin* nachalo, int id);
	short calculate_number_dostizhimyh_vershin(list_smezhnyh_vershin* l_sm_v);
	bool analyse_stok(list_vershin* nachalo, short id, short* mas, short num_versh);
	bool vstrech(short id, short* mas, short &num_versh);
	void analyse_all(list_vershin* vertices, list_smezhnyh_vershin* smezh_vert, short* dostigimiye_vershiny, short &now_pos, short &num_versh);
	void analyse_dostigimost(list_vershin* nachalo, list_vershin* analysing_vertice, short num_vert);


	void ustanovit_smezhnosti(list_smezhnyh_vershin* &nachalo_smezhnyh, int tekuschaya_vershina, int number_of_elements);
	void vyvod_smezh(list_smezhnyh_vershin* nachalo_spiska);
	void delete_list(list_smezhnyh_vershin* &nachalo);
	void delete_element(short id, list_smezhnyh_vershin* &start);
	void delete_element(short id, list_vershin* &start, list_vershin* &finish);

public:
	CGraph();
	~CGraph();

	void Zapolnit();
	void print();
	void find_drain();
	void find_source();
	void add_vertice();
	void delete_vertice(short n);
	void delete_graph();
};

//////////////////////////////////////CONSTRUCTORS/////////////////////////////////////////////
template<class T, typename counter>
CGraph<T,counter>::CGraph()
{
	m_num_of_vertices=0;
	m_last_element=-1;
	m_nachalo_spiska=NULL;
	m_konec_spiska=NULL;
}

template<class T, typename counter>
CGraph<T,counter>::~CGraph()
{
	this->delete_graph();
}


template<class T, typename counter>
bool CGraph<T,counter>::checker(short* vershiny, short nomer_ustanavlivaemoy_vershiny, short nomer_tekuschey_vershiny, short num_versh)
{
	bool met=false;
	if(nomer_ustanavlivaemoy_vershiny!=nomer_tekuschey_vershiny)
	{
		short i=0;
		while(i<num_versh)
		{
			if((vershiny[i]==nomer_ustanavlivaemoy_vershiny))
			{
				met=true;
			}
			i++;
		}
	}
	else
	{
		met=true;
	}
	return met;
}

template<class T, typename counter>
void CGraph<T,counter>::ustanovit_smezhnosti(list_smezhnyh_vershin* &nachalo_smezhnyh, int tekuschaya_vershina, int number_of_elements)
{
	nachalo_smezhnyh=NULL;
	if(number_of_elements>1)
	{
		short* vershiny = new short[number_of_elements];
		short numb_smezh=0;
		short i=0;
		list_smezhnyh_vershin* L1;


		short sm_versh=tekuschaya_vershina;
		while(sm_versh==tekuschaya_vershina)
		{
			sm_versh=rand()%number_of_elements;
		}
		L1 = new list_smezhnyh_vershin;		//Устанавливает связи между элементами
		L1->nomer_vershiny=sm_versh;
		L1->next_guy=L1->previous_guy=NULL;
		vershiny[numb_smezh]=L1->nomer_vershiny;
		numb_smezh++;
		nachalo_smezhnyh=L1;


		while(i<1)
		{
			sm_versh=tekuschaya_vershina;
			while(sm_versh==tekuschaya_vershina)
			{
				sm_versh=rand()%number_of_elements;
			}
			if(checker(vershiny,sm_versh, i,numb_smezh)==0)
			{
				list_smezhnyh_vershin* L = new list_smezhnyh_vershin;
				L->nomer_vershiny=sm_versh;
				L1->next_guy=L;
				L->previous_guy=L1;
				L1=L1->next_guy;
				vershiny[numb_smezh]=L->nomer_vershiny;
				numb_smezh++;
			}
			i++;
		}

		delete[] vershiny;
	}

}

template<class T, typename counter>
void CGraph<T,counter>::Zapolnit()
{
	counter number_of_elements;
	cout<<"\n\nEnter number of elements: \n";
	cin>>number_of_elements;
	srand(time(NULL));
	if(number_of_elements>0)
	{
		list_vershin* L1 = new list_vershin;		//Устанавливает связи между элементами
		L1->nomer_vershiny=0;
		m_nachalo_spiska=L1;
		m_konec_spiska=L1;
		L1->next_guy=L1->previous_guy=NULL;
		ustanovit_smezhnosti(L1->l_sm_v, L1->nomer_vershiny, number_of_elements);
		int k=1;
		while(k<number_of_elements)
		{
			list_vershin* L = new list_vershin;
			L->nomer_vershiny=k;
			L1->next_guy=L;
			L->previous_guy=L1;
			m_konec_spiska=L;
			ustanovit_smezhnosti(L->l_sm_v, L->nomer_vershiny, number_of_elements);
			L1=L1->next_guy;
			k++;
		}
		m_num_of_vertices=number_of_elements;
		m_last_element=number_of_elements-1;
		this->print();
	}
}


template<class T,typename counter>
void CGraph<T, counter>::vyvod_smezh(list_smezhnyh_vershin* nachalo_spiska)
{
	list_smezhnyh_vershin* maxim=nachalo_spiska;

	while(maxim)
	{
		cout<<setw(4)<<maxim->nomer_vershiny;
		maxim=maxim->next_guy;
	}
}

template<class T,typename counter>
void CGraph<T, counter>::print()
{
	list_vershin* maxim=m_nachalo_spiska;

	cout<<"\nYour Graph:\n";
	while(maxim)
	{
		cout<<setw(3)<<maxim->nomer_vershiny<<setw(3)<<"";
		vyvod_smezh(maxim->l_sm_v);
		cout<<endl;
		maxim=maxim->next_guy;
	}
}

template<class T,typename counter>
void CGraph<T, counter>::delete_list(list_smezhnyh_vershin* &nachalo)
{
	list_smezhnyh_vershin* L=nachalo;
	list_smezhnyh_vershin* L_next=L->next_guy;
	while(L)
	{
		L_next=L->next_guy;
		delete L;
		L=L_next;
	}
}

template<class T,typename counter>
void CGraph<T, counter>::delete_graph()
{
	list_vershin* L=m_nachalo_spiska;
	list_vershin* L_next=L->next_guy;
	m_konec_spiska=NULL;
	while(L)
	{
		L_next=L->next_guy;
		delete_list(L->l_sm_v);
		if(L->dostigimiye_vershiny)
		{
			delete []L->dostigimiye_vershiny;
		}
		delete L;
		L=L_next;
	}
	m_nachalo_spiska=NULL;
}

template<class T,typename counter>
bool CGraph<T, counter>::vstrech(short id, short* mas, short &num_versh)
{
	bool good=false;
	short k=0;
	while(k<num_versh)
	{
		if(mas[k]==id)
		{
			good=true;
			break;
		}
		k++;
	}
	return good;
}

template<class T,typename counter>
void CGraph<T, counter>::analyse_all(list_vershin* vertices, list_smezhnyh_vershin* smezh_vert, short* dostigimiye_vershiny, short &now_pos, short &num_versh)
{
	while(smezh_vert)
	{
		if(vstrech(smezh_vert->nomer_vershiny, dostigimiye_vershiny, now_pos)==false)
		{
			dostigimiye_vershiny[now_pos]=smezh_vert->nomer_vershiny;
			now_pos++;
			list_vershin* next_versh=vertices;
			while(next_versh->nomer_vershiny!=smezh_vert->nomer_vershiny)
			{
				next_versh=next_versh->next_guy;
			}
			analyse_all(vertices, next_versh->l_sm_v,dostigimiye_vershiny,now_pos,num_versh);
		}
		smezh_vert=smezh_vert->next_guy;
	}
}

template<class T,typename counter>
void CGraph<T, counter>::analyse_dostigimost(list_vershin* nachalo, list_vershin* analysing_vertice, short num_vert)
{
	if(analysing_vertice->l_sm_v!=NULL)
	{
		short i=0;
		list_smezhnyh_vershin* smezh_vert=analysing_vertice->l_sm_v;
		analysing_vertice->dostigimiye_vershiny = new short[num_vert];
		for(short l=0;l<num_vert;l++)
		{
			analysing_vertice->dostigimiye_vershiny[l]=-1;
		}
		analysing_vertice->dostigimiye_vershiny[i]=analysing_vertice->nomer_vershiny;
		i++;

		analyse_all(nachalo,smezh_vert, analysing_vertice->dostigimiye_vershiny, i, num_vert);

		if(i==num_vert)
		{
			cout<<analysing_vertice->nomer_vershiny<<endl;
		}
		//delete []analysing_vertice->dostigimiye_vershiny;
		//analysing_vertice->dostigimiye_vershiny=NULL;
	}
}


template<class T,typename counter>
bool CGraph<T, counter>::analyse_stok(list_vershin* nachalo, short id, short* mas, short num_versh)
{
	list_vershin* vertice=nachalo;
	short k=0;
	while(vertice)
	{
		if(vstrech(id,mas,num_versh))
		{
			k++;
		}
		else
		{
			break;
		}
		vertice=vertice->next_guy;
	}
	if(k==num_versh)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<class T,typename counter>
short CGraph<T, counter>::calculate_number_dostizhimyh_vershin(list_smezhnyh_vershin* l_sm_v)
{
	short num=0;
	list_smezhnyh_vershin* vershina=l_sm_v;

	while(vershina)
	{
		num++;
		vershina=vershina->next_guy;
	}

	return num;
}
template<class T,typename counter>
short CGraph<T, counter>::calculate_number_vershin_s_kotoryh_ona_dostizhima(list_vershin* nachalo, int id)
{
	short num=0;
	list_vershin* vershina=nachalo;

	while(vershina)
	{
		list_smezhnyh_vershin* smezhnaya_vershina=vershina->l_sm_v;
		while(smezhnaya_vershina)
		{
			if(smezhnaya_vershina->nomer_vershiny==id)
			{
				num++;
				break;
			}
			smezhnaya_vershina=smezhnaya_vershina->next_guy;
		}

		vershina=vershina->next_guy;
	}
	return num;
}

template<class T,typename counter>
void CGraph<T, counter>::find_drain()
{
	list_vershin* vershina=m_nachalo_spiska;
	cout<<endl<<"Drains:"<<endl;
	short i=0;
	while(i<m_num_of_vertices)
	{
		short l=0;
		vershina=m_nachalo_spiska;
		while(vershina)
		{
			if(analyse_stok(m_nachalo_spiska, i, vershina->dostigimiye_vershiny, m_num_of_vertices)==false)
			{
				break;
			}
			l++;
			vershina=vershina->next_guy;
		}
		if(l==m_num_of_vertices)
		{
			cout<<i<<endl;
		}
		i++;
	}
}

template<class T,typename counter>
void CGraph<T, counter>::find_source()
{
	list_vershin* vershina=m_nachalo_spiska;
	cout<<endl<<"Sources:"<<endl;
	while(vershina)
	{
		analyse_dostigimost(m_nachalo_spiska, vershina,m_num_of_vertices);	//анализировать на исток
		vershina=vershina->next_guy;
	}
}


template<class T, typename counter>
bool CGraph<T,counter>::checker(list_smezhnyh_vershin* vershiny, short nomer_ustanavlivaemoy_vershiny)
{
	bool met=false;
	if(nomer_ustanavlivaemoy_vershiny!=m_konec_spiska->nomer_vershiny)
	{
		list_smezhnyh_vershin* temp=m_konec_spiska->l_sm_v;
		while(temp)
		{
			if((temp->nomer_vershiny==nomer_ustanavlivaemoy_vershiny))
			{
				met=true;
			}
			temp=temp->next_guy;
		}
	}
	else
	{
		met=true;
	}
	return met;
}


template<class T, typename counter>
bool CGraph<T,counter>::checker(list_vershin* vershiny, short nomer_ustanavlivaemoy_vershiny)
{
	bool met=false;
	if(nomer_ustanavlivaemoy_vershiny!=m_konec_spiska->nomer_vershiny)
	{
		list_vershin* temp=m_nachalo_spiska;
		while(temp)
		{
			if((temp->nomer_vershiny==nomer_ustanavlivaemoy_vershiny))
			{
				met=true;
				break;
			}
			temp=temp->next_guy;
		}
	}
	else
	{
		met=true;
	}
	return met;
}

template<class T,typename counter>
void CGraph<T, counter>::add_vertice()
{
	m_konec_spiska->next_guy= new list_vershin;
	list_vershin* h=m_konec_spiska->next_guy;
	h->previous_guy=m_konec_spiska;
	m_konec_spiska=m_konec_spiska->next_guy;
	m_konec_spiska->next_guy=NULL;
	m_konec_spiska->nomer_vershiny=m_last_element+1;
	m_last_element++;
	m_num_of_vertices++;
	m_konec_spiska->l_sm_v=NULL;
	cout<<"\n\n\nYou are adding vertice "<<m_last_element<<"\n";
	cout<<"How much neighbour vertices do you need?\n";
	counter n=0;
	cin>>n;
	cout<<"\nEnter neighbour vertices: ";
	if(n>m_num_of_vertices)
	{
		n=m_num_of_vertices;
	}
	if(n>0)
	{
		counter id_neighbour_vertice=0;
		cin>>id_neighbour_vertice;
		list_smezhnyh_vershin* temp = NULL;
		if(checker(m_konec_spiska->l_sm_v,id_neighbour_vertice)==0)
		{
			m_konec_spiska->l_sm_v= new list_smezhnyh_vershin;
			temp = m_konec_spiska->l_sm_v;
			temp->nomer_vershiny=id_neighbour_vertice;
			temp->previous_guy=NULL;
			temp->next_guy=NULL;
		}
		for(counter k=1; k<n; k++)
		{
			cin>>id_neighbour_vertice;
			if(checker(m_konec_spiska->l_sm_v,id_neighbour_vertice)==0)
			{
				if(temp)
				{
					temp->next_guy= new list_smezhnyh_vershin;
					temp->next_guy->previous_guy=temp;
					temp = temp->next_guy;
					temp->nomer_vershiny=id_neighbour_vertice;
				}
				else
				{
					m_konec_spiska->l_sm_v= new list_smezhnyh_vershin;
					temp = m_konec_spiska->l_sm_v;
					temp->nomer_vershiny=id_neighbour_vertice;
					temp->previous_guy=NULL;
					temp->next_guy=NULL;
				}
			}
		}

		cout<<"\nEnter vertices, for that this vertice is neighbour: \nHow much?\n";
		cin>>n;
		if(n>0)
		{
			cout<<"Enter vertices:\n";
			for(short k=0;k<n;k++)
			{
				cin>>id_neighbour_vertice;
				list_vershin* temp=m_nachalo_spiska;
				if(id_neighbour_vertice!=m_last_element)
				{
					while(temp)
					{
						if((temp->nomer_vershiny==id_neighbour_vertice)&&(temp->l_sm_v->nomer_vershiny!=m_last_element))
						{
							list_smezhnyh_vershin* helper= new list_smezhnyh_vershin;
							helper->next_guy=temp->l_sm_v;
							temp->l_sm_v->previous_guy=helper;
							helper->previous_guy=NULL;
							temp->l_sm_v=helper;
							helper->nomer_vershiny=m_last_element;
							break;
						}
						temp=temp->next_guy;
					}
				}
			}
		}
	}
}

template<class T,typename counter>
void CGraph<T, counter>::delete_vertice(short n)
{
	if(checker(m_nachalo_spiska,n))
	{
		/*cout<<"\n\nEnter vertice you want delete:\n";
		short n;
		cin>>n;*/
		//cout<<"\n fff \n";
		//cout<<m_konec_spiska->nomer_vershiny;
		list_vershin* temp = m_nachalo_spiska;
		//cout<<m_konec_spiska->nomer_vershiny;
		//cout<<temp->nomer_vershiny<<" "<<temp<<" "<<temp->previous_guy;
		/*while(temp)
		{
			cout<<"\naaa\n";
			cout<<temp->nomer_vershiny<<" ";
			temp=temp->previous_guy;
		}*/

		while(temp)
		{
			delete_element(n,temp->l_sm_v);
			temp=temp->next_guy;
		}
		delete_element(n,m_nachalo_spiska,m_konec_spiska);
		m_num_of_vertices--;
	}
	else
	{
		cout<<"\nCheck Vertice that you want to delete\n";
	}
}


template <class T, typename counter>
void CGraph<T,counter>::delete_element(short id, list_smezhnyh_vershin* &start)
{
	if(start)
	{
		list_smezhnyh_vershin* help=start;
		if(help->nomer_vershiny==id)
		{
			list_smezhnyh_vershin* temp=start;
			start=start->next_guy;

			if(start)
			{
				start->previous_guy=NULL;
			}

			delete temp;
			temp=start;
		}
		else
		{
			list_smezhnyh_vershin* prev_elem=start;
			if(prev_elem->nomer_vershiny!=id)
			{
				list_smezhnyh_vershin* now_elem=start->next_guy;
				while((now_elem)&&(now_elem->nomer_vershiny!=id))
				{
					prev_elem=prev_elem->next_guy;
					now_elem=now_elem->next_guy;
				}
				if(now_elem)
				{
					prev_elem->next_guy=now_elem->next_guy;
					if(prev_elem->next_guy)
					{
						prev_elem->next_guy->previous_guy=prev_elem;
					}
					delete now_elem;
				}
			}
			else
			{
				if(prev_elem)
				{
					start=prev_elem->next_guy;
					delete prev_elem;
				}
				if(start)
				{
					start->previous_guy=NULL;
				}
			}
		}
	}
}

template <class T, typename counter>
void CGraph<T,counter>::delete_element(short id, list_vershin* &start,  list_vershin* &finish)
{

	list_vershin* help=start;
	if(help->nomer_vershiny==id)
	{
		list_vershin* temp=start;
		start=start->next_guy;
		start->previous_guy=NULL;
		delete_list(temp->l_sm_v);
		if(temp->dostigimiye_vershiny)
		{
			delete []temp->dostigimiye_vershiny;
			temp->dostigimiye_vershiny=NULL;
		}
		delete temp;
		temp=start;
	}
	else
	{
		list_vershin* now_elem=start->next_guy;
		list_vershin* prev_elem=start;
		while((now_elem)&&(now_elem->nomer_vershiny!=id))
		{
			prev_elem=prev_elem->next_guy;
			now_elem=now_elem->next_guy;
		}
			if(now_elem==NULL)
			{
				prev_elem->next_guy=NULL;
				delete_list(now_elem->l_sm_v);
				if(now_elem->dostigimiye_vershiny)
				{
					delete []now_elem->dostigimiye_vershiny;
					now_elem->dostigimiye_vershiny=NULL;
				}
				finish=prev_elem;
				delete now_elem;
			}
			else
			{
				prev_elem->next_guy=now_elem->next_guy;
				prev_elem->next_guy->previous_guy=prev_elem;
				delete_list(now_elem->l_sm_v);
				if(now_elem->dostigimiye_vershiny)
				{
					delete []now_elem->dostigimiye_vershiny;
					now_elem->dostigimiye_vershiny=NULL;
				}
				delete now_elem;
			}
	}
}

#endif /* CGRAPH_H_ */
