#pragma once
#include"GameObject.h"
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Animation.h"
//#define ID_TEX_BBOX -100		// special texture to draw object bounding box

using namespace std;

//class CGameObject;
//typedef CGameObject * LPGAMEOBJECT;

/*struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};*/

class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;
	//float dx;	// dx = vx*dt
	//float dy;	// dy = vy*dt
	int nx;
	DWORD dt;

	int currentState;


public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	
	//void RenderBoundingBox();

	//LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);	//xet 2 doi tuong dang di chuyen
	/*void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents); // va cham giua doi tuong hien tai 
																									//	va ds cac doi tuong
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
		*/

	void SetState(int state) { this->currentState = state; }
	int GetState() { return this->currentState; }

	CGameObject();

	virtual void Update(DWORD dt);
	virtual void Render();
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//virtual 
	

	~CGameObject();
};