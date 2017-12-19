#include "gf2d_camera.h"




void camera_init()
{

}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void set_camera(SDL_Rect camera, Entity * target)
{

	//Center the camera over the dot
	camera.x = (target->position.x + target->width / 2) - SCREEN_WIDTH / 2;
	camera.y = (target->position.y + target->height / 2) - SCREEN_HEIGHT / 2;
	camera.w = &SCREEN_WIDTH;
	camera.h = &SCREEN_HEIGHT;
	//Keep the camera in bounds.
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}

	return camera;
}






