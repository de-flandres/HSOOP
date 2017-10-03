
#include "CFG_MAIN.h"
#include "C_HackProcess.h"

C_HackProcess* C_HackProcess::_instance = 0;	// pattern singleton
DWORD C_HackProcess::MAIN_THREAD_ID = 0;

C_HackProcess* C_HackProcess::Hack(DWORD MainThreadID)
{
	MAIN_THREAD_ID = MainThreadID;
	return C_HackProcess::GetHackedProcess();
}

C_HackProcess* C_HackProcess::GetHackedProcess()
{
	if(_instance == NULL)
	{
		_instance = new C_HackProcess(GAME_WINDOW_NAME, GAME_PROCESS_NAME);
	}
	return _instance;
}

void C_HackProcess::LoadConfiguration()
{
	ConfigLoader->Open(ios::in);
	iCheat_Key_ReloadConfig = ConfigLoader->Load(CONFIG_FILE[eLOADER_HUNTERSKILL_KEY_RELOADCONFIG].strParam);
	iCheat_Key_Turn = ConfigLoader->Load(CONFIG_FILE[eLOADER_HUNTERSKILL_KEY_TURN].strParam);
	iCheat_Key_Exit = ConfigLoader->Load(CONFIG_FILE[eLOADER_HUNTERSKILL_KEY_EXIT].strParam);
	ConfigLoader->Close();
}

C_HackProcess::C_HackProcess(LPCSTR ProcessWindowName, const char* ProcessName)
{
	this->ProcessWindowName = ProcessWindowName;
	this->ProcessName = ProcessName;

	TimeSinceLastUpdate = clock(); //forces status update every x seconds
	GameAvailTIMER = 0;
	OnePressTIMER = 0;

	ConfigLoader = new C_ConfigLoader();
	LoadConfiguration();

	PrepareProcess(true);
	UpdateStatus();

	bMain_IsCheatEnabled = true;
	bMain_NeedToUpdateOnNextRun = true;
}

DWORD C_HackProcess::FindProcessName(const char* ProcessName, PROCESSENTRY32* pEntry)
{	 
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) return 0;
	if(!Process32First(hSnapshot, &ProcessEntry))
	{
		CloseHandle(hSnapshot);
		return 0;
	}
	do
	{
		if(!_strcmpi(ProcessEntry.szExeFile, ProcessName))
		{
			memcpy((void*)pEntry, (void*)&ProcessEntry, sizeof(PROCESSENTRY32));
			CloseHandle(hSnapshot);
			return ProcessEntry.th32ProcessID;
		}
	} while(Process32Next(hSnapshot, &ProcessEntry));
	CloseHandle(hSnapshot);
	return 0;
}

DWORD C_HackProcess::getThreadByProcess(DWORD DwordProcess)
{	 
	THREADENTRY32 ThreadEntry;
	ThreadEntry.dwSize = sizeof(THREADENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) return 0;

	if(!Thread32First(hSnapshot, &ThreadEntry))
	{
		CloseHandle(hSnapshot);
		return 0;
	}

	do
	{
		if(ThreadEntry.th32OwnerProcessID == DwordProcess)
		{
			CloseHandle(hSnapshot);
			return ThreadEntry.th32ThreadID;
		}
	} while(Thread32Next(hSnapshot, &ThreadEntry)); 
	CloseHandle(hSnapshot);       
	return 0;
}

DWORD C_HackProcess::FindDMAAddress(int PointerLevel, HANDLE ProcHandle, const DWORD Offsets[], DWORD BaseAddress)
{
	DWORD pointer = BaseAddress;
	DWORD pointerTemp;
	DWORD pointerAddress;

	for (int i = 0; i < PointerLevel; i++)
	{
		if(i == 0) ReadProcessMemory(ProcHandle, (LPCVOID)pointer, &pointerTemp, 4, NULL);

		pointerAddress = pointerTemp + Offsets[i];
		ReadProcessMemory(ProcHandle, (LPCVOID)pointerAddress, &pointerTemp, 4, NULL);
	}
	return pointerAddress;
}

DWORD C_HackProcess::GetModuleNamePointer(DWORD DwordProcessId, LPCSTR LPCSTRModuleName)
{ 
	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, DwordProcessId);
	if(!hSnapShot) return NULL;  
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL RunModule = Module32First(hSnapShot, &lpModuleEntry);
	while(RunModule)
	{
		if(!strcmp(lpModuleEntry.szModule, (TCHAR*)LPCSTRModuleName ))
		{
			CloseHandle( hSnapShot );
			return (DWORD)lpModuleEntry.modBaseAddr;
		}
		RunModule = Module32Next( hSnapShot, &lpModuleEntry );
	}
	CloseHandle(hSnapShot);
	return NULL;
}

void C_HackProcess::UpdateInfoPanel(bool NewCheatStatus, bool NewUpdateOnNextRun, int NewClock)
{
	bMain_IsCheatEnabled = NewCheatStatus;
	bMain_NeedToUpdateOnNextRun = NewUpdateOnNextRun;
	OnePressTIMER = NewClock;
}

void C_HackProcess::runSetDebugPrivs()
{
	HANDLE HandleProcess = GetCurrentProcess(), HandleToken;
	TOKEN_PRIVILEGES priv;
	LUID LUID;

	OpenProcessToken(HandleProcess, TOKEN_ADJUST_PRIVILEGES, &HandleToken);
	LookupPrivilegeValue(0, "seDebugPrivilege", &LUID);

	priv.PrivilegeCount = 1;
	priv.Privileges[0].Luid = LUID;
	priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(HandleToken, false, &priv, 0, 0, 0);

	CloseHandle(HandleToken);
	CloseHandle(HandleProcess);
}

void C_HackProcess::PrepareProcess(bool NeedToNullAll)
{
	if (NeedToNullAll)
	{
		GameProcess.th32ProcessID = NULL;
		//GameProcess = { 0 };
		GameWindow = NULL;
		HDC_Desktop = NULL;
		HandleProcess = NULL;

		dwordClient = 0;
		dwordEngine = 0;
		dwordServer = 0;
		dwordMaterialSys = 0;
		dwordInputSys = 0;
		dwordOverlay = 0;
		dwordVGui = 0;
		dwordLibCef = 0;
		dwordSteam = 0;
		dwordSteamClient = 0;
		dwordStdshader_dx9 = 0;
		dwordGameOverlayRenderer = 0;
		dwordMatchmaking = 0;

		GameScreenResolution[0] = 0;
		GameScreenResolution[1] = 0;

		NumberOfPlayers = 0;

		bMain_IsGameAvail = false;
		bMain_NeedToUpdateOnNextRun = false;
		TimeSinceLastUpdate = 0;
		GameAvailTIMER = 0;
		HackStatus = "UNKNOWN";

		setCurrentAccountID(INVALID_ACCOUNT_ID); // !!!
	}

	CHEAT_INFO();
	cout << "\tSTATUS:\t\tWaiting for the " << ProcessName << " ..." << endl;

	if(NeedToNullAll) Sleep(2000);

	runSetDebugPrivs();
	while (!FindProcessName(ProcessName, &GameProcess)) Sleep(10);
	while (!getThreadByProcess(GameProcess.th32ProcessID)) Sleep(10);
	HandleProcess = OpenProcess(PROCESS_ALL_ACCESS, false, GameProcess.th32ProcessID);

	while (dwordClient == 0x0) dwordClient = GetModuleNamePointer(GameProcess.th32ProcessID, "client.dll");
	while (dwordEngine == 0x0) dwordEngine = GetModuleNamePointer(GameProcess.th32ProcessID, "engine.dll");
	while (dwordMaterialSys == 0x0) dwordMaterialSys = GetModuleNamePointer(GameProcess.th32ProcessID, "materialsystem.dll");
	while (dwordMatchmaking == 0x0) dwordMatchmaking = GetModuleNamePointer(GameProcess.th32ProcessID, "matchmaking.dll");
	while (dwordGameOverlayRenderer == 0x0) dwordGameOverlayRenderer = GetModuleNamePointer(GameProcess.th32ProcessID, "gameoverlayrenderer.dll");

	//while(dwordSteamClient == 0x0) dwordSteamClient = GetModuleNamePointer(GameProcess.th32ProcessID, "steamclient.dll");
	//while(dwordStdshader_dx9 == 0x0) dwordStdshader_dx9 = GetModuleNamePointer(GameProcess.th32ProcessID, "stdshader_dx9.dll");
	//while (dwordServer == 0x0) dwordServer = GetModuleNamePointer(GameProcess.th32ProcessID, "server.dll");
	//while(dwordInputSys == 0x0) dwordInputSys = GetModuleNamePointer(GameProcess.th32ProcessID, "inputsystem.dll");
	//while(dwordVGui == 0x0) dwordVGui = GetModuleNamePointer(GameProcess.th32ProcessID, "vguimatsurface.dll");
	//while(dwordOverlay == 0x0) dwordOverlay = GetModuleNamePointer(GameProcess.th32ProcessID, "gameoverlayrenderer.dll");
	//while(dwordLibCef == 0x0) dwordLibCef = GetModuleNamePointer(GameProcess.th32ProcessID, "libcef.dll");
	//while(dwordSteam == 0x0) dwordSteam = GetModuleNamePointer(GameProcess.th32ProcessID, "steam.dll");

	GetGameScreenResolution(0, true);

	GameWindow = FindWindow(NULL, ProcessWindowName);
	HDC_Desktop = GetDC(GameWindow);
	UpdateInfoPanel(bMain_IsCheatEnabled, true, clock());
}

void C_HackProcess::UpdateStatus()
{
	GameAvailTIMER = clock();
	bMain_IsGameAvail = false;

	if (GameWindow = FindWindow(NULL, ProcessWindowName))
	{
		if (getThreadByProcess(GameProcess.th32ProcessID) != NULL)
		{
			if (HandleProcess == INVALID_HANDLE_VALUE || HandleProcess == NULL)
			{
				HackStatus = "Failed to open process " GAME_PROCESS_NAME "!";
			}
			else
			{
				HackStatus = "Injected! Get Awake!";
				bMain_IsGameAvail = true;
			}
		}
		else HackStatus = "Failed to obtain " GAME_PROCESS_NAME " process id!";
	}
	//else HackStatus = "Process " GAME_PROCESS_NAME " NOT FOUND";

	if (bMain_IsGameAvail == false) PrepareProcess(true);
}

void C_HackProcess::SetCheatEnabled(bool NewEnabledStatus)
{
	bMain_IsCheatEnabled = NewEnabledStatus;
}
bool C_HackProcess::IsCheatEnabled()
{
	return bMain_IsCheatEnabled;
}

void C_HackProcess::SetGameAvail(bool NewAvailStatus)
{
	bMain_IsGameAvail = NewAvailStatus;
}
bool C_HackProcess::IsGameAvail()
{
	return bMain_IsGameAvail;
}

void C_HackProcess::UpdateOnNextRun(bool NeedToUpdateOnNextRun)
{
	bMain_NeedToUpdateOnNextRun = NeedToUpdateOnNextRun;
}
bool C_HackProcess::NeedToUpdate()
{
	return bMain_NeedToUpdateOnNextRun;
}

void C_HackProcess::SetHandle(HANDLE NewHandle)
{
	HandleProcess = NewHandle;
}
HANDLE C_HackProcess::GetHandle()
{
	return HandleProcess;
}

int C_HackProcess::GetNumOfActivePlayers(bool FromMem)
{
	if (FromMem)
	{
		ReadProcessMemory(HandleProcess, (PBYTE*)(dwordServer + dw_NumberOfPlayers), &NumberOfPlayers, sizeof(int), 0);
	}
	return NumberOfPlayers;
}

int C_HackProcess::GetGameScreenResolution(int ResolutionType, bool FromMem)
{
	if (FromMem) ReadProcessMemory(HandleProcess, (PBYTE*)(dwordEngine + dw_GameScreenResolution), &GameScreenResolution, sizeof(GameScreenResolution), 0);
	return GameScreenResolution[ResolutionType];
}

int C_HackProcess::IsGameChatOpened()
{
	int tmp = 0;
	ReadProcessMemory(HandleProcess, (PBYTE*)(dwordClient + dw_IsGameChatOpened), &tmp, sizeof(tmp), 0);
	return tmp;
}

int C_HackProcess::IsSteamOverlayOpened()
{
	int tmp = 0;
	ReadProcessMemory(HandleProcess, (PBYTE*)(dwordGameOverlayRenderer + dw_IsSteamOpened), &tmp, sizeof(tmp), 0);
	return tmp;
}

int C_HackProcess::IsGamePaused()
{
	int tmp = 0;
	ReadProcessMemory(HandleProcess, (PBYTE*)(dwordClient + dw_IsGamePaused), &tmp, sizeof(tmp), 0);
	return tmp;
}