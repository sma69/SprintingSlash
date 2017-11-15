#pragma once
#ifndef __GF2D_GUI_H__
#define __GF2D_GUI_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_vector.h"
#include "gf2d_graphics.h"
#include "gf2d_text.h"


#define MAX_MENU_ITEMS  2

/**
@brief guiTextbox_new Creates a Textbox at a given position
@param position is the position on the screen the textbox is drawn
@returns Textbox at a given location on screen
*/
Textbox * guiTextbox_new(Vector2D position);

/**
@brief Creates pause menu
@param takes in screen surface
@param takes in font style
*/
Textbox* pauseMenu_init(Textbox* menus[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

/**
@brief pauseGame shows pause game menu
*/
int pauseMenu_update(Textbox* menus[], int paused, int done);


#endif