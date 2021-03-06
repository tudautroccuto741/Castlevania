#include "Tile.h"


bool CTile::IsInViewPort()
{
	CGame *game = CGame::GetInstance();
	// The viewport bounding box
	float vpLeft, vpTop, vpRight, vpBottom;
	game->CamereBoundingBox(vpLeft, vpTop, vpRight, vpBottom);
	if (vpLeft > this->r || vpTop > this->b
		|| vpRight < this->l || vpBottom < this->t)
		return false;

	return true;
}
void CTile::Render()
{
	LPDIRECT3DTEXTURE9 texture = CTextures::GetInstance()->Get(TEXTURE_ID_TILE_MAP);
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, 255);
}
