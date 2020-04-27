#include "Weapons.h"
#include "debug.h"
#include "Simon.h"
#include "Knife.h"

CWeapons * CWeapons::__instance = NULL;

/*
	Add the given item to the collection according to item name
*/
void CWeapons::Add(int weaponName, LPGAMEOBJECT weapon)
{
	weapon->SetVisible(false);
	weapons[weaponName].push_back(weapon);
}
void CWeapons::UseWeapon(int weaponName, LPGAMEOBJECT obj)
{
	switch (weaponName)
	{
	case (int)Weapon::KNIFE:
		UseKnife();
		break;
	default:
		break;
	}
}


LPGAMEOBJECT CWeapons::GetWeapon(int weapon)
{
	
	if (weapons[weapon].empty())
		DebugOut(L"\n[ERROR] No weapons");
	else
	{
		for (auto it = weapons[weapon].begin(); it != weapons[weapon].end(); ++it)
		{
			if ((*it)->GetVisible() == false)
			{
				//(*it)->SetVisible(true);
				return (*it);
				break;
			}
		}
	}
}

void CWeapons::UseKnife()
{
	LPGAMEOBJECT knife = GetWeapon((int)Weapon::KNIFE);
	int nxKn;
	knife->SetVisible(true);
	nxKn = CSimon::GetInstance()->GetDirection();
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS + DISTANCE_OF_KNIFE_AND_SIMON;
	knife->SetPosition(xK, yK);

}


CWeapons * CWeapons::GetInstance()
{
	if (__instance == NULL)
		__instance = new CWeapons();

	return __instance;
}
