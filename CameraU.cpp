// Alexandros Christou
// Implementation of CCameraU Class
// 16 April 2020

#include "CCameraU.h"
#include <TL-Engine.h>
#include "CVector3.h"
#include <iostream>
using namespace tle;



CCameraU::CCameraU(I3DEngine* e)
{
	Initialise(e);

}

void CCameraU::Initialise(I3DEngine* e) {
	
	m_e = e;

	m_state = C_FREE_MOVE;

	m_xFreeMove = 190.0f;
	m_yFreeMove = 350.0f;
	m_zFreeMove = 300.0f;

	m_xSpy = 0.0f;
	m_ySpy = 150.0f;
	m_zSpy = -200.0f;

	// Camera
	m_cam = m_e->CreateCamera(kManual, m_xFreeMove, m_yFreeMove, -m_zFreeMove);
	m_cam->RotateLocalX(45.0);

	m_step = 85.0f;  //55

	m_state = C_FREE_MOVE;

}

void CCameraU::Update(float dt, IModel* c, IModel* d, IModel* dF) {

	Controls(dt, c, d, dF);

}
void CCameraU::Controls(float dt, IModel* c, IModel* d, IModel* dF) {

	// Keys Control Movement:
	ArrowsControl(dt);

	// Different Camera ViewPoints ..
	CamViews(c, d, dF);

	// Reset Cameras Orientation, Position
	if (m_e->KeyHit(Key_C))
		Reset(d, dF);

	// Mouse Orientations ..
	MouseMovement(dt);

}


void CCameraU::MouseMovement(float dt) {
	float step = 15.0f;

	float dsMove = step * dt;			

	float mouseMovementX = m_e->GetMouseMovementX();
	float mouseMovementY = m_e->GetMouseMovementY();
	m_cam->RotateY(dsMove*mouseMovementX);
	m_cam->RotateLocalX(dsMove*mouseMovementY);
}

void CCameraU::ArrowsControl(float dt) {

	float ds = dt * m_step;

	// 1) MOVE UP
	if (m_e->KeyHeld(Key_Up)) {
		m_cam->MoveLocalZ(ds);
	}
	// 2) MOVE DOWN
	if (m_e->KeyHeld(Key_Down)) {
		m_cam->MoveLocalZ(-ds);
	}
	// LEFTWARDS
	if (m_e->KeyHeld(Key_Left)) {
		m_cam->MoveLocalX(-ds);
	}
	// RIGHTWARDS
	if (m_e->KeyHeld(Key_Right)) {
		m_cam->MoveLocalX(ds);
	}

}


void CCameraU::CamViews(IModel* c, IModel* d, IModel* dF) {

	// 1) FIRST-PERSON CAMERA (CAR DRIVE EXPIRIENCE)
	if (m_e->KeyHit(Key_1) && m_state != C_FPERSON) {
		m_state = C_FPERSON;
		FPersonCam(c, dF);
	}
	// 2) FREE MOVE CAMERA - TOP
	if (m_e->KeyHit(Key_2) && m_state != C_FREE_MOVE) {
		m_state = C_FREE_MOVE;
		FreeMove();
	}
	// 3) CHASE CAM - BEHIND CAR
	if (m_e->KeyHit(Key_3) && m_state != C_CHASE) {
		m_state = C_CHASE;
		ChaseCam(c,d);
	}
	// 4) SURVEILLANCE CAM - FOLLOW CAR
	if (m_e->KeyHit(Key_4) && m_state != C_SPY) {
		m_state = C_SPY;
		SpyCam(c);
	}
}

void CCameraU::FreeMove() {
	float angle = 45.0f;

	m_cam->DetachFromParent();
	m_cam = m_e->CreateCamera(kManual , m_xFreeMove, m_yFreeMove, -m_zFreeMove);
	m_cam->RotateLocalX(angle);

}
void CCameraU::ChaseCam(IModel* c, IModel* d) {
	
	m_cam->DetachFromParent();
	m_cam->AttachToParent(d);
	m_cam->SetPosition(d->GetX(), d->GetY(), d->GetZ());
	m_cam->ResetOrientation();
	
	//m_cam->RotateLocalX(-5);
}

void CCameraU::FPersonCam(IModel* c, IModel* d) {
	float angle = 5.0f;

	m_cam->DetachFromParent();
	m_cam->AttachToParent(d);
	m_cam->SetPosition(d->GetX(), d->GetY(), d->GetZ());
	m_cam->ResetOrientation();
	m_cam->RotateLocalX(-angle);

}

void CCameraU::SpyCam(IModel* c) {

	float angle = 45.0f;

	m_cam->DetachFromParent();	
	m_cam = m_e->CreateCamera (kManual, m_xSpy, m_ySpy, m_zSpy);
	m_cam->AttachToParent(c);
	m_cam->RotateLocalX(angle);

}

void CCameraU::Reset(IModel* d, IModel* dF) {

	switch (m_state)
	{
	case C_FREE_MOVE:
		m_cam->SetPosition(m_xFreeMove, m_yFreeMove, -m_zFreeMove);
		break;
	case C_CHASE:
		m_cam->SetPosition(d->GetX(), d->GetY() , d->GetZ());
		break;
	case C_FPERSON:
		m_cam->SetPosition(dF->GetX(), dF->GetY(), dF->GetZ());
		break;
	case C_SPY:
		m_cam->SetPosition(m_xSpy, m_ySpy, m_zSpy);
		break;

	}

}
