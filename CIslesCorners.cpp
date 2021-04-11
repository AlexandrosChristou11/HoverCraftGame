// Alexandros Christou
// Implementation of CIsleCorners class
// 17 April 2020

#include "CIslesCorners.h"
#include <TL-Engine.h>
using namespace tle;



CIslesCorners::CIslesCorners(IMesh* mtank, float x, float y, float z)
{
	Initialise(mtank, x, y, z);
}
void CIslesCorners::Initialise(IMesh* mtank, float x, float y, float z) {
	m_model = mtank->CreateModel(x, y, z);
	m_radius = 3.0;   


}


