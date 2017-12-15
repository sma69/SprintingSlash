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

	if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
		self->flip.x = 1;
		self->sprite = gf2d_sprite_load_all("images/players/zero_run.png", 43, 42, 11);
		self->position.x += (-self->moveSpeed * sprint);
	}
	if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
		self->flip.x = 0;
		self->sprite = gf2d_sprite_load_all("images/players/zero_run.png", 43, 42, 11);
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
		if (self->isGrounded != 1)
		{
			self->velocity.y += (1 * sprint);
		}
	}



}

void playerTouch(Entity* self, Entity* other)
{

	if(checkWallCollision(self, other) == 1) {
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

	/** <flip hitbox to position where the player is facing> */
	if (self->flip.x == 0) {
		self->hitbox.x = self->position.x + self->width - 10;
	}
	if (self->flip.x == 1)
	{ 
		self->hitbox.x = self->position.x - self->width + 10;
	}
	self->hitbox.y = self->position.y;
	self->hitbox.w = self->width;
	self->hitbox.h = self->height;

	if (self->velocity.x == 0 && self->velocity.y == 0)
	{
		self->sprite = gf2d_sprite_load_all("images/players/zero_idle.png", self->width, self->height, 6);
	}


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

void loadPlayerFromFile(char* filePath, Entity* self) {
	char* letter[1024];
	char* line[100];
	FILE *file;


	//open the file
	file = fopen(filePath, "r");
	rewind(file);

	//check if the user can open the file othe+rwise it does not exist
	if (file == NULL) {
		slog("File does not Exist");
	}
	else {
		printf("File Loaded");
	}
	while (fscanf(file, "%s", letter) != EOF)
	{
		if (strcmp(letter, "entity=") == 0) {
			fscanf(file, "%s", (char*)&self->type);
			continue;
		}
		if (strcmp(letter, "moveSpeed=") == 0) {
			fscanf(file, "%i", &self->moveSpeed);
			continue;
		}
		if (strcmp(letter, "width=") == 0) {
			fscanf(file, "%i", &self->width);
			continue;
		}
		if (strcmp(letter, "height=") == 0) {
			fscanf(file, "%i", &self->height);
			continue;
		}
		if (strcmp(letter, "hitOffset=") == 0) {
			fscanf(file, "%i %i", &self->hitOffset.x, &self->hitOffset.y);
			continue;
		}
		if (strcmp(letter, "color=") == 0) {
			fscanf(file, "%i %i %i %i", &self->color.x, &self->color.y, &self->color.z, &self->color.w);
			continue;
		}
		if (strcmp(letter, "hitActive=") == 0) {
			fscanf(file, "%i", &self->hitActive);
			continue;
		}

	}
	fclose(file);
	return self;

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
	
	loadPlayerFromFile("objects/player/player.txt", self);
	gSword1 = Mix_LoadWAV("music/swordSwing1.wav");
	//self->width = 43;
	//self->height = 46;
	//vector2d_set(self->hitOffset, 10, 0);
	vector2d_set(self->body, self->width, self->height);
	//self->moveSpeed = 4;
	self->jumpTime = 0;
	//self->gravity = self->normalGravity;
	//self->type = "player";
	self->al = anim_new();
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

	self->update = playerUpdate;

	self->touch = playerTouch;
	
	slog("player spawned");
	return self;
}



