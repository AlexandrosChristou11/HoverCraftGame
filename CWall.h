// Alexandros Christou
// Declaration of CWall class
// 13 April 2020

#include <TL-Engine.h>
#include "CVector3.h"

using namespace tle;

#pragma once
class CWall
{
public:
	// 1) Member Methods
	CWall() { };
	CWall (IMesh* mWall, float x, float y, float z);
	void Initialise(IMesh* mWall, float x, float y, float z);

	// Getters / Setters :
	CVector3 GetPosition() { return CVector3(m_model->GetX(), m_model->GetY(), m_model->GetZ()); }
	float GetLen() { return m_len; }
	float GetWid() { return m_wid; }
	float GetHeight() { return m_hei; }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	IModel* GetModel() { return m_model; }

private: 
	// 2) Member Variables
	IModel *m_model;			// Wall  models
	float m_len;				// length of wall
	float m_wid;				// width of wall
	float m_hei;				// height of wall
};

