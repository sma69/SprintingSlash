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

}

void entity_draw(struct Entity_S *self)
{
	gf2d_sprite_draw(
		&self->sprite,
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
