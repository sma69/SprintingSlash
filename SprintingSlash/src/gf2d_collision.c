#include "gf2d_collision.h"
/*
int checkWallCollision(Entity * self, Entity * other)
{
	//The sides of the Entity Hitboxes
	//The sides of the rectangles
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	//Calculate the sides of the main entity
	leftA = self->body.x;
	rightA = self->body.x + self->body.w;
	topA = self->body.y;
	bottomA = self->body.y + self->body.h;

	//Calculate the sides of the other entity
	leftB = other->body.x;
	rightB = other->body.x + other->body.w;
	topB = other->body.y;
	bottomB = other->body.y + other->body.h;

	//If any of the sides from A are outside of B
	if (bottomA > topB)
	{
		self->position.y = other->body.y - self->height;
		self->velocity.y = 0;
		self->isGrounded = 1;
		return 1;
	}

	if (topA < bottomB)
	{
		self->position.y = other->body.y + other->body.h - 1;
		return 1;
	}
	if (rightA > leftB)
	{
		self->position.x = other->body.x - self->width;
		return 1;
	}

	if (leftA > rightB)
	{
		self->position.x = other->body.x + other->body.w + 1 ;
		return 1;
	}

	//If none of the sides from A are outside B
	return 0;
}
*/

void gf2d_body_clear(Body *body)
{
	if (!body)return;
	memset(body, 0, sizeof(Body));
}

void gf2d_body_set(
	Body       *body,
	char       *name,
	Uint32      layer,
	Uint32      team,
	Vector2D    position,
	Vector2D    velocity,
	float       mass,
	float       gravity,
	float       elasticity,
	int(*bodyTouch)(struct Body_S *self, struct Body_S *other, Collision *collision),
	int(*worldTouch)(struct Body_S *self, Collision *collision))
{
	if (!body)return;
	body->layer = layer;
	body->team = team;
	vector2d_copy(body->position, position);
	vector2d_copy(body->velocity, velocity);
	body->mass = mass;
	body->gravity = gravity;
	body->elasticity = elasticity;
	body->bodyTouch = bodyTouch; 
	body->worldTouch = worldTouch;
	gf2d_word_cpy(body->name, name);
}

int checkBoxCollision(Entity * self, Entity * other)
{
	if (self->body.x + self->body.w < other->body.x || self->body.x > other->body.x + other->body.w ||
		self->body.y + self->body.h < other->body.y || self->body.y > other->body.y + other->body.h)
	{

			return 0;
		
	}

	return 1;
}

int checkCircleCollision(Entity *self, Entity * other)
{
	double positionA, positionB;

	
}

Entity* wall_new(Vector2D position)
{
	Entity * self = entity_new();
	
	vector2d_set(self->position, position.x, position.y);
	self->body.x = position.x;
	self->body.y = position.y;

	self->body.w = 200;
	self->body.h = 400;
	self->type = "wall";

	self->sprite = gf2d_sprite_load_all("images/walls/greyStoneWall.jpg", self->body.w, self->body.h, 1);
	return self;
}