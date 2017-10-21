#pragma once
#ifndef __GF2D_COLLISION_H__
#define __GF2D_COLLISION_H__

#include "gf2d_entity.h"

/**
@brief checkBoxCollision returns true if two entities  with Box colliders collide
*/

int checkBoxCollision(Entity * self, Entity * other);

/**
@brief checkSphereCollision returns true if two entities with circle colliders collide
*/

int checkCircleCollision(Entity * self, Entity * other);

/**
@brief check
*/

/**creates
@brief creates a wall entity at a given position
*/

Entity* wall_new(Vector2D position);

#endif