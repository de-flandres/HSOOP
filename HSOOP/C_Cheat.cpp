#include "C_Cheat.h"

C_Cheat::C_Cheat(int UniqueCheatID)
{
	_iUniqueCheatID = UniqueCheatID;
	bCheat_Status = false;

	this->bAccessed = HasAccountCheat(_iUniqueCheatID);
	Process = C_HackProcess::GetHackedProcess();	// pattern singleton
}

C_Cheat::~C_Cheat()
{
	bCheat_Status = false;
}

void C_Cheat::changeStatusOfCurrentCheat()
{
	bCheat_Status = !bCheat_Status;
}

bool C_Cheat::GetStatus()
{
	return bCheat_Status;
}

string C_Cheat::GetStringStatus()
{
	if (bCheat_Status && Process->IsCheatEnabled()) return "ON";
	return "OFF";
}

bool C_Cheat::IsAccessed()
{
	return bAccessed;
}

void C_Cheat::setAccessed(bool NewAccessStatus)
{
	bAccessed = NewAccessStatus;
}

void C_Cheat::SetProcess(C_HackProcess* NewProcess)
{
	Process = NewProcess;
}

C_HackProcess* C_Cheat::GetProcess()
{
	return Process;
}