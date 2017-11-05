#pragma once
#ifndef __GF2D_LEVEL_H__
#define __GF2D_LEVEL_H__

#include <SDL.h>
#include "gf2d_vector.h"


//Screen dimension constants
const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

//The dimensions of the level
const int LEVEL_WIDTH;
const int LEVEL_HEIGHT;

//Tile constants
const int TILE_WIDTH;
const int TILE_HEIGHT;
const int TOTAL_TILES;
const int TILE_SPRITES;

//The different tile sprites
const int TILE_RED;
const int TILE_GREEN;
const int TILE_BLUE;
const int TILE_CENTER;
const int TILE_TOP;
const int TILE_TOPRIGHT;
const int TILE_RIGHT;
const int TILE_BOTTOMRIGHT;
const int TILE_BOTTOM;
const int TILE_BOTTOMLEFT;
const int TILE_LEFT;
const int TILE_TOPLEFT;


/**
@brief The level tiling 
*/



typedef struct Tile_S{


	//The attributes of the tile
	SDL_Rect box;

	//The tile type
	int type;


}Tile;



Tile* tile_new(Vector2D position, int tileType);



#endif // !__GF2D_TILE_H__
