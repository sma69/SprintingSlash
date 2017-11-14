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
	Sprite * pauseBG;
	

	
	
	

    
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
	
	//Font and Audio Initialization
	TTF_Init();
	audio_init();

	//Object Manager Initialization
    gf2d_sprite_init(1024);
	entity_manager_init(1024);
	tb_manager_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/

    sprite = gf2d_sprite_load_all("images/backgrounds/bg_flat.png",LEVEL_WIDTH,LEVEL_HEIGHT,1);
	pauseBG = gf2d_sprite_load_all("images/backgrounds/BlackSquare.png", LEVEL_WIDTH, LEVEL_HEIGHT, 1);
	
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

	Textbox * health = guiTextbox_new(vector2d(0,0));
	health->text = "Health";

	//pause menu init
	Textbox* menus[MAX_MENU_ITEMS];
	const char* labels[MAX_MENU_ITEMS] = { "Resume", "Exit" };
	int selected[MAX_MENU_ITEMS] = { 0, 0 };
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	for (int i = 0; i < MAX_MENU_ITEMS; i++) {
		menus[i] = guiTextbox_new(vector2d(0, 0));
		menus[i]->text = labels[i];
		menus[i]->color = color[0];
	}
	//second loop because first element had issues in the first loop
	for (int i = 0; i < MAX_MENU_ITEMS; i++) {
		menus[i]->inuse = 0;
	}
	menus[0]->selected = 1;

	
	menus[0]->box.x = SCREEN_WIDTH / 2 - menus[0]->box.w / 2;
	menus[0]->box.y = SCREEN_HEIGHT / 2 - menus[0]->box.h;
	menus[1]->box.x = SCREEN_WIDTH / 2 - menus[1]->box.w / 2;
	menus[1]->box.y = SCREEN_HEIGHT / 2 - menus[1]->box.h + menus[0]->box.h;

	//Textbox* pause = pauseMenu_init(gf2d_graphics_get_screen_surface(), TTF_OpenFont("fonts/verdana.ttf", 24));

	//music init
	//The music that will be played

	Mix_Music *gMusic = NULL; 
	gMusic= Mix_LoadMUS("music/bridge-zone.wav");
	Mix_PlayMusic(gMusic, 100);

	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	
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
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf += 0.1;
		
		wall->frame += 0.1;
        if (mf >= 16.0)mf = 0;
		
		if (wall->frame >= 1.0)wall->frame = 0;

		if (keys[SDL_SCANCODE_P])
		{
			if (paused == 0) {
				paused = 1;
				//gf2d_sprite_draw_image(pauseBG, vector2d(0, 0));
				for (int i = 0; i < MAX_MENU_ITEMS; i++) {
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
				continue;

			}
			if (paused == 1){
				paused = 0;
				for (int i = 0; i < MAX_MENU_ITEMS; i++) 
				{
					menus[i]->inuse = 0;
				}
				continue;
			}
		}
		
		if (paused == 1)
		{
			if (keys[SDL_SCANCODE_W])
			{
				for (int i = 0; i < MAX_MENU_ITEMS; i++)
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
				for (int i = 0; i < MAX_MENU_ITEMS; i++)
				{
					if (menus[i]->selected == 1)
					{
						menus[i]->selected = 0;
						if (i + 1 == MAX_MENU_ITEMS)
							menus[i]->selected = 1;
						if (i + 1 < MAX_MENU_ITEMS)
							menus[i+1]->selected = 1;

						break;
					}
				}
			}
			//Change color of selected menu item
			for (int i = 0; i < MAX_MENU_ITEMS; i++) {
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
					for (int i = 0; i < MAX_MENU_ITEMS; i++)
					{
						menus[i]->inuse = 0;
					}
				}
				if (menus[1]->selected == 1)
				{
					done = 1;
					for (int i = 0; i < MAX_MENU_ITEMS; i++)
					{
						menus[i]->inuse = 0;
					}
				}
			}
		}
		
		if ( paused != 1)
		{
			entity_think_all();
			entity_touch_all();
			entity_update_all();
			
		}
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
			entity_draw_all(camera);
			textbox_draw_all(camera);

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
	gf2d_sprite_clear_all();
	entity_manager_close();
	textbox_manager_close();
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
