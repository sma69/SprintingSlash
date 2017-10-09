#ifndef __GF2D_PLAYER_H__
#define __GF2D_PLAYER_H__

#include <SDL.h>
#include "gf2d_entity.h"
#include "gf2d_graphics.h"

//the attributes of the dot
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;
const int DOT_VEL = 200;

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
@brief updates the player entity
*/
void playerUpdate(Entity* self);


/**
@brief  Players the player move
*/
void playerMove(Entity * self);

#endif