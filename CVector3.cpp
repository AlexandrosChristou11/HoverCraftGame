// Alexandros Christou
// Implementation of CVECTOR 3 class..
// 13 April 2020

#include "CVector3.h"



CVector3::CVector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

CVector3 CVector3:: operator-(CVector3 a) {

	CVector3 c;
	c.SetX(m_x - a.GetX());
	c.SetY(m_y - a.GetY());
	c.SetZ(m_z - a.GetZ());

	return c;
}
CVector3 CVector3::operator*(float a)
{
	// c =  b * a 
	// where a is a scalar, b is a vector.
	return CVector3(a*this->m_x, a*this->m_y, a*this->m_z);
}


CVector3 CVector3::operator/(float a)
{
	// c = b / a 
	// where a is a scalar, b is a vector.
	return CVector3(this->m_x / a, this->m_y / a, this->m_z / a);
}
