// Alexandros Christou
// Declaration of CCross class
// 27 April 2020

#include <TL-Engine.h>
#include "CVector3.h"
#pragma once

#define APPEAR 5
#define DISAPPEAR -20

using namespace tle;

class CCross
{
public:
	// 1) Member Methods
	CCross() {};
	CCross(IMesh* mCross, float x, float y, float z);
	void Initialiase(IMesh* mCross, float x, float y, float z);
	
	//Getters, setters ..
	IModel* GetModel() { return m_model; }
	void SetTimer(float t) { m_timer = t; }
	void SetY(float y) { m_model->SetY(y); }
	void SetLimit(float l) { m_timer += l; }
	
	void AppearCross(float dt);


private:
	// 2) Member Variables
	IModel* m_model;				// cross model
	float m_tLimit;					// timing limit to appear cross
	float m_timer;					// timer 
	int m_state;					// state in which cp shall appear
};

