#pragma once

#include "C_Target.h"
#include "C_MyPlayer.h"
#include "C_Enemy.h"
#include "C_Cheat_KeyUsing.h"

//-------AIMBOT VARS-----------------------------------------------------------------------------------

class C_CH_Aimbot : public C_Cheat_KeyUsing
{
public:
	C_CH_Aimbot(int UniqueCheatID);
	~C_CH_Aimbot();

	void perform();
	void LoadConfiguration();
	void sort();

	void setType(int NewType);
	void changeBoneNum(int ExtraBoneNum);
	void changeAngle(float ExtraAngle);
	void changeSmooth(float ExtraSmooth);
	void changeRange(float ExtraRange);
	void setAngle(float NewAngle);
	void setSmooth(float NewSmooth);
	void setRange(float NewRange);
	void setAutoShoot(bool NewAutoShootStatus);
	void setAutoMouse2(bool NewMode);
	void CalculateAngles();

	float GetAimRange();
	float GetAimAngle();
	float GetAimSmooth();

	int GetBoneNum();
	int GetAimbotType();

	bool GetAimbotAutoShoot();
	bool GetAutoMouse2();

	C_MyPlayer* getPlayer();
	C_Enemy** getEnemyList();
	C_Target** getTargetList();

private:
	C_MyPlayer* Player;
	C_Enemy* EnemyList[MAX_PLAYERS];
	C_Target* TargetList[MAX_PLAYERS];

	float flRange;
	float flAngle;
	float flSmooth;
	float difference_1;
	float difference_2;
	float AngToAngDst;

	bool bAimbot_UsedOnce;
	bool bAimbot_AutoShoot;
	bool bAimbot_AutoMouse2;

	int targets_count;
	int iAimbot_Type;
	int iBoneNum;

	int TimeSinceLastShoot;
};