#ifndef __GF2D_PLAYER_H__
#define __GF2D_PLAYER_H__

#include <SDL.h>
#include "gf2d_entity.h"
#include "gf2d_graphics.h"
#include "gf2d_file.h"
#include "gf2d_level.h"


//the attributes of the dot

int sprint;

/**
@brief  Function to calculate velocity
*/

/**
@brief  Initializes player entity
@param Position is the position in the game where the player is to spawn
@return a player entity at the given position
*/
Entity *player_new(Vector2D Position);

/**
@brief loads player initialization variables from file
@param filepath path to file
@param self is the entity being loaded
*/

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