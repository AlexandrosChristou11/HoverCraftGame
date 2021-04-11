// Alexandros Christou
// Implementation of Class CCross
// 27 April 2020


#include "CCross.h"
#include <TL-Engine.h>
#include <iostream>

using namespace tle;

CCross::CCross(IMesh* mCross , float x, float y, float z)
{
	Initialiase(mCross, x, y, z);
}

void CCross::Initialiase(IMesh* mCross, float x, float y, float z) {

	m_timer = 0.15f;
	m_tLimit = 0.05f;
	m_model = mCross->CreateModel(x ,y, z);
	m_model->Scale(0.4f);
}

void CCross::AppearCross(float dt) {
	
	// a) Appear Cross
	m_model->SetY(APPEAR);

		m_timer += dt;
		// b) Time is over -> disappear cross 
		if (m_timer > m_tLimit) {
			m_model->SetY(DISAPPEAR);
		}
	
}
