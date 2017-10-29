#include "gf2d_enemy.h"

void enemyThink(Entity* self)
{
	enemyMove(self);
}

void enemyMove(Entity * self)
{
	
	

}

void enemyUpdate(Entity * self)
{
	self->hitActive = 0;
	self->frame += 0.03;
	if (self->frame >= 1.0)self->frame = 0;
	float timeStep = 60;
	//move entity to left or right
	self->position.x += self->velocity.x;
	self->position.y += self->velocity.y;
	self->body.x = self->position.x;
	self->body.y = self->position.y;
	self->body.w = self->width;
	self->body.h = self->height;
	self->velocity.y += self->gravity;
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;


	//if entity went too far to the left
	if (self->position.x < 0)
	{
		//Move back
		self->position.x = 0;
		self->velocity.x = 3;
	}

	//or the right
	else if (self->position.x >= 1120 - self->width)
	{

		//self->position.x = 1200 - self->width;
		self->velocity.x = 0;
	}


	//if the dot went too far up
	if (self->position.y < 0)
	{
		//Move back
		self->position.y = 0;
	}
	//or down
	else if (self->position.y > 720 - self->height)
	{
		//Move Back
		self->position.y = 720 - self->height;
		self->velocity.y = 0;
		self->isGrounded = 1;
	}
}

void enemyTouch(Entity* self, Entity* other)
{

}

Entity *enemy_new(Vector2D Position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("enemy does not exist\n");
	
	}

	vector2d_set(self->position, Position.x, Position.y);
	self->width = 43;
	self->height = 46;
	vector2d_set(self->hitOffset, 10, 0);
	vector2d_set(self->body, self->width, self->height);
	self->moveSpeed = 4;
	self->velocity.x = 3;
	self->jumpTime = 0;
	self->gravity = 0.5f;
	self->type = "enemy";
	
	self->sprite = gf2d_sprite_load_all("images/players/redSquare.png", self->width, self->height, 1);
	vector2d_set(self->flip, 0, 0);
	vector4d_set(self->color, 255, 255, 255, 255);
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
	self->hitActive = 0;
	self->maxHealth = 100;
	self->health = self->maxHealth;
	self->frame = 0;
	self->dead = 0;
	//self->think = enemyThink;
	self->update = enemyUpdate;
	//self->touch = enemyTouch;
	slog("enemy spawned");
	return self;
}