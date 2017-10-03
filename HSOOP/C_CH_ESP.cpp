#include "C_CH_ESP.h"
#include <windowsx.h>

C_CH_ESP::C_CH_ESP(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	Player = new C_MyPlayer();
	for(int i = 0; i < MAX_PLAYERS; i++) EnemyList[i] = new C_Enemy(i);

	LoadConfiguration();
}

C_CH_ESP::~C_CH_ESP()
{
	delete Player;
	for(int i = 0; i < MAX_PLAYERS; i++) delete EnemyList[i];
}

void C_CH_ESP::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_ENABLED].strParam) == 0 ? false : true;
	iBorderThickness = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_BORDER].strParam);
	Color_Text_R = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TEXT_R].strParam);
	Color_Text_G = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TEXT_G].strParam);
	Color_Text_B = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_ESP_COLOR_TEXT_B].strParam);
	Process->ConfigLoader->Close();

	TextCOLOR = RGB(Color_Text_R, Color_Text_G, Color_Text_B);

	for (int i = 0; i < MAX_PLAYERS; i++) EnemyList[i]->LoadConfiguration();
}

void C_CH_ESP::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return; //ExitThread(0);

	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(ESP_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}

	if(bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		GetWindowRect(Process->GameWindow, &m_Rect);
		for(int i = 0; i < MAX_PLAYERS; i++)
		{
			Player->getBase(true);
			EnemyList[i]->getBase(i, true);
			if(EnemyList[i]->getHealth(true) < 1
				|| EnemyList[i]->IsAlive(true) == false
				|| EnemyList[i]->getTeam(true) == Player->getTeam(true)
				|| EnemyList[i]->getTeam(true) == TEAM_SPEC
				|| EnemyList[i]->IsEntityBaseExist() == false) continue;

			//if(EnemyList[i]->IsSpawned(true) == false) continue;

			float EnemyXY[3];

			EnemyList[i]->getPosition(true)[2] -= flAimEspDifference*2;

			if(WorldToScreen(EnemyList[i]->getPosition(false), EnemyXY, true))
			{
				DrawESP((int)(EnemyXY[0] - m_Rect.left), (int)(EnemyXY[1] - m_Rect.top), Get3dDistance(Player->getPosition(true), EnemyList[i]->getPosition(false)), i);
			}
		}
	}
}

void __fastcall C_CH_ESP::DrawESP(int x, int y, float distance, int EnemyID)
{
	float chartype_width_factor = 1.0f;
	float chartype_height_factor = 1.0f;

	if (EnemyList[EnemyID]->getTeam(true) == TEAM_INFECT)
	{
		switch (EnemyList[EnemyID]->getCharType(true))
		{
		case CHARACTER_TYPE_BOOMER: { chartype_width_factor = 1.5f; chartype_height_factor = 1.1f; break; }
		case CHARACTER_TYPE_HUNTER: { chartype_width_factor = 1.0f; chartype_height_factor = 1.0f; break; }
		case CHARACTER_TYPE_SMOKER: { chartype_width_factor = 1.1f; chartype_height_factor = 1.3f; break; }
		case CHARACTER_TYPE_TANK: { chartype_width_factor = 2.0f; chartype_height_factor = 1.2f; break; }
		default: { chartype_width_factor = 1.0f; chartype_height_factor = 1.0f; break; }
		}
	}

	int width = (int)( ((Process->GetGameScreenResolution(0, false) * 10.0f)/distance) * chartype_width_factor); // 21000
	int height = (int)( ((EnemyList[EnemyID]->getYDiff(true) * (Process->GetGameScreenResolution(1, false) * 0.6f))/distance) * chartype_height_factor ); // 650

	DrawBorderBox(x-(width/2), y-height, width, height, iBorderThickness, EnemyList[EnemyID]->getESPColor());

	/*if(EnemyID == Process->NearestEnemyIdInEnemyList && Aimbot->GetStatus())
	{
		DrawLine((m_Rect.right - m_Rect.left)/2, m_Rect.bottom - m_Rect.top, x, y, SnapLineCOLOR); // !X!
	}*/

	stringstream Health;
	stringstream CharType;

	Health << "HP: " << (int)EnemyList[EnemyID]->getHealth(false);
	CharType << EnemyList[EnemyID]->getCharTypeString(true);

	char* HealthText = new char[Health.str().size()+1];
	char* CharTypeText = new char[CharType.str().size() + 1];

	strcpy_s(HealthText, Health.str().size() + 1, Health.str().c_str());
	strcpy_s(CharTypeText, CharType.str().size() + 1, CharType.str().c_str());

	DrawString(x, y - height - 16, TextCOLOR, HealthText);
	DrawString(x, y + 3, TextCOLOR, CharTypeText);

	delete [] HealthText;
	delete [] CharTypeText;
}

void __fastcall C_CH_ESP::DrawLine(int StartX, int StartY, int EndX, int EndY, COLORREF Pen)
{
	int a;
	int b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, iBorderThickness, Pen);
	hOPen = (HPEN)SelectObject(Process->HDC_Desktop, hNPen);
	MoveToEx(Process->HDC_Desktop, StartX, StartY, NULL);
	a = LineTo(Process->HDC_Desktop, EndX, EndY);
	DeleteObject(SelectObject(Process->HDC_Desktop, hOPen));
}

void __fastcall C_CH_ESP::DrawBorderBox(int x, int y, int w, int h, int thickness, COLORREF CurrentColor)
{
	DrawFilledRect(x, y, w, thickness, CurrentColor);
	DrawFilledRect( x, y, thickness, h, CurrentColor);
	DrawFilledRect((x + w), y, thickness, h, CurrentColor);
	DrawFilledRect(x, y + h, w+thickness, thickness, CurrentColor);
}

void __fastcall C_CH_ESP::DrawFilledRect(int x, int y, int w, int h, COLORREF CurrentColor)
{
	RECT rect = { x, y, x + w, y + h };
	HBRUSH hbrush = CreateSolidBrush(CurrentColor);
	FillRect(Process->HDC_Desktop, &rect, hbrush);
	DeleteObject(hbrush);
}

void __fastcall C_CH_ESP::DrawString(int x, int y, COLORREF color, const char* text)
{	
	SetTextAlign(Process->HDC_Desktop,TA_CENTER|TA_NOUPDATECP);

	SetBkColor(Process->HDC_Desktop,COLOR_BLACK);
	SetBkMode(Process->HDC_Desktop, OPAQUE);

	SetTextColor(Process->HDC_Desktop,color);

	SelectObject(Process->HDC_Desktop, Font);

	TextOutA(Process->HDC_Desktop, x, y, text, strlen(text));

	DeleteObject(Font);
}

bool __fastcall C_CH_ESP::WorldToScreen(float *from, float *to, bool FromMem)
{
	float world = 0.0f;

	to[0] = Player->getWTSMatrix(FromMem).flMatrix[0][0] * from[0] +
			Player->getWTSMatrix(FromMem).flMatrix[0][1] * from[1] +
			Player->getWTSMatrix(FromMem).flMatrix[0][2] * from[2] +
			Player->getWTSMatrix(FromMem).flMatrix[0][3];

	to[1] = Player->getWTSMatrix(FromMem).flMatrix[1][0] * from[0] +
			Player->getWTSMatrix(FromMem).flMatrix[1][1] * from[1] +
			Player->getWTSMatrix(FromMem).flMatrix[1][2] * from[2] +
			Player->getWTSMatrix(FromMem).flMatrix[1][3];

	world = Player->getWTSMatrix(FromMem).flMatrix[3][0] * from[0] +
			Player->getWTSMatrix(FromMem).flMatrix[3][1] * from[1] +
			Player->getWTSMatrix(FromMem).flMatrix[3][2] * from[2] +
			Player->getWTSMatrix(FromMem).flMatrix[3][3];

	if(world > 0.01f)
	{
		float invw = 1.0f / world;
		to[0] *= invw;
		to[1] *= invw;

		int width = (int)(m_Rect.right - m_Rect.left);
		int height = (int)(m_Rect.bottom - m_Rect.top);

		float x = width / 2.0f;
		float y = height / 2.0f;

		x += 0.5f * to[0] * width + 0.5f;
		y -= 0.5f * to[1] * height + 0.5f;
		
		to[0] = x + m_Rect.left;
		to[1] = y + m_Rect.top;

		return true;
	}
	else
	{
		to[0] = -1.0f;
		to[1] = -1.0f;
	}

	return false;
}