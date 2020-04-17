#pragma once
#include <string>
#include <vector>
#include "Tileset.h"
#include <nlohmann\json.hpp>
#define SAFE_DISTANCE 0
#define TILED_LAYER_TYPE_TILELAYER "tilelayer"
#define TILED_LAYER_TYPE_OBJECTGROUP "objectgroup"
#define TILED_LAYER_TYPE "type"
#define TILED_LAYER_DATA "data"
#define TILED_LAYER_OBJECTS "objects"
#define TILED_LAYER_HEIGHT "height"
#define TILED_LAYER_WIDTH "width"
#define TILED_LAYER_ID "id"
#define TILED_LAYER_NAME "name"
#define TILED_LAYER_OPACITY "opacity"
#define TILED_LAYER_VISIBLE "visible"
#define TILED_LAYER_X "x"
#define TILED_LAYER_Y "y"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

using json = nlohmann::json;
using namespace std;

/*
	class for Tiled Layer object
*/
class CTileLayer {
	int id;

	vector<int> data; //tilelayer only, will consider changing this to vector<vector<int>>
	//vector<LPTILEDOBJECT> objects; // objectgroup only

	string name;
	string type;
	int height;
	int width;

	//there are still more fields but i dont have anything to do with them now
public:
	CTileLayer(json);
	bool isTileLayer() { return type == TILED_LAYER_TYPE_TILELAYER; }
	void Draw(LPTILESET tileset);
};
typedef CTileLayer* LPTILELAYER;

