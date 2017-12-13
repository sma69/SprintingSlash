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

void anim_manager_clear_all()
{
	
	for (int i = 0; i < animManager.maxAnimLists; i++)
	{
		anim_manager_delete(&animManager.animList[i]); // delete animation list at that point in memory
	}
}

void anim_manager_close()
{
	anim_manager_clear_all();
	if (animManager.animList != NULL)
	{
		free(animManager.animList);
	}
	animManager.animList = NULL;
	animManager.maxAnimLists = 0;
	slog("Animation List Manager closed");
}

void anim_manager_free(AnimationList* animList)
{
	if (!animList)
		return;
	animList->refCount--;
}

void anim_manager_init(Uint32 maxAnimLists)
{
	if (!maxAnimLists)
	{
		slog("cannot initialize without a max entity cap");
		return;
	}
	animManager.animList = (Animation*)malloc(sizeof(AnimationList)*maxAnimLists);
	if (!animManager.animList)
	{
		slog("failed to initialize Animation list");
		entity_manager_close();
		return;
	}
	animManager.maxAnimLists = maxAnimLists;
	memset(animManager.animList, 0, sizeof(AnimManager)*maxAnimLists);
	atexit(anim_manager_close);
	slog("entity system initialized");

}


AnimationList * anim_new()
{
	for (int i = 0; i < animManager.maxAnimLists; i++)
	{
		if ((animManager.animList[i].refCount == 0) && (animManager.animList[i].anim == NULL))
		{
			animManager.animList[i].refCount == 1;
			return &animManager.animList[i]; // return a reference to the animation list
		}
	}

	// check and clear the unused actions

	for (int i = 0; i < animManager.maxAnimLists; i++)
	{
		if ((animManager.animList[i].refCount == 0))
		{
			anim_manager_delete(&animManager.animList[i]);
			animManager.animList->refCount = 1;
			return &animManager.animList[i];
		}
	}
	slog("Cannot load animation list: animaiton List full");
	return 0;
}

