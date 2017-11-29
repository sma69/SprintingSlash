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

typedef struct AnimationList_S {
	Animation* animation;

}AnimationList;

typedef struct
{
	Sprite     *sprite;       /**<which sprite to draw this entity with*/
	Vector4D    color;        /**<color to shift sprite too*/
	float       frame;        /**<current frame for the sprite*/
	AnimationList *al;           /**<action list for managing sprite animations*/
	char*    animation;       /**<the current action*/
}Actor;

/**
* @brief initialize the action list system
*/
void gf2d_anim_init(Uint32 max);

void anim_manager_close();		

void anim_manager_init(Uint32 maxTextboxes); 

Textbox * anim_new();	

void anim_free(Textbox * self);

void anim_draw(Textbox * self);

void anim_draw_all(SDL_Rect camera);	







#endif 
