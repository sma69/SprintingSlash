#include "gf2d_player.h"
Mix_Chunk* gSword1;
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
		self->flip.x = 1;
		self->position.x += (-self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
		self->flip.x = 0;
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
		self->velocity.y += (1 * sprint);
	}



}

void playerTouch(Entity* self, Entity* other)
{

	if(checkBoxCollision(self, other) == 1) {
		self->isGrounded = 1;
	}
	
	self->hitActive = 0;
	if(keys[SDL_SCANCODE_E]) {
		self->hitActive = 1;
		//Load sound effects
		

		Mix_PlayChannel(-1,gSword1, 0,-1);
		if (gSword1 == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}

		if (self->hitActive == 1) {
			if (checkHitboxCollision(self, other) == 0) 
			{
				vector4d_set(self->color, 255, 255, 255, 255);
				self->hitActive = 0;
			}
			if (checkHitboxCollision(self, other) == 1)
			{
				vector4d_set(self->color, 255, 0, 100, 255);
				self->hitActive = 0;
				other->dead = 1;
			}
			
				
		}
		

	}

}



void playerUpdate(Entity * self)
{
	
	self->hitActive = 0;
	self->frame += 0.03;
	if (self->frame >= 6.0)self->frame = 0;
	float timeStep = 60;
	//move entity to left or right
	self->position.x += self->velocity.x;
	self->position.y += self->velocity.y;
	self->body.x = self->position.x;
	self->body.y = self->position.y;
	self->body.w = self->width;
	self->body.h = self->height;
	self->velocity.y += self->gravity;
	if (self->flip.x == 0) {
		self->hitbox.x = self->position.x - 10 + self->width;
	}
	if (self->flip.x == 1)
	{ 
		self->hitbox.x = self->position.x - 10 + self->width;
	}
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;



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
	
	gSword1 = Mix_LoadWAV("music/swordSwing1.wav");
	self->width = 43;
	self->height = 46;
	vector2d_set(self->hitOffset, 10, 0);
	vector2d_set(self->body, self->width, self->height);
	self->moveSpeed = 4;
	self->jumpTime = 0;
	//self->gravity = self->normalGravity;
	self->type = "player";
	self->sprite = gf2d_sprite_load_all("images/players/zero_idle.png", self->width, self->height, 6);
	vector2d_set(self->position, Position.x, Position.y);
	vector2d_set(self->flip, 0, 0);
	vector4d_set(self->color, 255, 255, 255, 255);
	self->hitbox.x = self->position.x + self->width;
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;
	self->hitActive = 0;
	self->frame = 0;
	self->dead = 0;
	self->think = playerThink;
	//(*self->think)(self);
	self->update = playerUpdate;
	//(*self->update)(self);
	self->touch = playerTouch;
	
	slog("player spawned");
	return self;
}



