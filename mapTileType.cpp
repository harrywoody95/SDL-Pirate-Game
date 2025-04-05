#include "MapTileType.h"
#include "TextureManager.h"
void MapTileAssets::LoadMapTileAssets()
{
	MapTileTexture MapTileTexture;

	MapTileTexture.Texture = TextureManager::LoadTexture("Assets/MapTiles/water.png");
	MapTileTexture.Type = (MapTileType)0;
	MapTiles.push_back(MapTileTexture);
}
