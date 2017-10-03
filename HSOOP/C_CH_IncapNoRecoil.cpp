#include "C_CH_IncapNoRecoil.h"

C_CH_IncapNoRecoil::C_CH_IncapNoRecoil(int UniqueCheatID, C_CH_Aimbot* Aimbot) : C_Cheat(UniqueCheatID)
{
	this->Aimbot = Aimbot;

	bAccessed = Aimbot->IsAccessed();

	LoadConfiguration();
}

C_CH_IncapNoRecoil::~C_CH_IncapNoRecoil()
{
	perform();
}

void C_CH_IncapNoRecoil::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_INCAPNORECOIL_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();

	//perform();
}

void C_CH_IncapNoRecoil::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if (bCheat_Status && Aimbot->GetStatus() && Process->IsCheatEnabled() && bAccessed)
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL1_ShiftAddress), &INCAPNORECOIL1_ON, sizeof(INCAPNORECOIL1_ON), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL2_ShiftAddress), &INCAPNORECOIL2_ON, sizeof(INCAPNORECOIL2_ON), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL3_ShiftAddress), &INCAPNORECOIL3_ON, sizeof(INCAPNORECOIL3_ON), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL1_ShiftAddress), &INCAPNORECOIL1_OFF, sizeof(INCAPNORECOIL1_OFF), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL2_ShiftAddress), &INCAPNORECOIL2_OFF, sizeof(INCAPNORECOIL2_OFF), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + INCAPNORECOIL3_ShiftAddress), &INCAPNORECOIL3_OFF, sizeof(INCAPNORECOIL3_OFF), NULL);
	}
}