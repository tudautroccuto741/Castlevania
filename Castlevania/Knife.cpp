#include "Knife.h"
#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Flame.h"
#include "Knife.h"

CKnife * CKnife::__instance = NULL;

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += x * dt;
	if (visible)
	{
		ChoiceAnimation();
		UpdatePosition();
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

		vector<LPCOLLISIONEVENT> coEventsResult;

		float min_tx, min_ty, nx = 0, ny;
		
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx;
		y += min_ty * dy;
		
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

void CKnife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	CKnifeItem * knife = new CKnifeItem();
	knife->GetBoundingBox(left, top, right, bottom);
}

void CKnife::ChoiceAnimation()
{
	int nxKn;
	nxKn = CSimon::GetInstance()->GetDirection();
	currentAniID = (nxKn > 0) ?
		(int)KnifeAniID::knifeRight :
		(int)KnifeAniID::knifeLeft;
}

void CKnife::Render()
{
	CGameObject::Render();
}

void CKnife::SetVisible(bool visible)
{
	CGameObject::SetVisible(visible);
	if (this->visible)
		if (currentAniID > 0)
			this->ResetAnimationTimer(currentAniID);
}

bool CKnife::IsOverlapping(LPGAMEOBJECT obj)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	return CGameObject::IsOverlapping(obj);
}

void CKnife::UpdatePosition()
{
	int nxKn;
	this->SetVisible(true);
	nxKn = CSimon::GetInstance()->GetDirection();
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	float xK = xS;
	float yK = yS + 6;
	SetPosition(xK, yK);
}

CKnife * CKnife::GetInstance()
{
	if (__instance == NULL)__instance = new CKnife();

	return __instance;
}

CKnife::CKnife()
{
	visible = false;
}