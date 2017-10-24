#ifndef __GF2D_PLAYER_H__
#define __GF2D_PLAYER_H__

#include <SDL.h>
#include "gf2d_entity.h"
#include "gf2d_graphics.h"

//the attributes of the dot

int sprint;

/**
@brief  Function to calculate velocity
*/

/**
@brief  Initializes player entity
*/
Entity *player_new(Vector2D Position);

/**
@brief  Makes the player think/takes in input
*/
void playerThink(Entity* self);

/**
@brief  Makes the player react to other entities
*/
void playerTouch(Entity* self, Entity* other);

/**
@brief updates the player entity
*/
void playerUpdate(Entity* self);


/**
@brief  Players the player move
*/
void playerMove(Entity * self);

#endif