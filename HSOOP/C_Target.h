#pragma once

#include "CFG_MAIN.h"

class C_Target
{
public:
	C_Target(int id, float aimbotAngle[], float myCoords[], float enemyCoords[], float AngToAngDist);

	float* GetAimbotAngle();
	float GetDistance();
	float GetAngToAngDist();

	int getIdInEnemyList();

private:
	float Distance;
	float AimbotAngle[3];
	float AngleToAngleDistance;
	int IdInEnemyList;

};