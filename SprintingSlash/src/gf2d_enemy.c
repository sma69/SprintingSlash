#include "gf2d_enemy.h"
#include "gf2d_collision.h"

void enemyThink(Entity* self)
{
	enemyMove(self);
}

void enemyMove(Entity * self)
{
	
	projectile_new(vector2d(self->position.x - 50, self->position.y), vector2d(-1, 0), 5);

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
		self->velocity.x = -3;
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

void enemy2Update(Entity * self)
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
	//self->velocity.y += self->gravity;
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
		self->velocity.x = -3;
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

void bossUpdate(Entity * self)
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
	//self->velocity.y += self->gravity;
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
}

void enemyTouch(Entity* self, Entity* other)
{
	//checkBoxCollision(self, other);
	if (checkWallCollision(self, other) == 1) {
		self->isGrounded = 1;
	}
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
	self->think = enemyThink;
	self->update = bossUpdate;
	self->touch = enemyTouch;
	slog("enemy spawned");
	return self;
}

Entity *enemy2_new(Vector2D Position)
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

	self->sprite = gf2d_sprite_load_all("images/players/blueSquare.jpg", self->width, self->height, 1);
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
	self->update = enemy2Update;
	//self->touch = enemyTouch;
	slog("enemy2 spawned");
	return self;
}

Entity *enemy3_new(Vector2D Position)
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

	self->sprite = gf2d_sprite_load_all("images/players/yellowSquare.png", self->width, self->height, 1);
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
	self->think = enemyThink;
	self->update = enemyUpdate;
	self->touch = enemyTouch;
	slog("enemy3 spawned");
	return self;
}


Entity *boss_new(Vector2D Position)
{
	Entity * self;
	self = entity_new();

	if (!self)
	{
		slog("enemy does not exist\n");

	}

	vector2d_set(self->position, Position.x, Position.y);
	self->width = 200;
	self->height = 200;
	vector2d_set(self->hitOffset, 10, 0);
	vector2d_set(self->body, self->width, self->height);
	self->moveSpeed = 4;
	//self->velocity.x = 3;
	self->jumpTime = 0;
	self->gravity = 0.5f;
	self->type = "enemy";

	self->sprite = gf2d_sprite_load_all("images/players/redSquare.png", self->width, self->height, 1);
	vector2d_set(self->flip, 0, 0);
	vector4d_set(self->color, 0, 0, 255, 105);
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
	self->hitActive = 0;
	self->maxHealth = 100;
	self->health = self->maxHealth;
	self->frame = 0;
	self->dead = 0;
	self->think = enemyThink;
	//self->update = bossUpdate;
	//self->touch = enemyTouch;
	slog("boss spawned");
	return self;
}


Entity *boss2_new(Vector2D Position)
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

	self->sprite = gf2d_sprite_load_all("images/players/zero_idle.png", self->width, self->height, 6);
	vector2d_set(self->flip, 0, 0);
	vector4d_set(self->color, 0, 0, 255, 255);
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
	self->hitActive = 0;
	self->maxHealth = 100;
	self->health = self->maxHealth;
	self->frame = 0;
	self->dead = 0;
	self->think = playerThink;
	self->update = enemyUpdate;
	self->touch = enemyTouch;
	slog("enemy spawned");
	return self;
}
