// Alexandros Christou
// Declaration of CDummy class
// 16 April 2020

#include <TL-Engine.h>
#include "CVector3.h"
using namespace tle;

#pragma once

class CDummy
{
public:
	// 1) Member Methods
	CDummy() { };
	CDummy(IMesh* mDummy, float x, float y, float z);
	void Initialise(IMesh* mDummy, float x, float y, float z);


	// Getters
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	IModel* GetModel() { return m_model; }
	CVector3 GetPosition() { return CVector3(m_model->GetX(), m_model->GetY(), m_model->GetZ()); }
	float GetRadius() { return m_radius; }

private:
	// 2) Member variables
	IModel* m_model;					// Dummy model
	float m_radius;						// radius for colission w/ opponent car
};

