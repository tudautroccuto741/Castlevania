#include "Weapons.h"
	
CWeapons * CWeapons::__instance = NULL;

void CWeapons::Update(DWORD dt)
{

}

void CWeapons::Render()
{

}


CWeapons *CWeapons::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapons();
	return __instance;
}

