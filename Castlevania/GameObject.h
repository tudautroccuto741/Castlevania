#pragma once
#include"GameObject.h"
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Animation.h"

using namespace std;

class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;

	int nx;

	int currentState;


public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->currentState = state; }
	int GetState() { return this->currentState; }

	CGameObject();

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~CGameObject();
};