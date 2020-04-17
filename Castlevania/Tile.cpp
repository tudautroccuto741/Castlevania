#include "Tile.h"
#include "Textures.h"
#include "Game.h"

CTile::CTile(int left, int top, int right, int bottom, int texture_id)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = CTextures::GetInstance()->Get(texture_id);
}
void CTile::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}
