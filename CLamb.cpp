// Alexandros Christou
// Implementation of CLamb Class
// 18 April  2030

#include "CLamb.h"
#include <TL-Engine.h>
using namespace tle;


CLamb::CLamb(IMesh* mLamp, float x, float y, float z)
{
	Initialise(mLamp, x, y, z);
}

void CLamb::Initialise(IMesh* mLamp, float x, float y, float z) {
	m_model = mLamp->CreateModel(x, y, z);
	m_radius = 2.5f;
}

