// Alexandros Christou
// Impementation of CCheckpoint Class
// 13 April 2020

#include "CCheckpoint.h"
#include <TL-Engine.h>
using namespace tle;


CCheckpoint::CCheckpoint(IMesh* mCheckpoint, float x, float y, float z)
{
	Initialise(mCheckpoint, x, y, z);
}

void CCheckpoint::Initialise(IMesh* mCheckpoint, float x, float y, float z) {
	m_model = mCheckpoint->CreateModel(x, y, z);
	m_radius = 15.0f;
}


