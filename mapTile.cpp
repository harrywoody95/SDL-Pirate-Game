#include "SDL.h"
#include "TextureManager.h"
#include "MapTile.h"

void MapTile::CreateMapTile(MapTileType Type, SDL_Rect SourceBox, SDL_Rect DestinationBox, MapTileAssets MTA)
{
	this->SourceBox = SourceBox;
	this->DestinationBox = DestinationBox;
	this->Type = Type;
	for (int index = 0; index < MTA.MapTiles.size(); index++)
	{
		if (MTA.MapTiles[index].Type == Type)
		{
			this->Texture = MTA.MapTiles[index].Texture;
			return;
		}
	}
}