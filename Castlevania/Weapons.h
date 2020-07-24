#pragma once
#include "GameObject.h"
#include <unordered_map>

using namespace std;

class CWeapons
{
	unordered_map<int, vector<LPGAMEOBJECT>> weapons;
	static CWeapons * __instance;
	float xS, yS;
	

public:
	void ChoiceWeapon(int weaponName);
	void UseKnife();
	void UseBoomerang();
	void UseAquafina();
	void UseAxe();
	void UseWatch();
	void UseBone();
	LPGAMEOBJECT GetWeapon(int weapon);
	void Add(int weaponName, LPGAMEOBJECT weapon);
	CWeapons() { ; }
	static CWeapons * GetInstance();
};


