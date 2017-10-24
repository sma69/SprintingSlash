#ifndef __GF2D_AUDIO_H__
#define __GF2D_AUDIO_H__


//Using SDL, SDL_image, SDL_mixer, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include "simple_logger.h"


//The music that will be played

Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;


void audio_init();

void audio_load();






#endif