// Alexandros Christou
// Impementation of Class CSprite
// 14 April 2020

#include "CSprite.h"
#include <TL-Engine.h>

using namespace tle;


CSprite::CSprite(I3DEngine* e, float x, float y)
{
	Initialise(e, x, y);
}

void CSprite::Initialise(I3DEngine* e, float x, float y) {

	m_s = e->CreateSprite("green1.jpg"); // ui_backdrop
	m_s->SetPosition(x, y);
	
}
// REFERENCE BACKDROP
// Google.com. 2020. Speed Line Anime Green - Google Search. [online] 
// Available at:
// <https://www.google.com/search?q=speed+line+anime++green&tbm=isch&ved=2ahUKEwjxwdOE7Y_pAhWP0YUKHUTRAnIQ2-cCegQIABAA&oq=speed+line+anime++green&gs_lcp=CgNpbWcQAzoECAAQHjoGCAAQCBAeUJfGAVjz1QFgn9cBaABwAHgAgAHmAYgBmgiSAQUwLjUuMZgBAKABAaoBC2d3cy13aXotaW1n&sclient=img&ei=X5yqXrGWMY-jlwTEoouQBw&bih=625&biw=1366&client=avast#imgrc=vAP80oWjV0qTOM&imgdii=lwCR7twTlgtN9M>
// [Accessed 30 April 2020].

