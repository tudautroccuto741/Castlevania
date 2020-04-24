#include "WeaponKnife.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Flame.h"
#include "Knife.h"

CWeaponKnife * CWeaponKnife::__instance = NULL;

void CWeaponKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		ChoiceAnimation();
		Attack();
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		vector<LPCOLLISIONEVENT> coEventsResult;

		float min_tx, min_ty, nx = 0, ny;
		
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx;
		
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (this->IsOverlapping(coObjects->at(i)))
			{
				if (dynamic_cast<CCandle *>(coObjects->at(i)))
				{
					coObjects->at(i)->Destroy();
				}
			}
		}
		
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CWeaponKnife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	CKnife * knife = new CKnife();
	knife->GetBoundingBox(left, top, right, bottom);
}

void CWeaponKnife::ChoiceAnimation()
{
	CKnife * knife = new CKnife();
	int nxKn;
	nxKn = CSimon::GetInstance()->GetDirection();
	//knife->SetCurrentAniID
	(currentAniID) = (nxKn > 0) ?
		(int)KnifeAniID::knifeRight :
		(int)KnifeAniID::knifeLeft;
}

void CWeaponKnife::Render()
{
	CGameObject::Render();
}

void CWeaponKnife::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	if (this->visible)
		if (currentAniID > 0)
			this->ResetAnimationTimer(currentAniID);
}

bool CWeaponKnife::IsOverlapping(LPGAMEOBJECT obj)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	return CGameObject::IsOverlapping(obj);
}

void CWeaponKnife::Attack()
{
	float left, top, right, bottom;
	int nxKn;
	this->SetVisible(true);
	CSimon::GetInstance()->GetBoundingBox(left, top, right, bottom);
	nxKn = CSimon::GetInstance()->GetDirection();
	//float xS, yS;
	x = left;
	y = top - 6;
	if (nxKn > 0)
	{
		x += dx;
	}
	else
	{
		x -= dx;
	}
	SetPosition(x, y);
}

CWeaponKnife * CWeaponKnife::GetInstance()
{
	if (__instance == NULL)__instance = new CWeaponKnife();

	return __instance;
}

CWeaponKnife::CWeaponKnife()
{
	visible = false;
}