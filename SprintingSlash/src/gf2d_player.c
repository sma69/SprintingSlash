#include "gf2d_player.h"

void playerThink(Entity* self)
{
	playerMove(self);
}

void playerMove(Entity * self) 
{
	//Player movement
	keys = SDL_GetKeyboardState(NULL);

	//toggle sprinting
	if (keys[SDL_SCANCODE_LSHIFT])
		sprint = 2;
	else
		sprint = 1;

	if (keys[SDL_SCANCODE_A]  || keys[SDL_SCANCODE_LEFT]) {
		self->position.x -= (self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
		self->position.x += (self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {

	
		if (self->isGrounded == 1)
		{
			self->velocity.y = -12.0f;
			self->isGrounded = 0;
		}

	}
	if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
		self->position.y += (self->moveSpeed * sprint);
	}
	/*
	if (self->position.x < 0) {
		self->position.x = 0;
	}
	else if (self->position.x > 1200 - self->width) {
		self->position.x = 1200 - self->width;
	}
	if (self->position.y < 0) {
		self->position.y = 0;
	}
	else if (self->position.y > 720 - self->height) {
		self->position.y = 720 - self->height;
		self->isFalling = 0;
		self->isGrounded = 1;
	}
	if (self->isGrounded == 1)
	{


	}
	else {
		self->isGrounded = 0;
		self->isFalling = 0;
	}
	*/
}

void playerUpdate(Entity * self)
{
	float timeStep = 60;
	//move entity to left or right
	self->position.x += self->velocity.x;
	self->position.y += self->velocity.y;
	self->velocity.y += self->gravity;


		//if entity went too far to the left
		if (self->position.x < 0)
		{
			//Move back
			self->position.x = 0;
		}

		//or the right
		else if (self->position.x > 1200 - self->width)
		{
			self->position.x = 1200 - self->width;
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
	self->width = 43;
	self->height = 46;
	vector2d_set(self->body, self->width, self->height);
	self->moveSpeed = 4;
	self->jumpTime = 0;
	self->gravity = 0.5f;
	self->sprite = gf2d_sprite_load_all("images/players/zero_idle.png", self->width, self->height, 6);
	vector2d_set(self->position, Position.x, Position.y);
	vector4d_set(self->color, 255, 255, 255, 255);
	self->frame = 0;
	self->think = playerThink;
	(*self->think)(self);
	self->update = playerUpdate;
	(*self->update)(self);
	slog("player spawned");
	return self;
}



