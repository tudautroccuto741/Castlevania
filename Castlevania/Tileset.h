#pragma once
#include <string>
#include <vector>
#include <nlohmann\json.hpp>
#include "Tile.h"
#define TILED_TILESET_SOURCE "source"
#define TILED_TILESET_FIRSTGID "firstgid"
#define TILED_TILESET_COLUMNS "columns"
#define TILED_TILESET_IMAGE "image"
#define TILED_TILESET_IMAGEWIDTH "imagewidth"
#define TILED_TILESET_IMAGEHEIGHT "imageheight"
#define TILED_TILESET_TILECOUNT "tilecount"
#define TILED_TILESET_TILEHEIGHT "tileheight"
#define TILED_TILESET_TILEWIDTH "tilewidth"
#define TILED_TILESET_MARGIN "margin"
#define TILED_TILESET_TYPE "type"
#define TILED_TILESET_TILEDVERSION "tiledversion"
#define TILED_TILESET_VERSION "version"
#define STAGES_DIR "Resource\\Stages\\"
using namespace std;
using json = nlohmann::json;
/*
	class for Tiled Tileset object
*/
class CTileset {
	string source; //dir to Tileset json
	int firstgid; //GID corresponding to the first tile in the set
	int columns; //The number of tile columns in the tileset

	int imagewidth;
	int imageheight;
	int tilecount;
	int tileheight;
	int tilewidth;

	vector<LPTILE> tiles;

	//fields that i should ignore for now
	int margin; // Buffer between image edge and first tile (pixels)
	string type;
	string image; // to be converted to interger (id in database), but for now lets just load texture id 0
	string tiledversion;
	float version;
public:
	CTileset(json root);
	void Draw(int tileID, int x, int y);
};
typedef CTileset* LPTILESET;