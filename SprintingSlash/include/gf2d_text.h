#ifndef __MGL_TEXT__H__
#define __MGL_TEXT__H__
/**
 * gf2d_text
 * @license The MIT License (MIT)
   @copyright Copyright (c) 2015 EngineerOfLies
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/**
 * @purpose the MGL text library provides common string support for fixed length
 *  strings.  For use with unlimited strings mgl will use glib's GString type
 */
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_types.h"
#include "gf2d_vector.h"
#include "simple_logger.h"

/**
 * constant lenth character buffers.
 * These will be used when the convenience of GString is not needed
 */

/**
 * @brief 16 character buffer used for short tags
 */
typedef char TextWord[16];
#define GF2DWORDLEN   16
#define gf2d_word_cmp(a,b) (strncmp(a,b,GF2DWORDLEN))
#define gf2d_word_cpy(dst,src) (strncpy(dst,src,GF2DWORDLEN))
#define gf2d_word_clear(a)  (memset(a,0,sizeof(char)*GF2DWORDLEN))
/**
 * @brief 128 character buffer used for statements
 */
typedef char TextLine[128];
#define GF2DLINELEN   128
#define gf2d_line_cmp(a,b) (strncmp(a,b,GF2DLINELEN))
#define gf2d_line_cpy(dst,src) (strncpy(dst,src,GF2DLINELEN))
#define gf2d_line_clear(a)  (memset(a,0,sizeof(char)*GF2DLINELEN))
/**
 * @brief 512 character buffer used for text blocks
 */
typedef char TextBlock[512];
#define GF2DTEXTLEN   512
#define gf2d_block_cmp(a,b) (strncmp(a,b,GF2DTEXTLEN))
#define gf2d_block_cpy(dst,src) (strncpy(dst,src,GF2DTEXTLEN))
#define gf2d_block_clear(a)  (memset(a,0,sizeof(char)*GF2DTEXTLEN))


/**
@brief Creates a Textbox for rendering text to the screen
*/

typedef struct Textbox_S{
	
	Uint32 refID;			//this is the Unique ID for each textbox
	TTF_Font* font;			//this opens a font style and sets a size
	SDL_Color color;		//this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surface;	//as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* texture;	//now you can convert it into a texture
	SDL_Rect box;			//create a rect
	char *text;				//the the 
	int size;				//font size
	int inuse;				//check if textbox is enabled or not

}Textbox;


void textbox_manager_close();				/**< Closes the Textbox System>*/

void tb_manager_init(Uint32 maxTextboxes);  /**< Initializes the Textbox System for use inside the game loop>*/

Textbox * textbox_new();	/**< Creates of new instance of a textbox inside the Textbox Manager>*/

void textbox_free(Textbox * self);			/**< Frees the textbox  Memory>*/

void textbox_draw(Textbox * self);			/**< Draws a single textbox with its given Rect Parameters>*/

void textbox_draw_all(SDL_Rect camera);		/**< Draws all textboxes in the Textbox Manager's textbox list>*/






#endif
