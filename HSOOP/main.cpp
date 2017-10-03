#include "C_CH_ESP.h"
#include "C_CH_Aimbot.h"
#include "C_CH_IncapNoRecoil.h"
#include "C_CH_Fullbright.h"
#include "C_CH_GlowHack.h"
#include "C_CH_NoFog.h"
#include "C_CH_NoSmoke.h"
#include "C_CH_Ceiling.h"
#include "C_CH_BunnyHop.h"
#include "C_CH_NoRecoil.h"

//-------------------------------------------------------------------------------------------------------

void deleteCheats();

C_HackProcess* _Process;

C_CH_ESP* _ESP;
C_CH_Aimbot* _Aimbot;
C_CH_IncapNoRecoil* _IncapNoRecoil;
C_CH_Fullbright* _Fullbright;
C_CH_GlowHack* _GlowHack;
C_CH_NoFog* _NoFog;
C_CH_NoSmoke* _NoSmoke;
C_CH_Ceiling* _Ceiling;
C_CH_BunnyHop* _BunnyHop;
C_CH_NoRecoil* _NoRecoil;

void start_aimbot()
{
	//bool HuntingUsed = false;

	while(true)
	{
		if (_Aimbot != 0)
		{
			_Aimbot->perform();

			/*if (_Aimbot->getPlayer()->getWeaponID(true) == WEAPON_ID_HUNTINGRIFLE)
			{
				if (HuntingUsed == false)
				{
					_Aimbot->setRange(10000.0f);
					_Aimbot->setAutoMouse2(false);
					//_Aimbot->setAutoShoot(false);
					//_Aimbot->setType(SKIN);
					_Process->UpdateInfoPanel(true, true, clock());
					HuntingUsed = true;
				}
			}
			else
			{
				if (HuntingUsed == true)
				{
					//_Aimbot->LoadConfiguration();
					_Process->ConfigLoader->Open(ios::in);
					_Aimbot->setRange((float)_Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_RANGE].strParam));
					_Aimbot->setAutoMouse2(_Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_AUTOMOUSE2].strParam));
					//_Aimbot->setAutoShoot((bool)_Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_AUTOSHOOT].strParam));
					//_Aimbot->setType(_Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_TYPE].strParam));
					_Process->ConfigLoader->Close();
					_Process->UpdateInfoPanel(true, true, clock());
					HuntingUsed = false;
				}
			}*/
		}

		Sleep(1); // for saving processor
	}
}

void start_esp()
{
	/*const BYTE NOP[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };

	WriteProcessMemory(_Process->GetHandle(), (PBYTE*)(_Process->dwordClient+0x202337), &NOP, sizeof(NOP), NULL);
	WriteProcessMemory(_Process->GetHandle(), (PBYTE*)(_Process->dwordClient+0x202609), &NOP, sizeof(NOP), NULL);

	DWORD TempAdd_Offsets[] = { 0xF9C, 0xCC0 };
	DWORD TempAdd = _Process->FindDMAAddress(2, _Process->GetHandle(), TempAdd_Offsets, _Process->dwordClient + dw_PlayerBase);
	
	for(int i = 5; i <= 10; i++, i = i == 10 ? 5 : i)
	{*/
		//WriteProcessMemory(_Process->GetHandle(), (PBYTE*)TempAdd, &i, sizeof(4), NULL);
		//Sleep(1);
	while(true)
	{
		if(_ESP != 0) _ESP->perform();
		Sleep(1);
	}
}

void start_bunny()
{
	while(true)
	{
		if (_BunnyHop != 0) _BunnyHop->perform();
		//Sleep(0);
	}
}

void start_ceiling()
{
	while(true)
	{
		if (_Ceiling != 0) _Ceiling->perform();
		Sleep(30);
	}
}

void start_incapnorecoil()
{
	while(true)
	{
		if (_IncapNoRecoil != 0) _IncapNoRecoil->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}

void start_fullbright()
{
	while(true)
	{
		if (_Fullbright != 0) _Fullbright->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}

void start_glowhack()
{
	while(true)
	{
		if (_GlowHack != 0) _GlowHack->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}

void start_nofog()
{
	while(true)
	{
		if (_NoFog != 0) _NoFog->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}

void start_norecoil()
{
	while (true)
	{
		if (_NoRecoil != 0) _NoRecoil->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}


void start_nosmoke()
{
	while(true)
	{
		if (_NoSmoke != 0) _NoSmoke->perform();
		Sleep(STATIC_CHEATS_UPDATE_TIME);
	}
}

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)	// when press red close-cross
	{
		if(_Process != 0) deleteCheats();

		return TRUE;
	}

	return FALSE;
}

int main(int argc, char* argv[])
{
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);

  _Process = C_HackProcess::Hack(GetCurrentThreadId());		// pattern singleton
	thread LicenseThread(CheckLicense);

	_Aimbot = new C_CH_Aimbot(eAIM);						// the first than esp and incapnospread
	_ESP = new C_CH_ESP(eESP);
	_Ceiling = new C_CH_Ceiling(eCEILING);
	_BunnyHop = new C_CH_BunnyHop(eBH);
	_IncapNoRecoil = new C_CH_IncapNoRecoil(eINCAPNORECOIL, _Aimbot);	// after aim
	_Fullbright = new C_CH_Fullbright(eFB);
	_GlowHack = new C_CH_GlowHack(eGLOW);
	_NoFog = new C_CH_NoFog(eNOFOG);
	_NoSmoke = new C_CH_NoSmoke(eNOSMOKE);
	_NoRecoil = new C_CH_NoRecoil(eNORECOIL);

	thread BunnyHopThread(start_bunny);
	thread AimbotThread(start_aimbot);
	thread ESPThread(start_esp);
	thread CeilingThread(start_ceiling);
	thread IncapNoRecoilThread(start_incapnorecoil);
	thread FullbrightThread(start_fullbright);
	thread GlowHackThread(start_glowhack);
	thread NoFogThread(start_nofog);
	thread NoSmokeThread(start_nosmoke);
	thread NoRecoilThread(start_norecoil);

	while (GetAsyncKeyState(_Process->iCheat_Key_Exit) == false)
	{
		SetNumLock(true);

		if (clock() - _Process->GameAvailTIMER > UPDATE_TIME)
		{
			if (getCurrentAccountID() != INVALID_ACCOUNT_ID)
			{
				_Aimbot->setAccessed(HasAccountCheat(eAIM));
				_ESP->setAccessed(HasAccountCheat(eESP));
				_Ceiling->setAccessed(HasAccountCheat(eCEILING));
				_BunnyHop->setAccessed(HasAccountCheat(eBH));
				_IncapNoRecoil->setAccessed(HasAccountCheat(eINCAPNORECOIL));
				_Fullbright->setAccessed(HasAccountCheat(eFB));
				_GlowHack->setAccessed(HasAccountCheat(eGLOW));
				_NoFog->setAccessed(HasAccountCheat(eNOFOG));
				_NoSmoke->setAccessed(HasAccountCheat(eNOSMOKE));
				_NoRecoil->setAccessed(HasAccountCheat(eNORECOIL));

				_Aimbot->SetProcess(_Process);
				_ESP->SetProcess(_Process);
				_Ceiling->SetProcess(_Process);
				_BunnyHop->SetProcess(_Process);
				_IncapNoRecoil->SetProcess(_Process);
				_Fullbright->SetProcess(_Process);
				_GlowHack->SetProcess(_Process);
				_NoFog->SetProcess(_Process);
				_NoSmoke->SetProcess(_Process);
				_NoRecoil->SetProcess(_Process);
			}

			_Process->UpdateStatus(); // for check if game closed(for new game process)

			if (_Process->NeedToUpdate())
			{
				CHEAT_INFO();
												cout << "\tSTATUS:\t\t"								<< _Process->HackStatus												<< endl;
				if (HasAccountCheat(eESP))		cout << "\t[NUM_0]\t\tESP\t\t\t[ "					<< _ESP->GetStringStatus()									<< " ]" << endl;
				if (HasAccountCheat(eFB))		cout << "\t[NUM_1]\t\tFULLBRIGHT\t\t[ "				<< _Fullbright->GetStringStatus()							<< " ]" << endl;
				if (HasAccountCheat(eNOSMOKE))	cout << "\t[NUM_2]\t\tNOSMOKE\t\t\t[ "				<< _NoSmoke->GetStringStatus()								<< " ]" << endl;
				if (HasAccountCheat(eNOFOG))	cout << "\t[NUM_3]\t\tNOFOG\t\t\t[ "				<< _NoFog->GetStringStatus()								<< " ]" << endl;
				if (HasAccountCheat(eGLOW))		cout << "\t[NUM_4]\t\tGLOWHACK\t\t[ "				<< _GlowHack->GetStringStatus()								<< " ]" << endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM_5]\t\tAIMBOT\t\t\t[ "				<< _Aimbot->GetStringStatus()								<< " ]" << endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM_6]\t\tAIMBOT TYPE\t\t[ "			<< (_Aimbot->GetAimbotType() == SKIN ? "SKIN" : "HITBOX")	<< " ]"	<< endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM_7, NUM8]\tAIMBOT SMOOTH\t\t[ "		<< _Aimbot->GetAimSmooth()									<< " ]"	<< endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM_9]\t\tAIMBOT AUTOSHOOT\t[ "			<< (_Aimbot->GetAimbotAutoShoot() ? "ON" : "OFF")			<< " ]"	<< endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM/ NUM*]\tAIMBOT RANGE\t\t[ "			<< _Aimbot->GetAimRange()									<< " ]" << endl;
				if (HasAccountCheat(eAIM))		cout << "\t[NUM+ NUM-]\tAIMBOT ANGLE\t\t[ "			<< _Aimbot->GetAimAngle()									<< " ]" << endl;
				if (HasAccountCheat(eAIM))		cout << "\t[PAUSEBREAK]\tAUTO-M2\t\t\t[ "			<< (_Aimbot->GetAutoMouse2() ? "ON" : "OFF")				<< " ]"	<< endl;
				if (HasAccountCheat(eAIM))		cout << "\t[R_ALT, R_CTRL]\tAIMBOT BONE_NUM\t\t[ "	<< _Aimbot->GetBoneNum()									<< " ]" << endl;
				if (HasAccountCheat(eBH))		cout << "\t[L_ALT]\t\tBUNNYHOP"																							<< endl;
				if (HasAccountCheat(eCEILING))	cout << "\t[CAPSLOCK]\tAUTO_SEILING"																					<< endl;
												cout << "\t[F3]\t\tRELOAD CONFIG"																						<< endl;
												cout << "\t[DELETE, END]\tON/OFF, Exit"																					<< endl;

				_Process->UpdateOnNextRun(false);
				_Process->TimeSinceLastUpdate = clock();
			}

			if (_Process->IsGameAvail())
			{
				_Process->GetGameScreenResolution(0, true);

				if (GetAsyncKeyState(_Process->iCheat_Key_Turn))
				{
					_Process->SetCheatEnabled(!_Process->IsCheatEnabled());
					_Process->UpdateInfoPanel(_Process->IsCheatEnabled(), true, clock());

					_Fullbright->perform();
					_IncapNoRecoil->perform();
					_NoSmoke->perform();
					_NoFog->perform();
					_GlowHack->perform();
					_NoRecoil->perform();
				}
				else if (GetAsyncKeyState(_Process->iCheat_Key_ReloadConfig))
				{
					_Process->LoadConfiguration();

					_Fullbright->LoadConfiguration();
					_IncapNoRecoil->LoadConfiguration();
					_NoSmoke->LoadConfiguration();
					_NoFog->LoadConfiguration();
					_GlowHack->LoadConfiguration();
					_NoRecoil->LoadConfiguration();

					_ESP->LoadConfiguration();
					_Aimbot->LoadConfiguration();
					_Ceiling->LoadConfiguration();
					_BunnyHop->LoadConfiguration();

					_Process->UpdateInfoPanel(_Process->IsCheatEnabled(), true, clock());
				}
			}
		} // updater
	} // while !EXIT_KEY

	//_Process->UpdateInfoPanel(false, false, 0);

	LicenseThread.detach();
	
	IncapNoRecoilThread.detach();
	FullbrightThread.detach();
	GlowHackThread.detach();
	NoFogThread.detach();
	NoSmokeThread.detach();

	BunnyHopThread.detach();
	AimbotThread.detach();
	ESPThread.detach();
	CeilingThread.detach();
	NoRecoilThread.detach();

	deleteCheats(); // !!!
}

void deleteCheats()
{
	_Process->SetCheatEnabled(false);

	if (_ESP != 0) delete _ESP;
	if (_IncapNoRecoil != 0) delete _IncapNoRecoil;
	if (_Aimbot != 0) delete _Aimbot;
	if (_Fullbright != 0) delete _Fullbright;
	if (_GlowHack != 0) delete _GlowHack;
	if (_NoFog != 0) delete _NoFog;
	if (_NoSmoke != 0) delete _NoSmoke;
	if (_Ceiling != 0) delete _Ceiling;
	if (_BunnyHop != 0) delete _BunnyHop;
	if (_NoRecoil != 0) delete _NoRecoil;
	if (_Process != 0) delete _Process;
}