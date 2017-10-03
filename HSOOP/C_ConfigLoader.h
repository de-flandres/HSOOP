#pragma once

#include <fstream>
#include <iostream>
#include <Windows.h>
#include "CFG_LOADER_PARAMETERS.h"

#define		NUMBER_OF_SPACES	5

class C_ConfigLoader
{
public:
	C_ConfigLoader();
	~C_ConfigLoader();

	bool Open(int OpenMode);
	void Close();
	void CreateConfigFile();
	int getLengthOfLongestString(int StringID);
	int getLongestStringID();

	int _fastcall Load(string ConfigFilePath);

private:
	fstream ConfigFileStream;
};