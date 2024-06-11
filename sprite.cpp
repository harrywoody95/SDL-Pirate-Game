#include "Sprite.h"
#include "SpriteList.h"
#include "TextureManager.h"

void Sprite::CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList)
{
	Position.x = x;
	Position.y = y;

	SourceBox.x = 0;
	SourceBox.y = 0;
	SourceBox.w = SpriteBitSize;
	SourceBox.h = SpriteBitSize;

	DestinationBox.w = 64 * Scale;
	DestinationBox.h = 64 * Scale;
	DestinationBox.x = Position.x;
	DestinationBox.y = Position.y;

	Texture = TextureManager::LoadTexture(Filename);

	SpriteList->Sprites.push_back(this);

}
void Sprite::DeleteSprite(SpriteList* SpriteList)
{
	for (int x = 0; x < SpriteList->Sprites.size(); x++)
	{
		if (this == SpriteList->Sprites[x])
		{
			SpriteList->Sprites.erase(SpriteList->Sprites.begin() + x);
			delete this;
			return;
		}
	}
}
void Sprite::Draw()
{
	TextureManager::Draw(Texture, SourceBox, DestinationBox);
}