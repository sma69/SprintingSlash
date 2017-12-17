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
	slog("Animation system initialized");

}


AnimationList * anim_new()
{
	for (int i = 0; i < animManager.maxAnimLists; i++)
	{
		if ((animManager.animList[i].refCount == 0) && (animManager.animList[i].anim == NULL))
		{
			animManager.animList[i].refCount = 1;
			
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

void animListLoadAnims(FILE *file, AnimationList* animList)
{
	Animation * anims;
	char buf[512];
	if (!file)return;
	rewind(file);
	anims = animList->anim;
	anims--;
	while (fscanf(file, "%s", buf) != EOF)
	{
		if (strcmp(buf, "sprite=") == 0)
		{
			fscanf(file, "%s", (char*)&animList->sprite);
			continue;
		}
		if (strcmp(buf, "width=") == 0)
		{
			fscanf(file, "%i", &animList->width);
			continue;
		}
		if (strcmp(buf, "height=") == 0)
		{
			fscanf(file, "%i", &animList->height);
			continue;
		}
		if (strcmp(buf, "frames=") == 0)
		{
			fscanf(file, "%i", &animList->frames);
			continue;
		}
		if (strcmp(buf, "scale=") == 0)
		{
			fscanf(file, "%lf,%lf", &animList->scale.x, &animList->scale.y);
			continue;
		}
		if (strcmp(buf, "color=") == 0)
		{
			fscanf(file, "%lf,%lf,%lf,%lf", &animList->color.x, &animList->color.y, &animList->color.z, &animList->color.w);
			continue;
		}
		if (strcmp(buf, "colorShift=") == 0)
		{
			fscanf(file, "%lf,%lf,%lf,%lf", &animList->colorShift.x, &animList->colorShift.y, &animList->colorShift.z, &animList->colorShift.w);
			continue;
		}
		if (strcmp(buf, "anim=") == 0)
		{
			anims++;
			fscanf(file, "%s", (char*)&anims->name);
			continue;
		}
		if (anims < animList->anim)
		{
			slog("file formatting error, expect action: tag before rest of data");
			continue;
		}
		if (strcmp(buf, "startFrame=") == 0)
		{
			fscanf(file, "%i", &anims->startFrame);
			continue;
		}
		if (strcmp(buf, "endFrame=") == 0)
		{
			fscanf(file, "%i", &anims->endFrame);
			continue;
		}
		if (strcmp(buf, "frameRate=") == 0)
		{
			fscanf(file, "%f", &anims->frameRate);
			continue;
		}
		fgets(buf, sizeof(buf), file);
	}
}

AnimationList *animListFromFile(char * filename)
{
	int i;
	for (i = 0; i < animManager.maxAnimLists; i++)
	{
		if (animManager.animList[i].fileName == filename)
		{
			return &animManager.animList[i];
		}
	}
	return NULL;// not found
}

int animCountFromFile(FILE *file)
{
	char buf[512];
	int count = 0;
	if (!file)return 0;
	rewind(file);
	while (fscanf(file, "%s", buf) != EOF)
	{
		if (strcmp(buf, "action:") == 0)
		{
			count++;
		}
		fgets(buf, sizeof(buf), file);
	}
	return count;
}


Animation *getAnimationFromList(AnimationList *al, char *name)
{

	if (!al)
	{
		slog("no action list provided");
		return NULL;
	}
	if (!name)
	{
		slog("no filename provided");
		return NULL;
	}
	for (int i = 0; i < al->numAnimations; i++)
	{
		if (gf2d_line_cmp(al->anim[i].name, name) == 0)
		{
			return &al->anim[i];
		}
	}
	return NULL;// not found
}

AnimationList *animListLoad(char* filePath)
{

		FILE *file;
		AnimationList *animList;
		int count;
		animList = animListFromFile(filePath);
		if (animList != NULL)
		{
			// found a copy already in memory
			animList->refCount++;
			return animList;
		}

		animList = anim_new();
		if (!animList)
		{
			return NULL;
		}
		file = fopen(filePath, "r");
		if (!file)
		{
			anim_manager_delete(animList);
			slog("failed to open action file: %s", filePath);
			return NULL;
		}
		animList->fileName = filePath;
		count = animCountFromFile(file);
		if (!count)
		{
			anim_manager_delete(animList);
			fclose(file);
			slog("No actions found in file: %s", filePath);
			return NULL;
		}
		animList->anim = (Animation*)malloc(sizeof(Animation)*count);
		memset(animList->anim, 0, sizeof(Animation)*count);
		animList->numAnimations = count;
		getAnimationFromList(file, animList);

		fclose(file);
		return animList;

}

