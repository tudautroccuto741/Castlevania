#include "Board.h"
#include "PlayScence.h"
#include "GameObject.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{
	if (isStop)
	{
		return;
	}
	if (GetTickCount() - _count >= 1000)
	{
		_time--;
		_count = GetTickCount();
	}
}
void CBoard::Render()
{
	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(969)->Draw(cx, cy, 255);
	CSimon* simon = CSimon::GetInstance();	

	drawBoard->DrawNumber(6, cx + 110, cy + 12, simon->GetScore());
	drawBoard->DrawNumber(4, cx + 295, cy + 12, _time);
	drawBoard->DrawNumber(2, cx + 465, cy + 12, CGame::GetInstance()->GetCurrentSceneID());
	drawBoard->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart());
	drawBoard->DrawNumber(2, cx + 400, cy + 52, simon->GetLife());
	drawBoard->DrawEnergyBar(cx + 110, cy + 30, 0, simon->GetHealth());
	if (weapon != 0)
	{
		switch (weapon)
		{
		case (int)Item::KNIFE:
			sprites->Get(80001)->Draw(cx + 310, cy + 40);;
			break;
		case (int)Item::AXE:
			sprites->Get(1000016)->Draw(cx + 310, cy + 32);
			break;
		case (int)Item::AQUAFINA:
			sprites->Get(1000015)->Draw(cx + 310, cy + 32);
			break;
		case (int)Item::BOOMERANG:
			sprites->Get(90000)->Draw(cx + 310, cy + 32);
			break;
		case (int)Item::WATCH:
			sprites->Get(90010)->Draw(cx + 310, cy + 32);
			break;
		default:
			break;
		}
		if (_numberOfWeapon != 0)
		{
			if (_numberOfWeapon == 2)
			{
				sprites->Get(13014)->Draw(cx + 440, cy + 40);
			}
			else if (_numberOfWeapon == 3)
			{
				sprites->Get(13017)->Draw(cx + 440, cy + 40);
			}
		}

	}
	game = NULL;
	sprites = NULL;
	simon = NULL;
}

void CBoard::ChangeWeapon()
{
	switch (weapon)
	{
	case 0:
		SetWeapon((int)Item::NONE);
		break;
	case (int)Item::KNIFE:
		SetWeapon((int)Item::KNIFE);
		break;
	case (int)Item::AQUAFINA:
		SetWeapon((int)Item::AQUAFINA);
		break;
	case (int)Item::BOOMERANG:
		SetWeapon((int)Item::BOOMERANG);
		break;
	case (int)Item::AXE:
		SetWeapon((int)Item::AXE);
		break;
	default:
		break;
	}
}