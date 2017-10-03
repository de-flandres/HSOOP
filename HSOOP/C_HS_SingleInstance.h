#pragma once

#include "CFG_MAIN.h"

class C_HS_SingleInstance
{
public:
	C_HS_SingleInstance(TCHAR *strMutexName);
	~C_HS_SingleInstance();
	BOOL IsAnotherInstanceRunning();

protected:
	DWORD m_dwLastError;
	HANDLE m_hMutex;
};