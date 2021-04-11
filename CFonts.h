// Alexandros Christou
// Declaration of class CFonts
// 14 April 2020

#include <TL-Engine.h>
using namespace tle;

#pragma once
class CFonts
{
public:
	// 1) Member Methods
	CFonts() {};
	CFonts(I3DEngine* e);
	void Update(I3DEngine* e);


	

private:
	// 2) Member Methods
	IFont* m_f;						// Font
};

