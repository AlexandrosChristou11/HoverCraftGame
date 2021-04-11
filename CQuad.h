// Declaration of CQuad class (particle system)
// Alexandros Christou
// 30 April 2020

#include <TL-Engine.h>

using namespace tle;

#define UP 0
#define DOWN 1

#pragma once
class CQuad
{
public:
	// 1) Member Methods
	CQuad() {};
	CQuad(IMesh* mQ, float x, float y, float z);
	void Initialise(IMesh* mQ, float x, float y, float z);
	void Update(float dt, IModel* c);

	// Getters, Setters ..
	IModel* GetModel() { return m_model; }

private:
	void States(float dt, IModel* c);
	void ModelMoveDown(float dt);
	void ModelMoveUp(float dt);

private:
	// 2) Member variables
	IModel* m_model;
	int m_state;
	float m_v;
	float m_ds;
	float m_NewVelocity;
};

