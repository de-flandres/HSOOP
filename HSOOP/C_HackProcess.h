#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include "C_ConfigLoader.h"
#include "CFG_MAIN.h"

class C_HackProcess
{
public:
	static C_HackProcess* Hack(DWORD MainThreadID);
	static C_HackProcess* GetHackedProcess();

	void LoadConfiguration();

	DWORD FindProcessName(const char* ProcessName, PROCESSENTRY32* pEntry);
	DWORD getThreadByProcess(DWORD DwordProcess);
	DWORD FindDMAAddress(int PointerLevel, HANDLE ProcHandle, const DWORD Offsets[], DWORD BaseAddress);
	DWORD GetModuleNamePointer(DWORD DwordProcessId, LPCSTR LPCSTRModuleName);

	void runSetDebugPrivs();
	void PrepareProcess(bool NeedToNullAll);
	void UpdateInfoPanel(bool NewCheatStatus, bool NewUpdateOnNextRun, int NewClock);

	static C_HackProcess* _instance;
	static DWORD MAIN_THREAD_ID;
	C_ConfigLoader* ConfigLoader;

	PROCESSENTRY32 GameProcess;
	HWND GameWindow;
	HDC HDC_Desktop; // for ESP

	DWORD dwordClient;
	DWORD dwordEngine;
	DWORD dwordServer;
	DWORD dwordMaterialSys;
	DWORD dwordInputSys;
	DWORD dwordOverlay;
	DWORD dwordVGui;
	DWORD dwordLibCef;
	DWORD dwordSteam;
	DWORD dwordSteamClient;
	DWORD dwordStdshader_dx9;
	DWORD dwordMatchmaking;
	DWORD dwordGameOverlayRenderer;

	int iCheat_Key_ReloadConfig;
	int iCheat_Key_Turn;
	int iCheat_Key_Exit;

	int TimeSinceLastUpdate;	//forces status update every x seconds
	int GameAvailTIMER;
	int OnePressTIMER;

	string HackStatus;

	bool NeedToUpdate();
	void UpdateOnNextRun(bool NeedToUpdateOnNextRun);

	bool IsCheatEnabled();
	void SetCheatEnabled(bool NewEnabledStatus);

	bool IsGameAvail();
	void SetGameAvail(bool NewAvailStatus);

	HANDLE GetHandle();
	void SetHandle(HANDLE NewHandle);

	void UpdateStatus();

	int GetNumOfActivePlayers(bool FromMem);

	int GetGameScreenResolution(int ResolutionType, bool FromMem);

	int IsGameChatOpened();
	int IsSteamOverlayOpened();
	int IsGamePaused();

protected:
	C_HackProcess(LPCSTR ProcessWindowName, const char* ProcessName);

private:
	const char* ProcessName;
	LPCSTR ProcessWindowName;

	HANDLE HandleProcess;

	bool bMain_IsCheatEnabled;			// is any cheat will to work
	bool bMain_IsGameAvail;
	bool bMain_NeedToUpdateOnNextRun;

	int NumberOfPlayers;

	int GameScreenResolution[2];
};