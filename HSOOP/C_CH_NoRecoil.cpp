#include "C_CH_NoRecoil.h"

C_CH_NoRecoil::C_CH_NoRecoil(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	LoadConfiguration();
}

C_CH_NoRecoil::~C_CH_NoRecoil()
{
	perform();
}

void C_CH_NoRecoil::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_NORECOIL_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();
}

void C_CH_NoRecoil::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return; //ExitThread(0);

	if (bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + RECOIL_ASSEMBLER), &RECOILOFF, sizeof(RECOILOFF), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + RECOIL_ASSEMBLER), &RECOILON, sizeof(RECOILON), NULL);
	}
}