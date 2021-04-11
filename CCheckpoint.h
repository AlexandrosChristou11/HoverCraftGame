// Alexandros Christou
// Declaration of CCheckpoint class
// 13 April 2020

#include <TL-Engine.h>
#include "CVector3.h"
using namespace tle;

#pragma once
class CCheckpoint
{
public:
	// 1) Member Methods
	CCheckpoint() { };
	CCheckpoint(IMesh* mCheckpoint, float x, float y, float z);
	void Initialise(IMesh* mCheckpoint, float x, float y, float z);
		
	// Getters, Setters ..
	CVector3 GetPosition() { return CVector3 (m_model->GetX(), m_model->GetY(), m_model->GetZ()); }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	float GetRadius() { return m_radius; }
	IModel* GetModel() { return m_model; }
	void SetTimer(float t) { m_time = t; }
	float GetTlimit() { return m_Tlimit; }
	void SetTlimit(float t) { m_Tlimit = t; }

	

private:
	// 2) Member Variables
	IModel* m_model;				// Walls' model
	float m_radius;					// radius ..
	IFont* m_font;					// Print message that user pass succesful a CP
	float m_time;					// time of showing that user pass from CP
	float m_Tlimit;
	IModel* m_cross;				// cross model when car pass from one CP
	
};

