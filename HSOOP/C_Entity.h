#pragma once

#include "CFG_MAIN.h"

class C_Entity
{
public:
	virtual void LoadConfiguration() = 0;

	virtual int getHealth(bool FromMem);
	virtual int getTeam(bool FromMem);
	virtual int getCharType(bool FromMem);
	virtual int getWeaponID(bool FromMem);

	virtual bool setTeam(int NewTeam);
	virtual bool IsSpawned(bool FromMem);
	virtual bool IsAlive(bool FromMem);
	virtual bool setBase(DWORD NewBase);
	virtual bool IsEntityBaseExist();

	virtual float* getBonePos(int Bone_Num, bool FromMem);
	virtual float* getPosition(bool FromMem);

	virtual float getMaxSpeed(bool FromMem);
	virtual float getYDiff(bool FromMem);

	virtual string getName(bool FromMem);
	virtual string getCharTypeString(bool FromMem);

protected:
	C_Entity();

	C_HackProcess* Process;

	DWORD EntityBase;
	DWORD BoneBase;

	string name;

	byte LifeStatus;

	int Team;
	int Health;
	int Spawned;
	int CharacterType;
	int WeaponID;

	float flMaxSpeed;
	float Y_diff;
	float Position[3];
	float EyeVector[3];
	float Current_Bone_Pos[3];
};