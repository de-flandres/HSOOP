#define _USE_MATH_DEFINES

#include "StaticFunctions.h"

/*void InjectInGameConfiguration()
{
	C_HackProcess* Process = C_HackProcess::_instance;
	HANDLE Handle = Process->GetHandle();

	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_rate), &rate, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_cl_cmdrate), &cl_cmdrate, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_cl_updaterate), &cl_updaterate, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_interp_ratio), &cl_interp_ratio, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_interp), &cl_interp, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_cl_resend), &cl_resend, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_lagcompensation), &cl_lagcompensation, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_cl_timeout), &cl_timeout, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_net_maxroutable), &net_maxroutable, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_net_splitrate), &net_splitrate, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_net_splitpacket_maxrate), &net_splitpacket_maxrate, sizeof(int), NULL);

	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_cl_forcepreload), &cl_forcepreload, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_ragdoll_limit), &cl_ragdoll_limit, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_con_enable), &con_enable, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordEngine + dw_dsp_enhance_stereo), &dsp_enhance_stereo, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_func_break_max_pieces), &func_break_max_pieces, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordMaterialSys + dw_mat_monitorgamma_tv_enabled), &mat_monitorgamma_tv_enabled, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordStdshader_dx9 + dw_mat_grain_scale_override), &mat_grain_scale_override, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_spec_allowroaming), &spec_allowroaming, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_sk_autoaim_mode), &sk_autoaim_mode, sizeof(int), NULL);

	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_rawinput), &m_rawinput, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_filter), &m_filter, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_mouseaccel1), &m_mouseaccel1, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_mouseaccel2), &m_mouseaccel2, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_customaccel), &m_customaccel, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_mousespeed), &m_mousespeed, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_pitch), &m_pitch, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_m_yaw), &m_yaw, sizeof(float), NULL);

	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_autohelp), &cl_autohelp, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_gameinstructor_enable), &gameinstructor_enable, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_hidemenu_spawnmode), &cl_hidemenu_spawnmode, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_hidemenu_spawnclass_hunter), &cl_hidemenu_spawnclass_hunter, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_hidemenu_spawnclass_smoker), &cl_hidemenu_spawnclass_smoker, sizeof(int), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_hidemenu_spawnclass_boomer), &cl_hidemenu_spawnclass_boomer, sizeof(int), NULL);

	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_r), &cl_glow_item_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_g), &cl_glow_item_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_b), &cl_glow_item_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_far_r), &cl_glow_item_far_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_far_g), &cl_glow_item_far_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_item_far_b), &cl_glow_item_far_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_hurt_r), &cl_glow_survivor_hurt_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_hurt_g), &cl_glow_survivor_hurt_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_hurt_b), &cl_glow_survivor_hurt_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_vomit_r), &cl_glow_survivor_vomit_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_vomit_g), &cl_glow_survivor_vomit_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_vomit_b), &cl_glow_survivor_vomit_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_ghost_infected_r), &cl_glow_ghost_infected_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_ghost_infected_g), &cl_glow_ghost_infected_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_ghost_infected_b), &cl_glow_ghost_infected_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_r), &cl_glow_infected_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_g), &cl_glow_infected_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_b), &cl_glow_infected_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_vomit_r), &cl_glow_infected_vomit_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_vomit_g), &cl_glow_infected_vomit_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_infected_vomit_b), &cl_glow_infected_vomit_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_r), &cl_glow_survivor_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_g), &cl_glow_survivor_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_b), &cl_glow_survivor_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_high_r), &cl_glow_survivor_health_high_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_high_g), &cl_glow_survivor_health_high_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_high_b), &cl_glow_survivor_health_high_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_med_r), &cl_glow_survivor_health_med_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_med_g), &cl_glow_survivor_health_med_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_med_b), &cl_glow_survivor_health_med_b, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_low_r), &cl_glow_survivor_health_low_r, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_low_g), &cl_glow_survivor_health_low_g, sizeof(float), NULL);
	WriteProcessMemory(Handle, (PBYTE*)(Process->dwordClient + dw_cl_glow_survivor_health_low_b), &cl_glow_survivor_health_low_b, sizeof(float), NULL);
}*/

float Get3dDistance(float* me, float* enemy)
{
	return (float)sqrt(
					pow(double(enemy[0] - me[0]), 2.0) +
					pow(double(enemy[1] - me[1]), 2.0) +
					pow(double(enemy[2] - me[2]), 2.0)
				);
}

void CalcAngle(float *from, float *to, float *angles)
{
    double delta[3] =
	{
		(from[0]-to[0]),
		(from[1]-to[1]),
		(from[2]-to[2])
	};

    double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
    angles[0] = (float)(atan(delta[2]/hyp) * (180.0f / M_PI));
    angles[1] = (float)(atan(delta[1]/delta[0]) * (180.0f / M_PI));
    angles[2] = 0.0f;
 
    if(delta[0] >= 0.0) angles[1] += 180.0f;
}

void SetNumLock(BOOL bState)
{
	/*if ((bState && !(keyState[VK_NUMLOCK] & 1))) ||
		(!bState && (keyState[VK_NUMLOCK] & 1)))*/
	if (bState && !(GetKeyState(VK_NUMLOCK) & 1))
	{
		keybd_event(VK_NUMLOCK, MapVirtualKeyEx(VK_NUMLOCK, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE, 0);
		keybd_event(VK_NUMLOCK, MapVirtualKeyEx(VK_NUMLOCK, MAPVK_VK_TO_VSC_EX, 0), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);

		/*// Simulate a key press
		keybd_event(VK_NUMLOCK,
			0x45,
			KEYEVENTF_EXTENDEDKEY | 0,
			0);

		// Simulate a key release
		keybd_event(VK_NUMLOCK,
			0x45,
			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
			0);*/
	}
}

void CHEAT_INFO()
{
	system("cls");
	//Sleep(10); // between cls and echo
	cout << "------------------------------------------------------------------------" << endl;
	cout << "\t        " CHEAT_NAME " " CHEAT_VERSION " " GAME_WINDOW_NAME " by aXe  " << endl;
	cout << "\t                    Awakening Pulse L4D-Team                          " << endl;
	cout << "\t               Engine, KpuoH, Bruce, Modest, aXe                      " << endl;
	cout << "------------------------------------------------------------------------" << endl;

	int temp_id = getCurrentAccountID();

	if (temp_id != INVALID_ACCOUNT_ID)
	{
		if (LICENSED_ACCOUNTS[temp_id].bSUBSCRIPTION_CHECK)
		{
			cout << "\tEXPIRE STATUS:\t[ "
				<< LICENSED_ACCOUNTS[temp_id].iDATE_LICENSE[0] << "."
				<< LICENSED_ACCOUNTS[temp_id].iDATE_LICENSE[1] << "."
				<< LICENSED_ACCOUNTS[temp_id].iDATE_LICENSE[2] << ", "

				<< LICENSED_ACCOUNTS[temp_id].iTIME_LICENSE[0] << ":"
				<< LICENSED_ACCOUNTS[temp_id].iTIME_LICENSE[1] << ":"
				<< LICENSED_ACCOUNTS[temp_id].iTIME_LICENSE[2] << " UTC+00 ]" << endl;
		}
		else
		{
			cout << "\tEXPIRE STATUS:\t[ LIFETIME ]" << endl;
		}
		cout << "\tACCOUNT:\t[ " << LICENSED_ACCOUNTS[temp_id].sNICKNAME << " ]" << endl;
	}
	else
	{
		cout << "\tEXPIRE STATUS:\t[ UNKNOWN ]" << endl;
		cout << "\tACCOUNT:\t[ UNKNOWN ]" << endl;
	}
}

bool HasAccountCheat(int UniqueCheatID)
{
	int CurrentAccount = getCurrentAccountID();
	int NumOfAvailCheats = sizeof(LICENSED_ACCOUNTS[CurrentAccount].iAVAIL_CHEATS) / sizeof(int); // 10 for all Accounts
	
	for (int i = 0; i < NumOfAvailCheats; i++)
	{
		if (LICENSED_ACCOUNTS[CurrentAccount].iAVAIL_CHEATS[i] == UniqueCheatID)
		{
			return true;
		}
	}

	return false;
}