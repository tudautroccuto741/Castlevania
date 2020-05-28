#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"
#include "Textures.h"
#include "Flames.h"
#include "Game.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;

	visible = false;
	animations = CAnimations::GetInstance();
	currentAniID = -1;
	lastAniID = -1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO) // 2 obj dang di chuyen
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;
	
	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy); // lay v cua doi tuong kia

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,  
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

// Choose the smallest t on each axis to select the corresponding collision object
void CGameObject::FilterCollision( 
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 100);
}

// rearrange the frames
void CGameObject::ResetAnimation(int aniID)
{
	animations->GetInstance()->Get(aniID)->SetCurrentFrame(-1);
}

void CGameObject::Destroy()
{
	CFlames::GetInstance()->ShowFlame(this);
	this->SetVisible(false);
}

bool CGameObject::IsOverlapping(LPGAMEOBJECT obj)
{
	float left, top, right, bottom;
	float leftObj, topObj, rightObj, bottomObj;

	obj->GetBoundingBox(leftObj, topObj, rightObj, bottomObj);
	GetBoundingBox(left, top, right, bottom);

	if (obj->GetVisible()) 
	{
		if (left < rightObj && right > leftObj &&
			top < bottomObj && bottom > topObj)
			return true;
	}
	return false;
}

bool CGameObject::IsInViewport()
{
	//float cx, cy;
	//CGame *game = CGame::GetInstance();
	//cx -= game->GetScreenWidth() / 2;
	//cy -= game->GetScreenHeight() / 2;
	//// The viewport bounding box
	////float vpLeft, vpTop, vpRight, vpBottom;
	////cameraInstance->GetBoundingBox(vpLeft, vpTop, vpRight, vpBottom);

	//// The object bounding box
	//float left, top, right, bottom;
	//this->GetBoundingBox(left, top, right, bottom);

	//if (cx > right || cy > bottom
	//	|| cx < left || cy < top)
	//	return false;

	return true;
}

void CGameObject::Untouchable()
{
	if (GetTickCount() - start_untouchable > 200)
		start_untouchable = 0;
	else vx = vy = 0;
}

void CGameObject::BeHit(int damage)
{
	if (start_untouchable == 0)
	{
		if (health > 0)
			health -= damage;

		// If killed..
		if (health <= 0)
		{
			this->Destroy();
		}

		// If the object is still alive
		else
			start_untouchable = GetTickCount();
	}
}

void CGameObject::Render()
{
	animations->Get(currentAniID)->Render(x, y, 255);

	this->RenderBoundingBox();
}

CGameObject::~CGameObject()
{
}