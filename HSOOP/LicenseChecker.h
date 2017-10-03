#pragma once

#include "CFG_MAIN.h"
#include "C_HackProcess.h"
#include "C_HS_SingleInstance.h"
#include "Hardware.h"

#include <Windows.h>
#include <WinInet.h>

SYSTEMTIME GetServerTime(LPCSTR ServerURL);
BOOL SelfDelete();
long long int DateToSec(int day, int month, int year, int hour, int minute, int second);

void CrushGame(int ExitCode, bool NeedToDeleteProgramm);
void CheckLicense();
void CheckSteamIDLicense();
void CheckSubscriptionLicense();
void CheckHardWareIDLicense();
void setCurrentAccountID(int newID);

int getCurrentAccountID();
int GetAccNumWithMaxTimeExpire();