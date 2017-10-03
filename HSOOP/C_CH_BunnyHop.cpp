#include "C_CH_BunnyHop.h"
#include "CFG_MAIN.h"

C_CH_BunnyHop::C_CH_BunnyHop(int UniqueCheatID) : C_Cheat_KeyUsing(UniqueCheatID)
{
	LoadConfiguration();
}

void C_CH_BunnyHop::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_BUNNYHOP_ENABLED].strParam) == 0 ? false : true;
	iCheat_Key_Use = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_BUNNYHOP_KEY_USE].strParam);
	Process->ConfigLoader->Close();
}

void C_CH_BunnyHop::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if(bCheat_Status && Process->IsCheatEnabled() &&
		bAccessed/* &&
		Process->IsGameChatOpened() == false &&
		Process->IsGamePaused() == false &&
		Process->IsSteamOverlayOpened() == false*/)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_IsOnFloor), &iIsPlayerOnFloor, sizeof(int), 0);
		// readmemory теперь тут (работает)

		if (GetAsyncKeyState(iCheat_Key_Use))
		{
			// а был тут (тоже работает, но хз)

			if (iIsPlayerOnFloor == 1)
			{
				WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_Jump), &ACTION_PLUS, sizeof(int), 0);
				//keybd_event(VK_LCONTROL, MapVirtualKeyEx(VK_LCONTROL, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
				//keybd_event(VK_SPACE, MapVirtualKeyEx(VK_SPACE, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
				//keybd_event(VK_LCONTROL, MapVirtualKeyEx(VK_LCONTROL, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
			}
			if (iIsPlayerOnFloor == 0)
			{
				//keybd_event(VK_SPACE, MapVirtualKeyEx(VK_SPACE, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
				WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_Jump), &ACTION_MINUS, sizeof(int), 0);
			}
		}
	}
}