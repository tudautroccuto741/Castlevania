#pragma once
#include "GameObject.h"
#include <unordered_map>

using namespace std;

class CWeapons
{
	unordered_map<int, vector<LPGAMEOBJECT>> weapons;
	static CWeapons * __instance;

public:
	void UseWeapon(int weaponName, LPGAMEOBJECT obj);
	void UseKnife();
	LPGAMEOBJECT GetWeapon(int weapon);
	void Add(int weaponName, LPGAMEOBJECT weapon);
	CWeapons() { ; }
	static CWeapons * GetInstance();
};

