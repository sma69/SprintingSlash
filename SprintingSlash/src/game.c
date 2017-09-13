#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Sprite *player;
    
    int mx,my;
	double playerScale = 0.5;
    float mf = 0, pf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {100, 100,255,200};
	Vector4D playerColor = { 255, 255, 255, 255 };
    
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
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	player = gf2d_sprite_load_all("images/players/redSquare.png",32, 32,1);
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	/*Player Properties*/
	Vector2D playerPosition = { 0, 0 };
	int moveSpeed = 4;
	int jumpSpeed = 20;
	int sprint = 1;
	int gravity = 5;
	int grounded = 0;
	

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf += 0.1;
		pf += 0.1;
        if (mf >= 16.0)mf = 0;
		if (pf >= 1.0)pf = 0;

		if(keys[SDL_SCANCODE_LSHIFT])
			sprint = 2;
		else 
			sprint = 1;
		
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

			//player entity drawn
			gf2d_sprite_draw(
				player,
				playerPosition,
				NULL,
				NULL,
				NULL,
				NULL,
				&playerColor,
				(int)pf);
            
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

			//Player movement
			
			//gravity
			playerPosition.y += gravity;
			
			if (keys[SDL_SCANCODE_A]) {
				playerPosition.x -= (moveSpeed * sprint);
			}
			if (keys[SDL_SCANCODE_D]) {
				playerPosition.x += (moveSpeed * sprint);
			}
			if (keys[SDL_SCANCODE_W]) {
				if (grounded == 1) {
					playerPosition.y -= (jumpSpeed * sprint);
				}
			}
			if (keys[SDL_SCANCODE_S]) {
				playerPosition.y += (moveSpeed * sprint);
			}
			/* collide with edges of screen */
			if (playerPosition.x < 0) {
				playerPosition.x = 0;
			}
			else if (playerPosition.x > 1200 - 32) {
				playerPosition.x = 1200 - 32;
			}
			if (playerPosition.y < 0) {
				playerPosition.y = 0;
			}
			else if (playerPosition.y > 720 - 32) {
				playerPosition.y = 720 - 32;
				grounded = 1;
			}
			else {
				grounded = 0;
			}

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
