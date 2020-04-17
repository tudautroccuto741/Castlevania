#pragma once
#include "Tileset.h"
#include <fstream>

CTileset::CTileset(json root)
{
	source = STAGES_DIR + root[TILED_TILESET_SOURCE].get<string>(); // fix this later
	firstgid = root[TILED_TILESET_FIRSTGID].get<int>();

	json tilesetRoot;
	ifstream input(source);
	input >> tilesetRoot;
	input.close();

	columns = tilesetRoot[TILED_TILESET_COLUMNS].get<int>();
	imagewidth = tilesetRoot[TILED_TILESET_IMAGEWIDTH].get<int>();
	imageheight = tilesetRoot[TILED_TILESET_IMAGEHEIGHT].get<int>();
	tilecount = tilesetRoot[TILED_TILESET_TILECOUNT].get<int>();
	tileheight = tilesetRoot[TILED_TILESET_TILEHEIGHT].get<int>();
	tilewidth = tilesetRoot[TILED_TILESET_TILEWIDTH].get<int>();
	margin = tilesetRoot[TILED_TILESET_MARGIN].get<int>();
	type = tilesetRoot[TILED_TILESET_TYPE].get<string>();
	image = tilesetRoot[TILED_TILESET_IMAGE].get<string>();
	tiledversion = tilesetRoot[TILED_TILESET_TILEDVERSION].get<string>();
	version = tilesetRoot[TILED_TILESET_VERSION].get<float>();
	//
	for (int row = 0; row < tilecount / columns; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int left, top, right, bottom;
			LPTILE tile;

			left = column * tilewidth;
			top = row * tileheight;
			right = left + tilewidth;
			bottom = top + tileheight;

			tile = new CTile(left, top, right, bottom, 0); // fix later
			tiles.push_back(tile);
		}
	}
}
void CTileset::Draw(int tileID, int x, int y) {
	if (tileID >= firstgid)
		tiles[tileID - firstgid]->Draw(x*tilewidth, y*tileheight);
}