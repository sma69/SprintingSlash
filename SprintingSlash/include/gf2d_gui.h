#pragma once
#ifndef __GF2D_GUI_H__
#define __GF2D_GUI_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_vector.h"

#define MAX_MENU_ITEMS  2


/**
@brief Creates pause menu
@param takes in screen surface
@param takes in font style
*/
int showMenu(SDL_Surface* screen, TTF_Font* font);

int pauseGame();


#endif