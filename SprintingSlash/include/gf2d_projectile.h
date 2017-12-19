#pragma once
#ifndef __GF2D_PROJECTILE_H__
#define __GF2D_PROJECTILE_H__

#include <SDL.h>
#include "gf2d_entity.h"
#include "gf2d_graphics.h"
#include "gf2d_vector.h"


/**
@brief spawns a linear projectile at a given location from a given speed and direction
@param Position spawns the projectile at this given spot in space
@param direction The direction of the projectile ( each value should not be outside of the range of -1 and 1)
@speed the speed of the projectile on both axis
@returns a projectile flying at tha given direction with a given speed
*/
Entity *projectile_new(Vector2D Position, Vector2D direction, int speed);

/**
@brief updates the projectile entity
*/
void projectileUpdate(Entity* self);


/**
@brief  Makes the projectile react to other entities
*/
void projectileTouch(Entity* self, Entity* other);



#endif