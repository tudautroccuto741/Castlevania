#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Animations.h"

vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}



CGameObject::~CGameObject()
{
}