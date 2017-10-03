#include "C_HS_SingleInstance.h"

C_HS_SingleInstance::C_HS_SingleInstance(TCHAR *strMutexName)
{
	//Make sure that you use a name that is unique for this application otherwise
	//two apps may think they are the same if they are using same name for
	//3rd parm to CreateMutex
	m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
	m_dwLastError = GetLastError(); //save for use later...
}
C_HS_SingleInstance::~C_HS_SingleInstance()
{
	if (m_hMutex)  //Do not forget to close handles.
	{
		CloseHandle(m_hMutex); //Do as late as possible.
		m_hMutex = NULL; //Good habit to be in.
	}
}
BOOL C_HS_SingleInstance::IsAnotherInstanceRunning()
{
	return (ERROR_ALREADY_EXISTS == m_dwLastError);
}