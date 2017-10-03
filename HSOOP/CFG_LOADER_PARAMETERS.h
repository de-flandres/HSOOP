#pragma once

#include <string>
#include "CFG_GAMECONSTANTS.h"
#include "CFG_BUTTONS.h"

using namespace std;

const string CONFIGURATION_PATH = "HunterSkill_config.txt";
const string CONFIGURATION_SEPARATOR = "=";
const string CONFIGURATION_COMMENT_SEPARATOR = "|";

const typedef struct
{
	string strParam;
	int defParam;
	string strComment;

} CONFIG;

const enum LOADER
{
	eLOADER_HUNTERSKILL_KEY_RELOADCONFIG,
	eLOADER_HUNTERSKILL_KEY_TURN,
	eLOADER_HUNTERSKILL_KEY_EXIT,

	eLOADER_FULLBRIGHT_ENABLED,
	eLOADER_NOSMOKE_ENABLED,
	eLOADER_NOFOG_ENABLED,
	eLOADER_GLOWHACK_ENABLED,
	eLOADER_INCAPNORECOIL_ENABLED,
	eLOADER_NORECOIL_ENABLED,

	eLOADER_ESP_ENABLED,
	eLOADER_ESP_BORDER,
	eLOADER_ESP_COLOR_SMOKER_GHOST_R,
	eLOADER_ESP_COLOR_SMOKER_GHOST_G,
	eLOADER_ESP_COLOR_SMOKER_GHOST_B,
	eLOADER_ESP_COLOR_SMOKER_SPAWNED_R,
	eLOADER_ESP_COLOR_SMOKER_SPAWNED_G,
	eLOADER_ESP_COLOR_SMOKER_SPAWNED_B,
	eLOADER_ESP_COLOR_BOOMER_GHOST_R,
	eLOADER_ESP_COLOR_BOOMER_GHOST_G,
	eLOADER_ESP_COLOR_BOOMER_GHOST_B,
	eLOADER_ESP_COLOR_BOOMER_SPAWNED_R,
	eLOADER_ESP_COLOR_BOOMER_SPAWNED_G,
	eLOADER_ESP_COLOR_BOOMER_SPAWNED_B,
	eLOADER_ESP_COLOR_HUNTER_GHOST_R,
	eLOADER_ESP_COLOR_HUNTER_GHOST_G,
	eLOADER_ESP_COLOR_HUNTER_GHOST_B,
	eLOADER_ESP_COLOR_HUNTER_SPAWNED_R,
	eLOADER_ESP_COLOR_HUNTER_SPAWNED_G,
	eLOADER_ESP_COLOR_HUNTER_SPAWNED_B,
	eLOADER_ESP_COLOR_TANK_GHOST_R,
	eLOADER_ESP_COLOR_TANK_GHOST_G,
	eLOADER_ESP_COLOR_TANK_GHOST_B,
	eLOADER_ESP_COLOR_TANK_SPAWNED_R,
	eLOADER_ESP_COLOR_TANK_SPAWNED_G,
	eLOADER_ESP_COLOR_TANK_SPAWNED_B,
	eLOADER_ESP_COLOR_TEXT_R,
	eLOADER_ESP_COLOR_TEXT_G,
	eLOADER_ESP_COLOR_TEXT_B,

	eLOADER_AIMBOT_ENABLED,
	eLOADER_AIMBOT_KEY_USE,
	eLOADER_AIMBOT_ANGLE,
	eLOADER_AIMBOT_SMOOTH,
	eLOADER_AIMBOT_RANGE,
	eLOADER_AIMBOT_BONUENUM,
	eLOADER_AIMBOT_AUTOSHOOT,
	eLOADER_AIMBOT_AUTOMOUSE2,
	eLOADER_AIMBOT_TYPE,

	eLOADER_BUNNYHOP_ENABLED,
	eLOADER_BUNNYHOP_KEY_USE,

	eLOADER_CEILING_ENABLED,
	eLOADER_CEILING_KEY_USE,
	eLOADER_CEILING_CLICKPAUSE
};

const CONFIG CONFIG_FILE[] =
{
	{ "hunterskill:key:reloadconfig",	CHEAT_RELOADCFG_BUTTON,	"[default:%d]          Key-id to reload CFG. See ids here: www.cherrytree.at/misc/vk.htm" },
	{ "hunterskill:key:turn",			CHEAT_TURN_BUTTON,		"[default:%d]           Key-id to turn ON/OFF all cheat-functions" },
	{ "hunterskill:key:exit",			CHEAT_EXIT_BUTTON,		"[default:%d]           Key-id to turn OFF all functions and close cheat" },

	{ "fullbright:enabled",				true,					"[0/1:default:%d]        is fullbright enabled" },
	{ "nosmoke:enabled",				false,					"[0/1:default:%d]        is nosmoke enabled" },
	{ "nofog:enabled",					false,					"[0/1:default:%d]        is nofog enabled" },
	{ "glowhack:enabled",				false,					"[0/1:default:%d]        is glowhack enabled" },
	{ "incapnorecoil:enabled",			true,					"[0/1:default:%d]        is incapnorecoil enabled" },
	{ "norecoil:enabled",				false,					"[0/1:default:%d]        is norecoil enabled" },

	{ "esp:enabled",					false,					"[0/1:default:%d]        is esp enabled" },
	{ "esp:border",						2,						"[1/5:default:%d]        esp border thickness" },
	{ "esp:color:smoker:ghost:R",		255,					"[0/255:default:%d]    esp color smoker as ghost (RED)" },
	{ "esp:color:smoker:ghost:G",		255,					"[0/255:default:%d]    esp color smoker as ghost (GREEN)" },
	{ "esp:color:smoker:ghost:B",		0,						"[0/255:default:%d]      esp color smoker as ghost (BLUE)" },
	{ "esp:color:smoker:spawned:R",		0,						"[0/255:default:%d]      esp color smoker as spawned (RED)" },
	{ "esp:color:smoker:spawned:G",		255,					"[0/255:default:%d]    esp color smoker as spawned (GREEN)" },
	{ "esp:color:smoker:spawned:B",		0,						"[0/255:default:%d]      esp color smoker as spawned (BLUE)" },
	{ "esp:color:boomer:ghost:R",		255,					"[0/255:default:%d]    esp color boomer as ghost (RED)" },
	{ "esp:color:boomer:ghost:G",		153,					"[0/255:default:%d]    esp color boomer as ghost (GREEN)" },
	{ "esp:color:boomer:ghost:B",		153,					"[0/255:default:%d]    esp color boomer as ghost (BLUE)" },
	{ "esp:color:boomer:spawned:R",		153,					"[0/255:default:%d]    esp color boomer as spawned (RED)" },
	{ "esp:color:boomer:spawned:G",		0,						"[0/255:default:%d]      esp color boomer as spawned (GREEN)" },
	{ "esp:color:boomer:spawned:B",		102,					"[0/255:default:%d]    esp color boomer as spawned (BLUE)" },
	{ "esp:color:hunter:ghost:R",		0,						"[0/255:default:%d]      esp color hunter as ghost (RED)" },
	{ "esp:color:hunter:ghost:G",		255,					"[0/255:default:%d]    esp color hunter as ghost (GREEN)" },
	{ "esp:color:hunter:ghost:B",		255,					"[0/255:default:%d]    esp color hunter as ghost (BLUE)" },
	{ "esp:color:hunter:spawned:R",		255,					"[0/255:default:%d]    esp color hunter as spawned (RED)" },
	{ "esp:color:hunter:spawned:G",		0,						"[0/255:default:%d]      esp color hunter as spawned (GREEN)" },
	{ "esp:color:hunter:spawned:B",		0,						"[0/255:default:%d]      esp color hunter as spawned (BLUE)" },
	{ "esp:color:tank:ghost:R",			0,						"[0/255:default:%d]      esp color tank as ghost (RED)" },
	{ "esp:color:tank:ghost:G",			0,						"[0/255:default:%d]      esp color tank as ghost (GREEN)" },
	{ "esp:color:tank:ghost:B",			0,						"[0/255:default:%d]      esp color tank as ghost (BLUE)" },
	{ "esp:color:tank:spawned:R",		255,					"[0/255:default:%d]    esp color tank as spawned (RED)" },
	{ "esp:color:tank:spawned:G",		127,					"[0/255:default:%d]    esp color tank as spawned (GREEN)" },
	{ "esp:color:tank:spawned:B",		0,						"[0/255:default:%d]      esp color tank as spawned (BLUE)" },
	{ "esp:color:text:R",				0,						"[0/255:default:%d]      esp color text (RED)" },
	{ "esp:color:text:G",				255,					"[0/255:default:%d]    esp color text (GREEN)" },
	{ "esp:color:text:B",				255,					"[0/255:default:%d]    esp color text (BLUE)" },

	{ "aimbot:enabled",					false,					"[0/1:default:%d]        is aimbot enabled" },
	{ "aimbot:key:use",					AIMBOT_BUTTON,			"[default:%d]          Key-id for using aimbot" },
	{ "aimbot:angle",					20,						"[1/180:default:%d]     FOV for aimbot" },
	{ "aimbot:smooth",					2,						"[0/100:default:%d]      smoothing value" },
	{ "aimbot:range",					500,					"[1/50000:default:%d]  ingame range for aimbot" },
	{ "aimbot:bonenum",					11,						"[0/52:default:%d]      the number of bone to aim" },
	{ "aimbot:autoshoot",				true,					"[0/1:default:%d]        is autoshooting enabled" },
	{ "aimbot:automouse2",				true,					"[0/1:default:%d]        is auto M2 button enabled" },
	{ "aimbot:type",					HITBOX,					"[0/1:default:%d]        type aimbot(SKIN/HITBOX)" },

	{ "bunnyhop:enabled",				true,					"[0/1:default:%d]        is bunnyhop enabled" },
	{ "bunnyhop:key:use",				BUNNYHOP_BUTTON,		"[default:%d]          Key-id for using bunnyhop" },

	{ "ceiling:enabled",				true,					"[0/1:default:%d]        is ceiling enabled" },
	{ "ceiling:key:use",				CEILING_BUTTON,			"[default:%d]           Key-id for using ceiling" },
	{ "ceiling:clickpause:ms",			50,						"[default:%d]           Some pause between ceiling auto-clicks in milliseconds" }

};

const string LOADER_CHEAT_INFO[] =
{
	"*********************************************",
	"*___________________________________________*",
	"*_______HunterSkill Left4Dead by aXe________*",
	"*______InstantHook Configuration File_______*",
	"*__________Awakening Pulse L4D-Team_________*",
	"*______Engine, aXe, Modest, KpuoH, Bruce____*",
	"*__________Best Momories 2013-2016__________*",
	"*___________________________________________*",
	"*********************************************",
};