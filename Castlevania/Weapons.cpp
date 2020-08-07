#include "Weapons.h"
#include "debug.h"
#include "Simon.h"
#include "Knife.h"
#include "Boomerang.h"
#include "Aquafina.h"
#include "Axe.h"

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
	case (int)Weapon::AQUAFINA:
		UseAquafina();
		break;
	case (int)Weapon::AXE:
		UseAxe();
		break;
	case (int)Weapon::WATCH:
		UseWatch();
		break;
	case (int)Weapon::BONE:
		UseBone();
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
	if(knife == NULL)
	{
		return;
	}
	knife->SetVisible(true);
	knife->nx = CSimon::GetInstance()->GetDirection();
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS + DISTANCE_OF_KNIFE_AND_SIMON;
	knife->SetPosition(xK, yK);
	CSimon::GetInstance()->SetHeart(1);
}

void CWeapons::UseBoomerang()
{
	LPGAMEOBJECT boom = GetWeapon((int)Weapon::BOOMERANG);
	if (boom == NULL) return;
	boom->SetVisible(true);
	boom->nx = CSimon::GetInstance()->GetDirection();
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xB = xS;
	float yB = yS + DISTANCE_OF_BOOMERANG_AND_SIMON;
	boom->SetPosition(xB, yB);
	CSimon::GetInstance()->SetHeart(1);
}

void CWeapons::UseAquafina()
{
	LPGAMEOBJECT aquafina = GetWeapon((int)Weapon::AQUAFINA);
	if (aquafina == NULL) return;
	aquafina->nx = CSimon::GetInstance()->GetDirection();
	aquafina->SetVisible(true);
	CSimon::GetInstance()->GetPosition(xS, yS);
	aquafina->SetPosition(xS, yS);
	CSimon::GetInstance()->SetHeart(1);
}

void CWeapons::UseAxe()
{
	LPGAMEOBJECT axe = GetWeapon((int)Weapon::AXE);
	if (axe == NULL) return;
	axe->nx = CSimon::GetInstance()->GetDirection();
	axe->SetVisible(true);
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS;
	axe->SetPosition(xK, yK);
	CSimon::GetInstance()->SetHeart(1);
}

void CWeapons::UseWatch()
{
	CSimon::GetInstance()->SetFreezing(true);
}

void CWeapons::UseBone()
{
	LPGAMEOBJECT bone = GetWeapon((int)Weapon::BONE);
	if (bone == NULL) return;
	bone->SetVisible(true);
}

CWeapons * CWeapons::GetInstance()
{
	if (__instance == NULL)
		__instance = new CWeapons();

	return __instance;
}
