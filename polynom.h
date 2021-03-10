#pragma once
#include "monom.h"
#include <list>
#include <cmath>
#include "List.h"

struct Node
{
	Monom mon;
	Node* next;
	Node(Monom _mon=NULL , Node* _next = NULL) : mon(_mon), next(_next) {}
};
class Polynom
{
	Node* head;
public:
	Polynom();

	Polynom operator +(Polynom& p);
	Polynom operator -(Polynom& p1);
	Polynom operator *(Polynom& p1);
	double calculation( double x, double y, double z);

	void getDegr(int state, string _s, double& c, int& x, int& y, int& z);
	void input(string s);
	bool isEmpty() { return head->next==head; }
	void push(Polynom& p, Monom& m);
	void push_back(Monom& p);
	/*IteratorList getIterator() {
		return IteratorList(head);
	}*/
	Node& getLast()
	{
		if(isEmpty())
			throw "List is empty";
		Node* tmp = head;
		while (tmp->next != head)
			tmp = tmp->next;
		return *tmp;
	}

	
	friend std::ostream& operator<< (std::ostream& o, const Polynom& list)
	{
		
		Node* p = list.head->next;
		if (p == list.head)
			o << "List is empty" << std:: endl;
		while (p != list.head)
		{
			cout << p->mon << " "; 
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
    head= new Node(m);
	head->next = head;
	
}


inline Polynom Polynom::operator+( Polynom & p1)
{
	Polynom res;
	Node* _p1 = p1.head->next;
	Node* _p2 = head->next;
	if (this->isEmpty()||p1.isEmpty())
		throw "Input polynom is empty";
	while (_p1!= p1.head && _p2!= head)
	{
	    if (_p1->mon.areSiml(_p2->mon))
		{
			
			Monom newM(_p1->mon);
			newM.setCoeff(_p1->mon.getCoeff() + _p2->mon.getCoeff());
			res.push_back(newM);
			_p1 = _p1->next;
			_p2 = _p2->next;
		}
		else
		{
			Monom _newM(_p1->mon.getMaxMon(_p2->mon));
			res.push_back(_newM);
			if (_newM == _p1->mon)
				_p1 = _p1->next;
			else
				_p2 = _p2->next;
		}
	}
	while (_p2 != head)
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

inline Polynom Polynom::operator-( Polynom& p1)
{
	Polynom res;
	Node* _p1 = p1.head->next;
	Node* _p2 = head->next;
	if (this->isEmpty() || p1.isEmpty())
		throw "Input polynom is empty";
	while (_p1 != p1.head && _p2 != head)
	{
		 if (_p1->mon.areSiml(_p2->mon))
		{

			Monom newM(_p1->mon);
			newM.setCoeff(_p1->mon.getCoeff() - _p2->mon.getCoeff());
			res.push_back(newM);
			_p1 = _p1->next;
			_p2 = _p2->next;
		}
		else
		{
			Monom _newM(_p1->mon.getMaxMon(_p2->mon));
			res.push_back(_newM);
			if (_newM == _p1->mon)
				_p1 = _p1->next;
			else
				_p2 = _p2->next;
		}
	}
	while (_p2 != head)
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

inline Polynom Polynom::operator*(Polynom& p1)
{
	Polynom res;
	Node* _p1 = p1.head->next;
	Node* _p2 = head->next;
	if (this->isEmpty() || p1.isEmpty())
		throw "Input polynom is empty";
	while (_p1 != p1.head )
	{
		_p2 = head->next;
		while (_p2 != head)
		{
			Monom m;
			m.coeff = _p1->mon.getCoeff() * _p2->mon.getCoeff();
			m.degr_con = _p1->mon.degr_con + _p2->mon.degr_con;
			res.push(res, m);
			_p2 = _p2->next;
		}
		_p1 = _p1->next;
	}
	
	return res;
}

inline double Polynom::calculation(double x, double y, double z)
{

	Node* tmp = this->head->next;
	double res = 0;
	while (tmp != head)
	{	
		res += tmp->mon.calk(x, y, z);
		tmp = tmp->next;
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


inline void Polynom::getDegr(int state, string _s, double& c,int& x, int& y, int& z)
{
	if (state == 0 && _s.length() > 0 ) c = atof(_s.c_str());
	if (state == 1 && _s.length() > 0) x = atof(_s.c_str());
	if (state == 2 && _s.length() > 0) y = atof(_s.c_str());
	if (state == 3 && _s.length() > 0) z = atof(_s.c_str());

}

inline void Polynom::input(string s)
{
	string _s = "";
	list < string > str_list;
	for (int i = 0;i < s.length();i++)
	{
		_s = "";
		while (i < s.length() && s[i] != '+' && s[i] != '-')
		{
			_s += s[i];
			i++;
		}
		str_list.push_back(_s);
	}
	list<string> ::iterator itr;
	for (itr = str_list.begin(); itr != str_list.end();itr++) {
		string m_str = *itr;
		int state = 0;
		double c = 1;
		int x = 0, y = 0, z = 0;
		_s = "";
		for (int i = 0;i < m_str.length();i++)
		{
			if (m_str[i] == 'x')
			{
				getDegr(state, _s, c, x, y, z);
				state = 1;
				_s = "";
			}
			else if (m_str[i] == 'y')
			{
				getDegr(state, _s, c, x, y, z);
				state = 2;
				_s = "";
			}
			else if (m_str[i] == 'z')
			{
				getDegr(state, _s, c, x, y, z);
				state = 3;
				_s = "";
			}
			else _s += m_str[i];
		}		
		getDegr(state, _s, c, x, y, z);
		Monom m(c, x, y, z);

		this->push(*this,m);
	}

}




inline void Polynom::push(Polynom& p, Monom& m)
{
	int count = 0;
	if (p.isEmpty()) {
		p.push_back(m);
		return;
	}
		Node* t = p.head->next;
		while (t != p.head) 
		{
			if (m.areSiml(t->mon)) 
			{
				t->mon.setCoeff(m.getCoeff() + t->mon.getCoeff());
				return;
			}
			if (m.getConv() > t->mon.getConv())
			{
				Node* newN = new Node(t->mon,t->next);
				t->mon=m;
				t->next = newN;
				return;
			}
		     t = t->next;
		}
		p.push_back(m);

}

inline void Polynom::push_back(Monom& p)
{

	if (isEmpty()) {
		Node* tmp = new Node(p, head);
		head->next = tmp;
		return;
	}

	Node* new_node = new Node(p, head);
	Node* mon = head;
	while (mon->next != head)
	{
		mon = mon->next;
	}
	mon->next = new_node;
}




