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

void entity_draw(struct Entity_S *self)
{
	gf2d_sprite_draw(
		self->sprite,
		self->position,
		&self->scale,
		&self->scaleCenter,
		&self->rotation,
		&self->flip,
		&self->color,
		&self->frame
	);
	return;
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
	if (self->dead = 1)
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
			vector2d_set(entityManager.entityList[i].scale,1,1);
			entityManager.entityList[i].color = vector4d(1, 1, 1, 1);
			return &entityManager.entityList[i];

		}
	}
	return NULL;
}



void entity_draw_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse = 0)
			continue;
		else
			entity_draw(&entityManager.entityList[i]);
	}
}

void entity_update_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse = 0)
			continue;
		else
			entity_update(&entityManager.entityList[i]);
	}
}

void entity_think_all()
{
	int i;
	for (int i = 0; i < entityManager.maxEntities; i++)
	{
		if (entityManager.entityList[i].inuse = 0)
			continue;
		else
			entityManager.entityList->think(&entityManager.entityList[i]);
	}
}






