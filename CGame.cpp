// Alexandros Christou
// Impementation of Class CGame
// 15 April 2020

#include "CGame.h"
#include "CCar.h"
#include <iostream>

#define INTRO_HIT_SPACE 0
#define COUNTDOWN 1
#define PLAY 2
#define END_OF_GAME 3

#define S_FONT_ONE 1
#define S_FONT_TWO 2
#define S_FONT_THREE 3
#define S_FONT_GO 4
#define S_FONT_START 5

#define H_PASS1 1
#define H_PASS2 2
#define H_PASS3 3
#define H_PASS4 4
#define H_PASS5 5
#define H_PASS6 6

using namespace tle;




CGame::CGame(I3DEngine* e)
{

	m_state = INTRO_HIT_SPACE;
	m_font = e->LoadFont("Adobe Garamond Pro", 120);
	m_bFont = e->LoadFont("Adobe Garamond Pro", 122);
	m_fBackDrop = e->LoadFont("Charlemagne std", 30);
	m_fSpeed = e->LoadFont("Charlemagne std", 210);
	//Update(e, dt);
	m_tRest = 0.0f;
	m_sFont = S_FONT_ONE;
	m_bCheck = false;
	m_hPass = H_PASS1;
	m_e = e;
	m_xText = 100;
	m_yText = 640;

	
}

void CGame::Update( float dt, float cSpeed, float cSpeedB) {

	// 1) Game Controls  ( press esc etc .. )
	Controls();

	// 2) Phases of game ( pass from Cpoints .. )
	StatesOfGame(dt);
	
	// 3) Print State Backdrop
	PrintState();
	
	// Print Speed
	PrintSpeed(cSpeed, cSpeedB);

}
void CGame:: PrintSpeed(float cSpeed, float cSpeedB) {
	string str = std::to_string(std::int16_t( cSpeed*50));
	string str2 = std::to_string(std::int16_t(cSpeedB * 50));
	
	m_fBackDrop->Draw("SPEED", 460, 640);
	if (m_e->KeyHeld(Key_W) || !m_e->KeyHeld(Key_W))
	m_fBackDrop->Draw(str, 495, 660, kDarkGrey);

}

void CGame::ShowLeaderBoard(int cPosition, string cName, float time ,float x, float y) {
	string sPos = std::to_string(cPosition);
	string sTime = std::to_string(time);

	
	m_font->Draw(sPos + "." + cName, x, y);
	m_bFont->Draw(sPos + "." + cName, x, y,kWhite);
}

void CGame::CarWonWait() {
	int x1 = 350;
	int y1 = 350;
	int x2 = 50;
	int y2 = 500;
	m_font->Draw("- WON -", x1, y1);
	m_bFont->Draw("- WON -", x1, y1, kWhite);


	m_font->Draw("Wait Opponents to finish ..", x2, y2);
	m_bFont->Draw("Wait Opponents to finish ..", x2, y2, kWhite);
}


void CGame::PrintState() {

	switch (m_state)
	{
	case INTRO_HIT_SPACE:
		m_fBackDrop->Draw("DEMO", m_xText , m_yText);
		break;
	case COUNTDOWN:
		m_fBackDrop->Draw("READY", m_xText, m_yText);
		break;
	case PLAY:
		m_fBackDrop->Draw("PLAY", m_xText, m_yText);
		break;
	case END_OF_GAME:
		m_fBackDrop->Draw("FINISHED", m_xText, m_yText);
		break;
	
	}
	

	

}
void CGame::RestartFont() {
	int x = 50;
	int y = 350;

	m_font->Draw("- Press R to Restart -", x, y);
	m_bFont->Draw("- Press R to Restart -", x, y, kWhite);
}

void CGame::StatesOfGame(float dt) {


	switch (m_state)
	{
	case INTRO_HIT_SPACE:
		// (a) Print Message on screen ..
		StartFont();
		// (b) Change state ..
		if (m_e->KeyHit(Key_Space))
			m_state = COUNTDOWN;
			
		break;
	case COUNTDOWN:
		CountDownMessages(dt);
		break;
	case PLAY:
		
		break;
	case END_OF_GAME:
		RestartFont();
		RestartGame();
		break;
	}
}

void CGame::RestartGame() {
	float restart = 0.0f;
	if (m_e->KeyHit(Key_R)) {
		m_state = INTRO_HIT_SPACE;
		m_tRest = restart;
		//SetState(m_state = INTRO_HIT_SPACE);
	}

}

void CGame::Controls() {
	
	// Escape
	if (m_e->KeyHit(Key_Escape)) {
		m_e->Stop();
	}

}

void CGame::StartFont() {
	int x = 300;
	int y = 100;
	
	m_font->Draw("- Press Start -", x, y, kBlack);
	m_bFont->Draw("- Press Start -", x, y, kWhite);

}

void CGame::CountDownMessages(float dt) {
	int x = 400;
	int y = 100;
	float sec1 = 1;
	float sec2 = 2;
	float sec3 = 3;
	float sec4 = 4;
	m_tRest += dt;
	
	switch (m_sFont) {
	case S_FONT_ONE:
		m_font->Draw("- 3 -", x, y, kBlack);
		m_bFont->Draw("- 3 -", x, y, kWhite);
		if (m_tRest > sec1 ) {
			m_sFont = S_FONT_TWO;
			
		}
		break;
	case S_FONT_TWO:
		
		m_font->Draw("- 2 -", x, y, kBlack);
		m_bFont->Draw("- 2 -", x, y, kWhite);
		if (m_tRest > sec2) {
			m_sFont = S_FONT_THREE;
		}
		break;
	case  S_FONT_THREE:
		m_font->Draw("- 1 -", x, y, kBlack);
		m_bFont->Draw("- 1 -", x, y, kWhite);
		if (m_tRest > sec3) {
			m_sFont = S_FONT_GO;
		}
		break;
	case  S_FONT_GO:
		m_font->Draw("- GO !! -", x, y, kBlack);
		m_bFont->Draw("- GO !! -", x, y, kWhite);
		if (m_tRest > sec4) {
			m_sFont = S_FONT_START;
		}
		break;
	case S_FONT_START:
		m_state = PLAY;
	}
}