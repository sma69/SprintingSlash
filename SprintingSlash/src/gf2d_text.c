#include "gf2d_text.h"

typedef struct {
	Uint32 maxTextboxes;
	Textbox * textboxList;
	Uint64 incr;
}TextboxManager;


static TextboxManager tbManager = { 0 };



void textbox_manager_close()
{
	int i;

	if (tbManager.textboxList != 0)
	{
		for (i = 0; i < tbManager.maxTextboxes; i++)
		{
			textbox_free(&tbManager.textboxList[i]);
		}
		free(tbManager.textboxList);
	}
	memset(&tbManager, 0, sizeof(TextboxManager));
	slog("Closed Textbox Manager");
}

void tb_manager_init(Uint32 maxTextboxes)
{
	if (!maxTextboxes)
	{
		slog("cannot initialize without a max entity cap");
		return;
	}
	memset(&tbManager, 0, sizeof(tbManager));

	tbManager.textboxList = (Textbox*)malloc(sizeof(Textbox)*maxTextboxes);
	if (!tbManager.textboxList)
	{
		slog("failed to allocate entity list");
		textbox_manager_close();
		return;
	
	}
	memset(tbManager.textboxList, 0, sizeof(Textbox)*maxTextboxes);
	tbManager.maxTextboxes = maxTextboxes;
	atexit(textbox_manager_close);
	slog("textbox system initialized");


}

Textbox *textbox_new()
{
	int i;
	for (i = 0; i < tbManager.maxTextboxes; i++)
	{
		if (tbManager.textboxList[i].inuse == 0)
		{
			memset(&tbManager.textboxList[i], 0, sizeof(Textbox));
			tbManager.textboxList[i].refID = tbManager.incr++;
			tbManager.textboxList[i].inuse = 1;

			//itoa(tbManager.entityList[i].refID, snum, 10);
			//printf("%s\n", snum);

			return &tbManager.textboxList[i];

		}
	}
	return NULL;
}



void textbox_free(Textbox * self)
{
	int i;
	if (!self)
		return;
	SDL_DestroyTexture(self->texture);
	memset(self, 0, sizeof(Textbox));
}



void textbox_draw(Textbox * self)
{
	self->surface = TTF_RenderText_Solid(self->font, self->text, self->color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	self->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), self->surface); //now you can convert it into a texture
	SDL_RenderCopy(gf2d_graphics_get_renderer(), self->texture, NULL, &self->box);
}

void textbox_draw_all(SDL_Rect camera)
{
	int i;
	for (int i = 0; i < tbManager.maxTextboxes; i++)
	{
		if (tbManager.textboxList[i].inuse == 0)
			continue;
		else
			textbox_draw(&tbManager.textboxList[i]);
	}
}