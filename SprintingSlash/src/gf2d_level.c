#include "gf2d_level.h"


//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
	
Entity* tile_new(Vector2D position, int tileType)
{

	Entity* self;
	self->body.x = position.x;
	self->body.y = position.y;

	//Set the collision box
	self->body.w = TILE_WIDTH;
	self->body.h = TILE_HEIGHT;

	self->sprite = gf2d_sprite_load_all("images/players/greyStoneWall.jpg", self->width, self->height, 6);

	//Get the Tile Type
	self->type = tileType;
	return self;

}

void draw_tile(SDL_Rect camera)
{

}