#include "Sprite.h"
#include "SpriteList.h"
#include "TextureManager.h"
#include "Game.h"

void Sprite::CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList)
{
	Movement.init(x, y);
	BitSize = SpriteBitSize;
	this->Scale = Scale;

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

void Sprite::Draw(Camera* Camera)
{
	SDL_Rect DestinationBox, SourceBox;
	SourceBox.x = 0;
	SourceBox.y = 0;
	SourceBox.w = BitSize;
	SourceBox.h = BitSize;

	DestinationBox.w = BitSize * Scale;
	DestinationBox.h = BitSize * Scale;
	DestinationBox.x = static_cast<int>(Movement.Position.x - Camera->Position.x);
	DestinationBox.y = static_cast<int>(Movement.Position.y - Camera->Position.y);
	TextureManager::Draw(Texture, SourceBox, DestinationBox);
}

void Sprite::Update()
{
	Movement.Update();
}
