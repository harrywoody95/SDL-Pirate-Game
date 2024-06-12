#pragma once
#include "SDL_mixer.h"
#include <String>
#include <vector>
struct Music
{
	std::string Name;
	Mix_Music* Music;
	void PlayMusic(bool loop);
	void StopMusic();
};
struct SoundEffect
{
	std::string Name;
	Mix_Chunk* Sound;
	void PlaySoundEffect();
};
struct MusicList
{
	std::vector <Music> List;

	void AddMusic(const char* FileName, std::string name);
};
struct SoundList
{
	std::vector <SoundEffect> List;
	void AddSoundEffect(const char* FileName, std::string name);
};
struct Audio
{
	MusicList MusicList;
	SoundList SoundList;
};