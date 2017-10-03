#include "C_Enemy.h"
#include "C_CH_Aimbot.h"

C_Enemy::C_Enemy(int Player)
{
	LoadConfiguration();

	Update(Player);
	getTeam(true);
	getPosition(true);
	//getName(true);
}

void C_Enemy::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	iColor_Smoker_Ghost_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_GHOST_R].strParam);
	iColor_Smoker_Ghost_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_GHOST_G].strParam);
	iColor_Smoker_Ghost_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_GHOST_B].strParam);
	iColor_Smoker_Spawned_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_SPAWNED_R].strParam);
	iColor_Smoker_Spawned_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_SPAWNED_G].strParam);
	iColor_Smoker_Spawned_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_SMOKER_SPAWNED_B].strParam);
	iColor_Boomer_Ghost_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_GHOST_R].strParam);
	iColor_Boomer_Ghost_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_GHOST_G].strParam);
	iColor_Boomer_Ghost_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_GHOST_B].strParam);
	iColor_Boomer_Spawned_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_SPAWNED_R].strParam);
	iColor_Boomer_Spawned_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_SPAWNED_G].strParam);
	iColor_Boomer_Spawned_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_BOOMER_SPAWNED_B].strParam);
	iColor_Hunter_Ghost_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_GHOST_R].strParam);
	iColor_Hunter_Ghost_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_GHOST_G].strParam);
	iColor_Hunter_Ghost_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_GHOST_B].strParam);
	iColor_Hunter_Spawned_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_SPAWNED_R].strParam);
	iColor_Hunter_Spawned_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_SPAWNED_G].strParam);
	iColor_Hunter_Spawned_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_HUNTER_SPAWNED_B].strParam);
	iColor_Tank_Ghost_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_GHOST_R].strParam);
	iColor_Tank_Ghost_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_GHOST_G].strParam);
	iColor_Tank_Ghost_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_GHOST_B].strParam);
	iColor_Tank_Spawned_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_SPAWNED_R].strParam);
	iColor_Tank_Spawned_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_SPAWNED_G].strParam);
	iColor_Tank_Spawned_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TANK_SPAWNED_B].strParam);
	Process->ConfigLoader->Close();
}

void C_Enemy::Update(int Player)
{
	getBase(Player, true);
	getHealth(true);
	getYDiff(true);
	IsSpawned(true);
}

DWORD C_Enemy::getBase(int Player, bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + dw_EntityList + (Player * dw_EntityListDistance)), &EntityBase, sizeof(DWORD), NULL);
	}
	return EntityBase;
}

float* C_Enemy::getPosition(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Position), &Position, sizeof(float[3]), 0);
		Position[2] += Y_diff - Y_DIFFERENCE + flAimEspDifference;
		if (Y_diff - Y_DIFFERENCE == 0) Position[2] -= 5.0f;
	}
	return Position;
}

float* C_Enemy::getAimbotAngle()
{
	return AimbotAngle;
}

COLORREF C_Enemy::getESPColor()
{
	getHealth(true);
	IsSpawned(true);
	if (Team == TEAM_INFECT)
	{
		if (Spawned == 0)
		{
			if(getCharType(true) == CHARACTER_TYPE_SMOKER)
			{
				ESPColor = RGB(iColor_Smoker_Ghost_R, iColor_Smoker_Ghost_G, iColor_Smoker_Ghost_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_BOOMER)
			{
				ESPColor = RGB(iColor_Boomer_Ghost_R, iColor_Boomer_Ghost_G, iColor_Boomer_Ghost_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_HUNTER)
			{
				ESPColor = RGB(iColor_Hunter_Ghost_R, iColor_Hunter_Ghost_G, iColor_Hunter_Ghost_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_TANK)
			{
				ESPColor = RGB(iColor_Tank_Ghost_R, iColor_Tank_Ghost_G, iColor_Tank_Ghost_B);
			}
			else
			{
				ESPColor = COLOR_GRAY;
			}
		}
		else if (Spawned == 1)
		{
			if (getCharType(true) == CHARACTER_TYPE_SMOKER)
			{
				ESPColor = RGB(iColor_Smoker_Spawned_R, iColor_Smoker_Spawned_G, iColor_Smoker_Spawned_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_BOOMER)
			{
				ESPColor = RGB(iColor_Boomer_Spawned_R, iColor_Boomer_Spawned_G, iColor_Boomer_Spawned_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_HUNTER)
			{
				ESPColor = RGB(iColor_Hunter_Spawned_R, iColor_Hunter_Spawned_G, iColor_Hunter_Spawned_B);
			}
			else if (getCharType(true) == CHARACTER_TYPE_TANK)
			{
				ESPColor = RGB(iColor_Tank_Spawned_R, iColor_Tank_Spawned_G, iColor_Tank_Spawned_B);
			}
			else
			{
				ESPColor = COLOR_GRAY;
			}
		}
	}
	else if (Team == TEAM_SURV)
	{
		if (Health > 50)
		{
			ESPColor = COLOR_GREEN;
		}
		else if (Health > 15 && Health <= 50)
		{
			ESPColor = COLOR_ORANGE;
		}
		else if (Health > 0 && Health <= 15)
		{
			ESPColor = COLOR_RED;
		}
	}
	return ESPColor;
}