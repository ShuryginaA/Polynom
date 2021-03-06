#pragma once
#include "monom.h"

struct Node
{
	Monom mon;
	Node* next;
	Node(Monom _mon=NULL , Node* _next = NULL) : mon(_mon), next(_next) {}
};
class Polynom
{
	Node* head;
	Node* first;
public:
	Polynom();
	Polynom(const Monom& mon) {  }
	~Polynom();

	Polynom& sum ( Polynom& p1);
	Polynom& sub(const Polynom& p1, const Polynom& p2);
	Polynom& mult(const Polynom& p1, const Polynom& p2);
	Polynom& calculation(const Polynom& p1, const Polynom& p2);
	
	bool isEmpty() { return !first; }
	int getSize();
	void push_back(Monom& p);
	/*IteratorList getIterator() {
		return IteratorList(first);
	}*/
	
	friend std::ostream& operator<< (std::ostream& o, const Polynom& list)
	{
		
		Node* p = list.first;
		if (!p)
			o << "List is empty" << std:: endl;
		while (p!=list.head)
		{
			if(p->mon.getCoeff()>0)
			     o << "+"<<p->mon<<" ";
			else 
				o << p->mon<<" ";
			p = p->next;
		}
		o << std::endl;
		return o;
	}
	
};

//class IteratorList {
//	Node* it;
//public:
//	IteratorList(Node* _it) :it(_it) {}
//
//	bool hasNext() {
//		return it != NULL;
//	}
//
//	Monom& next() {
//		if (!hasNext())throw - 1;
//		 Monom& m = it->mon;
//		it = it->next;
//		return m;
//	}
//
//};


inline Polynom::Polynom()
{
	Monom m; 
	m.makeHead();
    head= new Node(m, first);
	first=NULL;
}

inline Polynom::~Polynom()
{
	/*while (first)
	{
		Node* tmp = first->next;
		delete first;
		first = tmp;
	}*/
}

inline Polynom& Polynom::sum(Polynom& p1)
{
	Polynom res;
	Node* _p1 = p1.first;
	Node* _p2 = first;
	int x1, y1, z1, x2, y2, z2;
	//emptyness
	while (_p1!=p1.head &&_p2!=head)
	{
		if (_p1->mon.areSiml(_p2->mon))
		{
			Monom newM(_p1->mon);
			newM.setCoeff(_p1->mon.getCoeff() + _p2->mon.getCoeff());
			res.push_back(newM);
			_p1 = _p1->next;
			_p2= _p2->next;
		}
		else
		{
			Monom _newM(_p1->mon.getMaxMon(_p2->mon));
			res.push_back(_newM);
			if(_newM ==_p1->mon)
				_p1 = _p1->next;
			else 
				_p2 = _p2->next;
		}
	}
	while (_p2!=head)
	{
		res.push_back(_p2->mon);
		_p2 = _p2->next;		
	}
	while (_p1 != p1.head)
	{
		res.push_back(_p1->mon);
		_p1 = _p1->next;
	}
	return res;
}


//inline List<T>& List<T>::operator=(const List<T>& list)
//{
//	Node* p = list.first;
//	Node* p1 = NULL;
//	Node* tmp = NULL;
//	while (p)
//	{
//		tmp = new Node(p->data);
//		if (!first)
//		{
//			first = tmp;
//			p1 = tmp;
//		}
//		else
//		{
//			p1->next = tmp;
//			p1 = p1->next;
//		}
//		p = p->next;
//	}
//	return *this;
//
//}


inline void Polynom::push_back(Monom& p)
{
	
		if (isEmpty()) {
			Node* tmp = new Node(p, head);
			first = tmp;
			return;
		}
		Node* new_node = new Node(p);
		Node* mon = first;
		int i = 0;
		while (mon->next != head)
		{
			mon = mon->next;
		}
		mon->next = new_node;
		new_node->next = head;
}




