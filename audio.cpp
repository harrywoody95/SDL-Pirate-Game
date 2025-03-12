#include "Audio.h"

void MusicList::AddMusic(const char* FileName, std::string Name)
{
	Music Music;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Music.Music = Mix_LoadMUS(FileName);
	Music.Name = Name;
	List.push_back(Music);
}

void Music::PlayMusic(bool loop)
{
	if (loop)
	{
		Mix_PlayMusic(Music, -1);
	}
	else
	{
		Mix_PlayMusic(Music, 0);
	}
}

void SoundEffect::PlaySoundEffect()
{
	Mix_PlayChannel(-1, Sound, 0);
}

void Music::StopMusic()
{
	Mix_PauseMusic();
}

void SoundList::AddSoundEffect(const char* FileName, std::string Name)
{
	SoundEffect SE;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	SE.Sound = Mix_LoadWAV(FileName);
	SE.Name = Name;
	List.push_back(SE);
}
