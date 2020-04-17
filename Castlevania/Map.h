#include"GameObject.h"
#include"TileMap.h"
#include "Tile.h"

/*
Tiled Map Manager class
*/
class CMap {
	static CMap * __instance;
	vector<LPTILEDMAP> maps;
	int currentMap;
public:
	void Add(LPTILEDMAP map) { maps.push_back(map); }
	LPTILEDMAP GetCurrentMap() { return this->maps[currentMap]; }
	void SetCurrentMap(int index) { this->currentMap = index; }

	static CMap * GetInstance();
};