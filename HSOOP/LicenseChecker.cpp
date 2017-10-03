#include "LicenseChecker.h"

static int CurrentAccountID = INVALID_ACCOUNT_ID;

int getCurrentAccountID()
{
	return CurrentAccountID;
}

void setCurrentAccountID(int newID)
{
	CurrentAccountID = newID;
}

void CheckLicense()
{
	C_HS_SingleInstance HunterSkill_Instance(TEXT("Global\\{6543A370-6EE9-4103-A701-BF59D67F7709}"));
	if (HunterSkill_Instance.IsAnotherInstanceRunning()) CrushGame(0, false);

	while (true)
	{
		CheckHardWareIDLicense();
		CheckSteamIDLicense();
		CheckSubscriptionLicense();

		Sleep(UPDATE_TIME);
	}
}

void CheckSubscriptionLicense()
{
	if (LICENSED_ACCOUNTS[CurrentAccountID].bSUBSCRIPTION_CHECK)
	{
		SYSTEMTIME serverTime;

		int serverDay;
		int serverMonth;
		int serverYear;
		int serverHour;
		int serverMinute;
		int serverSecond;

		int NumOfServers = sizeof(SNTP_SERVERS_URL) / sizeof(LPCSTR);

		for (int i = 0; i < NumOfServers; i++)
		{
			serverTime = GetServerTime(SNTP_SERVERS_URL[i]);

			serverDay = serverTime.wDay;
			serverMonth = serverTime.wMonth;
			serverYear = serverTime.wYear;
			serverHour = serverTime.wHour;
			serverMinute = serverTime.wMinute;
			serverSecond = serverTime.wSecond;

			if (DateToSec(LICENSED_ACCOUNTS[CurrentAccountID].iDATE_LICENSE[0],
						LICENSED_ACCOUNTS[CurrentAccountID].iDATE_LICENSE[1],
						LICENSED_ACCOUNTS[CurrentAccountID].iDATE_LICENSE[2],
						LICENSED_ACCOUNTS[CurrentAccountID].iTIME_LICENSE[0],
						LICENSED_ACCOUNTS[CurrentAccountID].iTIME_LICENSE[1],
						LICENSED_ACCOUNTS[CurrentAccountID].iTIME_LICENSE[2]) >
				DateToSec(serverDay, serverMonth, serverYear, serverHour, serverMinute, serverSecond)) return;
			else
			{
				if (i + 1 == NumOfServers) CrushGame(0, true);
			}

			Sleep(SLEEP_BETWEEN_CONNECT_TRIES);
		}
	}
}

void CheckSteamIDLicense()
{
	if (C_HackProcess::_instance != NULL)
	{
		long long int CurrentSteamID;

		C_HackProcess* Process = C_HackProcess::_instance;

		if (Process->IsGameAvail() == false) return; // v35_final

		//ReadProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordSteamClient + dw_STEAMID), &CurrentSteamID, sizeof(CurrentSteamID), NULL);

		DWORD tmpAddress = Process->FindDMAAddress(1, Process->GetHandle(), dw_STEAMID_Offsets, Process->dwordMatchmaking + dw_STEAMID);
		ReadProcessMemory(Process->GetHandle(), (PBYTE*)(tmpAddress), &CurrentSteamID, sizeof(CurrentSteamID), NULL);

		if (CurrentAccountID != INVALID_ACCOUNT_ID)
		{
			if (LICENSED_ACCOUNTS[CurrentAccountID].bSTEAMID_CHECK)
			{
				if (LICENSED_ACCOUNTS[CurrentAccountID].iSTEAM_ID == CurrentSteamID) return;
				else
				{
					Sleep(2000);
					if (Process->IsGameAvail() == true) CrushGame(0, true); // v35_final
				}
			}
		}
		else
		{
			int NumOfAccounts = sizeof(LICENSED_ACCOUNTS) / sizeof(Account);

			for (int i = 0; i < NumOfAccounts; i++)
			{
				if (LICENSED_ACCOUNTS[i].bSTEAMID_CHECK)
				{
					if (LICENSED_ACCOUNTS[i].iSTEAM_ID == CurrentSteamID)
					{
						CurrentAccountID = i;
						Process->UpdateInfoPanel(Process->IsCheatEnabled(), true, clock());
						return;
					}
					else
					{
						if (i + 1 == NumOfAccounts)
						{
							Sleep(2000);
							if (Process->IsGameAvail() == true) CrushGame(0, true);  // v35_final
						}
					}
				}
			}
		}
	}
}

void CheckHardWareIDLicense()
{
	int NumOfAccounts = sizeof(LICENSED_ACCOUNTS) / sizeof(Account);
	string CurrentHardWare = GetHardWareID();

	for (int i = 0; i < NumOfAccounts; i++)
	{
		if (LICENSED_ACCOUNTS[i].bHARDWAREID_CHECK == true)
		{
			if (LICENSED_ACCOUNTS[i].sHARDWARE_ID.compare(CurrentHardWare) == 0)
			{
				CurrentAccountID = i;
				return;
			}
			else
			{
				if (i + 1 == NumOfAccounts) CrushGame(0, true);
			}
		}
	}
}

BOOL SelfDelete()
{
	TCHAR szFile[MAX_PATH], szCmd[MAX_PATH];

	if ((GetModuleFileName(0, szFile, MAX_PATH) != 0) &&
		(GetShortPathName(szFile, szFile, MAX_PATH) != 0))
	{
		lstrcpy(szCmd, "/c del ");
		lstrcat(szCmd, szFile);
		lstrcat(szCmd, " >> NUL");

		if ((GetEnvironmentVariable("ComSpec", szFile, MAX_PATH) != 0) &&
			((INT)ShellExecute(0, 0, szFile, szCmd, 0, SW_HIDE)>32))
			return TRUE;
	}

	return FALSE;
}

void CrushGame(int ExitCode, bool NeedToDeleteProgramm)
{
	if (C_HackProcess::_instance != NULL) TerminateProcess(C_HackProcess::_instance->GetHandle(), ExitCode);
	if(NeedToDeleteProgramm) SelfDelete(); // !!!
	exit(ExitCode);
}

SYSTEMTIME GetServerTime(LPCSTR ServerURL)
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hInternetSession) return sysTime;

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, ServerURL, 0, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);

	if (!hInternetFile)
	{
		InternetCloseHandle(hInternetSession);
		return sysTime;
	}

	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		return sysTime;
	}

	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);
	return sysTime;
}

long long int DateToSec(int day, int month, int year, int hour, int minute, int second)
{
	long long int tmp_Time = 0;

	tmp_Time += second;
	tmp_Time += minute * 60;
	tmp_Time += hour * 60 * 60;
	tmp_Time += day * 24 * 60 * 60;
	tmp_Time += month * 31 * 24 * 60 * 60;
	tmp_Time += (year - 2015) * 365 * 24 * 60 * 60;

	return tmp_Time;
}

int GetAccNumWithMaxTimeExpire()
{
	int ID = 0;
	for (int i = 0; i < sizeof(LICENSED_ACCOUNTS) / sizeof(Account); i++)
	{
		if (DateToSec(	LICENSED_ACCOUNTS[ID].iDATE_LICENSE[0],
						LICENSED_ACCOUNTS[ID].iDATE_LICENSE[1],
						LICENSED_ACCOUNTS[ID].iDATE_LICENSE[2],
						LICENSED_ACCOUNTS[ID].iTIME_LICENSE[0],
						LICENSED_ACCOUNTS[ID].iTIME_LICENSE[1],
						LICENSED_ACCOUNTS[ID].iTIME_LICENSE[2]) <
			DateToSec(	LICENSED_ACCOUNTS[i].iDATE_LICENSE[0],
						LICENSED_ACCOUNTS[i].iDATE_LICENSE[1],
						LICENSED_ACCOUNTS[i].iDATE_LICENSE[2],
						LICENSED_ACCOUNTS[i].iTIME_LICENSE[0],
						LICENSED_ACCOUNTS[i].iTIME_LICENSE[1],
						LICENSED_ACCOUNTS[i].iTIME_LICENSE[2])
			)
		{
			ID = i;
		}
	}
	return ID;
}