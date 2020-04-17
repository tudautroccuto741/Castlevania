#pragma once
#include "Sprite.h"
#include <d3dx9.h>
#include "GameObject.h"
#include "Game.h"
#include "Textures.h"

#define TILE_HEIGHT			32
#define TILE_WIDTH			32

class CTile
{	
	int left;
	int top;
	int right;
	int bottom;
	int x;
	int y;
	

public:
	
	CTile(int x, int y, int left, int top, int right, int bottom) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->x = x;
		this->y = y;
	};
	
	void Render();

};

typedef CTile * LPTILE;
