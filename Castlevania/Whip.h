#pragma once
#include "Weapons.h"

using namespace std;

enum class WhipAniID
{
	IDTexWhip,
	idleWhipRight = 9999,
	idleWhipLeft = 8888
};

class CWhip : public CWeapons
{
	float x = 0;
	float y = 0;


	DWORD time;
	bool isUsingweapon;

public:

	void Update(DWORD dt);
	void Render();

};

