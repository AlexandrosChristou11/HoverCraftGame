// Alexandros Christou
// Declaration of CWalkway class
// 18 April 2020

#include <TL-Engine.h>
#pragma once
using namespace tle;
class CWalway
{
public:
	// 1) Member Methods
	CWalway() {};
	CWalway(IMesh* mWalk, float x, float y, float z);
	void Initialise(IMesh* mWalk, float x, float y, float z);
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	float GetRadius() { return m_radius; }
	IModel* GetModel() { return m_model; }

private:
	// 2) Member Variables
	IModel* m_model;				// Lamps model
	float m_radius;					// radius ..
};

