// Alexandros Christou
// Implentation of class CArena
// 13 April 2020

#include "CArena.h"
#include <TL-Engine.h>

using namespace tle;


CArena:: CArena(IMesh* mSkybox, float x, float y, float z)
{
	Initialise(mSkybox, x, y, z);
}

void CArena::Initialise(IMesh* mSkybox, float x, float y, float z) {
	m_model = mSkybox->CreateModel(x, y, z);

}



