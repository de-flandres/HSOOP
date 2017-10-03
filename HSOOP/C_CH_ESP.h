#pragma once

#include "C_Enemy.h"
#include "C_MyPlayer.h"
#include "C_Cheat.h"
#include "C_CH_Aimbot.h"

//-------ESP VARS--------------------------------------------------------------------------------------

const DWORD dw_vMatrix				=		0x5266A8;		//	[ 0x5266A8 ]
const DWORD dw_antiFlick			=		0x520B60;		//	[ 0x520B60 ]

class C_CH_ESP : public C_Cheat
{
public:
	C_CH_ESP(int UniqueCheatID);
	~C_CH_ESP();

	void __fastcall DrawESP(int x, int y, float distance, int EnemyID);
	void __fastcall DrawLine(int StartX, int StartY, int EndX, int EndY, COLORREF Pen);
	void __fastcall DrawBorderBox(int x, int y, int w, int h, int thickness, COLORREF CurrentColor);
	void __fastcall DrawFilledRect(int x, int y, int w, int h, COLORREF CurrentColor);
	void __fastcall DrawString(int x, int y, COLORREF color, const char* text);
	bool __fastcall WorldToScreen(float *from, float *to, bool FromMem);

	void perform();
	void LoadConfiguration();

private:
	RECT m_Rect; 
	HFONT Font;				//font we use to write text with
	COLORREF TextCOLOR;

	C_MyPlayer* Player;
	C_Enemy* EnemyList[MAX_PLAYERS];

	int iBorderThickness;

	int Color_Text_R;
	int Color_Text_G;
	int Color_Text_B;
};