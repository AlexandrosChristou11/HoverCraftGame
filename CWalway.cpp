// Alexandros Christou
// Implementation of Class Cwalkway
// 18 April 2020

#include "CWalway.h"
#include <TL-Engine.h>
using namespace tle;


CWalway::CWalway(IMesh* mWalk, float x, float y, float z)
{
	Initialise(mWalk, x, y, z);
}

void CWalway::Initialise(IMesh* mWalk, float x, float y, float z) {
	m_model = mWalk->CreateModel(x, y, z);
	

}