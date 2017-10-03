#pragma once

#include <string>

#include "C_HackProcess.h"
#include "CFG_MAIN.h"

using namespace std;

#define UNDEFINED_CHEAT_ID -1

class C_Cheat
{
public:
	virtual void perform() = 0;
	virtual void LoadConfiguration() = 0;

	virtual void SetProcess(C_HackProcess* NewProcess);
	virtual C_HackProcess* GetProcess();

	virtual void changeStatusOfCurrentCheat();
	virtual bool GetStatus();
	virtual string GetStringStatus();

	virtual bool IsAccessed();
	virtual void setAccessed(bool NewAccessStatus);

protected:
	C_Cheat(int UniqueCheatID = UNDEFINED_CHEAT_ID);
	~C_Cheat();

	C_HackProcess* Process;

	string strCheat_StringStatus;
	bool bCheat_Status;
	bool bAccessed;

	int _iUniqueCheatID;
};