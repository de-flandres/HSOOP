#pragma once

#include "LicenseChecker.h"
//#include "CFG_GAMECVARS.h"
#include <cmath>

float Get3dDistance(float* myCoords, float* enemyCoords);

void CHEAT_INFO();
//void InjectInGameConfiguration();
void CalcAngle(float* src, float* dst, float* angles);
void SetNumLock(BOOL bState);

bool HasAccountCheat(int UniqueCheatID);