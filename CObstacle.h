// Alexandros Christou	
// Declaration of CObstace class
// 17 April 2020

#pragma once
#include <TL-Engine.h>
#include "CVector3.h"
using namespace tle;

class CObstacle
{
public:
	// 1) Member Methods
	CObstacle() {};
	CObstacle(IMesh* mOb, float x, float y, float z);
	void Initialise(IMesh* mOb, float x, float y, float z);

	// Getters, Setters ..
	IModel* GetModel() { return m_model; }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	float GetRadius() { return m_radius; }
	CVector3 GetPosition() { return CVector3(m_model->GetX(), m_model->GetY(), m_model->GetZ()); }


private:
	// 2) Member Variables
	IModel* m_model;			// Model of Obstacel
	float m_radius;				// Obs. radius

};

