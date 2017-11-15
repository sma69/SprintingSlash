#include <SDL.h>

#include <SDL_ttf.h>
#include "gf2d_gui.h"

Textbox * guiTextbox_new(Vector2D position)
{
	
	Textbox* self;
	self = textbox_new();


	//font init
	self->text = "empty textbox";
	self->size = 24;
	self->font = TTF_OpenFont("fonts/verdana.ttf", self->size); //this opens a font style and sets a size

	self->color.r = 255;  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	self->color.g = 255;
	self->color.b = 255;

	self->surface = TTF_RenderText_Solid(self->font, self->text, self->color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	self->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), self->surface); //now you can convert it into a texture

	self->box.x = position.x; // controls the rect's x coordinate 
	self->box.y = position.y; // controls the rect's y coordinte
	self->box.w = 200; // controls the width of the rect
	self->box.h = 100; // controls the height of the rect

	return self;
}

Textbox* mainMenu_init(Textbox* menus[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	const char* labels[MAX_MAIN_MENU_ITEMS] = { "Start Game","Options" ,"Exit" };
	SDL_Color color[2] = { { 255,255,255 },{ 0,255,255 } };
	for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
		menus[i] = guiTextbox_new(vector2d(0, 0));
		menus[i]->text = labels[i];
		menus[i]->color = color[0];
	}
	for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
		menus[i]->inuse = 0;
	}
	menus[0]->selected = 1;

	menus[0]->box.x = SCREEN_WIDTH / 2 - menus[0]->box.w / 2;
	menus[0]->box.y = SCREEN_HEIGHT / 2 - menus[0]->box.h;
	
	for (int i = 1; i < MAX_MAIN_MENU_ITEMS; i++)
	{
		menus[i]->box.x = menus[i - 1]->box.x;
		menus[i]->box.y = menus[i - 1]->box.y + menus[i - 1]->box.h;
	}
	
	menus[1]->box.x = SCREEN_WIDTH / 2 - menus[1]->box.w / 2;
	menus[1]->box.y = SCREEN_HEIGHT / 2 - menus[1]->box.h + menus[0]->box.h;

	return menus;


}

Textbox* pauseMenu_init(Textbox* menus[],const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	//pause menu init
	const char* labels[MAX_PAUSE_MENU_ITEMS] = { "Resume", "Exit" };
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++) {
		menus[i] = guiTextbox_new(vector2d(0, 0));
		menus[i]->text = labels[i];
		menus[i]->color = color[0];
	}
	//second loop because first element had issues in the first loop
	for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++) {
		menus[i]->inuse = 0;
	}
	menus[0]->selected = 1;


	menus[0]->box.x = SCREEN_WIDTH / 2 - menus[0]->box.w / 2;
	menus[0]->box.y = SCREEN_HEIGHT / 2 - menus[0]->box.h;
	menus[1]->box.x = SCREEN_WIDTH / 2 - menus[1]->box.w / 2;
	menus[1]->box.y = SCREEN_HEIGHT / 2 - menus[1]->box.h + menus[0]->box.h;

	return menus;
	
}

int mainMenu_update(Textbox* menus[], int *start, int *done)
{
	keys = SDL_GetKeyboardState(NULL);
	if (start == 0) {

		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
		{
			menus[i]->inuse = 0;
		}
	}
	else if (start == 1) {

		//gf2d_sprite_draw_image(pauseBG, vector2d(0, 0));
		for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
			menus[i]->inuse = 1;
			if (menus[i]->selected == 1)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 0;
				menus[i]->color.b = 100;
			}
			if (menus[i]->selected == 0)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 255;
				menus[i]->color.b = 255;
			}

		}
	}
	//Cycle through Items in the list of options
	if (start == 1)
	{
		if (keys[SDL_SCANCODE_W])
		{
			for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
			{
				if (menus[i]->selected == 1)
				{
					menus[i]->selected = 0;
					if (i - 1 < 0)
						menus[i]->selected = 1;
					if (i - 1 == 0)
						menus[i - 1]->selected = 1;
					break;
				}
			}
		}
		if (keys[SDL_SCANCODE_S])
		{
			for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++)
			{
				if (menus[i]->selected == 1)
				{
					menus[i]->selected = 0;
					if (i + 1 == MAX_MAIN_MENU_ITEMS)
						menus[i]->selected = 1;
					if (i + 1 < MAX_MAIN_MENU_ITEMS)
						menus[i + 1]->selected = 1;

					break;
				}
			}
		}
		//Change color of selected menu item
		for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++) {
			menus[i]->inuse = 1;
			if (menus[i]->selected == 1)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 0;
				menus[i]->color.b = 100;
			}
			if (menus[i]->selected == 0)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 255;
				menus[i]->color.b = 255;
			}

		}
		// Do the action of the selected option in menu
		if (keys[SDL_SCANCODE_RETURN])
		{
			if (menus[0]->selected == 1)
			{
				start = 0;
				for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
				{
					menus[i]->inuse = 0;
				}
				return 1;

			}
			if (menus[1]->selected == 1)
			{
				for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
				{
					menus[i]->inuse = 0;
				}
				return 2;
			}
			if (menus[2]->selected == 1)
			{
				done = 1;
				for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
				{
					menus[i]->inuse = 0;
				}
				return 3;

			}
		}
	}

}

int pauseMenu_update(Textbox* menus[],int *paused,int *done) 
{
	keys = SDL_GetKeyboardState(NULL);
	if (paused == 0) {
		
		for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
		{
			menus[i]->inuse = 0;
		}

	}
	else if (paused == 1) {
	
		//gf2d_sprite_draw_image(pauseBG, vector2d(0, 0));
		for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++) {
			menus[i]->inuse = 1;
			if (menus[i]->selected == 1)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 0;
				menus[i]->color.b = 100;
			}
			if (menus[i]->selected == 0)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 255;
				menus[i]->color.b = 255;
			}

		}


	}

	

	if (paused == 1)
	{
		if (keys[SDL_SCANCODE_W])
		{
			for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
			{
				if (menus[i]->selected == 1)
				{
					menus[i]->selected = 0;
					if (i - 1 < 0)
						menus[i]->selected = 1;
					if (i - 1 == 0)
						menus[i - 1]->selected = 1;
					break;
				}
			}
		}
		if (keys[SDL_SCANCODE_S])
		{
			for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
			{
				if (menus[i]->selected == 1)
				{
					menus[i]->selected = 0;
					if (i + 1 == MAX_PAUSE_MENU_ITEMS)
						menus[i]->selected = 1;
					if (i + 1 < MAX_PAUSE_MENU_ITEMS)
						menus[i + 1]->selected = 1;

					break;
				}
			}
		}
		//Change color of selected menu item
		for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++) {
			menus[i]->inuse = 1;
			if (menus[i]->selected == 1)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 0;
				menus[i]->color.b = 100;
			}
			if (menus[i]->selected == 0)
			{
				menus[i]->color.r = 255;
				menus[i]->color.g = 255;
				menus[i]->color.b = 255;
			}

		}
		// Do the action of the selected option in menu
		if (keys[SDL_SCANCODE_RETURN])
		{
			if (menus[0]->selected == 1)
			{
				paused = 0;
				for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
				{
					menus[i]->inuse = 0;
				}
				return 2;

			}
			if (menus[1]->selected == 1)
			{
				done = 1;
				for (int i = 0; i < MAX_PAUSE_MENU_ITEMS; i++)
				{
					menus[i]->inuse = 0;
				}
				return 3;

			}
		}
	}
}


	
