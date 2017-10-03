#include "C_CH_Ceiling.h"

C_CH_Ceiling::C_CH_Ceiling(int UniqueCheatID) : C_Cheat_KeyUsing(UniqueCheatID)
{
	Player = new C_MyPlayer();
	IsCeilingNow = false;

	LoadConfiguration();
	OneClickTIMER = clock();
}

C_CH_Ceiling::~C_CH_Ceiling()	// destructor
{
	delete Player;
}

void C_CH_Ceiling::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_CEILING_ENABLED].strParam) == 0 ? false : true;
	iCheat_Key_Use = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_CEILING_KEY_USE].strParam);
	ClickPauseInMS = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_CEILING_CLICKPAUSE].strParam);
	Process->ConfigLoader->Close();
}

void C_CH_Ceiling::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return; //ExitThread(0);

	if (bCheat_Status && Process->IsCheatEnabled() &&
		bAccessed &&
		Process->IsGameChatOpened() == false &&
		Process->IsGamePaused() == false &&
		Process->IsSteamOverlayOpened() == false)
	{
		if (GetAsyncKeyState(iCheat_Key_Use))
		{
			Player->getBase(true);
			if (Player->getTeam(true) == TEAM_INFECT && Player->getCharType(true) == CHARACTER_TYPE_HUNTER && Player->IsAlive(true) == true)
			{
				if (IsCeilingNow == false)
				{
					WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordEngine + MOUSE_ASSEMBLER), &MOUSEOFF, sizeof(MOUSEOFF), NULL);
					IsCeilingNow = true;
				}
				if (clock() - OneClickTIMER > ClickPauseInMS)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					OneClickTIMER = clock();
				}
			}
		}
		else
		{
			if (IsCeilingNow == true)
			{
				WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordEngine + MOUSE_ASSEMBLER), &MOUSEON, sizeof(MOUSEON), NULL);
				IsCeilingNow = false;
			}
		}
	}
}