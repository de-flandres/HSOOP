#include "C_Entity.h"

C_Entity::C_Entity()
{
	Process = C_HackProcess::GetHackedProcess();	// pattern singleton
}

int C_Entity::getTeam(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Team), &Team, sizeof(int), 0);
	}
	return Team;
}

bool C_Entity::setTeam(int NewTeam)
{
	WriteProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Team), &NewTeam, sizeof(int), NULL);
	return true;
}

int C_Entity::getWeaponID(bool FromMem)
{
	if (FromMem)
	{
		DWORD tmpAddress = Process->FindDMAAddress(1, Process->GetHandle(), dw_CurrentWeaponID_Offsets, EntityBase + dw_CurrentWeaponID);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(tmpAddress), &WeaponID, sizeof(int), NULL);
	}
	return WeaponID;
}

int C_Entity::getHealth(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Health), &Health, sizeof(int), 0);
	}
	return Health;
}

string C_Entity::getCharTypeString(bool FromMem)
{
	if (Team == TEAM_INFECT)
	{
		switch (getCharType(FromMem))
		{
			case CHARACTER_TYPE_SMOKER:
			{
				return "Smoker";
				break;
			}
			case CHARACTER_TYPE_BOOMER:
			{
				return "Boomer";
				break;
			}
			case CHARACTER_TYPE_HUNTER:
			{
				return "Hunter";
				break;
			}
			case CHARACTER_TYPE_TANK:
			{
				return "Tank";
				break;
			}
			default:
			{
				return "Unknown";
				break;
			}
		}
	}
	if (Team == TEAM_SURV)
	{
		return "Survivor";
	}
	else return "Spectator";
}

int C_Entity::getCharType(bool FromMem)
{
	if (FromMem)
	{
		DWORD tmpAddress = Process->FindDMAAddress(2, Process->GetHandle(), dw_CharacterType_Offsets, EntityBase + dw_CharacterType);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(tmpAddress), &CharacterType, sizeof(int), NULL);
	}
	return CharacterType;
}

float* C_Entity::getPosition(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Position), &Position, sizeof(float[3]), 0);
		Position[2] += Y_diff - Y_DIFFERENCE;
	}
	return Position;
}

float C_Entity::getMaxSpeed(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_MaxSpeed), &flMaxSpeed, sizeof(float), NULL);
	}
	return flMaxSpeed;
}

bool C_Entity::setBase(DWORD NewBase)
{
	EntityBase = NewBase;
	return true;
}

bool C_Entity::IsSpawned(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_IsSpawned), &Spawned, sizeof(int), 0);
	}
	if (Spawned == 1) return true;
	return false;
}
bool C_Entity::IsAlive(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_LifeStatus), &LifeStatus, sizeof(byte), 0);
	}
	if (LifeStatus == 0) return true;
	return false;
}

string C_Entity::getName(bool FromMem)
{
	if (FromMem)
	{
		DWORD tempAddress = Process->FindDMAAddress(1, Process->GetHandle(), dw_PlayerName_Offsets, EntityBase + dw_PlayerName);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(tempAddress), &name, 20, NULL);
	}
	return name;
}

float* C_Entity::getBonePos(int Bone_Num, bool FromMem)
{
	if (FromMem)
	{
		//getPosition(true); // !!!

		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_BoneMatrix), &BoneBase, sizeof(DWORD), 0);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(BoneBase + Bone_Num * 0x30 + 0x0C), &Current_Bone_Pos[0], sizeof(float), 0);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(BoneBase + Bone_Num * 0x30 + 0x1C), &Current_Bone_Pos[1], sizeof(float), 0);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(BoneBase + Bone_Num * 0x30 + 0x2C), &Current_Bone_Pos[2], sizeof(float), 0);
		Current_Bone_Pos[2] -= Y_DIFFERENCE;
	}

	return Current_Bone_Pos;
}

float C_Entity::getYDiff(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(EntityBase + dw_Y_diff), &Y_diff, sizeof(float), NULL);
	}
	return Y_diff;
}

bool C_Entity::IsEntityBaseExist()
{
	if (EntityBase != NULL || EntityBase != 0x00000000) return true;
	return false;
}
