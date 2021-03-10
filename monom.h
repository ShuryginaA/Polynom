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
	double coeff;
	int degr_con;
public:
	Monom(double _coef=1 , int x_deg=0 , int y_deg=0,int z_deg=0)
	{
		coeff = _coef;
		degr_con = x_deg * RADIX* RADIX + y_deg * RADIX + z_deg;
	}
	void makeHead() { coeff = 0;degr_con = -1; }
	Monom& operator=(const Monom& m) { coeff = m.coeff; degr_con = m.degr_con; return *this; }
	int operator==(const Monom& m) { return (coeff == m.coeff) && (degr_con == m.degr_con); }
	void setCoeff(double c) { coeff = c; }
	double getCoeff() { return coeff; }
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
	int getConv() { return degr_con; }
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

	double calk(double x, double y,double z) 
	{
		double res_x=1,res_y=1,res_z=1;
		int _x, _y, _z;
		double c = this->coeff;
		this->getDeg(_x, _y, _z);
		if (x == 0) {
			if (_x != 0)
				res_x = 0;
		}
		else res_x = exp(_x * log(x));
		
		if (y == 0) {
			if (_y != 0)
				res_y = 0;
		}
		else res_y = exp(_y * log(x));

		
		if (z == 0) {
			if (_z != 0)
				res_z = 0;
		}
		else res_z = exp(_z * log(x));
		
		return c * res_x * res_y * res_z;

	}
	bool areSiml(Monom& m){ return degr_con == m.degr_con; }
	friend std::ostream& operator<< (std::ostream& o, const Monom& m)
	{
		if (m.coeff == 0)
			return o;
		if(m.coeff>0)
		o << "+"<<m.coeff;
		else 
			o << m.coeff;
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

