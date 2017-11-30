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


void tileUpdate(Entity *self)
{

}


Entity* tile_new(Vector2D position, int tileType)
{

	Entity* self = entity_new();
	
	self->body.x = position.x;
	self->body.y = position.y;
	self->width = TILE_WIDTH;
	self->height = TILE_HEIGHT;
	//Set the collision box
	self->body.w = TILE_WIDTH;
	self->body.h = TILE_HEIGHT;

	self->sprite = gf2d_sprite_load_all("images/players/greyStoneWall.jpg", self->width, self->height, 1);

	//Get the Tile Type
	self->type = tileType;
	self->update = tileUpdate;
	return self;

}

Entity* wall_new(Vector2D position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("player does not exist\n");
		system("PAUSE");
		return NULL;
	}
	vector2d_set(self->position, position.x, position.y);
	self->body.x = position.x;
	self->body.y = position.y;

	self->body.w = 200;
	self->body.h = 400;
	self->type = "wall";
	self->sprite = gf2d_sprite_load_all("images/walls/greyStoneWall.jpg", self->body.w, self->body.h, 1);
	vector4d_set(self->color, 255, 255, 255, 255);
	return self;
}