#include "Weapons.h"
#include "debug.h"
#include "Simon.h"
#include "Knife.h"
#include "Boomerang.h"

CWeapons * CWeapons::__instance = NULL;

//	Add the corresponding weapon with the weapon name

void CWeapons::Add(int weaponName, LPGAMEOBJECT weapon)
{
	weapons[weaponName].push_back(weapon);
}

void CWeapons::ChoiceWeapon(int weaponName)
{
	switch (weaponName)
	{
	case (int)Weapon::KNIFE:
		UseKnife();
		break;
	case (int)Weapon::BOOMERANG:
		UseBoomerang();
		break;
	default:
		break;
	}
}

// Get weapon and return the weapon object
LPGAMEOBJECT CWeapons::GetWeapon(int weapon)
{
	if (weapons[weapon].empty())
		DebugOut(L"\n[ERROR] No weapons");
	else
	{
		for (auto i = weapons[weapon].begin(); i != weapons[weapon].end(); ++i)
		{	
			if ((*i)->GetVisible() == false)
			{
				return (*i);
				break;
			}
		}
	}
}

void CWeapons::UseKnife()
{
	LPGAMEOBJECT knife = GetWeapon((int)Weapon::KNIFE);
	knife->SetVisible(true);
	knife->nx = CSimon::GetInstance()->GetDirection();
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS + DISTANCE_OF_KNIFE_AND_SIMON;
	knife->SetPosition(xK, yK);
}

void CWeapons::UseBoomerang()
{
	LPGAMEOBJECT boom = GetWeapon((int)Weapon::BOOMERANG);
	boom->SetVisible(true);
	boom->nx = CSimon::GetInstance()->GetDirection();
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS + DISTANCE_OF_BOOMERANG_AND_SIMON;
	boom->SetPosition(xK, yK);
}

CWeapons * CWeapons::GetInstance()
{
	if (__instance == NULL)
		__instance = new CWeapons();

	return __instance;
}
