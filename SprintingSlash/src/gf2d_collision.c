#include "gf2d_collision.h"

//int checkWallCollision(Entity * self, Entity * other)
//{
//	//The sides of the Entity Hitboxes
//	//The sides of the rectangles
//	double leftA, leftB;
//	double rightA, rightB;
//	double topA, topB;
//	double bottomA, bottomB;
//
//	//Calculate the sides of the main entity
//	leftA = self->body.x;
//	rightA = self->body.x + self->body.w;
//	topA = self->body.y;
//	bottomA = self->body.y + self->body.h;
//
//	//Calculate the sides of the other entity
//	leftB = other->body.x;
//	rightB = other->body.x + other->body.w;
//	topB = other->body.y;
//	bottomB = other->body.y + other->body.h;
//
//	//If any of the sides from A are outside of B
//	if (bottomA > topB)
//	{
//		self->position.y = other->body.y - self->height;
//		self->velocity.y = 0;
//		self->isGrounded = 1;
//		return 1;
//	}
//
//	if (topA < bottomB)
//	{
//		self->position.y = other->body.y + other->body.h - 1;
//		return 1;
//	}
//	if (rightA > leftB)
//	{
//		self->position.x = other->body.x - self->width;
//		return 1;
//	}
//
//	if (leftA > rightB)
//	{
//		self->position.x = other->body.x + other->body.w + 1 ;
//		return 1;
//	}
//
//	//If none of the sides from A are outside B
//	return 0;
//}

int checkBoxCollision(Entity * self, Entity * other)
{
	if (self->body.x + self->body.w < other->body.x || self->body.x > other->body.x + other->body.w ||
		self->body.y + self->body.h < other->body.y || self->body.y > other->body.y + other->body.h)
	{
			self->moveSpeed = 4;
			vector4d_set(self->color, 255, 0, 255, 255);
			return 0;
		
	}
	self->moveSpeed = -4;
	vector4d_set(self->color, 255, 255, 255, 255);
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

	self->sprite = gf2d_sprite_load_all("images/walls/greyStoneWall.jpg", self->body.w, self->body.h, 1);
	return self;
}