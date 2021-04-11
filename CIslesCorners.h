// Alexandros Christou	
// Declaration of CIsleCorners class (obstacles)
// 17 April 2020

#include <TL-Engine.h>
using namespace tle;

#pragma once
class CIslesCorners
{
public:
	// 1) Member Methods
	CIslesCorners() {};
	CIslesCorners(IMesh* mtank, float x, float y, float z);
	void Initialise(IMesh* mtank, float x, float y, float z);

	// Getters, Setters ..
	IModel* GetModel() { return m_model; }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	float GetRadius() { return m_radius; }


private:
	// 2) Member Variables
	IModel* m_model;					// Model watertanks
	float m_radius;						// Radius of model

};

