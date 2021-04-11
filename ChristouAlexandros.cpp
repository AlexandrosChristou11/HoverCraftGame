// Alexandros Christou
// ChristouAlexandros.cpp: A program using the TL-Engine
// HOVER-RACING GAME
// CO1301 - GAMES CONCEPT


#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
#include "CArena.h"
#include "CIsle.h"
#include "CWall.h"
#include "CCheckpoint.h"
#include "CCar.h"
#include "CSprite.h"
#include "CGame.h"
#include "CCameraU.h"
#include "CDummy.h"
#include "CIslesCorners.h"
#include "CObstacle.h"
#include "CLamb.h"
#include "CWalway.h"
#include "CCross.h"
#include "CQuad.h"

#define INTRO_HIT_SPACE 0
#define COUNTDOWN 1
#define PLAY 2
#define END_OF_GAME 3
#define RESTART 0
#define CROSS_RESTART 3.0
#define RESTART_TIME 0.0
#define RESTART_HITPOINTS 100


#define CP1 0
#define CP2 1
#define CP3 2
#define CP4 3
#define CP5 4

#define USER_CAR 0
#define RIVAL_CAR 1



using namespace tle;

void DoNothing() {}

bool CheckPointOnePassed(CVector3 a, CVector3 b, float r1, float r2) {
	
	CVector3 s = b - a;
	if (s.Length() < r1 + r2) {
		return true;
	}
	return false;
}

void PassFromCpoints(CCar& c, CCheckpoint cp[], CGame& g, float& dt, int& indexC, CCross cross[], const int knCheckpoints) {
	int nextState = 1;
	
	// 1) Colision w/ CheckPoint - if it passed 

	for (int i = 0; i < knCheckpoints; i++) {
		if (CheckPointOnePassed(c.GetPosition(), cp[i].GetPosition(), c.GetRadius(), cp[i].GetRadius())) {
			// (a) User Player --> Print cross
			//(i) Pass from 1st Checkpoint-> restart the timer from last checkpoint
			if (indexC == USER_CAR) {
				if (i == CP5)
					cross[CP1].SetTimer(RESTART_TIME);
				else
					// (ii) if checkpoint pass one checkpoint -> restart the timer from the previous
				{
					cross[i + 1].SetTimer(RESTART_TIME);
				}
				// Appear cross only user's car pass from Checkpoint
				if (indexC == USER_CAR)
					cross[i].AppearCross(dt);
			}
			// Car has to pass from next lap
			if (c.GetState() == i) {
				c.SetStateLap(i + nextState);
				// increasing counter of car
				c.SetCounterP();
			}
			
		}

	// 2) Colission w/ Legs of Cpoint
		if (i == CP1 ) {
			float x = 60;
			float z = 1;
			float xR = 53;
			float zR = 2;
			CVector3 L(cp[i].GetX() - x, cp[i].GetY(), cp[i].GetZ() + z);
			CVector3 R(cp[i].GetX() + xR, cp[i].GetY(), cp[i].GetZ() + zR);
			// (a) Left Left
			if (CheckPointOnePassed(c.GetPosition(), L, c.GetRadius(), cp[i].GetRadius() + 2))
				c.CrushBounce();
			// (b) Right Leg
			if (CheckPointOnePassed(c.GetPosition(), R, c.GetRadius(), cp[i].GetRadius() + 2))
				c.CrushBounce();
		}
		else if (i == CP2 || i == CP3) {
			
			float zL = 30;
			float zR2 = 50;
			CVector3 L1(cp[i].GetX(), cp[i].GetY(), cp[i].GetZ() + zL);
			CVector3 R1(cp[i].GetX(), cp[i].GetY(), cp[i].GetZ() - zR2);
			// (a) Left Left
			if (CheckPointOnePassed(c.GetPosition(), L1, c.GetRadius(), cp[i].GetRadius())) {
				c.HitPoints();
				c.CrushBounce();
			}
			// (b) Right Leg
			if (CheckPointOnePassed(c.GetPosition(), R1, c.GetRadius(), cp[i].GetRadius())) {
				c.HitPoints();
				c.CrushBounce();
			}
		}
		else if (i == CP5) {
			float zL1 = 40;
		

			CVector3 L1(cp[i].GetX(), cp[i].GetY(), cp[i].GetZ() - zL1);
			CVector3 R1(cp[i].GetX(), cp[i].GetY(), cp[i].GetZ() + zL1);
			// (a) Left Left
			if (CheckPointOnePassed(c.GetPosition(), L1, c.GetRadius(), cp[i].GetRadius())) {
				c.HitPoints();
				c.CrushBounce();
			}
			// (b) Right Leg
			if (CheckPointOnePassed(c.GetPosition(), R1, c.GetRadius(), cp[i].GetRadius())) {
				c.HitPoints();
				c.CrushBounce();
			}
		}

		
	}


}



bool CollisionCarTank(CVector3 a, CVector3 b, float r1, float r2) {
	int yColl = 0;
	b.SetY(yColl);
	CVector3 s = b - a;
	if (s.Length() < r1 + r2) {
		return true;
	}
	return false;
}

void CollisionCarNtanks(CCar& c, CObstacle ob[],const int knOb) {
	for (int i = 0; i < knOb; i++) {
		if (CollisionCarTank(c.GetPosition(), ob[i].GetPosition(), c.GetRadius(), ob[i].GetRadius())) {
			c.CrushBounce();
			c.HitPoints();
		}
	}
}



bool isThereCollision(CVector3 c, CVector3 min, CVector3 max) {

	if (c.GetX() >  min.GetX() && c.GetX() < max.GetX() && c.GetZ() > min.GetZ() && c.GetZ() < max.GetZ()) {
		return true;
	}
	return false;
}

void CollisionBetweenCarNwallLeft(CCar& c, CWall& w, int index) {
	int divStep = 2;
	int firstRow1 = 0;
	int lastRow1 = 21;
	int firstRow2 = 66;
	int lastRow2 = 95;

	// Vertical Wall Collision
	if (index >= firstRow1 && index <= lastRow1 || index >= firstRow2 && index <= lastRow2)
	{
		
		CVector3 sMin(w.GetX() - c.GetRadius() - w.GetWid() / divStep, w.GetY() - c.GetRadius() - w.GetHeight(), w.GetZ() - c.GetRadius() - w.GetLen() / divStep);
		CVector3 sMax(w.GetX() + c.GetRadius() + w.GetWid() / divStep, w.GetY() + c.GetRadius() + w.GetHeight(), w.GetZ() + c.GetRadius() + w.GetLen() / divStep);
		if (isThereCollision(c.GetPosition(), sMin, sMax)) {
			c.HitPoints();
			c.CrushBounce();
		}
	}
	// Horizontal Wall Collision
	else
	{
		CVector3 sMin(w.GetX() - c.GetRadius() - w.GetLen() / divStep, w.GetY() - c.GetRadius() - w.GetHeight(), w.GetZ() - c.GetRadius() - w.GetWid() / divStep);
		CVector3 sMax(w.GetX() + c.GetRadius() + w.GetLen() / divStep, w.GetY() + c.GetRadius() + w.GetHeight(), w.GetZ() + c.GetRadius() + w.GetWid() / divStep);
		if (isThereCollision(c.GetPosition(), sMin, sMax)) {
			c.HitPoints();
			c.CrushBounce();
		}
	}
	
}

void CollisionBetweenCarNwallRight(CCar& c, CWall& w, int index) {
	int divStep = 2;
	int firstRow1 = 0;
	int lastRow1 = 22;
	int firstRow2 = 38;
	int lastRow2 = 60;

	// Vertical Wall Collision
	if (index >= firstRow1 && index <= lastRow1 || index >= firstRow2 && index <= lastRow2)
	{
		
		CVector3 sMin(w.GetX() - c.GetRadius() - w.GetWid() / divStep, w.GetY() - c.GetRadius() - w.GetHeight(), w.GetZ() - c.GetRadius() - w.GetLen() / divStep);
		CVector3 sMax(w.GetX() + c.GetRadius() + w.GetWid() / divStep, w.GetY() + c.GetRadius() + w.GetHeight(), w.GetZ() + c.GetRadius() + w.GetLen() / divStep);
		if (isThereCollision(c.GetPosition(), sMin, sMax)) {
			c.CrushBounce();
			c.HitPoints();
		}
	}
	// Horizontal Wall Collision
	else
	{
		CVector3 sMin(w.GetX() - c.GetRadius() - w.GetLen() / divStep, w.GetY() - c.GetRadius() - w.GetHeight(), w.GetZ() - c.GetRadius() - w.GetWid() / divStep);
		CVector3 sMax(w.GetX() + c.GetRadius() + w.GetLen() / divStep, w.GetY() + c.GetRadius() + w.GetHeight(), w.GetZ() + c.GetRadius() + w.GetWid() / divStep);
		if (isThereCollision(c.GetPosition(), sMin, sMax)) {
			c.CrushBounce();
			c.HitPoints();
		}
	}
	
}


void CollisionBetweenCarNisle(CCar& c, CIsle& isle) {

	CVector3 sMin(isle.GetX() - c.GetRadius() - isle.GetRadius(), isle.GetY() - c.GetRadius() - isle.GetRadius(), isle.GetZ() - c.GetRadius() - isle.GetRadius());
	CVector3 sMax(isle.GetX() + c.GetRadius() + isle.GetRadius(), isle.GetY() + c.GetRadius() + isle.GetRadius(), isle.GetZ() + c.GetRadius() + isle.GetRadius());

	if (isThereCollision(c.GetPosition(), sMin, sMax)) {
		c.HitPoints();
		c.CrushBounce();
	}
}
void CollisionBetweenCarNcorner(CCar& c, CIslesCorners& corner) {

	CVector3 sMin(corner.GetX() - c.GetRadius() - corner.GetRadius(), corner.GetY() - c.GetRadius() - corner.GetRadius(), corner.GetZ() - c.GetRadius() - corner.GetRadius());
	CVector3 sMax(corner.GetX() + c.GetRadius() + corner.GetRadius(), corner.GetY() + c.GetRadius() + corner.GetRadius(), corner.GetZ() + c.GetRadius() + corner.GetRadius());

	if (isThereCollision(c.GetPosition(), sMin, sMax)) {
		c.HitPoints();
		c.CrushBounce();
	}
}

void CollisionBetweenCarNobstacle(CCar& c, CObstacle& ob) {

	CVector3 sMin(ob.GetX() - c.GetRadius() - ob.GetRadius(), ob.GetY() - c.GetRadius() - ob.GetRadius(), ob.GetZ() - c.GetRadius() - ob.GetRadius());
	CVector3 sMax(ob.GetX() + c.GetRadius() + ob.GetRadius(), ob.GetY() + c.GetRadius() + ob.GetRadius(), ob.GetZ() + c.GetRadius() + ob.GetRadius());

	if (isThereCollision(c.GetPosition(), sMin, sMax)){	
		c.CrushBounce();
		c.HitPoints();
	}
}

void CollisionBetweenCarNlamp(CCar& c, CLamb& lamp) {

	CVector3 sMin(lamp.GetX() - c.GetRadius() - lamp.GetRadius(), lamp.GetY() - c.GetRadius() - lamp.GetRadius(), lamp.GetZ() - c.GetRadius() - lamp.GetRadius());
	CVector3 sMax(lamp.GetX() + c.GetRadius() + lamp.GetRadius(), lamp.GetY() + c.GetRadius() + lamp.GetRadius(), lamp.GetZ() + c.GetRadius() + lamp.GetRadius());

	if (isThereCollision(c.GetPosition(), sMin, sMax)) {
		c.HitPoints();
		c.CrushBounce();
	}
}

bool CollisionOpponentDummyCheckPoint(CDummy& d, CCar& c) {
	CVector3 sMin(d.GetX() - c.GetRadius() - d.GetRadius(), d.GetY() - c.GetRadius() - d.GetRadius(), d.GetZ() - c.GetRadius() - d.GetRadius());
	CVector3 sMax(d.GetX() + c.GetRadius() + d.GetRadius(), d.GetY() + c.GetRadius() + d.GetRadius(), d.GetZ() + c.GetRadius() + d.GetRadius());

	if (isThereCollision(c.GetPosition(),sMin, sMax)) {
		return true;
	}
	return false;
}
bool CheckIfCarFinished(CCar& c1, CCar& c2) {
	if (c1.GetState() == FINISH)
		return true;
	else if (c2.GetState() == FINISH)
		return true;

	return false;
}

void CollisionBetweenCars(CCar& c1, CCar& c2, float& dt) {
	float d = 3;


	CVector3 sMin(c2.GetX() - c1.GetRadius() - c2.GetRadius()-d, c2.GetY() - c1.GetRadius() - c2.GetRadius()- d, c2.GetZ() - c1.GetRadius() - c2.GetRadius()- d);
	CVector3 sMax(c2.GetX() + c1.GetRadius() + c2.GetRadius()- d, c2.GetY() + c1.GetRadius() + c2.GetRadius()- d, c2.GetZ() + c1.GetRadius() + c2.GetRadius()- d);

	// if a car has a finished the races -> do not collide with other opponent car
	if (!CheckIfCarFinished(c1, c2))
	if (CollisionCarTank(c1.GetPosition(), c2.GetPosition(), c1.GetRadius(), c2.GetRadius())) {
		//c1.CrushBounce();
		c1.CrushCars();

		c2.CrushBounceOpponent(dt);
		//c2.CrushBounce();
		c1.HitPoints();
		c2.HitPoints();
	}
	//c2.SetTimeCrushOpponent(0.0f);
}

void CollisionCarLegsCP(CCar& c, CDummy& dLegs) {
	CVector3 sMin(dLegs.GetX() - c.GetRadius() - dLegs.GetRadius(), dLegs.GetY() - c.GetRadius() - dLegs.GetRadius(), dLegs.GetZ() - c.GetRadius() - dLegs.GetRadius());
	CVector3 sMax(dLegs.GetX() + c.GetRadius() + dLegs.GetRadius(), dLegs.GetY() + c.GetRadius() + dLegs.GetRadius(), dLegs.GetZ() + c.GetRadius() + dLegs.GetRadius());

	if (isThereCollision(c.GetPosition(), sMin, sMax)) {
		c.HitPoints();
		c.CrushBounce();
	}

}


void CheckCarHasFinished(CCar c[], const int knCars, int FinalLap, int& CarHasFinished, CGame& g, CCameraU& cam) {

	// A) All cars have finished the game
	if (c[USER_CAR].GetState() == FINISH && c[RIVAL_CAR].GetState() == FINISH)
		g.SetState(END_OF_GAME);
	// B) Car 1 Has finished
	else if (c[USER_CAR].GetState() == FINISH && c[RIVAL_CAR].GetState() != FINISH) {
		g.CarWonWait();
		cam.SetCam(C_SPY);
		
	}
}

void CheckCarsPosition(CCar c[], const int knC) {
	
	if (c[USER_CAR].GetCounterP() > c[RIVAL_CAR].GetCounterP()) {
		c[USER_CAR].SetMapPosition(FIRST);
		c[RIVAL_CAR].SetMapPosition(LAST);
	}
	else {
		c[RIVAL_CAR].SetMapPosition(FIRST);
		c[USER_CAR].SetMapPosition(LAST);
	}


}

void PlayingMode(CCar c[], CCheckpoint cp[], CWall wallL[], CWall wallR[], CIsle isleL[], CIsle isleR[],
	float& dt, const int knIsleRight, const int knIsleLeft, const int knWallLeft, const int knWallRight, CGame& g, I3DEngine* e, CDummy dummy[], const int knDummy, int dummyCar, CCameraU& cam,
	CIslesCorners corner[], const int knCorner, CObstacle ob[], const int knOb, CLamb lamp[], const int knLamp, const int knCars, int myCar, CDummy dWay[], const int kndWay, int& indexD, int& CarHasFinished,
	CCross cross[], CDummy cpLegs[], const int kndLegs, CQuad q[], const int knQ, CQuad qR[], const int knCheckpoints) {

	// Important variables (lapCounter etc ..)
	int FinalLap = 3;
	int stepIndex = 1;
	int firstIndex = 0;

	// 2) Check if car has finished all Laps
	CheckCarHasFinished(c, knCars, FinalLap, CarHasFinished, g , cam);

	// 3a) Opponent car reaches the last wayPoint - start again from beginning
	if (indexD >= kndWay - stepIndex) indexD = RESTART;

	// 3b) Opponent car driving through dummy waypoints
	else if (indexD < kndWay - stepIndex)
		if (CollisionOpponentDummyCheckPoint(dWay[indexD], c[RIVAL_CAR]))
			indexD += stepIndex;

	// 4) Update Car
	c[USER_CAR].Update(dt, USER_CAR, dWay[firstIndex].GetModel());

	c[RIVAL_CAR].Update(dt, RIVAL_CAR, dWay[indexD].GetModel());

	// 5) Pass from CheckPoints 
	for (int i = 0; i < knCars; i++)
		PassFromCpoints(c[i], cp, g, dt, i, cross, knCheckpoints);

	// 6) CheckPosition
	CheckCarsPosition(c, knCars);

	// 6) Check For Collision 
	for (int iCar = 0; iCar < knCars; iCar++) {

		// (a) Wall Left
		for (int iWall = 0; iWall < knWallLeft; iWall++) {
			CollisionBetweenCarNwallLeft(c[iCar], wallL[iWall], iWall);
		}

		// (b) Wall Right
		for (int iWall = 0; iWall < knWallRight; iWall++) {
			CollisionBetweenCarNwallRight(c[iCar], wallR[iWall], iWall);
		}

		// (c) Isle Left
		for (int iIsle = 0; iIsle < knIsleLeft; iIsle++)
			CollisionBetweenCarNisle(c[iCar], isleL[iIsle]);

		//( (d) Isle Right
		for (int iIsle = 0; iIsle < knIsleRight; iIsle++) {
			CollisionBetweenCarNisle(c[iCar], isleR[iIsle]);
		}

		// (e) Corners ..
		for (int i = 0; i < knCorner; i++) {
			CollisionBetweenCarNcorner(c[iCar], corner[i]);
		}

		// (f) Obstacles
		CollisionCarNtanks(c[iCar], ob, knOb);

		// (g) Lamps
		for (int i = 0; i < knLamp; i++) {
			CollisionBetweenCarNlamp(c[iCar], lamp[i]);
		}
		// (h) Collision with CPoint 4 Legs!!
		for (int i = 0; i < kndLegs; i++) {
			CollisionCarLegsCP(c[iCar], cpLegs[i]);
		}
	}
	// (i) Car Vs Opponent car collision
	CollisionBetweenCars(c[USER_CAR], c[RIVAL_CAR], dt);
}


void RestartCarsLaps(CCar c[], const int knCars, int& indexD, CCross cross[]) {
	float x = -5;
	float z = -20;
	indexD = 0;
	for (int i = 0; i < knCars; i++) {
		c[i].SetLap(RESTART);
		c[i].SetStateLap(RESTART);
		c[i].GetCar()->SetPosition(x, 0, z);
		x += 15;
		c[i].GetCar()->ResetOrientation();
		c[i].SetSpeed(RESTART);
		c[i].SetHitPoints(RESTART_HITPOINTS);
		c[i].SetTime(RESTART_TIME);
	}
	// last cross restart
	cross[CP5].SetTimer(CROSS_RESTART);
}

void LeaderBoard(CCar c[], const int knCars, CGame& g) {
	float x = 300;
	float y = 100;

	if (c[USER_CAR].GetTime() < c[RIVAL_CAR].GetTime()) {
		c[USER_CAR].SetMapPosition(FIRST);
		g.ShowLeaderBoard(c[USER_CAR].GetMapPosition(), c[USER_CAR].GetName(), c[USER_CAR].GetTime(), x, y);
		y += 100;
		c[RIVAL_CAR].SetMapPosition(LAST);
		g.ShowLeaderBoard(c[RIVAL_CAR].GetMapPosition(), c[RIVAL_CAR].GetName(), c[RIVAL_CAR].GetTime(), x, y);
		
	}
	else if (c[USER_CAR].GetTime() > c[RIVAL_CAR].GetTime())
	{	c[RIVAL_CAR].SetMapPosition(FIRST);
		g.ShowLeaderBoard(c[RIVAL_CAR].GetMapPosition(), c[RIVAL_CAR].GetName(), c[RIVAL_CAR].GetTime(), x, y);
		y += 40;
		c[USER_CAR].SetMapPosition(LAST);
		g.ShowLeaderBoard(c[USER_CAR].GetMapPosition(), c[USER_CAR].GetName(), c[USER_CAR].GetTime(), x, y);
	
		
	}
	
}


void UpdateScene(CCar c[], CCheckpoint cp[], CWall wallL[], CWall wallR[], CIsle isleL[], CIsle isleR[],
	float& dt, const int knIsleRight, const int knIsleLeft, const int knWallLeft, const int knWallRight, CGame& g, I3DEngine* e, CDummy dummy[], const int knDummy, int dummyCarB, CCameraU& cam,
	CIslesCorners corner[], const int knCorner, CObstacle ob[], const int knOb, CLamb lamp[], const int knLamp, const int knCars, int myCar, CDummy dWay[], const int kndWay, int& indexD, int& CarHasFinished,
	CCross cross[], int dummyCarF, CDummy cpLegs[], const int kndLegs, CQuad q[], const int knQ, CQuad qR[], const int knCheckpoints)
{
	

	// 1) Update Game
	g.Update(dt, c[myCar].GetSpeed(), c[myCar].GetSpeedB());

	// 2) Update Camera
	cam.Update(dt, c[myCar].GetCar(), dummy[dummyCarB].GetModel(), dummy[dummyCarF].GetModel());

	for (int i = 0; i < knQ; i++) {
		q[i].Update(dt, c[USER_CAR].GetCar());
		qR[i].Update(dt, c[RIVAL_CAR].GetCar());
	}


	switch (g.GetState())
	{
	case INTRO_HIT_SPACE:
		RestartCarsLaps(c, knCars, indexD, cross);
		//c->SetLap(0);
		DoNothing();
		break;
	case COUNTDOWN:
		DoNothing();
		break;
	case PLAY:
		PlayingMode(c, cp, wallL, wallR, isleL, isleR, dt, knIsleRight, knIsleLeft, knWallLeft, knWallRight, g, e, dummy, knDummy, dummyCarB, cam, corner, knCorner, ob, knOb, lamp, knLamp, knCars, myCar, dWay, kndWay, indexD,
					CarHasFinished, cross, cpLegs ,kndLegs, q, knQ, qR, knCheckpoints);
		break;
	case END_OF_GAME:
		
		LeaderBoard(c,knCars,g);
		
		break;
	}

}
	






void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder("C:\\Users\\UserPC\\Desktop\\Assignment-All_Media");


	/**** Set up your scene here ****/

	
	// Meshes 
	IMesh* mSkybox = myEngine->LoadMesh("Skybox_Hell.x"); 
	IMesh* mIsle = myEngine->LoadMesh("IsleStraight.x");
	IMesh* mWall = myEngine->LoadMesh("Wall.x");
	IMesh* mCheckpoint = myEngine->LoadMesh("Checkpoint.x");
	IMesh* mGround = myEngine->LoadMesh("ground.x");
	IMesh* mTank = myEngine->LoadMesh("TankSmall1.x");
	IMesh* mTank2 = myEngine->LoadMesh("TankSmall2.x");
	IMesh* mIsleCorner = myEngine->LoadMesh("IsleTee.x");
	IMesh* mCar = myEngine->LoadMesh("race2.x"); 
	IMesh* mPlane = myEngine->LoadMesh("FFstarfighter.x");
	IMesh* mGrid = myEngine->LoadMesh("Grid.x");
	IMesh* mDummy = myEngine->LoadMesh("Dummy.x");
	IMesh* mWalk = myEngine->LoadMesh("Walkway.x");
	IMesh* mLamp = myEngine->LoadMesh("Lamp.x");
	IMesh* mTribune1 = myEngine->LoadMesh("Tribune2.x");
	IMesh* mPlanet = myEngine->LoadMesh("planet.x");
	IMesh* mPoolTable = myEngine->LoadMesh("PoolTable.x");
	IMesh* mBuilding = myEngine->LoadMesh("Arrow.x");
	IMesh* mSpaceship = myEngine->LoadMesh("Interstellar.x");
	IMesh* mCross = myEngine->LoadMesh("Cross.x");
	IMesh* mQuad = myEngine->LoadMesh("quad.x");

	
	IModel* m_ground = mGround->CreateModel();
	IModel* ship = mSpaceship->CreateModel(150, 5, 0);
	ship->RotateY(-120);
	ship->Scale(1.5f);
	

	IModel* m_poolTable = mPoolTable->CreateModel(100, 1, 70);
	m_poolTable->Scale(2.5f);
	m_poolTable->SetSkin("MoonHi.jpg");
	IModel* m_poolBall = mPlanet->CreateModel(120, 25, 70);
	m_poolBall->Scale(45.5f);
	IModel* m = mPlanet->CreateModel(-495, 25, 70);
	m->Scale(73.5f);
	
	int xb = 50;
	int yb = 0;
	int zb = 50;
	int yb1 = 0;
	IModel* aB[19];
	for (int i = 0; i < 19; i++) {
		if (i < 7) {
			aB[i] = mBuilding->CreateModel(xb, yb, zb);
			yb += 3;
		}
		else if (i >= 7 && i <=11){
			zb = 40;
			xb = 70;
			aB[i] = mBuilding->CreateModel(xb, yb1, zb);
			yb1 += 3;
			yb = 0;
		}
		else {
			zb = 0;
			xb = 90;
			aB[i] = mBuilding->CreateModel(xb, yb, zb);
			yb += 3;
		}

	}


	// Classes Isles, walls, checkpoint .. etc
	
	const int knArena = 7;
	CArena arena[knArena];
	float xSky = 0;
	float ySky = -1000;
	float zSky = 0;

	float xTri = -130;
	float yTri = 0;
	float zTri = -20;
	float zTriE = 140;


	for (int i = 0; i < knArena; i++) {
		// (a) SKy
		if (i == 0) { arena[i].Initialise(mSkybox, xSky, ySky, zSky); }
		//(b) Tribunes
		// (i) East Stand
		else if (i >= 1 && i <= 2) {
			arena[i].Initialise(mTribune1, xTri, yTri, zTri);
			arena[i].GetModel()->Scale(2.0f);
			arena[i].GetModel()->RotateY(90.f);
			zTri += 150;
			
		}
		// (ii) North Stand
		else if (i >= 3 && i <= 4) {
			xTri += 200;
			arena[i].Initialise(mTribune1, xTri, yTri, zTri);
			arena[i].GetModel()->Scale(2.0f);
			arena[i].GetModel()->RotateY(180.f);
			
		}
		// (iii) East Stand
		else if (i >= 5 && i <= 6) {
			xTri = 520;
			arena[i].Initialise(mTribune1, xTri, yTri, zTriE);
			arena[i].GetModel()->RotateY(-90.0f);
			arena[i].GetModel()->Scale(2.0f);
			zTriE -= 150;
		}

	}

	const int knIsleLeft = 16;
	CIsle isleL[knIsleLeft];

	float x = -18;
	float y = 0;
	float z = 10;
	

	// (a) Left Islef
	for (int i = 0; i < knIsleLeft; i++) {
		
			isleL[i].Initialise(mIsle, x, y, z);
			z += 13;
			isleL[i].GetModel()->SetSkin("tiles_red.jpg");
		}

	// (b) Right Islef

	const int knIsleRight = 29;
	CIsle isleR[knIsleRight];
	float x2 = 17.5;
	float z2 = 10;
	float x2R = 225;
	float z2R = 163;
	for (int i = 0; i < knIsleRight; i++) {
		if (i >= 11) {
			
			isleR[i].Initialise(mIsle, x2R, y, z2R);
			z2R -= 13;
		}
		else {
			isleR[i].Initialise(mIsle, x2, y, z2);
			z2 += 13;
		}
		isleR[i].GetModel()->SetSkin("tiles_red.jpg");
	}

	// (a) Wall Left
	const int knWallLeft = 145;
	CWall wallL[knWallLeft];
	float xWL = -18;
	float yWL = 0;
	float zWL = 14;
	float xWoutter = 424;
	float zWoutter = -112;
	for (int i = 0; i < knWallLeft; i++) {

		if (i >= 22 && i <= 32) { xWL += 10; zWL = 208;
		wallL[i].Initialise(mWall, xWL, yWL, zWL);
		wallL[i].GetModel()->RotateY(90.0f);
		}
		else if (i >= 33 && i<=65 ) {
			xWL += 10; zWL = 193;
			wallL[i].Initialise(mWall, xWL, yWL, zWL);
			wallL[i].GetModel()->RotateY(90.0f);
			
		}
		// Horizontal  
		else if (i >= 66 && i <= 95 ) {
			xWL = 428;
			zWL -= 10;
			wallL[i].Initialise(mWall, xWL, yWL, zWL);
		

		}
		else if (i >= 96) {
			
 			wallL[i].Initialise(mWall, xWoutter, yWL, zWoutter);
			wallL[i].GetModel()->RotateY(90.0f);
			xWoutter -= 9;
		}
	
		// Horizontal  
		else {

			wallL[i].Initialise(mWall, xWL, yWL, zWL);
			zWL += 9;
		}
		wallL[i].GetModel()->SetSkin("Tiles1.jpg");
	}

	// (b) Wall Right
	const int knWallRight = 82;
	CWall wallR[knWallRight];
	float xWR = 18;
	float yWR = 0;
	float zWR = 14;
	float xWR3 = 225;
	float zWR3 = 160;
	float xWInner = 218;
	float zWInner = -47;


	for (int i = 0; i < knWallRight; i++) {
		if (i >= 15 && i < 20) { xWR += 10; zWR = 138;
		wallR[i].Initialise(mWall, xWR, yWR, zWR);
		wallR[i].GetModel()->RotateY(90.0f);
		}// Horizontal RIGHT 
		else if (i >= 21 && i <= 22) {
			wallR[i].Initialise(mWall, xWR, yWR, zWR);
			zWR += 9;
		}

		else if (i >= 23 && i <= 37) {
			
			xWR += 10; zWR = 167;
			wallR[i].Initialise(mWall, xWR, yWR, zWR);
			wallR[i].GetModel()->RotateY(90.0f);
		}
		// Horizontal RIGHT 
		else if (i >= 38 && i <= 60) {
			wallR[i].Initialise(mWall, xWR3, yWR, zWR3);
			zWR3 -= 9;
			

		}
		else if (i >= 61) {
		
			wallR[i].Initialise(mWall, xWInner, yWR, zWInner);
			wallR[i].GetModel()->RotateY(90.0f);
			xWInner -= 9;
		}
		// Horizontal RIGHT 
		else  {
		wallR[i].Initialise(mWall, xWR, yWR, zWR);
		zWR += 9;
		}
		wallR[i].GetModel()->SetSkin("Tiles1.jpg");
	}

	// CheckPoints
	const int knCheckpoint = 5;
	CCheckpoint cpoint[knCheckpoint];
	float xCp = 0;
	float yCp = 0;
	float zCp = 0;

	float xCp2 = 90;
	float zCp2 = 180;

	float xCp3 = 210;
	float zCp3 = 50;

	float xCp4 = 370;
	float zCp4 = -60;

	for (int i = 0; i < knCheckpoint; i++) {

		if (i == 1) { 
			cpoint[i].Initialise(mCheckpoint, xCp2, yCp, zCp2);
			cpoint[i].GetModel()->RotateY(90.0f);
			cpoint[i].GetModel()->Scale(0.8f);
		}
		else if (i == 2) {
			cpoint[i].Initialise(mCheckpoint, xCp3, yCp, zCp2);
			cpoint[i].GetModel()->RotateY(90.0f);
			cpoint[i].GetModel()->Scale(0.8f);
		}
		else if (i == 3) {
			cpoint[i].Initialise(mCheckpoint, xCp4, yCp, zCp4);
			
		}
		else if (i == 4) {
			cpoint[i].Initialise(mCheckpoint, xCp2, yCp, -80);
			cpoint[i].GetModel()->RotateY(90.0f);
			cpoint[i].GetModel()->Scale(1.9f);
			

		}
		else {

			cpoint[i].Initialise(mCheckpoint, xCp, yCp, zCp);
		}
		cpoint[i].GetModel()->Scale(1.5f);	
		cpoint[i].GetModel()->SetSkin("tiles_half.jpg");
	}

	// Hover-Car

	const int knCars = 2;
	CCar car[knCars];
	float xCar = -5;
	float yCar = 3;
	float zCar = -20;
	int myCar = 0;
	int carOpponent = 1;
	for (int i = 0; i < knCars; i++) {
		car[i].Initialise(mCar, myEngine, xCar, yCar, zCar);
		xCar += 15;
	}
	car[carOpponent].GetCar()->SetSkin("gold.jpg");
	// Reference (skin)
	//Shutterstock. 2020.
	//4K Abstract Gold Copper Iron Stock Footage Video (100% Royalty-Free) 9102374 | Shutterstock. [online] Available at: 
	//<https://www.shutterstock.com/video/clip-9102374-4k-abstract-gold-copper-iron-metal-materials>
	//[Accessed 30 April 2020].




	// Quads ("particle system") --> users car
	const int knQuads = 100;
	float xQ = car[USER_CAR].GetX()+5;
	float yQ = car[USER_CAR].GetY();
	float zQ = car[USER_CAR].GetZ()+20;
	CQuad q[knQuads];
	float scale = 1.0f;
	for (int i = 0; i < knQuads; i++) {
		q[i].Initialise(mQuad ,xQ, yQ, zQ);
		q[i].GetModel()->Scale(scale);  // 4.0f
		q[i].GetModel()->AttachToParent(car[USER_CAR].GetCar());
		yQ += 0.02;
		zQ += 0.05;
		
		q[i].GetModel()->SetSkin("li.png"); 
		
		
		scale += 0.02f;
	}
	// REFERENCE SKIN
	//  Hiclipart.com. 2020. Sphere Ball Graphic Illustration, Lightning Sphere, Lightning Sphere Transparent Background PNG Clipart
	//| Hiclipart. [online] Available at: <https://www.hiclipart.com/free-transparent-background-png-clipart-ivicp>
	//[Accessed 30 April 2020].



	// Quads ("particle system") --> Rival car
	 xQ = car[RIVAL_CAR].GetX()-10;
	yQ = car[RIVAL_CAR].GetY();
	zQ = car[RIVAL_CAR].GetZ() + 20;
	CQuad qR[knQuads];
	scale = 1.0f;
	for (int i = 0; i < knQuads; i++) {
		qR[i].Initialise(mQuad, xQ, yQ, zQ);
		qR[i].GetModel()->Scale(scale);  // 4.0f
		qR[i].GetModel()->AttachToParent(car[RIVAL_CAR].GetCar());
		yQ += 0.02;
		zQ += 0.05;

		qR[i].GetModel()->SetSkin("blue.jpg"); // green1


		scale += 0.02f;
	}
	// REFERENCE (SKIN)
	// Google.com. 2020. Speed Line Anime Green - Google Search. [online] Available at:
	// <https://www.google.com/search?q=speed+line+anime++green&tbm=isch&ved=2ahUKEwjxwdOE7Y_pAhWP0YUKHUTRAnIQ2-cCegQIABAA&oq=speed+line+anime++green&gs_lcp=CgNpbWcQAzoECAAQHjoGCAAQCBAeUJfGAVjz1QFgn9cBaABwAHgAgAHmAYgBmgiSAQUwLjUuMZgBAKABAaoBC2d3cy13aXotaW1n&sclient=img&ei=X5yqXrGWMY-jlwTEoouQBw&bih=625&biw=1366&client=avast#imgrc=vAP80oWjV0qTOM&imgdii=lwCR7twTlgtN9M>
	// [Accessed 30 April 2020].


	// Corners 
	const int knCorners = 2;
	CIslesCorners corners[knCorners];
	float xT = 70;
	float yT = 0;
	float zT = 165;

	for (int i = 0; i < knCorners; i++) {
		
		// (a) Right Corner Before CP2
		if (i == 0)
		corners[i].Initialise(mIsleCorner, xT, yT, zT);
		// (b) Left Corner Before CP2
		else if ( i==1 )
		{
			corners[i].Initialise(mIsleCorner, xT + 25, yT, zT + 36);
			
		}
	}


	// Obstacles
	const int knOb = 40;
	CObstacle obstacles[knOb];
	float xO = 40;
	float yO = -10;
	float zO = 160;
	float xRow3 = 250;
	float zRow3 = 200;
	float xOSnake = 390;
	float zOSnake = 140;
	float xOSnakeOutter = 270;
	
	float xOc = -30;
	float yOc = 2;
	float zOc = -100;

	for (int i = 0; i < knOb; i++) {
		
		if (i == 0) {
			obstacles[i].Initialise(mTank, xO, yO, zO);
			obstacles[i].GetModel()->RotateZ(-30.0f);
			obstacles[i].GetModel()->RotateY(-45.0f);
			obstacles[i].GetModel()->Scale(1.0f);
		}
		else if (i >= 1 && i <= 4) {
			obstacles[i].Initialise(mTank2, xOSnake, yO, zOSnake);
			obstacles[i].GetModel()->RotateZ(30.0f);
			obstacles[i].GetModel()->RotateY(45.0f);
			xOSnake -= 10;
			
		}
		else if (i >= 5 && i <= 9) {
			zOSnake = 70;
			obstacles[i].Initialise(mTank2, xOSnakeOutter, yO, zOSnake);
			obstacles[i].GetModel()->RotateZ(-30.0f);
			obstacles[i].GetModel()->RotateY(-45.0f);
			xOSnakeOutter += 10;
			xOSnake = 360;
		}
		else if (i >= 10 && i <= 14) {
			zOSnake = 10;
			obstacles[i].Initialise(mTank2, xOSnake, yO, zOSnake);
			obstacles[i].GetModel()->RotateZ(30.0f);
			obstacles[i].GetModel()->RotateY(45.0f);
			xOSnake -= 10;
			xOSnakeOutter = 270;
		}
		else if (i >= 15 && i <= 16) {

			obstacles[i].Initialise(mTank2, xOc, yOc, zOc);
			obstacles[i].GetModel()->Scale(2.5f);
			zOc += 300;
		}
		else if (i == 17) {
			zOc = 200;
			xOc += 460;
			obstacles[i].Initialise(mTank2, xOc, yOc, zOc);
			obstacles[i].GetModel()->Scale(2.5f);
		}
		else if (i == 18) {
			xOc += 5;
			zOc -= 305;
			obstacles[i].Initialise(mTank2, xOc, yOc, zOc);
			obstacles[i].GetModel()->Scale(2.5f);

		}
		

		else  {
			obstacles[i].Initialise(mTank, xO+105, yO, zO+30);
			obstacles[i].GetModel()->RotateX(-30.0f);
			//obstacles[i].GetModel()->RotateY(45.0f);
			//obstacles[i].GetModel()->Scale(0.5f);

		}
		obstacles[i].GetModel()->SetSkin("RedGlow.jpg");

	}
	
	// Lamps ..
	const int knLamps = 17;
	CLamb lamp[knLamps];
	float xLamp = 30;
	float yLamp = 5;
	float zLamp = -40;
	float xLampOuter = -17;
	float zLampOuter = -110;
	for (int i = 0; i < knLamps; i++) {
		if (i <= 4) {
			lamp[i].Initialise(mLamp, xLamp, yLamp, zLamp);
			zLamp += 10;
			xLamp -= 3;
			lamp[i].GetModel()->RotateY(-30.0f);
			lamp[i].GetModel()->Scale(1.5f);
		}
		else {
			lamp[i].Initialise(mLamp, xLampOuter, yLamp, zLampOuter);
			zLampOuter += 10;
			lamp[i].GetModel()->Scale(1.5f);
		}
	}

	// Walkway ..
	const int knWalkway = 6;
	CWalway walkway[knWalkway];
	float xRoad = 240;
	float yRoad = 1;
	float zRoad = -80;
	for (int i = 0; i < knWalkway; i++) {
		walkway[i].Initialise(mWalk, xRoad, yRoad, zRoad);
		xRoad -= 25;
		walkway[i].GetModel()->Scale(5.5f);
		walkway[i].GetModel()->RotateY(90.0f);
		walkway[i].GetModel()->SetSkin("Fire.jpg");
	}


	// Sprite ..
	CSprite sBackDrop;
	sBackDrop.Initialise(myEngine, 70, 625);
	

	// Game ..
	CGame game(myEngine);
	game.SetState(INTRO_HIT_SPACE);

	// Vector..
	CVector3 xv (3.0f, 1.0f, 5.0f);
	CVector3 yv (1.0f, 0.0f, 1.0f);
	CVector3 zv = xv - yv;
	CVector3 av = xv * 2;
	CVector3 bv = xv / 2;

	// Camera ..
	CCameraU cam;
	cam.Initialise(myEngine);

	// Dummy ..
	const int knDummy = 7;
	CDummy dummy[knDummy];
	float xD = 0;
	float yD = 0;
	float zD = 90;
	int dummyCarB = 0;
	int dummyCarF = 6;
	int dummyCp = 0;
	for (int i = 0; i < knDummy; i++) {
		if (i == dummyCarB) {
			// (a) dummy at the back of the car
			dummy[i].Initialise(mDummy, car[myCar].GetX()+5, car[myCar].GetY()+5, car[myCar].GetZ() - 10);
			dummy[i].GetModel()->AttachToParent(car[myCar].GetCar());
		}
		// (b) dummy at the Front of the car
		else if (i == dummyCarF) {
			dummy[i].Initialise(mDummy, car[myCar].GetX() + 5, car[myCar].GetY(), car[myCar].GetZ() + 25);
			dummy[i].GetModel()->AttachToParent(car[myCar].GetCar());
		}
		// (c) check point dummy
		else if ( i >= 1 && i <= 5)
		{ dummy[i].Initialise(mDummy, cpoint[i-1].GetX(), cpoint[i-1].GetY(), cpoint[i-1].GetZ()); }
	}
	

	// Dummys Opponent Car WayPoints
	const int knWayPoints = 140;
	CDummy dWay[knWayPoints];
	float xWay = 5;
	float yWay = 5.5;
	float zWay = 10;

	for (int i = 0; i < knWayPoints; i++) {
		// 1) Road from Checkpoint 1 to Checkpoint 2
		if ( i < 4 ) {
			zWay +=45;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
			if (i == 3) zWay -= 13;
		}
		// 2) Before Checkpoint 2 and road through corridor 
		else if (i >= 4 && i < 18) {
			xWay += 20;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
			
		}
		// 3) After Checkpoint 3 -> Reach CPoint 4
			// (a) Pass from 1st & 2nd row of tanks
		else if (i >= 18 && i < 22) {
			zWay -= 20;
			xWay += 5;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
		}
			// (b) Pass from 3rd row of tanks -> Reach CP4
		else if (i >= 22 && i < 28) {
			xWay += 12;
			zWay -= 8;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
		}
			// (c) Pass 3rd row of tank
		else if (i >= 28 && i <= 35) {
			zWay -= 8;
			xWay += 5;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
			xWay -= 3;
		}
			// (d) Reach CP4
		else if ( i >= 36 && i < 43 ){
			zWay -= 11;
			xWay -= 5;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
		
		}
		// 4) Road from CP4 to Final CheckPoint
		else if (i >= 43 && i <= 102) {
			xWay -= 6;
			zWay -= 2;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
			zWay += 2.5;
		}
		// 5) Pass from Last Checkpoint - go find 1st dummyWaypoint and again the circle
		else if ( i >= 103 && i < 140 ) {
			zWay += 3;
			xWay += 0.3;
			dWay[i].Initialise(mDummy, xWay, yWay, zWay);
		}
	}

	// Dummies on checkpoint4's Legs (for collision)
	const int knDLegs = 2;
	CDummy cpLegs[knDLegs];
	float xLegs = 383.5;
	float yLegs = 0;
	float zLegs = -60;
	for (int i = 0; i < knDLegs; i++) {
		// RIGHT LEG
		if (i == 0) {
			cpLegs[i].Initialise(mDummy, xLegs, yLegs, zLegs);
			cpLegs[i].GetModel()->Scale(2.5f);
		}
		// LEFT LEG
		else if (i == 1) {
			xLegs -= 26;
			cpLegs[i].Initialise(mDummy, xLegs, yLegs, zLegs);
			cpLegs[i].GetModel()->Scale(2.5f);
		}
	}



	// Cross - Car Passed from CP
	CCross cross[knCheckpoint];
	for (int i = 0; i < knCheckpoint; i++) {
		cross[i].Initialiase(mCross, cpoint[i].GetX(), cpoint[i].GetY() - 10, cpoint[i].GetZ());
		if (i == CP1) {
			
			cross[i].SetTimer(0.0f);
		}
		// verical checkpoints --> rotate cross
		if (i == CP2 || i == CP3 || i == CP5)
			cross[i].GetModel()->RotateY(90.0f);
	}

	int indexDummyRoad= 0;
	int CarHasFinished = 0;
	

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		float dt = myEngine->Timer();
		// Draw the scene
		myEngine->DrawScene();

	
		
		m_poolBall->RotateY(dt*8);

		UpdateScene(car, cpoint, wallL, wallR, isleL, isleR, dt, knIsleRight, knIsleLeft, knWallLeft, knWallRight, game, myEngine,dummy,knDummy, dummyCarB, cam,
					corners, knCorners, obstacles, knOb, lamp, knLamps, knCars, myCar, dWay, knWayPoints, indexDummyRoad, CarHasFinished, cross, dummyCarF, cpLegs ,knDLegs,q, knQuads, qR, knCheckpoint);
	
		/**** Update your scene each frame here ****/

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
