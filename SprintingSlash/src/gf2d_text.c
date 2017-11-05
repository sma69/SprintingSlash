
#include "gf2d_text.h"

typedef struct {
	Uint32 maxEntities;
	Textbox * textboxList;
	Uint64 incr;
}TextboxManager;


static TextboxManager tbManager = { 0 };
/*
void textbox_manager_close()
{
	int i;

	if (tbManager.textboxList != 0)
	{
		for (i = 0; i < tbManager.maxEntities; i++)
		{
			textbox_free(&tbManager.textboxList[i]);
		}
		free(tbManager.textboxList);
	}
	memset(&tbManager, 0, sizeof(TextboxManager));
	slog("Closed Textbox Manager");
}

Textbox * textbox_new()
{
	Textbox* self;
	//font init
	self->text = "empty textbox";
	self->size = 24;
	self->font = TTF_OpenFont("fonts/verdana.ttf", self->size); //this opens a font style and sets a size

	self->color.r = 255;  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	self->color.g = 255;
	self->color.b = 255;

	self->surface = TTF_RenderText_Solid(self->font, self->text, self->color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	self->message = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), self->surface); //now you can convert it into a texture
	
	self->box.x = 0; // controls the rect's x coordinate 
	self->box.y = 0; // controls the rect's y coordinte
	self->box.w =  200; // controls the width of the rect
	self->box.h = 100; // controls the height of the rect

	return self;
}

void textbox_draw(Textbox * self)
{
	SDL_RenderCopy(gf2d_graphics_get_renderer(), self->message, NULL, &self->box);
}
*/