#ifndef __GF2D_ENTITY_H__
#define __GF2D_ENTITY_H__

#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_vector.h"



/**
@brief Entity manager functions to handle multiple entities in the world space
*/

#define MAX_ENTITIES = 1024


/**
@brief Entity class creation for all objects in game with a loaded sprite
@param sprite is teh image that the entity uses
@param position is the world position of the object
@param scale is the size of the object loaded in the game
@param rotation is the world rotation of the object
@param flip is the direction the sprite is facing
@param velocity is the direction and speed of the actor when force is applied
@param colorSift is the color filte acting on the sprite of the object
@param state is current state the object is in the toggle certian object properties
@param speed is the running speed of the object
@param jumpSpeed is the jump speed of the object
@param isKinematic is the toggle for enabling/disabling gravity
@param health is the total health an entity has before it is disabled
@return a game object that when is drawn functions on screen
*/

typedef struct Entity_S
{
	//Object/Sprite properties
	Uint32 refID;
	Sprite * sprite;
	Vector2D position;
	Vector2D scale;
	Vector2D scaleCenter;
	Vector2D rotation;
	Vector2D flip;
	Vector4D color;
	float frame;
	

	//transformation values
	Vector2D velocity;
	Vector2D acceleration;
	int speed;
	int jumpSpeed;
	int sprint;
	int state;
	int isKinematic;
	int maxHealth;
	int health;
	int cd;

	//state values
	int inuse;
	int dead;

	void (*think)(struct Entity_S *self); /**< makes the entity do an action in the worldspace */
	void (*update)(struct Entity_S *self); /**< updates the entity in every frame of the game loop */
	void (*touch)(struct Entity_S *self, struct Entity_S *other); /**< handles what happens on collision with other entities */

}Entity;



	//actor functions in game loop
	void entity_manager_close();  /**< Closes the entity manager */
	void entity_manager_init(Uint32 maxEntities);   /**< Initializes the entity manager */
	

	void entity_draw(struct Entity_S *self);  /**< draws the entity into the world */
	void entity_free(Entity *self);			  /**< Undraws the sprite of the entity in the world */
	Entity *entity_new();					  /**< instantiates a new entity on function call */

	//global entity functions
	void entity_draw_all();					  /**< draws all of the listed entities into the world */
	void entity_update_all();
	void entity_think_all();

	

#endif