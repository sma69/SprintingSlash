#include "gf2d_projectile.h"

aliveTime = 0;
void projectileUpdate(Entity* self)
{
	self->frame += 0.03;
	if (self->frame >= 1.0)self->frame = 0;
	
	self->position.x += self->velocity.x;
	self->position.y += self->velocity.y;
	self->body.x = self->position.x;
	self->body.y = self->position.y;
	self->body.w = self->width;
	self->body.h = self->height;
	aliveTime += self->velocity.x; 

	

	/*if (aliveTime >= 1000)
	{
		self->dead = 1;
	}*/

}


void projectileTouch(Entity* self, Entity* other)
{

		if (checkWallCollision(self, other) == 1)
		{

			self->dead = 1;

		}


}


Entity *projectile_new(Vector2D Position, Vector2D direction, float speed)
{

	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("projectile does not exist\n");
		system("PAUSE");
		return NULL;
	}

	//loadPlayerFromFile("objects/player/player.txt", self);
	direction.x = direction.x * speed;
	direction.y = direction.y * speed;
	self->width = 20;
	self->height = 20;
	//vector2d_set(self->hitOffset, 10, 0);
	vector2d_set(self->body, self->width, self->height);
	//self->moveSpeed = 4;
	self->jumpTime = 0;
	//self->gravity = self->normalGravity;
	self->type = "projectile";
	self->sprite = gf2d_sprite_load_all("images/projectiles/redSquare.png", self->width, self->height, 1);
	/*if (self->sprite == NULL)
	{
		slog("no projectile image");
	}*/
	vector2d_set(self->position, Position.x, Position.y);
	vector2d_set(self->flip, 0, 0);
	vector4d_set(self->color, 255, 255, 255, 255);
	vector2d_set(self->velocity, direction.x, direction.y);
	self->hitbox.x = self->position.x;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
	self->hitActive = 0;
	self->frame = 0;
	self->dead = 0;
	self->update = projectileUpdate;

	self->touch = projectileTouch;

	slog("projectile spawned");
	return self;
}