#pragma once
#ifndef __GF2D_CAMERA_H__
#define __GF2D_CAMERA_H__

#include <SDL.h>
#include "gf2d_entity.h"


void camera_show(Entity * self);



/**
@brief set the camera and set it on an entity
@param The entity target to keep the camera looking at
*/
void set_camera(Entity * self);

/**
*/
#endif
