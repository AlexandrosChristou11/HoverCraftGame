// Alexandros Christou
// Declaration of CCar Class
// 13 April 2020

#include <TL-Engine.h>
#include "CVector3.h"


#define CP_1 0
#define CP_2 1
#define CP_3 2
#define CP_4 3
#define CP_5 4
#define CP_LAST 5
#define FINISH 6

#define FIRST 1
#define LAST 2

#define LAP 1
#define LAST_LAP 3

#define RIVALS_LIMIT 1.3

#pragma once
using namespace tle;

class CCar
{
public:
	// 1) Member Methods
	CCar() {};
	CCar(IMesh* mCar, I3DEngine* e, float x, float y, float z);
	void Initialise(IMesh* mCar, I3DEngine* e, float x, float y, float z);
	void Update(float dt, int MyCar, IModel* dWay);

	// Getters , Setters .. 
	CVector3 GetPosition() { return CVector3 (m_model->GetX(), m_model->GetY(), m_model->GetZ()); }
	float GetRadius() { return m_radius; }
	IModel* GetCar() { return m_model; }
	float GetX() { return m_model->GetX(); }
	float GetY() { return m_model->GetY(); }
	float GetZ() { return m_model->GetZ(); }
	float GetSpeed() { return m_ds; }
	float GetSpeedB() { return m_dsBack; }
	void SetSpeed(float a) { m_ds = a; }
	void SetSpeedB(float a) { m_dsBack = a; }
	void SetStateLap(int s) { m_state = s; }
	int GetState() { return m_state; }
	int GetLap() { return m_LapCounter; }
	void SetLap(int s) { m_LapCounter = s; }
	void SetV(float v) { m_v = v; }
	float GetCounterP() { return m_counterP; }
	void SetCounterP() { m_counterP += 1; }

	void SetMapPosition(float p) { m_position = p; }
	int GetMapPosition() { return m_position; }
	string GetName() { return m_CarsName; }
	float GetTime() { return m_timing; }
	void SetTimeCrushOpponent(float t) { m_tCrush = t; }
	void SetTime(float t) { m_timing = t; }
	void SetHitPoints(float p) { m_HitPoints = p; }

	// Crushes
	void CrushBounce();
	void CrushCars();
	void CrushBounceOpponent(float dt);

	// Crush points
	void HitPoints();


private:
	// Member Methods
	void Controls(float dt);
	void FloatInAir();
	void Boost(float dt);
	void WarningBoostMessage();
	void UsersCar(float dt);
	void OpponentCar(IModel* dWay, float dt);
	void Movement(IModel* dWay, float dt);
	void PrintHitPoints();
	void StatesOfLaps();
	void PrintLap();
	void ShowCurrentPosition();
	void Time(float dt);
	void ShowTime();

private:
	// 2) Member Variables
	IModel* m_model;						// Hove-car model
	float m_v;								// Velocity
	float m_dsC;
	float m_vTwist;							// Twist velocity
	I3DEngine* m_engine;					// Engine
	float m_radius;							// radius of car
	float m_steeringAngle;
	float m_lean;							// car leaning as it turns
	float m_vLean;							// leaning velocity
	float m_lift;							// car lifting up variable
	float m_vLift;							// lifting velocity
	 float m_ds;							// cars speed forward
	 float m_dsBack;						// cars speed backward
	 float m_gravity;						// cars floating Gravity 
	 int m_stateFloating;					// car floating state
	 float m_tBoost;						// Time for boost
	 bool m_bOverHeat;						// car heat boosting limit 
	 IFont* m_fBoostWarning;				// ifont for boost 1 second warning
	 CVector3 m_sDir;						// Direction of Opponent car -> to dummy waypoint
	 float m_dsOpponent;					// Opponent Car's speed
	 float m_HitPoints;						// hit points when a car collides w/ an object
	 IFont* m_font;							// message about hit points
	 int m_state;							// Car's lap state
	 int m_LapCounter;						// counter of laps
	 IFont* m_Flap;							// font for laps showing
	 float m_counterP;						// counter++ when a checkpoint is passed - > position
	 int m_position;						// cars position on map
	 float m_timing;						// timing variables 
	 float m_secToMinutes;
	 string m_CarsName;						// user player or opponent -> display on leaderboad;
	 float m_tCrush;						// opponent car crush time waiting
};

