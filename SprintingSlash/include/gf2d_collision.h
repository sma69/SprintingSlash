#pragma once
#ifndef __GF2D_COLLISION_H__
#define __GF2D_COLLISION_H__

#include "gf2d_text.h"
#include "gf2d_entity.h"
#include "gf2d_text.h"
#include "gf2d_shape.h"


typedef struct Collision_S Collision;


typedef struct Body_S
{
	TextLine * name;
	int isActive;
	Uint32 team;
	Uint32 layer;
	Vector2D position;
	Vector2D velocity;
	Vector2D newVelocity;
	float gravity;
	float mass;
	float elasticity;
	Shape* shape;
	int(*bodyTouch)(struct Body_S *self, struct Body_S *other, Collision *collision);/**< function to call when two bodies collide*/
	int(*worldTouch)(struct Body_S *self, Collision *collision);/**<function to call when a body collides with a static shape*/
}Body;

struct Collision_S
{
	Uint8 collided;
	Vector2D point;
	Vector2D normal;
	Shape* shape;
	Body* body;
	float timeStep;

};

typedef struct
{
	Rect*   bodyList;       /**<list of bodies in the space*/
	int*      *staticShapes;   /**<list of shapes that will collide that do not move*/
	int         precision;      /**<number of backoff attempts before giving up*/
	Rect    bounds;         /**<absolute bounds of the space*/
	float       timeStep;       /**<how much each iteration of the simulation progresses time by*/
	Vector2D    gravity;        /**<global gravity pull direction*/
	float       dampening;      /**<rate of movement degrade  ambient frictions*/
	float       slop;           /**<how much to correct for body overlap*/
}Space;

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

/**
* @brief create a new space
* @return NULL on error or a new empty space
*/
Space *space_new();

/**
* @brief create a new space and set some defaults
* @param precision number of retry attempts when movement collides
* @param bounds the absolute bounds of the space
* @param timeStep this should be fraction that can add up to 1.  ie: 0.1 or 0.01, etc
* @param gravity the direction that gravity pulls
* @param dampening the rate of all movemement decay
* @param slop how much to correct for body overlap
*/
Space *space_new_full(
	int         precision,
	SDL_Rect        bounds,
	float       timeStep,
	Vector2D    gravity,
	float       dampening,
	float       slop);

/**
* @brief cleans up a space
*/
void space_free(Space *space);

/**
* @brief visualize the space and its contents
*/
void space_draw(Space *space);

/**
* @brief add a body to the space simulation
* @param space the space to add a body to
* @param body the body to add to the space
* @note the space will not free the body, but do not until it has been removed from the space
*/
void space_add_body(Space *space, Body *body);

/**
* @brief removes a body from the space
* @note this should not be done DURING a space update
* @param space the space to remove the body from
* @param body the body to remove
*/
void space_remove_body(Space *space, Body *body);

/**
* @brief apply a force to a body taking into account momentum
* @param body the body to move
* @param direction a unit vector for direction (Does not have to be)
* @param force the amount of force to apply
*/
void body_push(Body *body, Vector2D direction, float force);

/**
* @brief add a statuc shape to the space
* @note the shape parameters need to be in absolute space, not relative to any body
* @param space the space to add to
* @param shape the shape to add.
*/
void space_add_static_shape(Space *space, Shape* shape);

/**
* @brief update the bodies in the physics space for one time slice
* @param space the space to be updated
*/
void space_update(Space *space);

/**
* @brief check if a shape intersects with any body or shape within the space
* @param space the space to test
* @param shape the shape to test with
* @return the collision information
*/
Collision space_shape_test(Space *space, Shape * shape);

#endif
