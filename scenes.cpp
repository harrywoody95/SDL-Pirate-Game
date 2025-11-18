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
		s->BitSize = 2160;
	

		s->Texture = TextureManager::LoadTexture("Assets/MainMenu/background.png");
		s->Name = "Background";
		SDL_SetTextureColorMod(s->Texture, 0, 0, 0);
		Textures.push_back(s);

		Sprite* s1 = new Sprite();
		s1->BitSize = 1801;




		s1->Texture = TextureManager::LoadTexture("Assets/MainMenu/title.png");
		s1->Name = "Title";
		SDL_SetTextureColorMod(s1->Texture, 0, 0, 0);
		Textures.push_back(s1);

		Sprite* s2 = new Sprite();
		s2->BitSize = 328;


		s2->Texture = TextureManager::LoadTexture("Assets/MainMenu/newgame.png");
		s2->Name = "NewGame";
		SDL_SetTextureColorMod(s2->Texture, 0, 0, 0);
		Textures.push_back(s2);

		Sprite* s3 = new Sprite();
		s3->BitSize = 365;

		s3->Texture = TextureManager::LoadTexture("Assets/MainMenu/loadgame.png");
		s3->Name = "LoadGame";
		SDL_SetTextureColorMod(s3->Texture, 0, 0, 0);
		Textures.push_back(s3);

		Sprite* s4 = new Sprite();
		s4->BitSize = 235;

		s4->Texture = TextureManager::LoadTexture("Assets/MainMenu/Settings.png");
		s4->Name = "Settings";
		SDL_SetTextureColorMod(s4->Texture, 0, 0, 0);
		Textures.push_back(s4);

		Sprite* s5 = new Sprite();
		s5->BitSize = 340;
		


		s5->Texture = TextureManager::LoadTexture("Assets/MainMenu/exitgame.png");
		s5->Name = "ExitGame";
		SDL_SetTextureColorMod(s5->Texture, 0, 0, 0);
		Textures.push_back(s5);
		isTransitioning = true;
		fade = 0;
	}

}

void Scene::DrawScene(SceneType st, Game* game)
{
	for (int x = 0; x < Textures.size(); x++)
	{
		Textures[x]->Draw(&game->Camera);
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
				else if (Game->UserInput.MousePos.x >= Textures[x]->BitSize && Game->UserInput.MousePos.x <= Textures[x]->BitSize + Textures[x]->BitSize && Game->UserInput.MousePos.y >= Textures[x]->BitSize && Game->UserInput.MousePos.y <= Textures[x]->BitSize + Textures[x]->BitSize)
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
			Textures[x]->Draw(&Game->Camera);
			
			

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
			Textures[x]->Draw(&Game->Camera);
			

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
