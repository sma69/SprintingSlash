#ifndef __GF2D_ACTOR_H
#define __GF2D_ACTOR_H

#include "gf2d_sprite.h"
#include "gf2d_vector.h"


/**
@brief This structure is the system that manages actions done by entities

*/

typedef struct Animation_S {
	int startFrame;
	int endFrame;
	int recovery;
	int cd;
	char* anim;
	float frameRate;
}Animation;

/**
@brief This structure is the list of animations for an actor to hold
*/
typedef struct AnimationList_S {
	Animation* anim;
	Uint32 *refID;
	Uint32 *refCount;
	Sprite * sprite;
	int numAnimations;
	int height;
	int width;
	int frames;
	Vector2D scale;
	Vector4D color;
	Vector4D colorShift;


}AnimationList;

/**
@brief the actor component for objects to hold sprites and animations
*/

typedef struct
{
	Sprite     *sprite;       /**<which sprite to draw this entity with*/
	Vector4D    color;        /**<color to shift sprite too*/
	float       frame;        /**<current frame for the sprite*/
	AnimationList *al;           /**<action list for managing sprite animations*/
	char*    animName;       /**<the current action*/
}Actor;

/**
* @brief initialize the action list system
*/

void anim_manager_close();

void anim_manager_delete(AnimationList * animList);

void anim_manager_init(); 

AnimationList * anim_new();	

void anim_manager_free(AnimationList* animList);

void anim_draw(Textbox * self);

void anim_draw_all(SDL_Rect camera);	







#endif 
