// Alexandros Christou
// Implementation of CFonts class
// 14 April 2020

#include "CFonts.h"
#include <TL-Engine.h>
using namespace tle;


CFonts::CFonts(I3DEngine* e)
{
	Update(e);
}

void CFonts::Update(I3DEngine* e) {

	m_f = e->LoadFont("Monotype Corsiva", 40);
	m_f->Draw("Hello ", 0,100);

}

