#pragma once
#ifndef __GF2D_GUI_H__
#define __GF2D_GUI_H__

#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_vector.h"
#include "gf2d_graphics.h"
#include "gf2d_text.h"


#define MAX_PAUSE_MENU_ITEMS 2
#define MAX_MAIN_MENU_ITEMS 3

/**
@brief guiTextbox_new Creates a Textbox at a given position
@param position is the position on the screen the textbox is drawn
@returns Textbox at a given location on screen
*/
Textbox * guiTextbox_new(Vector2D position);

/**
@brief mainMenu_init Creates the Main Menu
@param menus the menu object needed so the menu is not on the heap
@param SCREEN_WIDTH the width of the screen viewport
@param SCREEN_HEIGHT the height of the screen viewport
@returns A Textbox list with the parameters of the Main Menu
*/

Textbox* mainMenu_init(Textbox* menus[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

/**
@brief pauseMenu_init Creates the Main Menu
@param menus the menu object needed so the menu is not on the heap
@param SCREEN_WIDTH the width of the screen viewport
@param SCREEN_HEIGHT the height of the screen viewport
@returns A Textbox list with the parameters of the Pause Menu
*/
Textbox* pauseMenu_init(Textbox* menus[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

/**
@brief pauseMenu_update shows and updates the pause menu while the game is paused
@param menus menu object for use to prevent null pointer on function call
@param pause The flag used to stop all entities from updating
@param done The flag used to terminate the game loop
@return A pause menu with listed options in descending order
*/
int pauseMenu_update(Textbox* menus[], int paused, int done);

/**
@brief mainMenu_update shows and updates the main menu at the start of the game
@param menus menu object for use to prevent null pointer on function call
@param start The flag used to pause the game before the main game loop
@param done The flag used to terminate the game loop
@return A main menu that runs at the start of the game
*/
int mainMenu_update(Textbox* menus[], int *start, int *done);


#endif