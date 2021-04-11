// Alexandros Christou
// Declaration of CVector3 class
// 13 April 2020


#include <math.h>
//using namespace tle;

#pragma once
class CVector3
{
public:
	// 1) Member Methods
	CVector3() { };
	CVector3(float x, float y, float z);
	float Length() { return sqrt(m_x*m_x + m_y*m_y + m_z*m_z); }
	

	// Operators:
	CVector3 operator-(CVector3 a);
	CVector3 operator*(float a);
	CVector3 operator/(float a);


	// Getters:
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetZ() { return m_z; }

	// Setters:
	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetZ(float z) { m_z = z; }
	

private:
	// 2) Member variables
	float m_x, m_y, m_z; 

};

