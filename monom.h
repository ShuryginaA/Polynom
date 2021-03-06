#pragma once
#ifndef __MONOM_H
#define  __MONOM_H 

#include<iostream>
#include <string>
using namespace std;

const int RADIX = 20;
class Monom
{
protected:
	int coeff;
	int degr_con;
public:
	Monom(int _coef=1 , int x_deg=0 , int y_deg=0,int z_deg=0) 
	{
		coeff = _coef;
		degr_con = x_deg * RADIX* RADIX + y_deg * RADIX + z_deg;
	}
	void makeHead() { coeff = 0;degr_con = -1; }
	Monom& operator=(const Monom& m) { coeff = m.coeff; degr_con = m.degr_con; return *this; }
	int operator==(const Monom& m) { return (coeff == m.coeff) && (degr_con == m.degr_con); }
	void setCoeff(int c) { coeff = c; }
	int getCoeff() { return coeff; }
	void getDeg(int& deg_x,int& deg_y, int& deg_z) 
	{ 
		int deg_tmp = degr_con;
		deg_x = deg_tmp / (RADIX * RADIX);
		deg_tmp -= deg_x * RADIX * RADIX;
		if(deg_tmp>0)
			deg_y = deg_tmp / RADIX;
		else { deg_y = 0;deg_z = 0; }
		deg_tmp -= deg_y * RADIX;
		deg_z = deg_tmp % RADIX;
	
	}
	void getDeg (int& deg_x, int& deg_y, int& deg_z) const
	{
		int deg_tmp = degr_con;
		deg_x = deg_tmp / (RADIX * RADIX);
		deg_tmp -= deg_x * RADIX * RADIX;
		if (deg_tmp > 0)
			deg_y = deg_tmp / RADIX;
		else { deg_y = 0;deg_z = 0; }
		deg_tmp -= deg_y * RADIX;
		deg_z = deg_tmp % RADIX;

	}
	int maxDeg()
	{
		int x, y, z;
		int max;
		this->getDeg(x, y, z);
		if (x > y)
			max = x;
		else max = y;
		if (z > max)
			max = z;
		return max;
	}
	Monom& getMaxMon(Monom& m1)
	{
		if (this->maxDeg() > m1.maxDeg())
			return *this;
		else if (this->maxDeg() < m1.maxDeg())
			return m1;
		else {
			int x, y, z;
			int x1, y1, z1;
			this->getDeg(x, y, z);
			m1.getDeg(x1, y1, z1);
			if (x > x1)
				return *this;
			if (x1 > x)
				return m1;
			if (y > y1)
				return *this;
			if (y1 > y)
				return m1;
			if (z > z1)
				return *this;
			if (z1 > z)
				return m1;
		}
	}
	bool areSiml(Monom& m){ return degr_con == m.degr_con; }
	friend std::ostream& operator<< (std::ostream& o, const Monom& m)
	{
		o << m.coeff<<"*";
		int x, y, z;
		m.getDeg(x,y,z);
		if (x > 0)
			o << "x" << "^" << x;
		if (y > 0)
			o << "y" << "^" << y;
		if (z > 0)
			o << "z" << "^" << z;
		return o;
	}
	friend class Polynom;
};
#endif

