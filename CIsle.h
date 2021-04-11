// Alexandros Christou
// Declaration of Class CIsle
// 12 April 2020

#include <TL-Engine.h>
#include "CVector3.h"
using namespace tle;
#pragma once
class CIsle
{
public:
	// 1) Member methods
	CIsle() {};
	CIsle(IMesh* mIsle, float x, float y, float z);
	void Initialise(IMesh* mIsle, float x, float y, float z);
		
	// Getters ..
	CVector3 GetPosition() { return CVector3(m_model->GetX(), m_model->GetY(), m_model->GetZ()); }
	float GetRadius() { return m_radius; }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	IModel* GetModel() { return m_model; }

private:
	// 2) Member variables
	IModel*  m_model;			// isle model
	float m_radius;				// radius of wall-isle (vareli)
};

