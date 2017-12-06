#include "gf2d_actor.h"

/**
@brief The static animation list manager class for each game object
*/
typedef struct {
	Uint32 maxAnimLists;
	AnimationList * animList;
	Uint64 incr;
}AnimManager;

AnimManager animManager;



void anim_manager_close()
{



}

void anim_manager_delete(AnimationList * animList)
{
	if (!animList)   // if the animation list does not exist
		return; 
	if (animList->anim != NULL)
	{
		free(animList->anim);
	}
	memset(animList, 0, sizeof(AnimationList)); // clear the data of the animation list
		
}

void anim_manager_free(AnimationList* animList)
{
	if (!animList)
		return;
	animList->refCount--;
}
