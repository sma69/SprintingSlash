#include <SDL.h>
#include <SDL_ttf.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_entity.h"
#include "gf2d_collision.h"
#include "gf2d_camera.h"
#include "gf2d_audio.h"
#include "gf2d_gui.h"



//Screen attributes
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//The frame rate
const int FRAMES_PER_SECOND = 60;

SDL_Rect camera = { 0, 0, &SCREEN_WIDTH, &SCREEN_HEIGHT };

void set_camera(SDL_Rect camera, Entity * self)
{

	//Center the camera over the dot
	camera.x = (self->position.x + self->width / 2) - SCREEN_WIDTH / 2;
	camera.y = (self->position.y + self->height / 2) - SCREEN_HEIGHT / 2;
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

void camera_show(SDL_Rect self)
{
	//show the entity relative to the camera
	SDL_RenderSetViewport(gf2d_graphics_get_renderer(), &camera);

}

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
   
	
    Sprite * sprite;
	Sprite * playerSprite;
	Entity * player;
	Entity * wall;
	Entity * wall2;
	Entity * wall3;
	Entity * enemy1;
	Entity * enemy2;
	

	
	
	

    
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
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
	TTF_Init();
	audio_init();

    gf2d_sprite_init(1024);
	entity_manager_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/

    sprite = gf2d_sprite_load_all("images/backgrounds/bg_flat.png",LEVEL_WIDTH,LEVEL_HEIGHT,1);
	
	//player initialization	
	Vector2D playerPosition = { 10, 10 };
	player = player_new(playerPosition);

	//wall init
	Vector2D wallPosition = { 600, 300 };
	wall = wall_new(wallPosition);

	Vector2D wall2Position = { 300, 300 };
	wall2 = wall_new(wall2Position);
	//enemy init
	Vector2D enemy1Position = { 200,300 };
	enemy1 = enemy_new(enemy1Position);

	Vector2D wall3Position = { 50, 600 };
	wall3 = wall_new(wall3Position);

	//font init

	//Textbox * health = textbox_new();

	//music init
	//The music that will be played

	Mix_Music *gMusic = NULL; 
	gMusic= Mix_LoadMUS("music/bridge-zone.wav");
	Mix_PlayMusic(gMusic, 100);

	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	
	
	TTF_Font* Verdana = TTF_OpenFont("fonts/verdana.ttf", 24); //this opens a font style and sets a size

	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Verdana, "Slash!", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	
	//playerSprite = gf2d_sprite_load_all("images/players/redSquare.png", 32, 32, 1);
	
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	/*Player Properties*/
	int moveSpeed = 4;
	int jumpSpeed = 20;
	int sprint = 1;
	int gravity = 0;
	int grounded = 0;

	//Pause Menu
	
	int paused = 0;
	int pauseMenu = showMenu(gf2d_graphics_get_screen_surface(), Verdana);
	
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf += 0.1;
		//player->frame += 0.03;
		wall->frame += 0.1;
        if (mf >= 16.0)mf = 0;
		//if (player->frame >= 6.0)player->frame = 0;
		if (wall->frame >= 1.0)wall->frame = 0;

		if (keys[SDL_SCANCODE_P])
		{
		
			if (pauseMenu == 1)
				paused = 1;
			break;

		}

		entity_touch_all();
		entity_update_all();
		entity_think_all();
		set_camera(camera, player);
		//camera_show(camera);
		//if(checkBoxCollision(player, wall))
			//player->isGrounded = 1;
		//if (checkBoxCollision(player, enemy1))
			
		//checkHitboxCollision(player, wall);

        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
			//apply_surface(0, 0,  ,gf2d_graphics_get_screen_surface, &camera);

			//set cam
			

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

			SDL_RenderCopy(gf2d_graphics_get_renderer(), Message, NULL, &Message_rect);
			entity_draw_all();

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
       // slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
	slog("---Deinitializing entities");

    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
