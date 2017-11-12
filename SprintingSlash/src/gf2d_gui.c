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

int showMenu(SDL_Surface* screen, TTF_Font* font)
{
/*
	Uint32 time;
	int x, y;
	const char* labels[MAX_MENU_ITEMS] = { "Resume", "Exit" };
	SDL_Surface* menus[MAX_MENU_ITEMS];
	int selected[MAX_MENU_ITEMS] = { 0, 0 };
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };

	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menus[0] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[MAX_MENU_ITEMS];
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].x = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[1].x = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;
	while (1)
	{
		time - SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < MAX_MENU_ITEMS; i++)
					SDL_FreeSurface(menus[i]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < MAX_MENU_ITEMS; i++)
				{
					if (x >= pos[i].x && x <= pos[i].w && y >= pos[i].y && y <= pos[i].y &&
						y <= pos[i].y + pos[i].h) {

						//if menu item is not selected
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
						else {
							//if menu item is selected
							if (selected[i])
							{
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							}
						}
				}
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < MAX_MENU_ITEMS; i++)
					if (x >= pos[i].x && x <= pos[i].w && y >= pos[i].y && y <= pos[i].y &&
						y <= pos[i].y + pos[i].h)
					{
						for (int i = 0; i < MAX_MENU_ITEMS; i++)
							SDL_FreeSurface(menus[i]);
						return 1;
					}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) 
				{
					for (int i = 0; i < MAX_MENU_ITEMS; i++)
						SDL_FreeSurface(menus[i]);
					return 0;
				}
			}
		}
		
		for (int i = 0; i < MAX_MENU_ITEMS; i++)
		{
			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
		}
		SDL_Flip(screen);
		
		if (1000 / 30 > (SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}
	*/
}


	
