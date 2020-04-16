#include "Whip.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"

CWhip * CWhip::__instance = NULL;

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (visible)
	{
		int nnx = CSimon::GetInstance()->GetDirection();
		currentAniID = (nnx > 0) ? ((int)WhipAniID::idleWhippingRight) : ((int)WhipAniID::idleWhippingLeft);
		CGameObject::Update(dt);
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
		right = x + FRONT_WHIP_BBOX_WIDTH;
		bottom = y + FRONT_WHIP_BBOX_HEIGHT;
	}
	
}

void CWhip::UpdatePosition(int aniID)
{
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);
	
	float whipTexWidth = FRONT_WHIP_BBOX_WIDTH;

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

	// When the rope is at the back of Simon, ignore it
	if ((nx > 0 && x < xS) || (nx < 0 && x > xS))
		return false;

	return CGameObject::IsOverlapping(obj);
}

CWhip * CWhip::GetInstance()
{
	if (__instance == NULL)__instance = new CWhip();

	return __instance;
}
