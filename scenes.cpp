#include "Scenes.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"

void Scene::CreateScene(SceneType st, Game* game)
{
	if (st == SceneType::Mainmenu)
	{
		int w, h;
		w = static_cast<int>(game->Window.GetResolution().x);
		h = static_cast<int>(game->Window.GetResolution().y);
		Name = "MainMenu";
		Sprite* s = new Sprite();
		s->SourceBox.x = 0;
		s->SourceBox.y = 0;
		s->SourceBox.w = 3840;
		s->SourceBox.h = 2160;

		s->DestinationBox.x = 0;
		s->DestinationBox.y = 0;
		s->DestinationBox.w = w;
		s->DestinationBox.h = h;

		s->Texture = TextureManager::LoadTexture("Assets/MainMenu/background.png");
		s->Name = "Background";
		SDL_SetTextureColorMod(s->Texture, 0, 0, 0);
		Textures.push_back(s);

		Sprite* s1 = new Sprite();
		s1->SourceBox.x = 0;
		s1->SourceBox.y = 0;
		s1->SourceBox.w = 1801;
		s1->SourceBox.h = 163;

		s1->DestinationBox.w = s1->SourceBox.w;
		s1->DestinationBox.h = s1->SourceBox.h;
		s1->DestinationBox.x = (w - s1->DestinationBox.w) / 2;
		s1->DestinationBox.y = (h - s1->DestinationBox.h) / 10 ;

		s1->Texture = TextureManager::LoadTexture("Assets/MainMenu/title.png");
		s1->Name = "Title";
		SDL_SetTextureColorMod(s1->Texture, 0, 0, 0);
		Textures.push_back(s1);

		Sprite* s2 = new Sprite();
		s2->SourceBox.x = 0;
		s2->SourceBox.y = 0;
		s2->SourceBox.w = 328;
		s2->SourceBox.h = 75;

		s2->DestinationBox.w = s2->SourceBox.w;
		s2->DestinationBox.h = s2->SourceBox.h;
		s2->DestinationBox.x = (w - s2->DestinationBox.w) / 2;
		s2->DestinationBox.y = (h - s2->DestinationBox.h) / 2;

		s2->Texture = TextureManager::LoadTexture("Assets/MainMenu/newgame.png");
		s2->Name = "NewGame";
		SDL_SetTextureColorMod(s2->Texture, 0, 0, 0);
		Textures.push_back(s2);

		Sprite* s3 = new Sprite();
		s3->SourceBox.x = 0;
		s3->SourceBox.y = 0;
		s3->SourceBox.w = 365;
		s3->SourceBox.h = 76;

		s3->DestinationBox.w = s3->SourceBox.w;
		s3->DestinationBox.h = s3->SourceBox.h;
		s3->DestinationBox.x = (w - s3->DestinationBox.w) / 2;
		s3->DestinationBox.y = static_cast<int>((h - s3->DestinationBox.h) / 1.7);

		s3->Texture = TextureManager::LoadTexture("Assets/MainMenu/loadgame.png");
		s3->Name = "LoadGame";
		SDL_SetTextureColorMod(s3->Texture, 0, 0, 0);
		Textures.push_back(s3);

		Sprite* s4 = new Sprite();
		s4->SourceBox.x = 0;
		s4->SourceBox.y = 0;
		s4->SourceBox.w = 235;
		s4->SourceBox.h = 76;

		s4->DestinationBox.w = s4->SourceBox.w;
		s4->DestinationBox.h = s4->SourceBox.h;
		s4->DestinationBox.x = (w - s4->DestinationBox.w) / 2;
		s4->DestinationBox.y = static_cast<int>((h - s4->DestinationBox.h) / 1.5);

		s4->Texture = TextureManager::LoadTexture("Assets/MainMenu/Settings.png");
		s4->Name = "Settings";
		SDL_SetTextureColorMod(s4->Texture, 0, 0, 0);
		Textures.push_back(s4);

		Sprite* s5 = new Sprite();
		
		s5->SourceBox.x = 0;
		s5->SourceBox.y = 0;
		s5->SourceBox.w = 340;
		s5->SourceBox.h = 76;

		s5->DestinationBox.w = s5->SourceBox.w;
		s5->DestinationBox.h = s5->SourceBox.h;
		s5->DestinationBox.x = (w - s5->DestinationBox.w) / 2;
		s5->DestinationBox.y = static_cast<int>((h - s5->DestinationBox.h) / 1.34);


		s5->Texture = TextureManager::LoadTexture("Assets/MainMenu/exitgame.png");
		s5->Name = "ExitGame";
		SDL_SetTextureColorMod(s5->Texture, 0, 0, 0);
		Textures.push_back(s5);
		isTransitioning = true;
		fade = 0;
	}

}

void Scene::DrawScene(SceneType st)
{
	for (int x = 0; x < Textures.size(); x++)
	{
		TextureManager::Draw(Textures[x]->Texture, Textures[x]->SourceBox, Textures[x]->DestinationBox);
	}
}

void Scene::UpdateScene(SceneType st, Game* Game)
{
	if (st == SceneType::Mainmenu)
	{
		if (!Mix_PlayingMusic())
		{
			Mix_FadeInMusic(Game->Audio.MusicList.List[0].Music, -1, 4000);
			//Game->Audio.MusicList.List[0].PlayMusic(true);
		}
		if (isTransitioning == false)
		{
			for (int x = 0; x < Textures.size(); x++)
			{
				if (Textures[x]->Name == "Background" || Textures[x]->Name == "Title")
				{
					continue;
				}
				else if (Game->UserInput.MousePos.x >= Textures[x]->DestinationBox.x && Game->UserInput.MousePos.x <= Textures[x]->DestinationBox.x + Textures[x]->DestinationBox.w && Game->UserInput.MousePos.y >= Textures[x]->DestinationBox.y && Game->UserInput.MousePos.y <= Textures[x]->DestinationBox.y + Textures[x]->DestinationBox.h)
				{
					SDL_SetTextureColorMod(Textures[x]->Texture, 100, 100, 100);
					if (Textures[x]->Name == "NewGame" && Game::Event.type == SDL_MOUSEBUTTONDOWN)
					{
						isTransitioning = true;
						fade = 255;
						Mix_FadeOutMusic(2700);
						FadeOut(Game);
						Game->Flags.MainMenu = false;
					}
					if (Textures[x]->Name == "ExitGame" && Game::Event.type == SDL_MOUSEBUTTONDOWN)
					{
						Game->IsRunning = false;
					}
				}
				else
				{
					SDL_SetTextureColorMod(Textures[x]->Texture, 255, 255, 255);
				}
			}
		}
		else
		{
			FadeIn(Game);
		}
	}
}

void Scene::FadeIn(Game* Game)
{
	while (isTransitioning)
	{
		for (int x = 0; x < Textures.size(); x++)
		{
			SDL_SetTextureColorMod(Textures[x]->Texture, fade, fade, fade);
			TextureManager::Draw(Textures[x]->Texture, Textures[x]->SourceBox, Textures[x]->DestinationBox);
			
			

		}
		fade++;
		if (fade == 255)
		{
			isTransitioning = false;
		}
		SDL_RenderPresent(Game->Renderer.MainRenderer);
		SDL_Delay(10);
	}
}

void Scene::FadeOut(Game* Game)
{
	while (isTransitioning)
	{
		for (int x = 0; x < Textures.size(); x++)
		{
			SDL_SetTextureColorMod(Textures[x]->Texture, fade, fade, fade);
			TextureManager::Draw(Textures[x]->Texture, Textures[x]->SourceBox, Textures[x]->DestinationBox);
			

		}
		fade--;
		if (fade == 0)
		{
			isTransitioning = false;
		}
		SDL_RenderPresent(Game->Renderer.MainRenderer);
		SDL_Delay(10);
	}
}
