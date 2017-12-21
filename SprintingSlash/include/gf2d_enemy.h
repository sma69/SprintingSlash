#pragma once
#ifndef __GF2D_ENEMY_H__
#define __GF2D_ENEMY_H__

#include  "gf2d_entity.h"
#include "gf2d_player.h"


/**
@brief  Initializes player entity
*/
Entity *enemy_new(Vector2D Position);

/**
@brief  Makes the player think/takes in input
*/
void enemyThink(Entity* self);

/**
@brief  Makes the player react to other entities
*/
void enemyTouch(Entity* self, Entity* other);

/**
@brief updates the enemy entity
*/
void enemyUpdate(Entity* self);

/**
@brief updates the second enemy entity
*/
void enemy2Update(Entity * self);

/**
@brief updates the first boss entity
*/
void bossUpdate(Entity * self);


/**
@brief  the Enemy's movement function of its think
*/
void enemyMove(Entity * self);

/**
@brief Spawns the first boss at a given location
*/

Entity *boss_new(Vector2D Position);


/**
@brief Spawns the second boss at a given location
*/
Entity *boss2_new(Vector2D Position);


#endif