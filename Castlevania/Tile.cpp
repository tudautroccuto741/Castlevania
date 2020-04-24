#include "Tile.h"

void CTile::Render()
{
	LPDIRECT3DTEXTURE9 texture = CTextures::GetInstance()->Get(TEXTURE_ID_TILE_MAP);
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, 255);
}
