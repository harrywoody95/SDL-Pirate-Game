//#include "GameObj.h"
//
//void GameObject::CreateGameObject(const char* Filename, int Xpos, int Ypos)
//{
//	this->Xpos = Xpos;
//	this->Ypos = Ypos;
//	Texture = TextureManager::LoadTexture(Filename);
//}
//
//void GameObject::Update()
//{
//	SourceBox.w = 64; // size of sprite 32 x 32 etc
//	SourceBox.h = 64;
//	SourceBox.x = 0;
//	SourceBox.y = 0;
//
//	DestinationBox.x = Xpos;
//	DestinationBox.y = Ypos;
//	DestinationBox.w = SourceBox.w; // can scale this using a *2 etc
//	DestinationBox.h = SourceBox.h;
//}
//
//void GameObject::Render()
//{
//	SDL_RenderCopy(Renderer::MainRenderer, Texture, &SourceBox, &DestinationBox);
//}
