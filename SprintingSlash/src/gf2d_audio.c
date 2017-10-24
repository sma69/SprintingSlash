#include "gf2d_audio.h"

void audio_init()
{
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	int success;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		slog("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = 0;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		slog("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = 0;
	}
}

void audio_load()
{

}