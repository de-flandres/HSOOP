#pragma once

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <thread>
#include <Windows.h>

#include "CFG_BUTTONS.h"
#include "CFG_COLORS.h"
#include "CFG_ACCOUNTS.h"
#include "CFG_GAMECONSTANTS.h"

#include "StaticFunctions.h"
#include "C_HackProcess.h"

using namespace std;

const Account LICENSED_ACCOUNTS[] =
{
  ACC_N2K
};

const LPCSTR SNTP_SERVERS_URL[] =
{
	"http://vk.com",
	"http://yandex.ru",
	"http://google.com",
	"http://amazon.com",
	"http://ebay.com",
	"http://facebook.com",
	"http://twitter.com",
	"http://linkedin.com",
	"http://youtube.com",
	"http://wikipedia.com",
};

#define GAME_WINDOW_NAME					"Left 4 Dead"
#define GAME_PROCESS_NAME					"left4dead.exe"

#define	CHEAT_VERSION						"v38_final"
#define CHEAT_NAME							"HunterSkill InstantHook"

#define	PRESS_TIMER							190
#define	UPDATE_TIME							150
#define STATIC_CHEATS_UPDATE_TIME			200
#define SLEEP_BETWEEN_CONNECT_TRIES			1000				// sizeof(SNTP_SERVERS_URL) * SLEEP_BETWEEN_CONNECT_TRIES(ms)
#define SLEEP_BETWEEN_HWID_GENERATION_TRIES	10000				// time in ms between hardware generation

#define MAX_PLAYERS							24					// maximum of players

#define MAX_PLAYERNAME_LENGTH				16

const DWORD dw_STEAMID						=	0x51A18;		// tier0_s.dll		0x41460
																// vstdlib_s.dll	0x41C9C
																// matchmaking.dll	0x51A18

const DWORD dw_STEAMID_Offsets[]			=	{ 0x8 };		// tier0_s.dll		0xC
																// vstdlib_s.dll	0x1EC
																// matchmaking.dll	0x8

const DWORD dw_GameScreenResolution			=	0x3B41C4;		// engine.dll

const DWORD dw_IsGameChatOpened				=	0x56B9A8;		// client.dll

const DWORD dw_IsSteamOpened				=	0xEE7C0;		// 0xEE7C0 // 0xEE910 // gameoverlayrenderer.dll

const DWORD dw_IsGamePaused					=	0x5BF428;		// engine.dll 0x57A1C0 // client.dll 0x5BF428 // vguimatsurface.dll 0x11F30C

const DWORD dw_PlayerBase					=	0x53F750;		// 0x53F750
const DWORD dw_EntityList					=	0x54E4BC;		// 0x54E4BC

const DWORD dw_BoneMatrix					=	0x660;			// PlayerBase // 0x660, 0x894, 0x8A4

const DWORD dw_Team							=	0xBC;			// PlayerBase
const DWORD dw_Health						=	0xC4;			// PlayerBase
const DWORD dw_Position						=	0xFC;			// PlayerBase // 0xFC // E80
const DWORD dw_IsSpawned					=	0x1BC;			// PlayerBase
const DWORD dw_LifeStatus					=	0x11F;			// PlayerBase

const DWORD dw_Attack						=	0x56DD40;		// client.dll
const DWORD dw_Attack2						=	0x56DD28;		// client.dll
const DWORD dw_Jump							=	0x56DD58;		// client.dll
const DWORD dw_Duck							=	0x56DCE0;		// client.dll

const DWORD dw_EntityListDistance			=	0x10;			//How far in memory is each enemy data

const DWORD dw_AngleRotation				=	0x3B5C68;		// engine.dll
const DWORD dw_AngleRotation_Offsets[]		=	{ 0x4AAC };		// dw_AngleRotation

const DWORD dw_MaxSpeed						=	0x1150;			// PlayerBase

const DWORD dw_CharacterType				=	0x24;			// PlayerBase
const DWORD dw_CharacterType_Offsets[]		=	{ 0x20,0x250 };	// dw_CharacterType

const DWORD dw_PlayerName					=	0x14;			// PlayerBase
const DWORD dw_PlayerName_Offsets[]			=	{ 0x638 };		// dw_PlayerName

const DWORD dw_CurrentWeaponID				=	0x15D8;			// PlayerBase
const DWORD dw_CurrentWeaponID_Offsets[]	=	{ 0x6C };		// dw_CurrentWeaponID

const DWORD dw_NumberOfPlayers				=	0x649FD8;		// server.dll

const DWORD dw_Y_diff						=	0xD4;			// PlayerBase