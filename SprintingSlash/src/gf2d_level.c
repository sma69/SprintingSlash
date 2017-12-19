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




void teleWallUpdate(Entity *self)
{
	
}

void teleWallTouch(Entity * self, Entity * other)
{
	if (checkWallCollision(self, other) == 1)
	{
		if (other->type == "player")
		{
			other->position.y = self->position.y - 300;
		}
	}
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
	//self->update = tileUpdate;
	return self;

}

Entity* wall_new(Vector2D position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("wall does not exist\n");
		system("PAUSE");
		return NULL;
	}
	vector2d_set(self->position, position.x, position.y);
	self->body.x = position.x;
	self->body.y = position.y;
	self->frame = 1;
	self->body.w = TILE_WIDTH;
	self->body.h = TILE_HEIGHT;
	self->type = "wall";
	self->sprite = gf2d_sprite_load_all("images/walls/greyStoneWall.jpg", self->body.w, self->body.h, 1);
	vector4d_set(self->color, 255, 255, 255, 255);
	self->touch = teleWallTouch;
	return self;
}

Entity* teleWall_new(Vector2D position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("wall does not exist\n");
		system("PAUSE");
		return NULL;
	}
	vector2d_set(self->position, position.x, position.y);
	self->body.x = position.x;
	self->body.y = position.y;
	self->frame = 1;
	self->body.w = TILE_WIDTH;
	self->body.h = TILE_HEIGHT;
	self->type = "wall";
	self->sprite = gf2d_sprite_load_all("images/walls/tile_aqua.png", self->body.w, self->body.h, 1);
	self->touch = teleWallTouch;
	vector4d_set(self->color, 255, 255, 255, 255);
	return self;
}

Entity * set_level(char* filePath)
{
	//The tile offsets
	int x = 0, y = 0;

	char* letter[1024];
	char* line[100];
	FILE *file;

	Entity * level[192];


	//open the file
	file = fopen(filePath, "r");
	rewind(file);

	//check if the user can open the file othe+rwise it does not exist
	if (file == NULL) {
		slog("File does not Exist");
		return;
	}
	else {
		printf("File Loaded");
	}
	int t = 0;
	while (fscanf(file, "%s", letter) != EOF)
	{

		if (strcmp(letter, "00") == 0) {
			//do nothing go to next space
		}
		if (strcmp(letter, "01") == 0) {
			Vector2D pos = { x, y };
			level[t] = wall_new(pos);
			t++;
		}
		if (strcmp(letter, "02") == 0) {
			Vector2D pos = { x, y };
			level[t] = player_new(pos);
			t++;
		}

		if (strcmp(letter, "03") == 0) {
			Vector2D pos = { x, y };
			level[t] = teleWall_new(pos);
			t++;
		}

		//Move to next tile spot
		x += TILE_WIDTH;

		//If we've gone too far
		if (x >= LEVEL_WIDTH)
		{
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
	}
		fclose(file);
		return level;
}