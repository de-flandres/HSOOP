#include "C_Target.h"

C_Target::C_Target(int id, float aimbotAngle[], float myCoords[], float enemyCoords[], float AngToAngDist)
{
	IdInEnemyList = id;

	AngleToAngleDistance = AngToAngDist;

	Distance = Get3dDistance(myCoords, enemyCoords);

	AimbotAngle[0] = aimbotAngle[0];
	AimbotAngle[1] = aimbotAngle[1];
	AimbotAngle[2] = aimbotAngle[2];
}

float* C_Target::GetAimbotAngle()
{
	return AimbotAngle;
}
float C_Target::GetDistance()
{
	return Distance;
}
int C_Target::getIdInEnemyList()
{
	return IdInEnemyList;
}
float C_Target::GetAngToAngDist()
{
	return AngleToAngleDistance;
}
