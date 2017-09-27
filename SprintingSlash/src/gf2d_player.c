#include "gf2d_entity.h"

Entity *player_new(Vector2D Position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("player does not exist\n");
		system("PAUSE");
		return NULL;
	}
	self->sprite = gf2d_sprite_load_all("images/players/redSquare.png", 32, 32, 1);
	vector2d_set(self->position, Position.x, Position.y);
	vector4d_set(self->color, 255, 255, 255, 255);
	self->frame = 1;
	slog("player spawned");
	return self;
}