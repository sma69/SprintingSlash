#pragma once
#ifndef __GF2D_LEVEL_H__
#define __GF2D_LEVEL_H__

#include <SDL.h>
#include <stdio.h>
#include "gf2d_vector.h"
#include "gf2d_entity.h"
#include "gf2d_collision.h"



extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

/**
@brief The level tiling 
*/




/**
@brief Creates a new tile at the given position and with the given type
@param The position vector in the level where the tile is instantiated
@param THe type of the the when drawn into the game
@return A new type to be drawn into the game
*/
Entity* tile_new(Vector2D position, int tileType);


/**
@brief loads level parameter variables
@param filePath the file to load the level from
*/
Entity * set_level(char* filePath);

Entity * getPlayerPosition();			/**< Gets the position of the player entity>*/

#endif // !__GF2D_TILE_H__
