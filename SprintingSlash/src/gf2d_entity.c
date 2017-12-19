#include "gf2d_entity.h"


enum {
	PLAYER,
	ENEMY,
	ALLY,
};

typedef struct {
	Uint32 maxEntities;
	Entity * entityList;
	Uint64 incr;
}EntityManager;


static EntityManager entityManager = { 0 };


void entity_manager_close()
{
	int i;

	if (entityManager.entityList != 0)
	{
		for (i = 0; i < entityManager.maxEntities; i++)
		{
			entity_free(&entityManager.entityList[i]);
		}
		free(entityManager.entityList);
	}
	memset(&entityManager, 0, sizeof(EntityManager));
	slog("Closed Entity Manager");
}

void entity_manager_init(Uint32 maxEntities)
{
	if (!maxEntities)
	{
		slog("cannot initialize without a max entity cap");
		return;
	}
	memset(&entityManager, 0, sizeof(EntityManager));

	entityManager.entityList = (Entity*)malloc(sizeof(Entity)*maxEntities);
	if (!entityManager.entityList)
	{
		slog("failed to allocate entity list");
		entity_manager_close();
		return;
	}
	memset(entityManager.entityList, 0, sizeof(Entity)*maxEntities);
	entityManager.maxEntities = maxEntities;
	atexit(entity_manager_close);
	slog("entity system initialized");

}

void entity_draw(Entity *self, SDL_Rect camera)
{

	gf2d_sprite_draw(
		self->sprite,
		vector2d( self->position.x - camera.x,self->position.y - camera.y ),
		&self->scale,
		&self->scaleCenter,
		&self->rotation,
		&self->flip,
		&self->color,
		(int)self->frame
	);
	
}

void entity_think(Entity *self)
{
	if (!self)
	{
		slog("Entity Think Failed: Wrong Entity");
		return;
	}
	if (!self->inuse)
	{
		slog("Entity Think Failed: Entity not in use");
		return;
	}


	if (self->think != NULL)
	{
		self->think(self);
	}
}

void entity_touch(Entity *self, Entity * other)
{
	if (!self || !other->inuse)
	{
		slog("Entity Touch Failed: Wrong Entity");
		return;
	}

	if (!self->inuse || !other->inuse)
	{
		slog("Entity Touch Failed: Entity not in use");
		return;
	}

	if (self->touch != NULL)
	{
		self->touch(self, other);
	}
}

void entity_update(Entity *self)
{
	if (!self)
	{
		slog("Entity Update Failed: Wrong Entity");
		return;
	}
	if (!self->inuse)
	{
		slog("Entity Update Failed: Entity not in use");
		return;
	}
	if (self->dead == 1)
	{
		entity_free(self);
		return;
	}

	

	
	if (self->update != NULL)
	{
		self->update(self);
	}
}

void entity_free(Entity *self)
{
	int i;
	if (!self)
		return;
	gf2d_sprite_free(self->sprite);
	memset(self, 0, sizeof(Entity));
}

char snum[5];

Entity *entity_new()
{
	int i;
	for (i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse == 0)
		{
			memset(&entityManager.entityList[i], 0, sizeof(Entity));
			entityManager.entityList[i].refID = entityManager.incr++;
			entityManager.entityList[i].inuse = 1;
			entityManager.entityList[i].normalGravity  = 0.5f;
			
			itoa(entityManager.entityList[i].refID,snum, 10);
			printf("%s\n", snum);
			vector2d_set(entityManager.entityList[i].scale,1,1);
			entityManager.entityList[i].color = vector4d(255, 255, 255, 255);
			
			return &entityManager.entityList[i];

		}
	}
	return NULL;
}



void entity_draw_all(SDL_Rect camera)
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse == 0)
			continue;
		else
			entity_draw(&entityManager.entityList[i], camera);
	}
}

void entity_update_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse == 0)
			continue;
		if (entityManager.entityList[i].update != NULL) {
			
			entity_update(&entityManager.entityList[i]);
		}
	}
}

void entity_think_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse == 0)
			continue;
		if (entityManager.entityList[i].think != NULL)
		{
			
			entity_think(&entityManager.entityList[i]);
		}
	}
}

void entity_touch_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse == 0)
			continue;
		if (entityManager.entityList[i].touch != NULL)
		{
			for (int j = 0; j < entityManager.maxEntities; j++)
			{ 
				if (entityManager.entityList[j].inuse == 0)
					continue;
				if (j == i)
					continue;
							entity_touch(&entityManager.entityList[i], &entityManager.entityList[j]);
			
			}
		}
	}
}

void entity_clear_all()
{
	int i;
	for (i = 0; i < entityManager.maxEntities; i++)
	{
		entity_free(&entityManager.entityList[i]);// clean up the data
	}
}

Entity * getPlayer()
{
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].type == "player")
		{
			return &entityManager.entityList[i];
		}
	}
	return NULL;
}







