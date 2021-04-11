// Alexandros Christou 
// Declaration of Class CCameraU
// 16 April 2020

#include <TL-Engine.h>
#include "CCar.h"
#include "CDummy.h"
#define C_FREE_MOVE 0
#define C_CHASE 1
#define C_FPERSON 2
#define C_SPY 3

#pragma once
using namespace tle;


class CCameraU
{
public:
	// 1) Member Methods
	CCameraU() {};
	CCameraU(I3DEngine* e);
	void Initialise(I3DEngine* e);
	void Update(float dt, IModel* c, IModel* d, IModel* dF);
	
	// Setter ..
	void SetCam(int c) { m_state = c; }

private:
	void Controls(float dt, IModel* c, IModel* d, IModel* dF);
	void FreeMove();
	void ChaseCam(IModel* c, IModel* d);
	void FPersonCam(IModel* c, IModel* d);
	void SpyCam(IModel* c);
	void CamViews(IModel* c, IModel* d, IModel* dF);
	void ArrowsControl(float dt);
	void Reset(IModel* d, IModel* dF);
	void MouseMovement(float dt);
	//void ChangeCam(IModel* c, IModel* d);

private:
	// 2) Member Variables
	I3DEngine* m_e;						// Enigne
	ICamera* m_cam;						// Camera
	ICamera* m_Chasecam;				// Chase camera
	ICamera* m_fpCam;					// First Person cam
	int m_state;						// Camera state
	float m_step;						// Camera movement step
	float m_xFreeMove;				
	float m_yFreeMove;				
	float m_zFreeMove;		
	float m_xSpy;				
	float m_ySpy;				
	float m_zSpy;				


};


