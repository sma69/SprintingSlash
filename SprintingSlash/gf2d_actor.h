#ifndef __GF2D_ACTOR_H
#define __GF2D_ACTOR_H

#include "gf2d_sprite.h"
#include "gf2d_vector.h"


/**
@brief This structure is the system that manages actions done by entities

*/

typedef struct Action_S {
	int startFrame;
	int endFrame;
	int recovery;
	int cd;
	char* anim;
	float frameRate;
}Action;

typedef struct ActionList_S {
	Action* actions;

}ActionList;

typedef struct
{
	Sprite     *sprite;       /**<which sprite to draw this entity with*/
	Vector4D    color;        /**<color to shift sprite too*/
	float       frame;        /**<current frame for the sprite*/
	ActionList *al;           /**<action list for managing sprite animations*/
	char*    action;       /**<the current action*/
}Actor;

/**
* @brief initialize the action list system
*/
void gf2d_action_list_init(Uint32 max);

/**
* @brief load an action list from file or get a reference to one already in memory
* @param filename the name of the action list to load
* @return NULL on error or a pointer to the action list
*/
ActionList *gf2d_action_list_load(
	char *filename
);

/**
* @brief let the system know you are done with the action list
* @param actionList the list to free
*/
void gf2d_action_list_free(ActionList *actionList);








#endif 
