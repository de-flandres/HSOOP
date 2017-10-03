#pragma once

#include "C_Entity.h"

class C_Enemy : public C_Entity
{
public:
	C_Enemy(int Player);

	void Update(int Player);
	void LoadConfiguration();

	float* getPosition(bool FromMem);
	float* getAimbotAngle();

	COLORREF getESPColor();

	DWORD getBase(int Player, bool FromMem);

private:
	float AimbotAngle[3];
	
	COLORREF ESPColor;

	int iColor_Smoker_Ghost_R;
	int iColor_Smoker_Ghost_G;
	int iColor_Smoker_Ghost_B;
	int iColor_Smoker_Spawned_R;
	int iColor_Smoker_Spawned_G;
	int iColor_Smoker_Spawned_B;

	int iColor_Boomer_Ghost_R;
	int iColor_Boomer_Ghost_G;
	int iColor_Boomer_Ghost_B;
	int iColor_Boomer_Spawned_R;
	int iColor_Boomer_Spawned_G;
	int iColor_Boomer_Spawned_B;

	int iColor_Hunter_Ghost_R;
	int iColor_Hunter_Ghost_G;
	int iColor_Hunter_Ghost_B;
	int iColor_Hunter_Spawned_R;
	int iColor_Hunter_Spawned_G;
	int iColor_Hunter_Spawned_B;

	int iColor_Tank_Ghost_R;
	int iColor_Tank_Ghost_G;
	int iColor_Tank_Ghost_B;
	int iColor_Tank_Spawned_R;
	int iColor_Tank_Spawned_G;
	int iColor_Tank_Spawned_B;

};