#include "gf2d_player.h"

void playerThink(Entity* self)
{
	playerMove(self);
}

void playerMove(Entity * self) 
{
	//Player movement
	keys = SDL_GetKeyboardState(NULL);
	//gravity
	self->position.y += self->gravity;

	//toggle sprinting
	if (keys[SDL_SCANCODE_LSHIFT])
		sprint = 2;
	else
		sprint = 1;

	if (keys[SDL_SCANCODE_A]) {
		self->position.x -= (self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_D]) {
		self->position.x += (self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_W]) {

		self->velocity.y += 0.1;
		self->jumpTime += 1;

		if (self->jumpTime <= 100)
		{
			self->isJumping = 1;
			self->isGrounded = 0;
		}
		if (self->jumpTime >= 100)
		{
			self->isFalling = 1;
			self->isGrounded = 0;
		}
		if (self->isFalling == 0)
		{
			self->isGrounded = 0;
			self->position.y -= ((self->velocity.y) * sprint);
		}
	}
	if (keys[SDL_SCANCODE_S]) {
		self->position.y += (self->moveSpeed * sprint);
	}
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
	if (self->isGrounded = 1)
	{
		self->velocity.y;
		self->jumpTime = 0;

	}
	else {
		self->isGrounded = 0;
		self->isFalling = 0;
	}

}

void playerUpdate(Entity * self)
{
	float timeStep = 60;
	//move entity to left or right
	self->position.x += self->velocity.x * timeStep;


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

	//Move the dot up or down
	self->position.y += self->velocity.y * timeStep;

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
	self->moveSpeed = 4;
	self->jumpTime = 0;
	self->gravity = 2;
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



