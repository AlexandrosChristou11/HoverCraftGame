// Alexandros Christou
// Declaration of Class CSprite
// 14 April 2020

#pragma once
#include <TL-Engine.h>
using namespace tle;

class CSprite
{
public:
	// 1) Member Methods ..
	CSprite() {} ;
	CSprite (I3DEngine* e, float x, float y);
	void Initialise(I3DEngine* e, float x, float y);
	ISprite* GetBackDrop() { return m_s; }

private: 
	// 2) Member Variables ..
	ISprite * m_s;							// backdrop ..

};

