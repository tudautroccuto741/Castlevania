#pragma once
#include "TileMap.h"
#include <fstream>
#include "Debug.h"
#include "GameObject.h"
using json = nlohmann::json;

CTileMap::CTileMap(LPCWSTR jsonPath)
{
	json root;
	ifstream input(jsonPath);
	input >> root;
	input.close();

	height = root[TILED_MAP_HEIGHT].get<int>();
	width = root[TILED_MAP_WIDTH].get<int>();
	tileheight = root[TILED_MAP_TILEHEIGHT].get<int>();
	tilewidth = root[TILED_MAP_TILEHEIGHT].get<int>();
	nextlayerid = root[TILED_MAP_NEXTLAYERID].get<int>();
	nextobjectid = root[TILED_MAP_NEXTOBJECTID].get<int>();
	infinite = root[TILED_MAP_INFINITE].get<bool>();
	orientation = root[TILED_MAP_ORIENTATION].get<string>();
	renderorder = root[TILED_MAP_RENDERORDER].get<string>();
	tiledversion = root[TILED_MAP_TILEDVERSION].get<string>();
	type = root[TILED_MAP_TYPE].get<string>();
	version = root[TILED_MAP_VERSION].get<float>();
	tileset = new CTileset(root[TILED_MAP_TILESETS][0]); // fix later maybe, just maybe

	json layerRoot = root[TILED_MAP_LAYERS];
	for (json::iterator it = layerRoot.begin(); it != layerRoot.end(); it++)
	{
		LPTILELAYER layer = new CTileLayer(*it);
		layers.push_back(layer);
	}
	

}
void CTileMap::Draw()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->Draw(tileset);
	}
}
