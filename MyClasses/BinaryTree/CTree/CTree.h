/*
 * CTree.h
 *
 *  Created on: 09.04.2015
 *      Author: maximus
 */

#pragma once
#ifndef CTREE_H_
#define CTREE_H_
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class CTree
{
private:
	struct TREE
	{
		T id;
		TREE* left_guy;
		TREE* right_guy;
	};
	TREE* root;

	TREE* search_pos(T idik)
	{
		T id=idik;
		TREE* ppv;
		TREE* pv=root;
		while(pv)
		{
			ppv=pv;
			if(id<pv->id)
			{
				pv=pv->left_guy;
			}
			else
			{
				pv=pv->right_guy;
			}
		}
		return ppv;
	}

	void delete_tree(TREE* &r);
	void vyvod_po_urovnyam(TREE* r, short level);
	void obhod_dereva(TREE* root);
	void delete_leave(TREE* branch, TREE* leave);
	void delete_leaves_h(TREE* root);

public:
	CTree(T id);
	~CTree();

	void insert_element(T id);
	void print_ascending(ostream& =cout);
	void print(ostream& =cout);
	void delete_leaves();
	void enter(short num, istream& =cin);
};

/////////////////////////////////////////CONSTRUCTORS/////////////////////////////////////////

template<class T>
CTree<T>::CTree(T id)
{
	root = new TREE;
	root->id=id;
}

template<class T>
CTree<T>::~CTree()
{
	if(root)
	{
		delete_tree(root->left_guy);
		delete_tree(root->right_guy);
	}
	delete root;
	root=NULL;
	cout<<"\n\nDestructed\n";
}


/////////////////////////////////////////OPERATORS/////////////////////////////////////////

/////////////////////////////////////////METHODS/////////////////////////////////////////

template<class T>
void CTree<T>::delete_tree(TREE* &root)
{
	if(root)
	{
		delete_tree(root->left_guy);
		delete_tree(root->right_guy);
	}
	delete root;
	root=NULL;
}

template <class T>
void CTree<T>::insert_element(T id)
{
	TREE* place_for_inserting=search_pos(id);
	if(id<place_for_inserting->id)
	{
		place_for_inserting->left_guy = new TREE;
		place_for_inserting->left_guy->id = id;
	}
	else if(id>place_for_inserting->id)
	{
		place_for_inserting->right_guy = new TREE;
		place_for_inserting->right_guy->id = id;
	}
}

template<class T>
void CTree<T>::obhod_dereva(TREE* root)
{
	if(root)
	{
		if(root->left_guy)
		{
			obhod_dereva(root->left_guy);
		}

		cout<<setw(5)<<root->id;

		if(root->right_guy)
		{
			obhod_dereva(root->right_guy);
		}
	}
}

template <class T>
void CTree<T>::print_ascending(ostream& f)
{
	if(root)
	{
		f<<"\n\nYour tree:\n";
		if(root->left_guy)
		{
			obhod_dereva(root->left_guy);
		}

		f<<setw(5)<<root->id;

		if(root->right_guy)
		{
			obhod_dereva(root->right_guy);
		}
		f<<"\n";
	}
}

template <class T>
void CTree<T>::vyvod_po_urovnyam(TREE* root, short level)
{
	if(root)
	{
		vyvod_po_urovnyam(root->left_guy,level+1);


		for(short i=0; i<level; i++)
		{
			cout<<setw(3)<<"";
		}
		cout<<setw(3)<<root->id<<endl;

		vyvod_po_urovnyam(root->right_guy, level+1);
	}
}


template <class T>
void CTree<T>::print(ostream& f)
{
	if(root)
	{
		f<<"\n\nYour tree:\n";
		short level=0;

		vyvod_po_urovnyam(root->left_guy,level+1);

		for(short i=0; i<level; i++)
		{
			f<<setw(3)<<"";
		}
		f<<setw(3)<<root->id<<endl;

		vyvod_po_urovnyam(root->right_guy, level+1);
		f<<"\n";
	}
}

template<class T>
void CTree<T>::delete_leaves()
{
	delete_leaves_h(root);
}

template <class T>
void CTree<T>::delete_leaves_h(TREE* root)
{
	TREE* pv=root;
	if(root->left_guy)
	{
		pv=root->left_guy;
		if((pv->left_guy)||(pv->right_guy))
		{
			delete_leaves_h(pv);
		}
		else
		{
			delete_leave(root, root->left_guy);
		}
	}
	if(root->right_guy)
	{
		pv=root->right_guy;
		if((pv->left_guy)||(pv->right_guy))
		{
			delete_leaves_h(pv);
		}
		else
		{
			delete_leave(root, root->right_guy);
		}
	}
}

template <class T>
void CTree<T>::delete_leave(TREE* branch, TREE* leave)
{
	if(branch->left_guy==leave)
	{
		delete leave;
		branch->left_guy=NULL;
	}
	else if(branch->right_guy==leave)
	{
		delete leave;
		branch->right_guy=NULL;
	}

}

template<class T>
void CTree<T>::enter(short num, istream& f)
{
	cout<<"\n\nEnter your tree:\n";
	for(short k=0;k<num;k++)
	{
		T now=0;
		f>>now;
		insert_element(now);
	}
}

#endif /* CTREE_H_ */
