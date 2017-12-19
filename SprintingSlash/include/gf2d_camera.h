#pragma once
#ifndef __GF2D_CAMERA_H__
#define __GF2D_CAMERA_H__

#include <SDL.h>
#include "gf2d_entity.h"
#include "gf2d_level.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

void camera_show(SDL_Rect camera);



/**
@brief set the camera and set it on an entity
@param camera The camera rect that the viewport will use
@param target The entity target to keep the camera looking at
*/
void set_camera(SDL_Rect camera, Entity * target);

/**
@brief apply the background to follow the camer's position
*/
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif
