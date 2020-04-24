#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Flame.h"

CWhip * CWhip::__instance = NULL;

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		CGameObject::Update(dt);
		ChoiceAnimation();
		UpdatePosition(currentAniID);
		vector<LPCOLLISIONEVENT> coEvents;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		
		vector<LPCOLLISIONEVENT> coEventsResult;
		
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			if (animations->Get(currentAniID)->GetCurrentFrame() == 2)
			{
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
			}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	left = x;
	top = y;

	// whip front.
	if ((nx > 0 && x > xS) || (nx < 0 && x < xS))
	{
		switch (lv)
		{
		case WHIP_LV1:
			right = x + FRONT_WHIP_BBOX_WIDTH_LV1;
			bottom = y + FRONT_WHIP_BBOX_HEIGHT_LV1;
			break;
		case WHIP_LV2:
			right = x + FRONT_WHIP_BBOX_WIDTH_LV2;
			bottom = y + FRONT_WHIP_BBOX_HEIGHT_LV2;
		case WHIP_LV3:
			right = x + FRONT_WHIP_BBOX_WIDTH_LV3;
			bottom = y + FRONT_WHIP_BBOX_HEIGHT_LV3;
			break;
		}
	}
	else
	{
		right = x + BACK_WHIP_BBOX_WIDTH;
		bottom = y + BACK_WHIP_BBOX_HEIGHT;
	}
	
}

void CWhip::UpdatePosition(int aniID)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	
	float whipTexWidth;
	if (lv == WHIP_LV3)
	{
		whipTexWidth = FRONT_WHIP_BBOX_WIDTH_LV3;
	}
	else if (lv == WHIP_LV2)
	{
		whipTexWidth = FRONT_WHIP_BBOX_WIDTH_LV2;
	}
	else
	{
		whipTexWidth = FRONT_WHIP_BBOX_WIDTH_LV1;
	}

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniID);
	int nxw = CSimon::GetInstance()->GetDirection();

	if (ani->GetCurrentFrame() == 2)
	{
		x = (nxw > 0) ? 
			xS + SIMON_IDLE_BBOX_WIDTH :
			xS - whipTexWidth;
	}
	else
	{
		x = (nxw > 0) ? 
			xS - BACK_WHIP_BBOX_WIDTH : 
			xS + SIMON_IDLE_BBOX_WIDTH;
	}
	y = yS;
}

void CWhip::Render()
{
	CGameObject::Render();
}

void CWhip::SetVisible(bool visible)
{ 
	CGameObject::SetVisible(visible);
	if (this->visible)
		if (currentAniID > 0)
			this->ResetAnimationTimer(currentAniID);
}

bool CWhip::IsOverlapping(LPGAMEOBJECT obj)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	// When the whip is at the back of Simon, ignore it
	if ((nx > 0 && x < xS) || (nx < 0 && x > xS))
		return false;

	return CGameObject::IsOverlapping(obj);
}

void CWhip::ChoiceAnimation()
{
	nx = CSimon::GetInstance()->GetDirection();
	if (lv == WHIP_LV3)
	{
		currentAniID = (nx > 0) ? 
			((int)WhipAniID::idleWhippingRightLv3) : 
			((int)WhipAniID::idleWhippingLeftLv3);
	}
	else if (lv == WHIP_LV2)
	{
		currentAniID = (nx > 0) ?
			((int)WhipAniID::idleWhippingRightLv2) :
			((int)WhipAniID::idleWhippingLeftLv2);
	}
	else
	{
		currentAniID = (nx > 0) ?
			((int)WhipAniID::idleWhippingRight) :
			((int)WhipAniID::idleWhippingLeft);
	}
}

void CWhip::LvUp()
{
	if (lv == WHIP_LV1)
	{
		lv = WHIP_LV2;
	}
	else if (lv == WHIP_LV2)
	{
		lv = WHIP_LV3;
	}
}

CWhip * CWhip::GetInstance()
{
	if (__instance == NULL)__instance = new CWhip();

	return __instance;
}

CWhip::CWhip()
{
	visible = false;
	lv = WHIP_LV1;
}