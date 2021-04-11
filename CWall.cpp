// Alexandros Christou
// Impementation of CWall class
// 13 April 2020

#include "CWall.h"
#include <TL-Engine.h>

using namespace tle;


CWall::CWall(IMesh* mWall,  float x, float y, float z)
{
	Initialise(mWall, x, y, z);
}

void CWall::Initialise(IMesh* mWall,float x, float y, float z) {
	m_model = mWall->CreateModel(x, y, z);
	
	m_len = 4.0f;
	m_wid = 0.05f;
	m_hei = 4.0f;
	//m_radius = -2.0f;
}

