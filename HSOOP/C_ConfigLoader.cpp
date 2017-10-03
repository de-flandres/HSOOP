#include "C_ConfigLoader.h"

C_ConfigLoader::C_ConfigLoader()
{
	CreateConfigFile();
}

C_ConfigLoader::~C_ConfigLoader()
{
	Close();
}

void C_ConfigLoader::CreateConfigFile()
{
	ConfigFileStream.open(CONFIGURATION_PATH, ios::out | ios::_Noreplace); // here
	if (ConfigFileStream.is_open() == true)	// if file exists, it will not execute (see upper _Noreplace)
	{
		int tmpLength = getLengthOfLongestString(getLongestStringID());

		for (int i = 0; i < sizeof(CONFIG_FILE) / sizeof(CONFIG); i++)
		{
			ConfigFileStream << CONFIG_FILE[i].strParam << CONFIGURATION_SEPARATOR << CONFIG_FILE[i].defParam;

			for (int j = 0; j < (tmpLength - getLengthOfLongestString(i)) + NUMBER_OF_SPACES; j++) ConfigFileStream << " ";

			ConfigFileStream << CONFIGURATION_COMMENT_SEPARATOR;

			for (int j = 0; j < NUMBER_OF_SPACES; j++) ConfigFileStream << " ";
			
			char* tempComment = new char[CONFIG_FILE[i].strComment.length()];
			sprintf(tempComment, CONFIG_FILE[i].strComment.c_str(), CONFIG_FILE[i].defParam);
			ConfigFileStream << tempComment;
			delete [] tempComment;
			
			if (i + 1 < sizeof(CONFIG_FILE) / sizeof(CONFIG)) ConfigFileStream << endl;
		}

		ConfigFileStream << endl << endl << endl << endl;
		for (int i = 0; i < sizeof(LOADER_CHEAT_INFO) / sizeof(string); i++)
		{
			ConfigFileStream << LOADER_CHEAT_INFO[i] << endl;
		}
		ConfigFileStream << endl;
	}
	Close();
}

int C_ConfigLoader::getLongestStringID()
{
	unsigned int maxLength = CONFIG_FILE[0].strParam.length();
	unsigned int stringID = 0;
	for (int i = 0; i < sizeof(CONFIG_FILE) / sizeof(CONFIG); i++)
	{
		if (CONFIG_FILE[i].strParam.length() > maxLength)
		{
			maxLength = CONFIG_FILE[i].strParam.length();
			stringID = i;
		}
	}
	return stringID;
}

int C_ConfigLoader::getLengthOfLongestString(int StringID)
{
	unsigned int maxLength = CONFIG_FILE[StringID].strParam.length();
	maxLength += CONFIGURATION_SEPARATOR.length();

	unsigned int numOfDigits = 0;
	unsigned int tmp = CONFIG_FILE[StringID].defParam;
	do
	{
		++numOfDigits;
		tmp /= 10;
	} while (tmp);
	maxLength += numOfDigits;

	return maxLength;
}

bool C_ConfigLoader::Open(int OpenMode)
{
	ConfigFileStream.open(CONFIGURATION_PATH, OpenMode);
	if (ConfigFileStream.is_open() == false) CreateConfigFile();

	return ConfigFileStream.is_open();
}
void C_ConfigLoader::Close()
{
	if (ConfigFileStream.is_open() == true) ConfigFileStream.close();
}

int _fastcall C_ConfigLoader::Load(string SearchingString)
{
	string line;
	string tmp;
	while (getline(ConfigFileStream, line))
	{
		if (line.find(SearchingString) == 0)
		{
			tmp = line.substr(SearchingString.length() + CONFIGURATION_SEPARATOR.length());
			ConfigFileStream.seekp(0); // !!!
			return atoi(tmp.c_str());
		}
	}
	return 0;
}