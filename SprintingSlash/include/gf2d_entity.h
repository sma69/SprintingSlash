#ifndef __GF2D_ENTITY_H__
#define __GF2D_ENTITY_H__

#include "gf2d_sprite.h"


/**
@brief Entity class creation for all objects in game with a loaded sprite
@param sprite is teh image that the entity uses
@param position is the world position of the object
@param scale is the size of the object loaded in the game
@param rotation is the world rotation of the object
@param flip is the direction the sprite is facing
@param colorSift is the color filte acting on the sprite of the object
@param state is current state the object is in the toggle certian object properties
@param speed is the running speed of the object
@param jumpSpeed is the jump speed of the object
@param isKinematic is the toggle for enableing/disabling gravity
@return a game object that when is drawn functions on screen
*/

typedef struct Entity_S
{
	Sprite * sprite;
	Vector2D * position;
	Vector2D * scale;
	Vector2D * rotation;
	Vector2D * flip;
	Vector4D * colorShift;
	int speed;
	int jumpSpeed;
	int state;
	int isKinematic = 0;


private:
	int health;

}Entity;





#endif