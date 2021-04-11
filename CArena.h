// Alexandros Christou
// Declaration of class CArena
// 13 April 2020

#pragma once
#include <TL-Engine.h>

using namespace tle;
class CArena
{
public:
	// 1) Member Methods
	CArena () {};
	CArena(IMesh* mSkybox, float x, float y, float z);
	void Initialise(IMesh* mSkybox, float x, float y, float z);
	IModel* GetModel() { return m_model; }


private:
	// 2) Member Variables
	IModel* m_model;					// Model of Skybox

	
};

