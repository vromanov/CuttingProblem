#include <cassert>
#include <cmath>
#include <iostream>

#include "Segment.h"

Segment::Segment(const Vector2F &a, const Vector2F &b):
		_a(a), _b(b)
{
	return;
};
Segment::Segment(const Segment& s): _a(s._a), _b(s._b)
{
	return;
}
Segment::~Segment()
{
	return;
}

double Segment::length () const
{
	return sqrt((_a.X()-_b.X())*(_a.X()-_b.X()) + (_a.Y()-_b.Y())*(_a.Y()-_b.Y()));
}

const Vector2F& Segment::start() const
{
	return _a;
}
const Vector2F& Segment::end() const
{
	return _b;
}

double Segment::distance (const Vector2F& c) const
{
	double A = (_a.X()==_b.X()?0:1/(_b.X()-_a.X()));
	double B = (_b.Y()==_a.Y()?0:1/(_a.Y()-_b.Y()));
	double C = -_a.X()*A - _a.Y()*B;

	assert((A!=0)||(B!=0));

	if (B==0)
		return fabs(-C/A-c.Y());
	if (A==0)
		return fabs(-C/B-c.X());

	return fabs((A*c.X()+B*c.Y()+C)/sqrt(A*A+B*B));
}

bool Segment::inside(const Vector2F& c) const
{
	return Segment(start(),c).length()
		  +Segment(c,end()).length()<=length();
}

//bool Segment::inLine (const Vector2F& c) const
//{
//	return Triangle(start(), end(), c).quasiArea() == 0;
//}

Segment& Segment::operator=(const Segment& s)
{
	_a = s._a;
	_b = s._b;
	return *this;
}