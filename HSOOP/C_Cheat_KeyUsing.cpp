#include "C_Cheat_KeyUsing.h"

C_Cheat_KeyUsing::C_Cheat_KeyUsing(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{

}

int C_Cheat_KeyUsing::getKey()
{
	return iCheat_Key_Use;
}

void C_Cheat_KeyUsing::setKey(int NewKey)
{
	iCheat_Key_Use = NewKey;
}