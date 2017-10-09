#include "gf2d_collision.h"

int check_collision(Entity * self, Entity * other)
{
	//The sides of the Entity Hitboxes
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

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
	if (bottomA <= topB)
	{
		return 0;
	}

	if (topA >= bottomB)
	{
		return 0;
	}

	if (rightA <= leftB)
	{
		return 0;
	}

	if (leftA >= rightB)
	{
		return 0;
	}

	//If none of the sides from A are outside B
	return 1;
}