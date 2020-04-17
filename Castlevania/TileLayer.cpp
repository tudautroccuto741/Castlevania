#include "TileLayer.h"

CTileLayer::CTileLayer(json root)
{
	id = root[TILED_LAYER_ID].get<int>();
	name = root[TILED_LAYER_NAME].get<string>();
	type = root[TILED_LAYER_TYPE].get<string>();

	
	if (type == TILED_LAYER_TYPE_TILELAYER)
	{
		height = root[TILED_LAYER_HEIGHT].get<int>();
		width = root[TILED_LAYER_WIDTH].get<int>();
		json dataRoot = root[TILED_LAYER_DATA];
		for (auto it = dataRoot.begin(); it != dataRoot.end(); ++it)
		{
			data.push_back(*it);
		}
	}
}
void CTileLayer::Draw(LPTILESET tileset)
{
	if (type == TILED_LAYER_TYPE_TILELAYER)
	{
		//CCamera* camera = CCamera::GetInstance();
		float top, left, right, bottom;
		//camera->GetViewSize(top, left, bottom, right);
		int sta_x, sta_y, end_x, end_y;
		sta_x = left / TILE_WIDTH - SAFE_DISTANCE;
		sta_y = top / TILE_HEIGHT - SAFE_DISTANCE;
		end_x = right / TILE_WIDTH + SAFE_DISTANCE;
		end_y = bottom / TILE_HEIGHT + SAFE_DISTANCE;
		if (sta_x < 0) sta_x = 0;
		if (sta_y < 0) sta_y = 0;
		if (end_x >= width) end_x = width - 1;
		if (end_y >= height) end_y = height - 1;
		for (int x = sta_x; x <= end_x; x++)
		{
			for (int y = sta_y; y <= end_y; y++) {
				int i = x + y * width;
				tileset->Draw(data[i], i%width, i / width);
			}
		}
	}
}
