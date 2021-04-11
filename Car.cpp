// Alexandros Christou
// Implementation of Class CCar
// 13 April 2020

#include "CCar.h"
#include <TL-Engine.h>
#include <iostream>
#include "CVector3.h"
#include <string>
#include <ctime>
using namespace tle;

#define CAR_UP 0
#define CAR_DOWN 1


CCar::CCar(IMesh* mCar, I3DEngine* e, float x, float y, float z)
{
	Initialise(mCar, e, x ,y, z);
}

void CCar::Initialise(IMesh* mCar, I3DEngine* e, float x, float y, float z) {
	m_model = mCar->CreateModel(x, y , z);
	
	m_v = 310.0f;
	m_ds = 0.0;
	m_dsBack = 0.0;
	m_vTwist = 500.0f;
	m_engine = e;
	m_radius = 5.0f;
	m_steeringAngle = 0.0f;
	m_lean = 0.0f;
	m_vLean = 15.0f;
	m_lift = 0.0f;
	m_vLift = 10.0f;
	m_gravity = 0.0f;
	m_stateFloating = CAR_UP;
	m_tBoost = 0.0f;
	m_bOverHeat = false;
	m_fBoostWarning = e->LoadFont("Charlemagne std", 22);
	m_sDir = CVector3(0.0f, 0.0f, 0.0f);
	m_dsOpponent = 0.0f;
	m_HitPoints = 100.0;
	m_font = e->LoadFont("Charlemagne std", 23);
	m_state = 0;
	m_LapCounter = 0;

	m_secToMinutes = 0.0f;
	m_timing = 0.0f;
	m_counterP = 0;
	m_CarsName = "";


	m_tCrush = 0.0f;

}

void CCar::Update(float dt , int isMyCar, IModel* dWay){

	//  User's Car
	if (isMyCar == 0) 
		UsersCar(dt);
	else
	// Opponent Car
	{
		OpponentCar(dWay, dt);
	}

}

void CCar::StatesOfLaps() {

	switch (m_state)
	{
	case CP_1:
		

		break;
	case CP_2:
		
	
		break;
	case CP_3:
		
		
		break;
	case CP_4:
		
		
		break;
	case CP_5:
		
		break;
	case CP_LAST:
		m_LapCounter += LAP;	
		if (m_LapCounter == LAST_LAP) m_state = FINISH;
		else {
			m_state = CP_1;
		}
		break;
	case FINISH :
		break;
	}

}

void CCar::ShowTime() {
	float minute = 60.0f;
	float t = round(m_timing);
	float t2 = round(m_secToMinutes);
	string sSec = std::to_string(m_timing);
	string sMin = std::to_string(m_secToMinutes);
	
	m_font->Draw("TIME:", 220, 640);

	// If seconds > 60SEC -> show time in minutes
	if (m_timing > minute)
		m_font->Draw(sMin, 200, 660);
	else {
		m_font->Draw(sSec, 200, 660);

	}

}

void CCar::Time(float dt) {
	float minute = 60.0f;
	// car has not finish the race
	if (m_state != FINISH)
	m_timing += dt;

	// Convert seconds to Minutes
	if (m_timing > minute)
		m_secToMinutes = m_timing / minute;
	
	//cout << m_secToMinutes << endl;
}

void CCar::PrintLap() {
	float x1 = 580;
	float y1 = 640;
	float x2 = 590;
	float y2 = 660;
	string str = std::to_string(std::int16_t(m_LapCounter));
	m_font->Draw("LAPS", x1, y1);
	m_font->Draw(str+ "/3", x2, y2);
}

void CCar::OpponentCar(IModel* dWay, float dt) {
	
	m_CarsName = "Opponent";

	// Float in the air
	FloatInAir();

	// Follow waypoints
	Movement(dWay, dt);

	// Laps
	StatesOfLaps();

	// Time
	Time(dt);
}

void CCar::PrintHitPoints() {
	float x1 = 650;
	float y1 = 640;
	float x2 = 675;
	float y2 = 660;
	string str = std::to_string(std::int16_t(m_HitPoints));
	m_font->Draw("HITPOINTS:", x1, y1);
	m_font->Draw(str, x2, y2);
}

void CCar::HitPoints() {
	int losePoints = 5;
	m_HitPoints -= losePoints;

}

void CCar::Movement(IModel* dWay, float dt) {
	float step = 2.0f;
	//m_dsOpponent += dt;
	if (m_ds < RIVALS_LIMIT)
	m_ds += dt;
	//m_ds = dt * m_v;

	// Movement through wayPoints (dummies)
	CVector3 d (dWay->GetX(), dWay->GetY(), dWay->GetZ());
	CVector3 c (m_model->GetX(), m_model->GetY(), m_model->GetZ());
	CVector3 s = d - c;

	m_sDir = s / s.Length();

	m_model->Move(m_sDir.GetX()* m_ds/step, m_sDir.GetY()*m_ds/step, m_sDir.GetZ()*m_ds/step);
	m_model->LookAt(dWay);

}

void CCar::ShowCurrentPosition() {
	float x1 = 320;
	float y1 = 640;
	float x2 = 350;
	float y2 = 660;
	string s = std::to_string(m_position);
	
	m_font->Draw("POSITION:", x1, y1);
	m_font->Draw(s+"/2", x2, y2);
}

void CCar::UsersCar(float dt) {
	
	m_CarsName = "User";

	// 1) Cars Controls
	Controls(dt);

	// 2) Float in the air
	FloatInAir();

	// 3) State of Laps
	StatesOfLaps();

	// 4) Print Laps
	PrintLap();

	// 5) Boost 
	Boost(dt);

	// 6) HitPoints when crush w/ an object
	PrintHitPoints();

	// 7) Show cars currenct position against opponent
	ShowCurrentPosition();

	// 8) Timer
	Time(dt);
	ShowTime();
	

}

void CCar::Boost(float dt) {
	float restartBoost = 0.0f;
	int step = 2;
	int stepLose = 100;
	float warning = 2.0f;
	float limitBoost = 3.0;
	float limitBoostNotAvailable = 5.0;
	float speedLimit = 1.9;

	// (a) BOOST is not overheater -> CAR ACCELERATE SPEED
	if (!m_bOverHeat) {
		if (m_engine->KeyHeld(Key_Space)) {
			m_tBoost += dt;

			//(i) Time is is within limits
			if (m_tBoost < limitBoost) {
				m_ds += dt/step;
				if (m_tBoost >= warning)
					WarningBoostMessage();
			}
			// (ii) Boost reaches Limit -> Overheated 
			else if (m_tBoost >= limitBoost) {
				if (m_ds > speedLimit)
					m_ds = m_ds/step;
				
				// loses power speed
				else {
					m_ds -= dt * stepLose;
				}
				m_tBoost = restartBoost;
				m_bOverHeat = true;
			}
		}
	}
	// (b) BOOST is overheated
	else {
		// (i) Wait till boost is available again
		if (m_tBoost < limitBoostNotAvailable)
			m_tBoost += dt;
		else {
			// (ii) Boost is available 
			m_bOverHeat = false;
			m_tBoost = restartBoost;
		}
	}
	
	
	


}

void CCar::WarningBoostMessage() {
	int x1 = 820;
	int y1 = 630;
	int x2 = 830;
	int y2 = 646;
	int x3 = 800;
	int y3 = 665;

	m_fBoostWarning->Draw("WARNING !!", x1, y1,kRed);
	m_fBoostWarning->Draw("-BOOST-", x2, y2,kRed);
	m_fBoostWarning->Draw("-OVERHEATED-", x3, y3, kRed);
}

void CCar::FloatInAir() {
	float stepFloat = 0.035;				// maybe reduce
	float stepLimitUp = 0.1;
	float stepLimitDown = 0.05;
	//m_model->SetY(5.0f);
	const float maxHeigth = 5.5f;
	const float minHeight = 4.0;
	//float step = 0.1;
	switch (m_stateFloating)
	{
		// 1) Car Float Up
	case CAR_UP:
		m_gravity += stepFloat;
		m_model->SetY(m_gravity);
		if (m_gravity > maxHeigth) m_stateFloating = CAR_DOWN;
		break;
		// 2) Car Float Down
	case CAR_DOWN:
		m_gravity -= stepFloat;
		m_model->SetY(m_gravity);
		if (m_gravity < minHeight) m_stateFloating = CAR_UP;
		break;
	}
}

void CCar::CrushCars() {
	m_ds = m_ds ;
	m_model->MoveLocalZ(m_ds*2);

}

void CCar::CrushBounce() {
	float MoveFrontwards = 0.0f;
	float MoveBackWards = 0.0f;
	float step = 2;

		// 1) Collision Resolution (BOUNCING) when car moving frontwards
		if (m_ds > MoveFrontwards) {
			m_ds = -m_ds;
			m_model->MoveLocalZ(m_ds*step);
		}
		// 2) Collision Resolution (BOUNCING) when car moving backwards
		else if (m_ds < MoveBackWards) {
			m_ds = abs(m_ds);
			m_model->MoveLocalZ(m_ds*step);
		}
	
	
}

void CCar::CrushBounceOpponent(float dt) {
	float step = 2;
	m_ds = -m_ds / step;
	m_model->MoveLocalZ(m_ds);
}


void CCar:: Controls(float dt) {
	
	float ds = dt * m_v;
	float dsNew = 1.0f;
	float dsTwist = dt * m_vTwist;
	float stepAngle = 0.5;
	float stepSteeringAngle = 0.2;			
	float steeringAngleLimit = 40.0;

	float stepLean = 0.2;
	float leanLimit = 10.0f;
	float dsLean = m_vLean*dt;

	float liftLimit = 3.0f;
	float stepLift = 0.2f;

	float maxLimit = 1.9f;
	float minLimit = 0.0f;
	float LmoveBack = -2;
	float stepMove = 2;

	float lift = 10.0 * dt;

	// 1a) Move Forwards
	if (m_engine->KeyHeld(Key_W)) {
		
		if (m_ds < maxLimit) {
			m_ds += dt;
		}
		
		m_model->MoveLocalZ(m_ds/2);

	}
	// 1b) Decrease speed when forward button is left
	else if (!m_engine->KeyHit(Key_W)) {
		
		
		if (m_ds > minLimit) {
			m_ds -= dt;
		}
		m_model->MoveLocalZ(m_ds/stepMove);
	}
	// Car is lifting
	if (m_engine->KeyHeld(Key_W)) {

		if (m_lift < liftLimit) {
			m_lift += stepLift;
			m_model->RotateLocalX(-lift);

		}

	}
	else if (!m_engine->KeyHeld(Key_W))
	{
		if (m_lift > minLimit) {
			m_lift -= stepLift;
			m_model->RotateLocalX(lift);  // 0.2
		}
	}


	// 2a) Move Backwards
	if (m_engine->KeyHeld(Key_S)) {
		
		if (m_ds > LmoveBack) {
			m_ds -= dt;
		}
		m_model->MoveLocalZ(m_ds/stepMove);
	}
	// 2b) Increase speed when backward button is left
	else if (!m_engine->KeyHit(Key_S)) {
		
		if (m_ds <  minLimit) {
			m_ds+= dt;
		}
		m_model->MoveLocalZ(m_ds/stepMove);
	}
	

	// 3) Move Clockwise
	if (m_engine->KeyHeld(Key_D)) {
		//m_model->MoveLocalX(ds);
		if (m_steeringAngle <= steeringAngleLimit)
			m_steeringAngle += stepSteeringAngle;
			m_model->RotateY(stepSteeringAngle* dsTwist);

			
	}
	// a) Cars is leaning to the right
	if (m_engine->KeyHeld(Key_D)) {
		if (m_lean >= -leanLimit) {
			m_lean -= stepLean;
			m_model->RotateLocalZ(-dsLean);
		}

	}
	// b) Cars streghtens 
	else if (!m_engine->KeyHeld(Key_D)) {
		if (m_lean < minLimit) {
			m_lean += stepLean;
			m_model->RotateLocalZ(dsLean);
		}
	}

	// 4) Move anti-Clockwise
	if (m_engine->KeyHeld(Key_A)) {
		
		if (m_steeringAngle >= -steeringAngleLimit)
			m_steeringAngle -= stepSteeringAngle;
			m_model->RotateY(-stepSteeringAngle* dsTwist);
		
			

	}

	// a) Cars is leaning to the Left
	if (m_engine->KeyHeld(Key_A)) {
		if (m_lean <= leanLimit) {
			m_lean += stepLean;
			m_model->RotateLocalZ(dsLean);
		}


	}
	// b) Cars streghtens 
	else if (!m_engine->KeyHeld(Key_A)) {
		if (m_lean > minLimit) {
			m_lean -= stepLean;
			m_model->RotateLocalZ(-dsLean);
		}
	}

	
}

