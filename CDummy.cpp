// Alexandros Christou
// Implementation of Class CDummy
// 16 April 2020

#include "CDummy.h"
#include <TL-Engine.h>
using namespace tle;


CDummy::CDummy(IMesh* mDummy, float x, float y, float z)
{
	Initialise(mDummy, x, y, z);
}


void CDummy::Initialise(IMesh* mDummy, float x, float y, float z) {
	m_model = mDummy->CreateModel(x, y, z);
	m_radius = 1.0f;

}


