#pragma once

#include "C_Entity.h"

typedef struct
{
	float flMatrix [4][4];
}WorldToScreenMatrix;

class C_MyPlayer : public C_Entity
{
public:
	C_MyPlayer();

	void Update();
	void LoadConfiguration();

	float* getEyeVector(bool FromMem);

	DWORD getBase(bool FromMem);
	DWORD getViewVectorAddress(bool FromMem);

	WorldToScreenMatrix getWTSMatrix(bool FromMem);

private:
	DWORD ViewVectorAddress;

	int flickerCheck;

	WorldToScreenMatrix WorldToScreenMatrix;

};