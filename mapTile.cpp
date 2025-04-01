#include "SDL.h"
#include "TextureManager.h"
#include "MapTile.h"
#include "Camera.h"

void MapTile::CreateMapTile(float x, float y, MapTileType Type, int BitSize, int Scale, MapTileAssets MTA, bool Solid)
{
	this->Solid = Solid;
	Position.x = x;
	Position.y = y;
	this->Type = Type;
	this->Bitsize = BitSize;
	this->Scale = Scale;
	for (int index = 0; index < MTA.MapTiles.size(); index++)
	{
		if (MTA.MapTiles[index].Type == Type)
		{
			this->Texture = MTA.MapTiles[index].Texture;
			break;
		}
	}
	if (Solid)
	{
		Collision.Left = Position.x;
		Collision.Top = Position.y;
		Collision.Right = Position.x + (Bitsize * Scale);
		Collision.Bottom = Position.y + (Bitsize * Scale);
	}
}

void MapTile::Update(Camera* camera)
{
}

void MapTile::Draw(Camera* camera)
{
	SDL_Rect SourceBox, DestinationBox;
	SourceBox.w = 32;
	SourceBox.h = 32;
	SourceBox.x = 0;
	SourceBox.y = 0;
	DestinationBox.w = 32 * 2;
	DestinationBox.h = 32 * 2;
	DestinationBox.x = Position.x;
	DestinationBox.y = Position.y;

	DestinationBox.x = DestinationBox.x - camera->Position.x;
	DestinationBox.y = DestinationBox.y - camera->Position.y;

	TextureManager::Draw(Texture, SourceBox, DestinationBox);
}
