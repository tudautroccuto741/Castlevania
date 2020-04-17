#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "TileLayer.h"
#include "Tileset.h"
#define TILED_MAP_HEIGHT "height"
#define TILED_MAP_WIDTH "width"
#define TILED_MAP_NEXTLAYERID "nextlayerid"
#define TILED_MAP_NEXTOBJECTID "nextobjectid"
#define TILED_MAP_TILEHEIGHT "tileheight"
#define TILED_MAP_TILEWIDTH "tilewidth"
#define TILED_MAP_INFINITE "infinite"
#define TILED_MAP_ORIENTATION "orientation"
#define TILED_MAP_RENDERORDER "renderorder"
#define TILED_MAP_TILEDVERSION "tiledversion"
#define TILED_MAP_TYPE "type"
#define TILED_MAP_VERSION "version"
#define TILED_MAP_TILESETS "tilesets"
#define TILED_MAP_LAYERS "layers"
using namespace std;

/*
	class for Tiled Map object
*/
class CTileMap {
	int height; //Number of tile rows
	int width; // Number of tile columns
	int tileheight;
	int tilewidth;
	//
	vector<LPTILELAYER> layers;
	LPTILESET tileset; // should be vector 
	//fields that we should ignore for now

	int nextlayerid; //Auto-increments for each layer
	int nextobjectid; // Auto-increments for each layer
	bool infinite; //Whether the map has infinite dimensions
	string orientation;
	string renderorder;
	string tiledversion;
	string type;
	float version;
public:
	CTileMap(LPCWSTR jsonPath);
	void Draw();
	void CreateObject();
	int GetMapHeight() { return height * tileheight; }
	int getMapWidth() { return width * tilewidth; }
};
typedef CTileMap* LPTILEDMAP;

