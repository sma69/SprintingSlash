#pragma once
#ifndef __GF2D_COLLISION_H__
#define __GF2D_COLLISION_H__

#include "gf2d_entity.h"

/**
@brief check_collision returns true if two entities collide
*/

int check_collision(Entity * self, Entity * other);

/**creates
@brief creates a wall entity at a given position
*/

void wall_new(Vector2D position);

#endif