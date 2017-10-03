#pragma once

#include "C_Cheat.h"

class C_Cheat_KeyUsing : public C_Cheat
{
public:
	virtual int getKey();
	virtual void setKey(int NewKey);

protected:
	C_Cheat_KeyUsing(int UniqueCheatID);

	int iCheat_Key_Use;
};