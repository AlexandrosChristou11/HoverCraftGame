// Alexandros Christou
// Implementation of CObstacle Class
// 17 April 2020

#include "CObstacle.h"
#include <TL-Engine.h>
using namespace tle;



CObstacle::CObstacle(IMesh* mOb, float x, float y, float z)
{
	Initialise(mOb, x, y, z);
}
void CObstacle::Initialise(IMesh* mOb, float x, float y, float z) {

	m_model = mOb->CreateModel(x, y, z);
	m_radius = 5.5f;

}

