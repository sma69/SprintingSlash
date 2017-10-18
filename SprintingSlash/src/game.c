#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_entity.h"
#include "gf2d_collision.h"





	





int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
   
	
    Sprite * sprite;
	Sprite * playerSprite;
	Entity * player;
	Entity * wall;
	

	
	
	

    
    int mx,my;
	double playerScale = 0.5;
    float mf = 0, pf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {100, 100,255,200};
	Vector4D playerColor = { 255, 255, 255, 255 };

	//player animation vars
	SDL_Rect playerRect;
	int frameWidth, frameheight;
	int textureWidth, textureHeight;

    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
	entity_manager_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/

    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	//player initialization
	
	Vector2D playerPosition = { 10, 10 };
	player = player_new(playerPosition);

	//wall init
	Vector2D wallPosition = { 600, 600 };
	wall = wall_new(wallPosition);


	
	//playerSprite = gf2d_sprite_load_all("images/players/redSquare.png", 32, 32, 1);
	
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	/*Player Properties*/
	int moveSpeed = 4;
	int jumpSpeed = 20;
	int sprint = 1;
	int gravity = 0;
	int grounded = 0;
	

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf += 0.1;
		player->frame += 0.03;
        if (mf >= 16.0)mf = 0;
		if (player->frame >= 6.0)player->frame = 0;


		entity_think_all();
		entity_update_all();
		checkBoxCollision(player, wall);

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

			//player entity drawn
			//gf2d_sprite_draw(
			//	player->sprite,
			//	player->position,
			//	NULL,
			//	NULL,
			//	NULL,
			//	NULL,
			//	&player->color,
			//	(int)player->frame);
				
			entity_draw_all();
			//Show the wall
			//SDL_FillRect(gf2d_graphics_get_screen_surface(), &wall->body, SDL_MapRGB(gf2d_graphics_get_screen_surface(), 0x77, 0x77, 0x77));

            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);

		


        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
	slog("---Deinitializing entities");

    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
