// Alexandros Christou
// Implementation of class CIsle
// 12 April 2020

#include "CIsle.h"
#include <TL-Engine.h>
using namespace tle;

CIsle::CIsle(IMesh* mIsle, float x, float y, float z)
{
	Initialise(mIsle, x, y, z);
}

void CIsle::Initialise(IMesh* mIsle, float x, float y, float z) {
	m_model = mIsle->CreateModel(x, y, z);
	
	m_radius = 1.0f;

 }


