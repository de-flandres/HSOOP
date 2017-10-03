#include "C_MyPlayer.h"
#include "C_CH_ESP.h"

C_MyPlayer::C_MyPlayer()
{
	LoadConfiguration();

	Update();
	getTeam(true);
	getHealth(true);
	getEyeVector(true);
	getWTSMatrix(true);
	IsSpawned(true);
}

void C_MyPlayer::LoadConfiguration()
{

}

void C_MyPlayer::Update()
{
	getBase(true);
	getPosition(true);
	getYDiff(true);
}

DWORD C_MyPlayer::getBase(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_PlayerBase), &EntityBase, sizeof(DWORD), NULL);
	}
	return EntityBase;
}

float* C_MyPlayer::getEyeVector(bool FromMem)
{
	if(FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(getViewVectorAddress(true)), EyeVector, sizeof(float[3]), NULL);
	}
	return EyeVector;
}
DWORD C_MyPlayer::getViewVectorAddress(bool FromMem)
{
	if(FromMem)
	{
		ViewVectorAddress = Process->FindDMAAddress(1, Process->GetHandle(), dw_AngleRotation_Offsets, Process->dwordEngine + dw_AngleRotation);
	}
	return ViewVectorAddress;
}
WorldToScreenMatrix C_MyPlayer::getWTSMatrix(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordEngine + dw_antiFlick), &flickerCheck, sizeof(int), 0);
		if (flickerCheck == 1) ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordEngine + dw_vMatrix), &WorldToScreenMatrix, sizeof(WorldToScreenMatrix), 0);
	}
	return WorldToScreenMatrix;
}