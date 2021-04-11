// Implementation of CQuad Class
// Alexandros Christou
// 30 April 2020

#include "CQuad.h"
#include <TL-Engine.h>

using namespace tle;



CQuad::CQuad(IMesh* mQ, float x, float y, float z)
{

	Initialise(mQ, x, y, z);
}

void CQuad::Initialise(IMesh* mQ, float x, float y, float z) {
	m_v = 110.0f;
	m_model = mQ->CreateModel(x, y, z);
	m_model->Scale(0.1f);
	m_state = DOWN;

	
}

void CQuad::Update(float dt, IModel* c) {

	// States of quads - movement!!
	States(dt, c);

}
void CQuad::States(float dt, IModel* c) {
	float limitMax = 2.0f;
	float limitMin = 1.5;

	switch (m_state)
	{
	case DOWN:
		ModelMoveDown(dt);
		if (m_model->GetY() <= limitMax)
			m_state = UP;
		break;
	case UP:
		ModelMoveUp(dt);
		if (m_model->GetY() >= c->GetLocalY()-limitMin)
			m_state = DOWN;

	}

}

void CQuad::ModelMoveDown(float dt) {
	m_ds = dt * m_v;

	m_model->MoveLocalY(-m_ds);

}

void CQuad::ModelMoveUp(float dt) {
	float accelerate = 50.0f;
	m_NewVelocity = m_ds + accelerate * dt;

	m_model->MoveLocalY(m_NewVelocity);

}