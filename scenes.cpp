#include "Scenes.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"

void Scene::CreateScene(SceneType st)
{
	if (st == SceneType::Mainmenu)
	{
		Name = "MainMenu";
		Sprite* s = new Sprite();
		s->SourceBox.x = 0;
		s->SourceBox.y = 0;
		s->SourceBox.w = 3840;
		s->SourceBox.h = 2160;

		s->DestinationBox.x = 0;
		s->DestinationBox.y = 0;
		s->DestinationBox.w = 1920;
		s->DestinationBox.h = 960;

		s->Texture = TextureManager::LoadTexture("Assets/MainMenu/background.png");
		s->Name = "Background";
		SDL_SetTextureColorMod(s->Texture, 0, 0, 0);
		Textures.push_back(s);

		Sprite* s1 = new Sprite();
		s1->SourceBox.x = 0;
		s1->SourceBox.y = 0;
		s1->SourceBox.w = 1801;
		s1->SourceBox.h = 163;

		s1->DestinationBox.x = 170;
		s1->DestinationBox.y = 35;
		s1->DestinationBox.w = 1601;
		s1->DestinationBox.h = 143;

		s1->Texture = TextureManager::LoadTexture("Assets/MainMenu/title.png");
		s1->Name = "Title";
		SDL_SetTextureColorMod(s1->Texture, 0, 0, 0);
		Textures.push_back(s1);

		Sprite* s2 = new Sprite();
		s2->SourceBox.x = 0;
		s2->SourceBox.y = 0;
		s2->SourceBox.w = 328;
		s2->SourceBox.h = 75;

		s2->DestinationBox.x = 796;
		s2->DestinationBox.y = 400;
		s2->DestinationBox.w = 328;
		s2->DestinationBox.h = 75;

		s2->Texture = TextureManager::LoadTexture("Assets/MainMenu/newgame.png");
		s2->Name = "NewGame";
		SDL_SetTextureColorMod(s2->Texture, 0, 0, 0);
		Textures.push_back(s2);

		Sprite* s3 = new Sprite();
		s3->SourceBox.x = 0;
		s3->SourceBox.y = 0;
		s3->SourceBox.w = 365;
		s3->SourceBox.h = 76;

		s3->DestinationBox.x = 777;
		s3->DestinationBox.y = 500;
		s3->DestinationBox.w = 365;
		s3->DestinationBox.h = 75;

		s3->Texture = TextureManager::LoadTexture("Assets/MainMenu/loadgame.png");
		s3->Name = "LoadGame";
		SDL_SetTextureColorMod(s3->Texture, 0, 0, 0);
		Textures.push_back(s3);

		Sprite* s4 = new Sprite();
		s4->SourceBox.x = 0;
		s4->SourceBox.y = 0;
		s4->SourceBox.w = 235;
		s4->SourceBox.h = 76;

		s4->DestinationBox.x = 842;
		s4->DestinationBox.y = 600;
		s4->DestinationBox.w = 235;
		s4->DestinationBox.h = 75;

		s4->Texture = TextureManager::LoadTexture("Assets/MainMenu/Settings.png");
		s4->Name = "Settings";
		SDL_SetTextureColorMod(s4->Texture, 0, 0, 0);
		Textures.push_back(s4);

		Sprite* s5 = new Sprite();
		s5->SourceBox.x = 0;
		s5->SourceBox.y = 0;
		s5->SourceBox.w = 340;
		s5->SourceBox.h = 76;

		s5->DestinationBox.x = 790;
		s5->DestinationBox.y = 700;
		s5->DestinationBox.w = 340;
		s5->DestinationBox.h = 75;

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

void MainMenu(Game* Game)
{
	SDL_Rect Source;
	SDL_Rect BackgroundDestination, TitleDestination, NewDestination, LoadDestination, SettingsDestination, ExitDestination;

	Source.x = 0;
	Source.y = 0;
	Source.w = 3840;
	Source.h = 2160;

	BackgroundDestination.x = 0;
	BackgroundDestination.y = 0;
	BackgroundDestination.w = 1920;
	BackgroundDestination.h = 960;

	SDL_Texture* Background = TextureManager::LoadTexture("Assets/MainMenu/background.png");
	TextureManager::Draw(Background, Source, BackgroundDestination);

	Source.w = 1801;
	Source.h = 163;
	TitleDestination.w = 1601;
	TitleDestination.h = 143;
	TitleDestination.y = 35;
	TitleDestination.x = 170;

	SDL_Texture* Title = TextureManager::LoadTexture("Assets/MainMenu/title.png");
	TextureManager::Draw(Title, Source, TitleDestination);

	Source.w = 328;
	Source.h = 75;
	NewDestination.w = 328;
	NewDestination.h = 75;
	NewDestination.y = 400;
	NewDestination.x = 796;
	SDL_Texture* NewGame = TextureManager::LoadTexture("Assets/MainMenu/newgame.png");
	if (Game->UserInput.MousePos.x >= NewDestination.x && Game->UserInput.MousePos.x <= NewDestination.x + NewDestination.w && Game->UserInput.MousePos.y >= NewDestination.y && Game->UserInput.MousePos.y <= NewDestination.y + NewDestination.h)
	{
		SDL_SetTextureColorMod(NewGame, 100, 100, 100);
		TextureManager::Draw(NewGame, Source, NewDestination);
		if (Game::Event.type == SDL_MOUSEBUTTONDOWN)
		{
			Game->Flags.MainMenu = false;
		}
	}
	else
	{
		TextureManager::Draw(NewGame, Source, NewDestination);
	}

	Source.w = 365;
	Source.h = 76;
	LoadDestination.w = 365;
	LoadDestination.h = 75;
	LoadDestination.y = 500;
	LoadDestination.x = 777;
	SDL_Texture* LoadGame = TextureManager::LoadTexture("Assets/MainMenu/loadgame.png");
	if (Game->UserInput.MousePos.x >= LoadDestination.x && Game->UserInput.MousePos.x <= LoadDestination.x + LoadDestination.w && Game->UserInput.MousePos.y >= LoadDestination.y && Game->UserInput.MousePos.y <= LoadDestination.y + LoadDestination.h)
	{
		SDL_SetTextureColorMod(LoadGame, 100, 100, 100);
		TextureManager::Draw(LoadGame, Source, LoadDestination);
		if (Game::Event.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
	}
	else
	{
		TextureManager::Draw(LoadGame, Source, LoadDestination);
	}

	Source.w = 235;
	Source.h = 76;
	SettingsDestination.w = 235;
	SettingsDestination.h = 75;
	SettingsDestination.y = 600;
	SettingsDestination.x = 842;
	SDL_Texture* Settings = TextureManager::LoadTexture("Assets/MainMenu/Settings.png");
	if (Game->UserInput.MousePos.x >= SettingsDestination.x && Game->UserInput.MousePos.x <= SettingsDestination.x + SettingsDestination.w && Game->UserInput.MousePos.y >= SettingsDestination.y && Game->UserInput.MousePos.y <= SettingsDestination.y + SettingsDestination.h)
	{
		SDL_SetTextureColorMod(Settings, 100, 100, 100);
		TextureManager::Draw(Settings, Source, SettingsDestination);
		if (Game::Event.type == SDL_MOUSEBUTTONDOWN)
		{

		}
	}
	else
	{
		TextureManager::Draw(Settings, Source, SettingsDestination);
	}

	Source.w = 340;
	Source.h = 76;
	ExitDestination.w = 340;
	ExitDestination.h = 75;
	ExitDestination.y = 700;
	ExitDestination.x = 790;
	SDL_Texture* ExitGame = TextureManager::LoadTexture("Assets/MainMenu/exitgame.png");
	if (Game->UserInput.MousePos.x >= ExitDestination.x && Game->UserInput.MousePos.x <= ExitDestination.x + ExitDestination.w && Game->UserInput.MousePos.y >= ExitDestination.y && Game->UserInput.MousePos.y <= ExitDestination.y + ExitDestination.h)
	{
		SDL_SetTextureColorMod(ExitGame, 100, 100, 100);
		TextureManager::Draw(ExitGame, Source, ExitDestination);
		if (Game::Event.type == SDL_MOUSEBUTTONDOWN)
		{
			Game->IsRunning = false;
		}
	}
	else
	{
		TextureManager::Draw(ExitGame, Source, ExitDestination);
	}


}

void StartGame()
{

}