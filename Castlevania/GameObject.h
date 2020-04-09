#pragma once
#include"GameObject.h"
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Animation.h"
#include <algorithm>
#include"Animations.h"

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
public:
	float x;
	float y;

	float vx;
	float vy;

	bool visible;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	int nx;

	CAnimations* animations;

	DWORD dt;

	int currentState;

	int currentAniID;
	int lastAniID;


public:
	//position
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }

	//speed
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	//nx
	void SetDirection(int nx) { this->nx = nx; }
	int GetDirection() { return this->nx; }

	//state
	void SetState(int state) { this->currentState = state; }
	int GetState() { return this->currentState; }

	//currentAni
	void SetCurrentAniID(int aniID) { this->currentAniID = aniID; }
	int GetCurrentAniID() { return this->currentAniID; }

	//Visible
	virtual void SetVisible(bool visible) { this->visible = visible; }
	bool GetVisible() { return this->visible; }

	
	void RenderBoundingBox();

	//2 object moving
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);

	// va cham giua doi tuong hien tai 
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents); 
	
	//cac doi tuong dung dau tien theo truc x va truc y																						//	voi ds cac doi tuong
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
		
	void ResetAnimationTimer(int aniID);


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	CGameObject();
	~CGameObject();
};