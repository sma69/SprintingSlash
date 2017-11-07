#pragma once
#ifndef __GF2D_LEVEL_H__
#define __GF2D_LEVEL_H__

#include <SDL.h>
#include <stdio.h>
#include "gf2d_vector.h"
#include "gf2d_entity.h"



/**
@brief The level tiling 
*/



typedef struct Tile_S{


	//The attributes of the tile
	SDL_Rect box;

	//The tile type
	int type;


}Tile;



/**
@brief Creates a new tile at the given position and with the given type
@param The position vector in the level where the tile is instantiated
@param THe type of the the when drawn into the game
@return A new type to be drawn into the game
*/
Entity* tile_new(Vector2D position, int tileType);


/**
@brief loads level parameter variables
*/
int init_level_parameters();

void draw_tile(SDL_Rect camera);

#endif // !__GF2D_TILE_H__
