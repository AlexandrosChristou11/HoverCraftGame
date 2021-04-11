// Alexandros Christou
// Declaration of Class CGame
// 14 April 2020

#include <TL-Engine.h>
using namespace tle;

#pragma once
class CGame
{
public:
	// 1) Member Methods
	CGame() {};
	CGame( I3DEngine* e);
	void Update(float dt, float cSpeed, float cSpeedB);

	// Getters , Setters ..
	void SetState(int s) { m_state = s; }
	int GetState() { return m_state; }
	void SetBcheck(bool b) { m_bCheck = b; }
	//bool GetBcheck() { return m_bCheck; }
	int GetHpass() { return m_hPass; }
	void SetHpass(int a) { m_hPass = a; }

	void CarWonWait();
	void ShowLeaderBoard(int cPosition, string cName, float time, float x, float y);

private:
	void StartFont();
	void CountDownMessages(float dt);
	void Controls();
	void StatesOfGame(float dt);
	void PrintState();
	void PrintSpeed(float cSpeed, float cSpeedB);
	void RestartGame();
	void RestartFont();

private:
	// 2) Member Variables
	int m_state;						// Game State .. 
	IFont* m_font;						// Fonts (text messages) ..
	IFont* m_fBackDrop;					// Text on backdrop ...
	float m_tRest;						// Time variable for execute messages (3,2,1 .. etc)
	int m_sFont;						// state of font
	bool m_bCheck;						// checks if the state has change
	int m_hPass;						// Hover has pass
	I3DEngine* m_e;						// engine
	float m_xText;						// Message on backdrop
	float m_yText;						// Message on backdrop
	IFont* m_fSpeed;					// speed in backdrop
	IFont* m_bFont;						// outliner font

};

