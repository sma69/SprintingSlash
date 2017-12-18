#ifndef __GF2D_ACTOR_H
#define __GF2D_ACTOR_H

#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include "gf2d_file.h"
#include "simple_logger.h"


/**
@brief This structure is the system that manages actions done by entities

*/

typedef struct Animation_S {
	int startFrame;
	int endFrame;
	int recovery;
	int cd;
	char* name;
	char* filePath;
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
	char* fileName;


}AnimationList;

/**
@brief the actor component for objects to hold sprites and animations
*/

typedef struct
{
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

void anim_manager_init(Uint32 maxAnimLists);

AnimationList * anim_new();	

void anim_manager_free(AnimationList* animList);

int animCountFromFile(FILE *file);

AnimationList *animListFromFile(char * filename);

AnimationList *animListLoad(char* filePath);





#endif 
