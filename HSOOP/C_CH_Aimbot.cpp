#include "C_CH_Aimbot.h"

C_CH_Aimbot::C_CH_Aimbot(int UniqueCheatID) : C_Cheat_KeyUsing(UniqueCheatID)
{
	Player = new C_MyPlayer();
	for(int i = 0; i < MAX_PLAYERS; i++) EnemyList[i] = new C_Enemy(i);

	LoadConfiguration();

	bAimbot_UsedOnce = false;					// false as default
}

C_CH_Aimbot::~C_CH_Aimbot()	// destructor
{
	delete Player;
	for(int i = 0; i < MAX_PLAYERS; i++) delete EnemyList[i];
}

void C_CH_Aimbot::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_ENABLED].strParam) == 0 ? false : true;
	bAimbot_AutoShoot = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_AUTOSHOOT].strParam) == 0 ? false : true;
	bAimbot_AutoMouse2 = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_AUTOMOUSE2].strParam) == 0 ? false : true;
	iCheat_Key_Use = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_KEY_USE].strParam);
	iAimbot_Type = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_TYPE].strParam);
	iBoneNum = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_BONUENUM].strParam);
	flRange = (float)Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_RANGE].strParam);
	flAngle = (float)Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_ANGLE].strParam);
	flSmooth = (float)Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_AIMBOT_SMOOTH].strParam);
	Process->ConfigLoader->Close();
}

void C_CH_Aimbot::sort()
{
	C_Target* temp;
	for (int i = 0; i < targets_count - 1; i++)
	{
		for (int j = 0; j < targets_count - i - 1; j++)
		{
			if (TargetList[j]->GetAngToAngDist() > TargetList[j + 1]->GetAngToAngDist())
			{
				temp = TargetList[j];
				TargetList[j] = TargetList[j + 1];
				TargetList[j + 1] = temp;
			}
		}
	}
}

void C_CH_Aimbot::CalculateAngles()
{
	targets_count = 0;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		Player->Update();
		EnemyList[i]->Update(i);

		if (EnemyList[i]->getTeam(true) == Player->getTeam(true) || EnemyList[i]->getTeam(false) == TEAM_SPEC) continue;

		if (EnemyList[i]->IsSpawned(true) == false) continue;

		CalcAngle(Player->getPosition(true), EnemyList[i]->getBonePos(iBoneNum, true), EnemyList[i]->getAimbotAngle());

		difference_1 = fmod((EnemyList[i]->getAimbotAngle()[0] - Player->getEyeVector(true)[0]), 360.0f);
		difference_2 = fmod((EnemyList[i]->getAimbotAngle()[1] - Player->getEyeVector(false)[1]), 360.0f);
		if (difference_1 >= 180.0f) difference_1 -= 360.0f; // if (difference_1 > 180.0f) difference_1 -= 360.0f;
		if (difference_2 >= 180.0f) difference_2 -= 360.0f; // if (difference_2 > 180.0f) difference_2 -= 360.0f;
		AngToAngDst = (float)sqrt(pow(double(difference_1), 2.0) + pow(double(difference_2), 2.0));
		
		TargetList[targets_count] = new C_Target(i, EnemyList[i]->getAimbotAngle(), Player->getPosition(true), EnemyList[i]->getPosition(true), AngToAngDst);
		targets_count++;
	}

	if (targets_count > 0)	sort();				// sorting !!!
}

void C_CH_Aimbot::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(AIMBOT_TURN_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_TYPE_BUTTON))
			{
				setType((GetAimbotType() == SKIN ? HITBOX : SKIN));
				Process->UpdateInfoPanel(true, true, clock());

			}
			else if (GetAsyncKeyState(AIMBOT_AUTOSHOOT_BUTTON))
			{
				setAutoShoot((GetAimbotAutoShoot() == false ? true : false));
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_ANGLE_PLUS))
			{
				if (GetAimAngle() < 6) changeAngle(1.0);
				else if (GetAimAngle() >= 6 && GetAimAngle() < 20) changeAngle(2.0);
				else if (GetAimAngle() >= 20 && GetAimAngle() < 40) changeAngle(4.0);
				else if (GetAimAngle() >= 40 && GetAimAngle() < 80) changeAngle(8.0);
				else if (GetAimAngle() >= 80 && GetAimAngle() < 180) changeAngle(12.0);
				else changeAngle(20.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_ANGLE_MINUS))
			{
				if (GetAimAngle() < 6) changeAngle(-1.0);
				else if (GetAimAngle() >= 6 && GetAimAngle() < 20) changeAngle(-2.0);
				else if (GetAimAngle() >= 20 && GetAimAngle() < 40) changeAngle(-4.0);
				else if (GetAimAngle() >= 40 && GetAimAngle() < 80) changeAngle(-8.0);
				else if (GetAimAngle() >= 80 && GetAimAngle() < 180) changeAngle(-12.0);
				else changeAngle(-20.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_RANGE_PLUS))
			{
				changeRange(100.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_RANGE_MINUS))
			{
				changeRange(-100.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_SMOOTH_PLUS))
			{
				if (GetAimSmooth() < 6) changeSmooth(1.0);
				else if (GetAimSmooth() >= 6 && GetAimSmooth() < 20) changeSmooth(2.0);
				else if (GetAimSmooth() >= 20 && GetAimSmooth() < 40) changeSmooth(4.0);
				else if (GetAimSmooth() >= 40 && GetAimSmooth() < 80) changeSmooth(8.0);
				else if (GetAimSmooth() >= 80 && GetAimSmooth() < 180) changeSmooth(12.0);
				else if (GetAimSmooth() >= 180 && GetAimSmooth() < 360) changeSmooth(20.0);
				else if (GetAimSmooth() >= 360 && GetAimSmooth() < 1000) changeSmooth(50.0);
				else if (GetAimSmooth() >= 1000 && GetAimSmooth() < 5000) changeSmooth(100.0);
				else changeSmooth(1000.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_SMOOTH_MINUS))
			{
				if (GetAimSmooth() < 6) changeSmooth(-1.0);
				else if (GetAimSmooth() >= 6 && GetAimSmooth() < 20) changeSmooth(-2.0);
				else if (GetAimSmooth() >= 20 && GetAimSmooth() < 40) changeSmooth(-4.0);
				else if (GetAimSmooth() >= 40 && GetAimSmooth() < 80) changeSmooth(-8.0);
				else if (GetAimSmooth() >= 80 && GetAimSmooth() < 180) changeSmooth(-12.0);
				else if (GetAimSmooth() >= 180 && GetAimSmooth() < 360) changeSmooth(-20.0);
				else if (GetAimSmooth() >= 360 && GetAimSmooth() < 1000) changeSmooth(-50.0);
				else if (GetAimSmooth() >= 1000 && GetAimSmooth() < 5000) changeSmooth(-100.0);
				else changeSmooth(-1000.0);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_BONENUM_PLUS))
			{
				changeBoneNum(1);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_BONENUM_MINUS))
			{
				changeBoneNum(-1);
				Process->UpdateInfoPanel(true, true, clock());
			}
			else if (GetAsyncKeyState(AIMBOT_MOUSE2MODE_BUTTON))
			{
				setAutoMouse2(!GetAutoMouse2());
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}

	if(bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		if(GetAsyncKeyState(iCheat_Key_Use)/* &&
			Process->IsGameChatOpened() == false &&
			Process->IsGamePaused() == false &&
			Process->IsSteamOverlayOpened() == false*/)
		{
			Player->getBase(true);

			if (Player->getTeam(true) == TEAM_SURV)
			{
				CalculateAngles(); // !!!
				if (targets_count > 0)
				{
					if (TargetList[0]->GetDistance() <= flRange)
					{
						if (360.0f - fmod(TargetList[0]->GetAngToAngDist(), 360.0f) <= flAngle
							|| fmod(TargetList[0]->GetAngToAngDist(), 360.0f) <= flAngle)
						{
							if (bAimbot_UsedOnce == false)
							{

								if (flSmooth > 0)	// плавное перемещение курсора
								{
									float tmp_EyeVector[3];
									float tmp_Position[3];
									float tmp_body[3];
									float tmp_bone[3];

									for (float i = 0.0f; i < flSmooth; i++)
									{
										if (iAimbot_Type == SKIN)
										{
											tmp_Position[0] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, true)[0];
											tmp_Position[1] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, false)[1];
											tmp_Position[2] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, false)[2];
										}
										else if (iAimbot_Type == HITBOX)
										{
											tmp_body[0] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(AIMBOT_BODY_BONE_NUM, true)[0];
											tmp_body[1] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(AIMBOT_BODY_BONE_NUM, false)[1];
											tmp_body[2] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(AIMBOT_BODY_BONE_NUM, false)[2];

											tmp_bone[0] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, true)[0];
											tmp_bone[1] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, false)[1];
											tmp_bone[2] = EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, false)[2];

											tmp_Position[0] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(true)[0] + (tmp_bone[0] - tmp_body[0]);
											tmp_Position[1] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(false)[1] + (tmp_bone[1] - tmp_body[1]);
											tmp_Position[2] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(false)[2] + (tmp_bone[2] - tmp_body[2]);

											/*tmp_Position[0] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(true)[0];
											tmp_Position[1] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(false)[1];
											tmp_Position[2] = EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(false)[2];*/
										}

										CalcAngle(Player->getPosition(true), tmp_Position, TargetList[0]->GetAimbotAngle() );

										difference_1 = fmod((TargetList[0]->GetAimbotAngle()[0] - Player->getEyeVector(true)[0]), 360.0f);
										difference_2 = fmod((TargetList[0]->GetAimbotAngle()[1] - Player->getEyeVector(false)[1]), 360.0f);
										if (difference_1 > 180.0f) difference_1 -= 360.0f;
										if (difference_2 > 180.0f) difference_2 -= 360.0f;

										tmp_EyeVector[0] = Player->getEyeVector(false)[0] + (difference_1 / (flSmooth - i));
										tmp_EyeVector[1] = Player->getEyeVector(false)[1] + (difference_2 / (flSmooth - i));
										tmp_EyeVector[2] = 0;

										if (i + 1.0f == flSmooth)
										{
											if (bAimbot_AutoShoot)
											{
												WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_Attack), &ACTION_PLUS, sizeof(int), NULL);
												TimeSinceLastShoot = clock();
											}
										}

										WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Player->getViewVectorAddress(true)), tmp_EyeVector, sizeof(float[3]), NULL);
										
										Sleep(1);
									}
								}
								else // if smooth == 0
								{
									if (iAimbot_Type == SKIN)
									{
										CalcAngle(Player->getPosition(true), EnemyList[TargetList[0]->getIdInEnemyList()]->getBonePos(iBoneNum, true), TargetList[0]->GetAimbotAngle());
									}
									else if (iAimbot_Type == HITBOX)
									{
										CalcAngle(Player->getPosition(true), EnemyList[TargetList[0]->getIdInEnemyList()]->getPosition(true), TargetList[0]->GetAimbotAngle());
									}

									if (bAimbot_AutoShoot)
									{
										WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_Attack), &ACTION_PLUS, sizeof(int), NULL);
										TimeSinceLastShoot = clock();
									}
									WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Player->getViewVectorAddress(true)), TargetList[0]->GetAimbotAngle(), sizeof(float[3]), NULL);
								}
								if (bAimbot_AutoMouse2)
								{
									if (bAimbot_AutoShoot)
									{
										Sleep(60); // !!!
										mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									}
								}
								if (bAimbot_AutoShoot) bAimbot_UsedOnce = true;
							}	// bIsUsedOnce
						}		// if in angle
					}			//if in range
				}				// targetloop > 0
			}					// playerteam == teamSURV
		}						// if aimbutton holding
		else
		{
			if (bAimbot_UsedOnce == true)
			{
				if (clock() - TimeSinceLastShoot > flSmooth)
				{
					bAimbot_UsedOnce = false;
					WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_Attack), &ACTION_MINUS, sizeof(int), NULL);
				}
			}
		}
		targets_count = 0; // !!!
	}
}

void C_CH_Aimbot::setType(int NewType)
{
	iAimbot_Type = NewType;
}
void C_CH_Aimbot::setAutoMouse2(bool NewMode)
{
	bAimbot_AutoMouse2 = NewMode;
}
void C_CH_Aimbot::setAutoShoot(bool NewAutoShootStatus)
{
	bAimbot_AutoShoot = NewAutoShootStatus;
}
void C_CH_Aimbot::setAngle(float NewAngle)
{
	if (NewAngle > 0) flAngle = NewAngle;
}
void C_CH_Aimbot::setSmooth(float NewSmooth)
{
	if (NewSmooth > 0) flSmooth = NewSmooth;
}
void C_CH_Aimbot::setRange(float NewRange)
{
	if (NewRange > 0) flRange = NewRange;
}
void C_CH_Aimbot::changeAngle(float ExtraAngle)
{
	if(flAngle + ExtraAngle >= 0) flAngle += ExtraAngle;
}
void C_CH_Aimbot::changeRange(float ExtraRange)
{
	if(flRange + ExtraRange >= 0) flRange += ExtraRange;
}
void C_CH_Aimbot::changeSmooth(float ExtraSmooth)
{
	if (flSmooth + ExtraSmooth >= 0) flSmooth += ExtraSmooth;
}
void C_CH_Aimbot::changeBoneNum(int ExtraBoneNum)
{
	if (iBoneNum + ExtraBoneNum >= 0) iBoneNum += ExtraBoneNum;
}
float C_CH_Aimbot::GetAimRange()
{
	return flRange;
}
float C_CH_Aimbot::GetAimAngle()
{
	return flAngle;
}
float C_CH_Aimbot::GetAimSmooth()
{
	return flSmooth;
}
int C_CH_Aimbot::GetAimbotType()
{
	return iAimbot_Type;
}
int C_CH_Aimbot::GetBoneNum()
{
	return iBoneNum;
}
bool C_CH_Aimbot::GetAutoMouse2()
{
	return bAimbot_AutoMouse2;
}
bool C_CH_Aimbot::GetAimbotAutoShoot()
{
	return bAimbot_AutoShoot;
}
C_MyPlayer* C_CH_Aimbot::getPlayer()
{
	return Player;
}
C_Enemy** C_CH_Aimbot::getEnemyList()
{
	return EnemyList;
}
C_Target** C_CH_Aimbot::getTargetList()
{
	return TargetList;
}