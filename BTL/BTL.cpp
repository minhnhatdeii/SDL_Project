/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>
#include <SDL_mixer.h>
#include <cmath>
//Screen dimension constants
bool quit = false;
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int MAX_NUM_ENEMY_1=6;
const int MAX_NUM_ENEMY_2=6;
const int MAX_NUM_ENEMY_3=6;
int NUM_ENEMY3 =1;
int NUM_ENEMY1 = 3;
int NUM_ENEMY2 = 3;
const int ENEMY1_HEART = 3;
int ENEMY1_VELY = 2;
double ENEMY2_VELY = 1;
const int ENEMY2_HEART = 2;
const double ENEMY3_VELX = 1;
const int ENEMY3_HEART = 30;

const int SPEED_BACKGROUND = 1;

const int NUM_IMG_EXPLOSION = 9;
const int NUM_IMG_DOT_MOVE=9;
const int NUM_IMG_DOT_STAND=6;
const int NUM_IMG_ENEMY1=6;
const int NUM_IMG_ENEMY2=7;
const int NUM_IMG_ENEMY3=7;
const int NUM_IMG_AMO_DOT = 9;
const int NUM_IMG_SPECIAL_AMO = 8;
const int NUM_IMG_AMO_ENEMY2 = 7;
const int NUM_IMG_FOOD_HEART=8;
const int NUM_IMG_FOOD_RED=5;
const int NUM_IMG_FOOD_YELLOW=9;
const int NUM_IMG_FOOD_PURPLE=9;
const int NUM_IMG_LEVEL = 9;
//MENU
const int NUM_ITEM_MENU = 3;
const int NUM_ITEM_PAUSE = 3;
const int NUM_ITEM_GAMEOVER = 3;

bool bool_pause=false;
bool bool_game_over = false;
bool fight=true;
std::string char_tmp;
int type_amo = 0;
int time_special_amo = SCREEN_FPS*7;
int count_remain_special_amo = 0;
int DOT_HEART = 3;
int COMMON_DOT_AMO_VEL = 7;//dot_amo_vel
int MAX_DOT_AMO_VEL = 20;//dot_amo_vel
const int MAX_DOT_HEART = 3;
int SCORE =0;
int HIGH_SCORE=0;
int time;
int point=0;
double goc=0.466;
const int MAX_DAMAGE_AMO = 3;
const int COMMON_DAMAGE_AMO = 1;
int DAMAGE_AMO = COMMON_DAMAGE_AMO;

const int SPEED_ANIMATION = 5;

int count_appear_food1=0;
int SPEED_APPEAR_FOOD1 =SCREEN_FPS*10;// thoi gian xuat hien trai tim

int count_appear_special_food=0;
int SPEED_APPEAR_SPECIAL_FOOD =SCREEN_FPS*15;//thoi gian xuaat dan ddac biet

const int reload_enemy_amo =120;//reload dan enemy
int dot_amo_rate = 0;
const int common_reload_dot_amo = 15;
const int max_reload_dot_amo = 0;
int reload_dot_amo = common_reload_dot_amo;
const int time_limit_render_level = SCREEN_FPS*3;
int count_time_render_level=0;
bool level_render_success = false;
int level = 1;


std::string path_img_dot_stand="";
std::string path_img_dot_move="";
std::string path_img_enemy1="";
std::string path_img_enemy3="";
std::string path_img_enemy2="";
std::string path_img_amo_enemy2="";
std::string path_img_amo_dot="";
std::string path_img_food_heart="";
std::string path_img_food_red="";
std::string path_img_food_yellow="";
std::string path_img_food_purple="";
std::string path_img_special_amo="";
std::string path_img_explosion="";
std::string path_img_level="";


int moveY_BG=0;

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
std::string int_to_str(int a)
{
    std::string res;
    while (a>0)
    {
        res = char (a%10 + '0') + res;
        a/=10;
    }
    return res;
}
//Texture wrapper class

//The dot that will move around on the screen
//LTexture
//Food class
//Shuriken class
//LTimer class
// enemy class



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

TTF_Font* gFont = NULL;
/*TTF_Font* gFont2 = NULL;
TTF_Font* gFont3 = NULL;
TTF_Font* gMenu_Font = NULL;
*/
//The window renderer
SDL_Renderer* gRenderer = NULL;

#include "LTexture.h"

LTexture gBackground;
LTexture gMenu_IMG;
LTexture Map_IMG;
LTexture gTutorial_IMG;
LTexture gPause_IMG;
LTexture gGameOver_IMG;
LTexture gHeart_Data;
LTexture Score_Data;
//Scene textures
LTexture gDotTexture_Stand[NUM_IMG_DOT_STAND];//ban than
LTexture gDotTexture_Move[NUM_IMG_DOT_MOVE];

LTexture gFoodTexture1[NUM_IMG_FOOD_HEART];//ITEM_HEART
LTexture gFoodTexture_Red[NUM_IMG_FOOD_RED];//ITEM_RED
LTexture gFoodTexture_Yellow[NUM_IMG_FOOD_YELLOW];//ITEM_YELLOW
LTexture gFoodTexture_Purple[NUM_IMG_FOOD_PURPLE];//ITEM_PURPLE

LTexture gShurikenTexture[NUM_IMG_AMO_DOT];//dan minh
LTexture gShurikenTexture_SPECIAL[NUM_IMG_SPECIAL_AMO];

LTexture gShuriken2Texture[NUM_IMG_AMO_ENEMY2];//dan dich

LTexture gEnemy1Texture[NUM_IMG_ENEMY1];//dich
LTexture gEnemy2Texture[NUM_IMG_ENEMY2];//dich2
LTexture gEnemy3Texture[NUM_IMG_ENEMY3];//dich2
LTexture gExplosion[NUM_IMG_EXPLOSION];

LTexture gTextTexture;//heart
LTexture gTextTexture2;//score
LTexture gTextTexture3;//time
LTexture gTextHighScore;//highscore
LTexture gTextMenu[NUM_ITEM_MENU];//menu
LTexture gTextPause[NUM_ITEM_PAUSE];//pause
LTexture gTextGameOver[NUM_ITEM_GAMEOVER];//gameover
LTexture gTutorial_Text;

LTexture pause_on_play;
LTexture button_img;
LTexture button_pause_img[NUM_ITEM_PAUSE];
LTexture button_gameover_img[NUM_ITEM_GAMEOVER];
LTexture LevelTexture[NUM_IMG_LEVEL];

Mix_Chunk *gKunai = NULL;

Mix_Chunk *gEnemyHurt = NULL;

Mix_Chunk* gPickItem = NULL;

Mix_Chunk* gMenuClick = NULL;
Mix_Chunk* gMenuMotion = NULL;

//food
#include "Food.h"
//shuriken
#include "Shuriken.h"
//LTimer
#include "LTimer.h"
//enemy
#include "Enemy.h"
//Dot
#include "Dot.h"



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "DinoRun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	if (success)
    {
        SDL_Surface* icon = IMG_Load("logo.png");
        SDL_SetWindowIcon(gWindow,icon);
    }
    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	if( !Map_IMG.loadFromFile( "menu_map.png" ) )
	{
		printf( "Failed to load map texture!\n" );
		success = false;
	}
    if( !button_img.loadFromFile( "button.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !gHeart_Data.loadFromFile( "data_tmp.png" ) )
	{
		printf( "Failed to load heartdata texture!\n" );
		success = false;
	}
	if( !Score_Data.loadFromFile( "data_tmp.png" ) )
	{
		printf( "Failed to load score data texture!\n" );
		success = false;
	}
	for(int i=0;i<NUM_ITEM_PAUSE;i++)
    {
         if( !button_pause_img[i].loadFromFile( "motion_button.png" ) )
        {
            printf( "Failed to load button texture!\n" );
            success = false;
        }
    }
    for(int i=0;i<NUM_ITEM_GAMEOVER;i++)
    {
         if( !button_gameover_img[i].loadFromFile( "motion_button.png" ) )
        {
            printf( "Failed to load button texture!\n" );
            success = false;
        }
    }
    if( !gGameOver_IMG.loadFromFile( "gameover.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !gPause_IMG.loadFromFile( "pause_img.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !pause_on_play.loadFromFile( "motion_button.png" ) )
	{
		printf( "Failed to load mottion button texture!\n" );
		success = false;
	}
    if( !gMenu_IMG.loadFromFile( "menu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gTutorial_IMG.loadFromFile( "tutorial.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBackground.loadFromFile( "theway.jpg" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}


	//Load press texture
    gFont = TTF_OpenFont( "font.ttf", 42 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );

    }

    //end font
    //sound
	gKunai = Mix_LoadWAV( "kunaieffect.wav" );
	if( gKunai == NULL )
	{
		printf( "Failed to load kunai sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gEnemyHurt = Mix_LoadWAV( "enemy_hurt.mp3" );
	if( gEnemyHurt == NULL )
	{
		printf( "Failed to load enemy sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gPickItem = Mix_LoadWAV( "pickitem.wav" );
	if( gPickItem == NULL )
	{
		printf( "Failed to load kunai sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMenuClick = Mix_LoadWAV( "menu_click.mp3" );
	if( gMenuClick == NULL )
	{
		printf( "Failed to load menuclick sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMenuMotion = Mix_LoadWAV( "menu_motion.wav" );
	if( gMenuMotion == NULL )
	{
		printf( "Failed to load menumotion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//end sound

	//FOOD
	for (int i=0;i<NUM_IMG_FOOD_HEART;i++)
    {
        path_img_food_heart = path_img_food_heart + "heart_removebg/heart (" + char(i+1+'0') + ").png";
        if( !gFoodTexture1[i].loadFromFile(path_img_food_heart ) )
        {
            printf( "Failed to load food texture!\n" );

        }
        path_img_food_heart="";
    }
    for (int i=0;i<NUM_IMG_FOOD_RED;i++)
    {
        path_img_food_red = path_img_food_red + "redorb_removebg/redorb (" + char(i+1+'0') + ").png";
        if( !gFoodTexture_Red[i].loadFromFile(path_img_food_red ) )
        {
            printf( "Failed to load food texture!\n" );

        }
        path_img_food_red="";
    }
    for (int i=0;i<NUM_IMG_FOOD_YELLOW;i++)
    {
        path_img_food_yellow = path_img_food_yellow + "yelloworb_removebg/yelloworb (" + char(i+1+'0') + ").png";
        if( !gFoodTexture_Yellow[i].loadFromFile(path_img_food_yellow ) )
        {
            printf( "Failed to load food texture!\n" );

        }
        path_img_food_yellow="";
    }
    for (int i=0;i<NUM_IMG_FOOD_PURPLE;i++)
    {
        path_img_food_purple = path_img_food_purple + "purpleorb_removebg/purpleorb (" + char(i+1+'0') + ").png";
        if( !gFoodTexture_Purple[i].loadFromFile(path_img_food_purple ) )
        {
            printf( "Failed to load food texture!\n" );

        }
        path_img_food_purple="";
    }
    //END FOOD
    //DOT
	for (int i=0;i<NUM_IMG_DOT_STAND;i++)
    {
        path_img_dot_stand = path_img_dot_stand + "dino1_removebg/stand/dino_stand (" + char(i+1+'0') + ").png";
        if( !gDotTexture_Stand[i].loadFromFile(path_img_dot_stand ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_dot_stand="";
    }
    for (int i=0;i<NUM_IMG_DOT_MOVE;i++)
    {
        path_img_dot_move = path_img_dot_move + "dino1_removebg/move/dino_move (" + char(i+1+'0') + ").png";
        if( !gDotTexture_Move[i].loadFromFile(path_img_dot_move ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
         path_img_dot_move="";
    }

    //END DOT
    //enemy1
    for (int i=0;i<NUM_IMG_ENEMY1;i++)
    {
        path_img_enemy1 = path_img_enemy1 + "zom_removebg/zom (" + char(i+1+'0') + ").png";
        if( !gEnemy1Texture[i].loadFromFile(path_img_enemy1 ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_enemy1="";
    }
    for (int i=0;i<NUM_IMG_EXPLOSION;i++)
    {
        path_img_explosion = path_img_explosion + "explosion_removebg/explosion (" + char(i+1+'0') + ").png";
        if( !gExplosion[i].loadFromFile(path_img_explosion ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_explosion="";
    }
    //enemy2
    for (int i=0;i<NUM_IMG_ENEMY2;i++)
    {
        path_img_enemy2 = path_img_enemy2 + "monster_removebg/monster (" + char(i+1+'0') + ").png";
        if( !gEnemy2Texture[i].loadFromFile(path_img_enemy2 ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_enemy2="";
    }
    //enemy3
    for (int i=0;i<NUM_IMG_ENEMY3;i++)
    {
        path_img_enemy3 = path_img_enemy3 + "monster_removebg/monster (" + char(i+1+'0') + ").png";
        if( !gEnemy3Texture[i].loadFromFile(path_img_enemy3 ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_enemy3="";
    }
    //amo_dot
    for (int i=0;i<NUM_IMG_AMO_DOT;i++)
    {
        path_img_amo_dot = path_img_amo_dot + "fireball1_removebg/fireball1 (" + char(i+1+'0') + ").png";
        if( !gShurikenTexture[i].loadFromFile(path_img_amo_dot ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_amo_dot="";
    }
     for (int i=0;i<NUM_IMG_SPECIAL_AMO;i++)
    {
        path_img_special_amo = path_img_special_amo + "fireball2_removebg/fireball2 (" + char(i+1+'0') + ").png";
        if( !gShurikenTexture_SPECIAL[i].loadFromFile(path_img_special_amo ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_special_amo="";
    }

    //amo_enemy2
    for (int i=0;i<NUM_IMG_AMO_ENEMY2;i++)
    {
        path_img_amo_enemy2 = path_img_amo_enemy2 + "enemyamo_removebg/enemyamo (" + char(i+1+'0') + ").png";
        if( !gShuriken2Texture[i].loadFromFile(path_img_amo_enemy2 ) )
        {
            printf( "Failed to load dot texture!\n" );

        }
        path_img_amo_enemy2="";
    }
    //level
    for (int i=0;i<NUM_IMG_LEVEL;i++)
    {
        path_img_level = path_img_level + "level_removebg/level (" + char(i+1+'0') + ").png";
        if( !LevelTexture[i].loadFromFile(path_img_level ) )
        {
            printf( "Failed to load level texture!\n" );

        }
        path_img_level="";
    }

	return success;
}

void close()
{
    gPause_IMG.free();
    gGameOver_IMG.free();
    pause_on_play.free();
    button_img.free();
    Map_IMG.free();

	for (int i=0;i<NUM_IMG_DOT_STAND;i++)
	gDotTexture_Stand[i].free();
	for (int i=0;i<NUM_IMG_LEVEL;i++)
	LevelTexture[i].free();

	for (int i=0;i<NUM_IMG_DOT_MOVE;i++)
	gDotTexture_Move[i].free();

    for (int i=0;i<NUM_ITEM_PAUSE;i++)
	button_pause_img[i].free();

    for (int i=0;i<NUM_ITEM_PAUSE;i++)
	gTextPause[i].free();

	for (int i=0;i<NUM_ITEM_GAMEOVER;i++)
	button_gameover_img[i].free();

    for (int i=0;i<NUM_ITEM_GAMEOVER;i++)
	gTextGameOver[i].free();

    gMenu_IMG.free();
    gTutorial_IMG.free();
	for (int i=0;i<NUM_IMG_FOOD_HEART;i++)
    gFoodTexture1[i].free();
    for (int i=0;i<NUM_IMG_FOOD_RED;i++)
    gFoodTexture_Red[i].free();
    for (int i=0;i<NUM_IMG_FOOD_YELLOW;i++)
    gFoodTexture_Yellow[i].free();
    for (int i=0;i<NUM_IMG_FOOD_PURPLE;i++)
    gFoodTexture_Purple[i].free();

    for (int i=0;i<NUM_IMG_AMO_DOT;i++)
    gShurikenTexture[i].free();
    for (int i=0;i<NUM_IMG_SPECIAL_AMO;i++)
    gShurikenTexture_SPECIAL[i].free();

    for (int i=0;i<NUM_IMG_AMO_ENEMY2;i++)
    gShuriken2Texture[i].free();

    gBackground.free();
    for (int i=0;i<NUM_IMG_ENEMY1;i++)
    gEnemy1Texture[i].free();
    for (int i=0;i<NUM_IMG_ENEMY2;i++)
    gEnemy2Texture[i].free();
    for (int i=0;i<NUM_IMG_ENEMY3;i++)
    gEnemy3Texture[i].free();
    for (int i=0;i<NUM_IMG_EXPLOSION;i++)
    gExplosion[i].free();
    gHeart_Data.free();
    Score_Data.free();
    TTF_CloseFont( gFont );
	gFont = NULL;

    gTextTexture.free();
    gTextTexture2.free();
    gTextTexture3.free();
    for (int i =0 ;i<NUM_ITEM_MENU;i++)
    gTextMenu[i].free();
    gTutorial_Text.free();
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	Mix_FreeChunk(gKunai);
    gKunai = NULL;
    Mix_FreeChunk(gEnemyHurt);
    gEnemyHurt = NULL;
    Mix_FreeChunk(gPickItem);
    gPickItem = NULL;
    Mix_FreeChunk(gMenuClick);
    gMenuClick = NULL;
    Mix_FreeChunk(gMenuMotion);
    gMenuMotion = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

int set_map ()
{
    Map_IMG.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        SDL_Rect button[3];
        button[0] = {45,277,108,188};
        button[1] = {190,278,110,191};
        button[2] = {346,273,110,188};
    SDL_Event setmap_event;
    int x_mouse=0,y_mouse=0;
    bool click = false;
    while (true)
    {
        while (SDL_PollEvent(&setmap_event))
        {
            switch (setmap_event.type)
            {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    {

                    }
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                         x_mouse = setmap_event.motion.x;
                         y_mouse = setmap_event.motion.y;
                         for (int i=0;i<3;i++)
                         {
                             if (x_mouse >=button[i].x && x_mouse <= button[i].x+button[i].w && y_mouse >= button[i].y && y_mouse <=button[i].y+button[i].h)
                             {

                                Mix_PlayChannel( -1, gMenuClick, 0 );
                                if (i==0)
                                {
                                    gBackground.loadFromFile( "theway3.png" );
                                }
                                else if (i==1)
                                {
                                    gBackground.loadFromFile("theway.jpg");
                                }
                                else if (i==2)
                                {
                                    gBackground.loadFromFile("theway2.png");
                                }
                                return 0;
                             }
                         }
                    break;
                    }
                    default:
                    break;
                    }
                }
            SDL_RenderPresent( gRenderer );
        }

    return 1;//quit
}

int tutorial()
{
    gTutorial_IMG.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_Color white = { 255,255,255};
    if( !gTutorial_Text.loadFromRenderedText("PLAY GAME" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
        SDL_Rect button;
        button = {77,592,354,92};
    SDL_Event tutorial_event;
    int x_mouse=0,y_mouse=0;
    bool click = false;
    while (true)
    {
        gTutorial_Text.render(122,608,252,58);

        while (SDL_PollEvent(&tutorial_event))
        {
            switch (tutorial_event.type)
            {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    {
                     x_mouse = tutorial_event.motion.x;
                     y_mouse = tutorial_event.motion.y;
                         if (x_mouse >=button.x && x_mouse <= button.x+button.w && y_mouse >= button.y && y_mouse <=button.y+button.h)
                         {
                             gTutorial_Text.setColor(255,0,127);
                         }
                         else
                         {
                             gTutorial_Text.setColor(138,43,226);
                         }
                     }
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                         x_mouse = tutorial_event.motion.x;
                         y_mouse = tutorial_event.motion.y;
                             if (x_mouse >=button.x && x_mouse <= button.x+button.w && y_mouse >= button.y && y_mouse <=button.y+button.h)
                             {
                                 click = true;
                                 if (click == true) {Mix_PlayChannel( -1, gMenuClick, 0 );click=false;}
                                 return 0;
                             }
                   // break;
                    }
                    default:
                    break;
                    }
                }
            SDL_RenderPresent( gRenderer );
        }

    return 1;
}
int menu()
{
   // std::cout<<tan((25*3.1415)/180);
    //std::cout<<"menu";
    gMenu_IMG.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_Color purple = { 138,43,226};


    if( !gTextMenu[0].loadFromRenderedText("PLAY GAME" ,purple ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    if( !gTextMenu[1].loadFromRenderedText("EXIT" ,purple ) )
        {
            printf( "Failed to render text texture!\n" );
        }
     if( !gTextMenu[2].loadFromRenderedText("HOW TO PLAY" ,purple ) )
        {
            printf( "Failed to render text texture!\n" );
        }
        SDL_Rect button[NUM_ITEM_MENU];
        button[0] = {120,380,260,60};
        button[1] = {120,480,260,60};
        button[2] = {120,580,260,60};
    SDL_Event menu_event;
    int check_tutorial;
    int check_setmap;
    int x_mouse=0,y_mouse=0;
    while (true)
    {
        gTextMenu[0].render(140,390,215,45);
        gTextMenu[1].render(190,485,112,45);
        gTextMenu[2].render(140,580,215,45);
        while (SDL_PollEvent(&menu_event))
        {
            switch (menu_event.type)
            {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    {
                     x_mouse = menu_event.motion.x;
                     y_mouse = menu_event.motion.y;
                     for (int i=0;i<NUM_ITEM_MENU;i++)
                     {
                         if (x_mouse >=button[i].x && x_mouse <= button[i].x+button[i].w && y_mouse >= button[i].y && y_mouse <=button[i].y+button[i].h)
                         {
                             gTextMenu[i].setColor(255,0,127);
                         }
                         else
                         {
                             gTextMenu[i].setColor(138,43,226);
                         }
                     }
                    }
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                         x_mouse = menu_event.motion.x;
                         y_mouse = menu_event.motion.y;
                         for (int i=0;i<NUM_ITEM_MENU;i++)
                         {
                             if (x_mouse >=button[i].x && x_mouse <= button[i].x+button[i].w && y_mouse >= button[i].y && y_mouse <=button[i].y+button[i].h)
                             {

                                 Mix_PlayChannel( -1, gMenuClick, 0 );
                                 if (i == 0)
                                 {
                                     check_setmap = set_map();
                                     if (check_setmap == 1) return 1;
                                     else return 0;
                                 }
                                 else if (i == 2)
                                 {
                                     check_tutorial = tutorial();
                                     if (check_tutorial == 1) return 1;
                                     else if (check_tutorial == 0)
                                     {
                                         check_setmap = set_map();
                                         if (check_setmap == 1) return 1;
                                         else return 0;
                                    }

                                 }
                                 else   return i;
                             }
                        }

                   // break;
                    }
                    default:
                    break;
                    }
                }
                if (HIGH_SCORE>0)
                        {
                            //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + int_to_str(HIGH_SCORE*100);
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }
                        else
                        {
                        //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + "000";
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                             gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }
            SDL_RenderPresent( gRenderer );
        }

    return 1;
}

int pause()
{
    if (SCORE >= HIGH_SCORE) HIGH_SCORE = SCORE;
    //std::cout<<"pause";
    gPause_IMG.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_Rect pause_button_rect[NUM_ITEM_PAUSE];
    pause_button_rect[0] = {50,315,100,100};//HOME
    pause_button_rect[1] = {200,315,100,100};//RESUME
    pause_button_rect[2] = {350,315,100,100};//EXIT
    int x_mouse=0,y_mouse=0;
    SDL_Color white = { 255,255,255};
    if( !gTextPause[0].loadFromRenderedText("Home" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    if( !gTextPause[1].loadFromRenderedText("Resume" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    if( !gTextPause[2].loadFromRenderedText("Exit" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
        SDL_Rect pause_button_img_rect[NUM_ITEM_PAUSE];
        pause_button_img_rect[0] = {366,25,105,105};//home
        pause_button_img_rect[1] = {252,22,109,109};//resume
        pause_button_img_rect[2] = {29,23,102,107};//exit

        SDL_Event pause_event;
    while (true)
    {
       // gTextPause[0].render(50,450,100,100);
       // gTextPause[1].render(200,450,100,100);
       // gTextPause[2].render(350,450,100,100);

        button_pause_img[0].render(50,315,100,100,&pause_button_img_rect[0]);
        button_pause_img[1].render(200,315,100,100,&pause_button_img_rect[1]);
        button_pause_img[2].render(350,315,100,100,&pause_button_img_rect[2]);

        while (SDL_PollEvent(&pause_event))
        {
            switch (pause_event.type)
            {
                case SDL_QUIT:
                    return 2;
                case SDL_MOUSEMOTION:
                    {
                     x_mouse = pause_event.motion.x;
                     y_mouse = pause_event.motion.y;
                     for (int i=0;i<NUM_ITEM_PAUSE;i++)
                     {
                         if (x_mouse >=pause_button_rect[i].x && x_mouse <= pause_button_rect[i].x+pause_button_rect[i].w && y_mouse >=pause_button_rect[i].y && y_mouse <=pause_button_rect[i].y+pause_button_rect[i].h)
                         {
                             //gTextPause[i].setColor(255,255,0);
                             button_pause_img[i].setColor(0,0,255);
                         }
                         else
                         {
                            //gTextPause[i].setColor(255,255,255);
                            button_pause_img[i].setColor(255,255,255);
                         }
                     }
                    }
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                         x_mouse = pause_event.motion.x;
                         y_mouse = pause_event.motion.y;
                         for (int i=0;i<NUM_ITEM_PAUSE;i++)
                         {
                         if (x_mouse >=pause_button_rect[i].x && x_mouse <= pause_button_rect[i].x+pause_button_rect[i].w &&
                             y_mouse >=pause_button_rect[i].y && y_mouse <=pause_button_rect[i].y+pause_button_rect[i].h)
                             {

                                Mix_PlayChannel( -1, gMenuClick, 0 );
                                 return i;
                             }
                        }

                   // break;
                    }
                    default:
                    break;
                    }
                }
                if (HIGH_SCORE>0)
                        {
                            //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + int_to_str(HIGH_SCORE*100);
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }
                        else
                        {
                        //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + "000";
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                             gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }
            SDL_RenderPresent( gRenderer );
        }
    return 2;
}
int game_over()
{

    gGameOver_IMG.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    if (SCORE >= HIGH_SCORE) HIGH_SCORE = SCORE;
    //std::cout<<HIGH_SCORE;
    //freopen("highscore.txt","r",stdout);
   // std::cout<<HIGH_SCORE;

    SDL_Rect gameover_button_rect[NUM_ITEM_PAUSE];
    gameover_button_rect[0] = {50,315,100,100};//HOME
    gameover_button_rect[1] = {200,315,100,100};//PLAYAGAIN
    gameover_button_rect[2] = {350,315,100,100};//EXIT
    int x_mouse=0,y_mouse=0;
    SDL_Color white = { 255,255,255};
    if( !gTextGameOver[0].loadFromRenderedText("Home" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    if( !gTextGameOver[1].loadFromRenderedText("PLAY AGAIN" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
    if( !gTextGameOver[2].loadFromRenderedText("Exit" ,white ) )
        {
            printf( "Failed to render text texture!\n" );
        }
        SDL_Rect gameover_button_img_rect[NUM_ITEM_GAMEOVER];
        gameover_button_img_rect[0] = {366,25,105,105};//home
        gameover_button_img_rect[1] = {23,369,110,104};//play again
        gameover_button_img_rect[2] = {29,23,102,107};//exit

        SDL_Event gameover_event;
    while (true)
    {
        //gTextGameOver[0].render(50,450,100,100);
        //gTextGameOver[1].render(200,450,100,100);
        //gTextGameOver[2].render(350,450,100,100);

        button_gameover_img[0].render(50,315,100,100,&gameover_button_img_rect[0]);
        button_gameover_img[1].render(200,315,100,100,&gameover_button_img_rect[1]);
        button_gameover_img[2].render(350,315,100,100,&gameover_button_img_rect[2]);

        while (SDL_PollEvent(&gameover_event))
        {
            switch (gameover_event.type)
            {
                case SDL_QUIT:
                    return 2;
                case SDL_MOUSEMOTION:
                    {
                     x_mouse = gameover_event.motion.x;
                     y_mouse = gameover_event.motion.y;
                     for (int i=0;i<NUM_ITEM_GAMEOVER;i++)
                     {
                         if (x_mouse >=gameover_button_rect[i].x && x_mouse <= gameover_button_rect[i].x+gameover_button_rect[i].w && y_mouse >=gameover_button_rect[i].y && y_mouse <=gameover_button_rect[i].y+gameover_button_rect[i].h)
                         {
                            // gTextGameOver[i].setColor(255,255,0);
                             button_gameover_img[i].setColor(0,0,255);
                         }
                         else
                         {
                            //gTextGameOver[i].setColor(255,255,255);
                            button_gameover_img[i].setColor(255,255,255);
                         }
                     }
                    }
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                         x_mouse = gameover_event.motion.x;
                         y_mouse = gameover_event.motion.y;
                         for (int i=0;i<NUM_ITEM_PAUSE;i++)
                         {
                         if (x_mouse >=gameover_button_rect[i].x && x_mouse <= gameover_button_rect[i].x+gameover_button_rect[i].w && y_mouse >=gameover_button_rect[i].y && y_mouse <=gameover_button_rect[i].y+gameover_button_rect[i].h)
                             {

                                Mix_PlayChannel( -1, gMenuClick, 0 );
                                 return i;
                             }
                        }

                   // break;
                    }

                    default:
                    break;
                    }
                }
            if (HIGH_SCORE>0)
                        {
                            //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + int_to_str(HIGH_SCORE*100);
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }
                        else
                        {
                        //font score
                            char_tmp = char_tmp + "HIGH SCORE : " + "000";
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextHighScore.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                             gTextHighScore.render(120,240,260,60);
                            char_tmp="";
                        }

            SDL_RenderPresent( gRenderer );
        }

    return 2;
}
int main( int argc, char* args[] )
{
        freopen("highscore.txt","r",stdin);
		    std::cin>>HIGH_SCORE;
	//Start up SDL and create window

	//std::cout << ENEMY1_VELY/(0.445) <<std:: endl;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

		    LTimer fpsTimer;
		    LTimer capTimer;
		    int countedFrames = 0;
			fpsTimer.start();
			//Main loop flag

            int check_pause;
            int check_gameover;
            enum TypeScreen
            {
                NONE_ = 0,
                MENU_ = 1,
                PAUSE_ = 2,
                GAMEOVER_ = 3
            };
            int type_screen = MENU_;
			//Event handler
			SDL_Event e;

			Dot dot;
			Food food;
			Food food2;
			//food2.set_type(2);
			food2.set_type(GetRandom(1,3));
            int enemy_amo_rate[MAX_NUM_ENEMY_2];
            int tmp;
            int size_dot_amo;
            Enemy m_enemy [MAX_NUM_ENEMY_1];
            Enemy m2_enemy [MAX_NUM_ENEMY_2];
            SDL_Rect pause_button = {225,0,50,50};
            for (int t=0;t<MAX_NUM_ENEMY_1;t++)//KHOI TAO ENEMY1
            {
                m_enemy[t].set_type(1);
                m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                m_enemy[t].set_is_move(true);
                m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
            }

            for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)//KHOI TAO ENEMY2
            {
                m2_enemy[t2].set_type(2);
                m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));//tan phi = y/x
                m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-150,-50));
                enemy_amo_rate[t2] = 0;
                m2_enemy[t2].set_is_move(true);
                m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
            }

			//Menu
			int check_menu = menu();
            if (check_menu == 1) quit = true;
            else type_screen=NONE_;
			//While application is running
			while( !quit )
			{
			    if (type_screen == GAMEOVER_)
                {
                        check_gameover = game_over();
                        //std::cout<<check_gameover;
                        if (check_gameover == 0)//menu
                        {
                            dot.reset();
                            DOT_HEART = MAX_DOT_HEART;
                            count_remain_special_amo = 0;
                            dot.set_type_amo(0);
                            type_amo=0;
                            level = 1;
                            count_time_render_level=0;
                            level_render_success = false;
                            count_appear_food1=0;
                            count_appear_special_food=0;
                            dot_amo_rate =0 ;
                            dot.clear_amo();
                            SCORE = 0;
                             for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                            {
                                if (m_enemy[t].get_is_render()==true)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }
                            }

                            for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                            {
                                if (m2_enemy[t2].get_is_render()==true)
                                {
                                    m2_enemy[t2].set_type(2);
                                    m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                            }
                            bool_game_over = false;
                            type_screen = MENU_;
                        }
                        else if (check_gameover == 1)//play again
                        {

                           // dot = clone;
                            dot.reset();
                            DOT_HEART = MAX_DOT_HEART;
                            count_remain_special_amo = 0;
                            dot.set_type_amo(0);
                            type_amo=0;
                            level = 1;
                            count_time_render_level=0;
                            level_render_success = false;
                            count_appear_food1=0;
                            count_appear_special_food=0;
                            dot_amo_rate =0 ;
                            dot.clear_amo();
                            SCORE = 0;
                             for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                            {
                                if (m_enemy[t].get_is_render()==true)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }
                            }

                            for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                            {
                                if (m2_enemy[t2].get_is_render()==true)
                                {
                                    m2_enemy[t2].set_type(2);
                                    m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                            }
                            bool_game_over = false;
                            type_screen = NONE_;
                        }
                        else if (check_gameover == 2 )
                        {
                            quit = true;
                        }


                }
			    else if (type_screen == PAUSE_)
                {
                        check_pause = pause();
                        if (check_pause == 0)//menu
                        {
                            dot.reset();
                            DOT_HEART = MAX_DOT_HEART;
                            count_remain_special_amo = 0;
                            dot.set_type_amo(0);
                            type_amo=0;
                            level = 1;
                            count_time_render_level=0;
                            level_render_success = false;
                            count_appear_food1=0;
                            count_appear_special_food=0;
                            dot_amo_rate =0 ;
                            dot.clear_amo();
                            SCORE = 0;
                             for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                            {
                                if (m_enemy[t].get_is_render()==true)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }
                            }

                            for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                            {
                                if (m2_enemy[t2].get_is_render()==true)
                                {
                                    m2_enemy[t2].set_type(2);
                                    m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                            }

                            bool_pause = false;
                            type_screen = MENU_;
                        }
                        else if (check_pause == 2)//exit
                        {
                            quit = true;
                        }
                        else
                        {
                            type_screen = NONE_;
                            bool_pause = false;
                        }
                }
			    else if (type_screen == MENU_)
                {
                    check_menu = menu();
                    if (check_menu == 1) quit = true;
                    else type_screen = NONE_;
                    //std::cout<<type_screen;
                }

			    else if (type_screen == NONE_)
                {



			   // std::cout<<4;
			    capTimer.start();

				SDL_RenderClear( gRenderer );

                //background


                gBackground.render(0,moveY_BG,SCREEN_WIDTH,SCREEN_HEIGHT);
                gBackground.render(0,-SCREEN_HEIGHT+moveY_BG,SCREEN_WIDTH,SCREEN_HEIGHT);
                moveY_BG+=SPEED_BACKGROUND;
                if (moveY_BG>=SCREEN_HEIGHT) moveY_BG=0;

                    //LEVEL 1
                   /* if (SCORE==0 && level_render_success==true && level == 0)
                    {
                        level = 1;
                        count_time_render_level=0;
                        level_render_success = false;
                    }*/
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==1)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[0].render(73,180,355,96,&level_rect);//level1
                        count_time_render_level++;
                        NUM_ENEMY1=6;
                        NUM_ENEMY2=0;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(0);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(0);
                                       // std::cout<<1;
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }

                    //LEVEL 2
                    if (point>=20 && level_render_success==true && level == 1)
                    {
                        level = 2;
                        point=0;
                        count_time_render_level=0;
                        level_render_success = false;

                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    m2_enemy[t2].set_type(2);
                                    //m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    //enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                    }
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==2)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[1].render(73,180,355,96,&level_rect);//level2
                        count_time_render_level++;
                        NUM_ENEMY1=6;
                        NUM_ENEMY2=0;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(1);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(1);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }
                    //LEVEL 3
                     if (point>=20 && level_render_success==true && level==2)
                    {
                        level = 3;
                        point=0;
                        count_time_render_level=0;
                        level_render_success = false;

                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    m2_enemy[t2].set_type(2);
                                   // m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    //enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                    }
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==3)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[2].render(73,180,355,96,&level_rect);//level3
                        count_time_render_level++;
                        NUM_ENEMY1=0;
                        NUM_ENEMY2=6;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(0);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(0);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }
                    //LEVEL 4
                    if (point>=20 && level_render_success==true && level==3)
                    {
                        level = 4;
                        point=0;
                        count_time_render_level=0;
                        level_render_success = false;

                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    m2_enemy[t2].set_type(2);
                                   // m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    //enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                    }
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==4)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[3].render(73,180,355,96,&level_rect);//level4
                        count_time_render_level++;
                        NUM_ENEMY1=0;
                        NUM_ENEMY2=6;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(1);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(1);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }
                    //LEVEL 5
                    if (point>=20 && level_render_success==true && level==4)
                    {
                        level = 5;
                        point=0;
                        count_time_render_level=0;
                        level_render_success = false;

                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    m2_enemy[t2].set_type(2);
                                    //m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    //enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                    }
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==5)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[4].render(73,180,355,96,&level_rect);//level5
                        count_time_render_level++;
                        NUM_ENEMY1=4;
                        NUM_ENEMY2=4;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(0);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(0);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }
                    //LEVEL 6
                    if (point>=30 && level_render_success==true && level==5)
                    {
                        level = 6;
                        point=0;
                        count_time_render_level=0;
                        level_render_success = false;

                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                    m_enemy[t].set_type(1);
                                    m_enemy[t].set_enemy_vel(ENEMY1_VELY);
                                     m_enemy[t].set_enemy_velX(ENEMY1_VELY/(0.466));
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-300,-100));
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    m2_enemy[t2].set_type(2);
                                   // m2_enemy[t2].clear_amo();
                                    m2_enemy[t2].set_enemy_vel(ENEMY2_VELY);
                                    m2_enemy[t2].set_enemy_velX(ENEMY2_VELY/(0.466));
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    //enemy_amo_rate[t2] = 0;
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                    }
                 if (count_time_render_level<=time_limit_render_level && level_render_success==false && level==6)
                    {
                        //std::cout<<1;
                         SDL_Rect level_rect = {216,154,224,66};
                        LevelTexture[5].render(73,180,355,96,&level_rect);//level6
                        count_time_render_level++;
                        NUM_ENEMY1=4;
                        NUM_ENEMY2=4;
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(1);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(1);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                        //SDL_RenderPresent( gRenderer );
                    }
                    //level 7
                    if (point>=15 && level_render_success==true && level==6)
                    {
                        level = 7;

                    }
                    if (level == 7)
                    {
                        SPEED_APPEAR_FOOD1=SCREEN_FPS*7;
                        SPEED_APPEAR_SPECIAL_FOOD=SCREEN_FPS*10;
                        level_render_success=true;
                        point=0;
                        NUM_ENEMY1=5;
                        NUM_ENEMY2=5;
                        //count_time_render_level=0;


                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(1);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(1);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                    }
                    //level 8
                    if (point>=15 && level_render_success==true && level==7)
                    {
                        level = 8;

                    }
                    if (level==8)
                    {
                        SPEED_APPEAR_FOOD1=SCREEN_FPS*5;
                        SPEED_APPEAR_SPECIAL_FOOD=SCREEN_FPS*8;
                        point=0;
                        level_render_success=true;
                        NUM_ENEMY1=6;
                        NUM_ENEMY2=6;
                        //count_time_render_level=0;


                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                                {
                                   if (t<NUM_ENEMY1)
                                   {
                                       m_enemy[t].set_is_render(true);
                                       m_enemy[t].set_typemove(1);
                                   }
                                   else m_enemy[t].set_is_render(false);
                                }

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                                {
                                    if (t2<NUM_ENEMY2)
                                    {
                                        m2_enemy[t2].set_is_render(true);
                                        m2_enemy[t2].set_typemove(1);
                                    }
                                    else m2_enemy[t2].set_is_render(false);
                                }
                    }

                    if (count_time_render_level>time_limit_render_level)
                    {
                        level_render_success=true;
                    }

                SDL_Rect pause_button_img_rect = {137,139,114,104};
                pause_on_play.render(225,0,50,50,&pause_button_img_rect);

                //fps

                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
				//Move the dot and check collision
               // size_enemy = enemy_list.size();
                //dot

                if (count_appear_food1>SPEED_APPEAR_FOOD1)
                {
                    food.set_type(0);
                    food.move(dot.getRect());
                    food.render();

                }
                if (count_appear_special_food>SPEED_APPEAR_SPECIAL_FOOD)
                {

                    food2.move(dot.getRect());
                    food2.render();

                }
                if (count_remain_special_amo>time_special_amo  ) {type_amo = 0;count_remain_special_amo=0;}

                while( SDL_PollEvent( &e ) != 0 )
				{
				    int x_mouse=0,y_mouse=0;
					//User requests quit
					switch (e.type)
                    {
                        case SDL_QUIT:
                            quit = true;
                        case SDL_MOUSEMOTION:
                            {
                                 x_mouse = e.motion.x;
                                 y_mouse = e.motion.y;
                                 if (x_mouse >=pause_button.x && x_mouse <= pause_button.x+pause_button.w && y_mouse >= pause_button.y && y_mouse <=pause_button.y+pause_button.h)
                                 {
                                     pause_on_play.setColor(0,0,255);
                                 }
                                 else
                                 {
                                     pause_on_play.setColor(255,255,255);
                                 }
                            }
                        break;
                        case SDL_MOUSEBUTTONDOWN:
                        {
                             x_mouse = e.motion.x;
                             y_mouse = e.motion.y;
                             if (x_mouse >=pause_button.x && x_mouse <= pause_button.x+pause_button.w && y_mouse >= pause_button.y && y_mouse <=pause_button.y+pause_button.h)
                                 {

                                     Mix_PlayChannel( -1, gMenuClick, 0 );
                                     bool_pause = true;
                                     type_screen = PAUSE_;
                                     //std::cout<<"PAUSE";

                                 }
                       // break;
                        }
                        break;
                        case SDL_KEYDOWN:
                            {
                                if (e.key.keysym.sym==SDLK_p)
                                {
                                    Mix_PlayChannel( -1, gMenuClick, 0 );
                                    bool_pause = true;
                                    type_screen = PAUSE_;
                                }
                            }
                            break;
                        default:
                        break;
                }

					//Handle input for the dot
					 dot.handleEvent( e );

				}

				dot.move();

                dot.render();
                dot.MakeAmo();

//ENEMY1
            //std::cout<<"quit:"<<quit;
            for (int t=0;t<MAX_NUM_ENEMY_1;t++)
                {
                    if (m_enemy[t].get_is_move()==true && m_enemy[t].get_explosion()==false && m_enemy[t].get_is_render()==true)
                    {

                     //tmp = enemy->get_enemy1_heart();std::cout<<tmp;
                        m_enemy[t].move();
                        m_enemy[t].render();
                        //tmp = enemy->get_enemy1_heart();std::cout<<tmp;

                            if (checkCollision(m_enemy[t].getRect(),dot.getRect()) && level_render_success == true)
                        {
                            Mix_PlayChannel( -1, gEnemyHurt, 0 );
                            DOT_HEART--;
                            m_enemy[t].set_explosion(true);
                            m_enemy[t].set_is_move(false);
                            if (DOT_HEART <= 0)
                            {

                                bool_game_over = true;
                                type_screen = GAMEOVER_;
                                break;
                            }

                        }
                    }
                }

                //std::cout<<quit;
                //std::cout<<bool_game_over;




//end_ENEMY1
//std::cout<<bool_game_over;
//ENEMY 2
//std::cout<<quit;
if (quit == false)
{
            for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                {
                    if (m2_enemy[t2].get_is_move()==true  && m2_enemy[t2].get_explosion()==false && m2_enemy[t2].get_is_render()==true)
                    {
                        m2_enemy[t2].move();
                        m2_enemy[t2].render();

                        if (enemy_amo_rate[t2]>=reload_enemy_amo && m2_enemy[t2].get_y()>=0)
                        {
                            //std::cout<<1;
                            m2_enemy[t2].InitAmo();
                            enemy_amo_rate[t2] = 0;
                        }
                        if (m2_enemy[t2].get_y()>=0 && m2_enemy[t2].get_y()<=3)
                        {
                            enemy_amo_rate[t2] = reload_enemy_amo-40;;
                        }


                            if (checkCollision(m2_enemy[t2].getRect(),dot.getRect()) && level_render_success == true)
                            {
                                DOT_HEART--;
                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                m2_enemy[t2].set_explosion(true);
                                m2_enemy[t2].set_is_move(false);
                                if (DOT_HEART <= 0)
                                {
                                    type_screen = GAMEOVER_;
                                    bool_game_over = true;
                                    break;
                                }
                            }

                    }

                        for (int tt3=0;tt3<m2_enemy[t2].get_amo_list().size();tt3++)
                        {

                                if (checkCollision(m2_enemy[t2].get_amo_list()[tt3].getRect(),dot.getRect()) &&
                                    m2_enemy[t2].get_amo_list()[tt3].get_is_move() == true && m2_enemy[t2].get_is_render()==true && level_render_success == true)//Xet va cham cua dan dich voi dino
                                {
                                    DOT_HEART--;
                                    if (DOT_HEART <= 0)
                                    {
                                        m2_enemy[t2].remove_amo(tt3);
                                        type_screen = GAMEOVER_;
                                        bool_game_over = true;

                                        break;
                                    }
                                    else
                                    {
                                        m2_enemy[t2].remove_amo(tt3);
                                    }

                                }

                            }

                            if (bool_game_over == true || type_screen!= NONE_) {break;}
                            if (m2_enemy[t2].get_is_render()==true) m2_enemy[t2].MakeAmo();


                }
}

//std::cout<<bool_game_over;
//xu ly game over
//std::cout<<quit;


//DOT_AMO
           // std::cout<<quit;
            if (quit == false)
            {
                //std::cout<<dot.get_amo_list().size();
                size_dot_amo = dot.get_amo_list().size();
                for (int ii=0;ii<size_dot_amo;ii++)
                {
                    if (dot.get_amo_list()[ii].get_is_move()== true)
                    {
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)//ENEMY1
                    {
                     //tmp = enemy->get_enemy1_heart();std::cout<<tmp;
                        if (m_enemy[t].get_is_move()==true && m_enemy[t].get_is_render()==true)
                        {
                                    if (dot.get_amo_list()[ii].get_shurikentype() == 0)
                                    {

                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;
                                        if (checkCollision(dot.get_amo_list()[ii].getRect(),m_enemy[t].getRect()) && level_render_success == true)
                                        {
                                            if (m_enemy[t].get_type()==1)
                                            {
                                                //std::cout<<enemy->get_enemy1_heart();
                                                m_enemy[t].down_enemy1_heart(DAMAGE_AMO);
                                                if (m_enemy[t].get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    point++;
                                                     Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                    m_enemy[t].set_explosion(true);
                                                    m_enemy[t].set_is_move(false);
                                                }
                                            }
                                            //dot.get_amo_list()[ii].set_is_move(false);
                                            //dot.remove_amo(ii);
                                            dot.erase_amo(ii);
                                            //std::cout<<dot.get_amo_list()[ii].get_is_move();
                                        }


                                    }
                                   else if (dot.get_amo_list()[ii].get_shurikentype()==1) //RED
                                    {
                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = MAX_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;
                                        if (checkCollision(dot.get_amo_list()[ii].getRect(),m_enemy[t].getRect())&& level_render_success == true)
                                        {

                                            if (m_enemy[t].get_type()==1)
                                            {
                                                //std::cout<<m_enemy[t].get_enemy1_heart();
                                                m_enemy[t].down_enemy1_heart(DAMAGE_AMO);
                                                if (m_enemy[t].get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    point++;
                                                     Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                    m_enemy[t].set_explosion(true);
                                                    m_enemy[t].set_is_move(false);

                                                }
                                            }
                                            //dot.get_amo_list()[ii].set_is_move(false);
                                           //dot.remove_amo(ii);
                                           dot.erase_amo(ii);
                                        }

                                    }
                                   else if (dot.get_amo_list()[ii].get_shurikentype() == 2) //YELLOW
                                    {
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = max_reload_dot_amo;
                                        dot.set_dot_amo_vel(MAX_DOT_AMO_VEL);
                                        if (checkCollision(dot.get_amo_list()[ii].getRect(),m_enemy[t].getRect())&& level_render_success == true)
                                        {

                                            if (m_enemy[t].get_type()==1)
                                            {
                                                //std::cout<<m_enemy[t].get_enemy1_heart();
                                                m_enemy[t].down_enemy1_heart(DAMAGE_AMO);
                                                if (m_enemy[t].get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    point++;
                                                     Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                    m_enemy[t].set_explosion(true);
                                                    m_enemy[t].set_is_move(false);
                                                }
                                            }
                                            //dot.get_amo_list()[ii].set_is_move(false);
                                            //dot.remove_amo(ii);
                                            dot.erase_amo(ii);
                                        }
                                    }
                                   else if (dot.get_amo_list()[ii].get_shurikentype() == 3) //Purple
                                    {
                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;

                                        if (checkCollision(dot.get_amo_list()[ii].getRect(),m_enemy[t].getRect())&& level_render_success == true)
                                        {

                                            if (m_enemy[t].get_type()==1)
                                            {
                                                //std::cout<<m_enemy[t].get_enemy1_heart();
                                                m_enemy[t].down_enemy1_heart(DAMAGE_AMO);
                                                if (m_enemy[t].get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    point++;
                                                     Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                    m_enemy[t].set_explosion(true);
                                                    m_enemy[t].set_is_move(false);

                                                }
                                            }
                                            //dot.get_amo_list()[ii].set_is_move(true);
                                            //dot.remove_amo(ii);

                                        }
                                    }

                                }
                            }

                        }
                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)//ENEMY2
                        {
                            if (m2_enemy[t2].get_is_move()==true && m2_enemy[t2].get_is_render()==true)
                            {
                                if (dot.get_amo_list()[ii].get_is_move() == true )
                                    {
                                        if (dot.get_amo_list()[ii].get_shurikentype() == 0)
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                            if (m2_enemy[t2].get_is_move()==true)
                                        {
                                            if (checkCollision(dot.get_amo_list()[ii].getRect(),m2_enemy[t2].getRect())&& level_render_success == true)
                                            {

                                                if (m2_enemy[t2].get_type()==2)
                                                {
                                                    //std::cout<<m2_enemy[t2].get_enemy2_heart();
                                                        //tmp = m2_enemy[t2].get_enemy2_heart();
                                                        m2_enemy[t2].down_enemy2_heart(DAMAGE_AMO);

                                                    if (m2_enemy[t2].get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        point++;
                                                         Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                        m2_enemy[t2].set_explosion(true);
                                                        m2_enemy[t2].set_is_move(false);

                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                               // dot.get_amo_list()[ii].set_is_move(false);
                                               dot.erase_amo(ii);
                                            }
                                        }
                                        }



                                      else  if (dot.get_amo_list()[ii].get_shurikentype() == 1) // red
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = MAX_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                             if (m2_enemy[t2].get_is_move()==true)
                                        {
                                            if (checkCollision(dot.get_amo_list()[ii].getRect(),m2_enemy[t2].getRect())&& level_render_success == true)
                                            {

                                                if (m2_enemy[t2].get_type()==2)
                                                {
                                                    //std::cout<<m2_enemy[t2].get_enemy2_heart();
                                                        //tmp = m2_enemy[t2].get_enemy2_heart();
                                                        m2_enemy[t2].down_enemy2_heart(DAMAGE_AMO);

                                                    if (m2_enemy[t2].get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        point++;
                                                         Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                         m2_enemy[t2].set_explosion(true);
                                                         m2_enemy[t2].set_is_move(false);

                                                    }
                                                }
                                                //
                                                //dot.get_amo_list()[ii].set_is_move(false);
                                                //dot.remove_amo(ii);
                                                dot.erase_amo(ii);
                                            }
                                        }
                                            //


                                        //
                                        }
                                       else  if (dot.get_amo_list()[ii].get_shurikentype() == 2) // yellow
                                        {
                                            dot.set_dot_amo_vel(MAX_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = max_reload_dot_amo;
                                             if (m2_enemy[t2].get_is_move()==true)
                                        {
                                            if (checkCollision(dot.get_amo_list()[ii].getRect(),m2_enemy[t2].getRect())&& level_render_success == true)
                                            {

                                                if (m2_enemy[t2].get_type()==2)
                                                {
                                                    //std::cout<<m2_enemy[t2].get_enemy2_heart();
                                                        //tmp = m2_enemy[t2].get_enemy2_heart();
                                                        m2_enemy[t2].down_enemy2_heart(DAMAGE_AMO);

                                                    if (m2_enemy[t2].get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        point++;
                                                         Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                        m2_enemy[t2].set_explosion(true);
                                                        m2_enemy[t2].set_is_move(false);
                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                               // dot.get_amo_list()[ii].set_is_move(false);
                                               dot.erase_amo(ii);
                                            }
                                        }
                                        }
                                       else  if (dot.get_amo_list()[ii].get_shurikentype() == 3) // purple
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                             if (m2_enemy[t2].get_is_move()==true)
                                        {
                                            if (checkCollision(dot.get_amo_list()[ii].getRect(),m2_enemy[t2].getRect())&& level_render_success == true)
                                            {

                                                if (m2_enemy[t2].get_type()==2)
                                                {
                                                    //std::cout<<m2_enemy[t2].get_enemy2_heart();
                                                        //tmp = m2_enemy[t2].get_enemy2_heart();
                                                        m2_enemy[t2].down_enemy2_heart(DAMAGE_AMO);

                                                    if (m2_enemy[t2].get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        point++;
                                                         Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                        m2_enemy[t2].set_explosion(true);
                                                        m2_enemy[t2].set_is_move(false);


                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                              // dot.get_amo_list()[ii].set_is_move(true);
                                            }
                                        }
                                    }
                                }
                            }
                              if (dot.get_amo_list()[ii].get_shurikentype() == 1 && dot.get_amo_list()[ii].get_is_move() == true) // red
                                {
                                    for (int tt3=0;tt3<m2_enemy[t2].get_amo_list().size();tt3++)
                                    {
                                            if (checkCollision(m2_enemy[t2].get_amo_list()[tt3].getRect(),dot.get_amo_list()[ii].getRect()) &&
                                                m2_enemy[t2].get_amo_list()[tt3].get_is_move() == true)
                                            {
                                                m2_enemy[t2].remove_amo(tt3);
                                            }
                                    }
                                }
                            }

                        }

            }
//reset enemy and explosion
                        for (int t=0;t<MAX_NUM_ENEMY_1;t++)//ENEMY1
                        {
                            if (m_enemy[t].get_is_render()==true)
                            {
                                if (m_enemy[t].get_explosion()==true)
                                {
                                        m_enemy[t].die_render();
                                }
                                else if (m_enemy[t].get_explosion()==false && m_enemy[t].get_is_move()==false)
                                {
                                    m_enemy[t].set_is_move(true);
                                    m_enemy[t].set_xy(GetRandom(0,SCREEN_WIDTH-70),GetRandom(-300,-100));
                                    m_enemy[t].set_enemy1_heart(ENEMY1_HEART);
                                }
                            }
                        }
                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)//ENEMY1
                        {
                            if (m2_enemy[t2].get_is_render()==true)
                            {
                                if (m2_enemy[t2].get_explosion()==true)
                                {
                                        m2_enemy[t2].die_render();
                                }
                                else if (m2_enemy[t2].get_explosion()==false && m2_enemy[t2].get_is_move()==false)
                                {
                                    m2_enemy[t2].set_is_move(true);
                                    m2_enemy[t2].set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-150,-50));

                                    enemy_amo_rate[t2]=0;
                                    m2_enemy[t2].set_enemy2_heart(ENEMY2_HEART);
                                }
                            }
                        }

                        //font heart
                        //Render text
                        //std::cout<<quit;


                            if (DOT_HEART>0)
                            {
                                SDL_Rect heart_rect = {92,88,49,52};
                                gHeart_Data.render(0,0,45,45,&heart_rect);
                                char_tmp =char_tmp + "x" + int_to_str(DOT_HEART);
                                SDL_Color textColor = { 255,255,255};
                                if( !gTextTexture.loadFromRenderedText( char_tmp, textColor ) )
                                {
                                    printf( "Failed to render text texture!\n" );

                                }
                                gTextTexture.render(45,0,50,50);
                                char_tmp="";
                            }
                            else
                            {
                                //font heart
                                //Render text
                                SDL_Rect heart_rect = {92,88,49,52};
                                gHeart_Data.render(0,0,45,45,&heart_rect);
                                char_tmp =char_tmp + "x0";
                                SDL_Color textColor = { 255,255,255};
                                if( !gTextTexture.loadFromRenderedText( char_tmp, textColor ) )
                                {
                                    printf( "Failed to render text texture!\n" );

                                }
                                gTextTexture.render(45,0,50,50);
                                char_tmp="";

                            }
                            //SCORE
                            if (SCORE>0)
                            {
                                SDL_Rect score_rect = {92,88,49,52};
                                gHeart_Data.render(0,0,45,45,&score_rect);
                                char_tmp = char_tmp + "SCORE : " + int_to_str(SCORE*100);
                                SDL_Color textColor = { 255,255,255};
                                if( !gTextTexture2.loadFromRenderedText( char_tmp, textColor ) )
                                {
                                    printf( "Failed to render text texture!\n" );

                                }
                                gTextTexture2.render(SCREEN_WIDTH-120,0,100,50);
                                char_tmp="";
                            }
                            else
                            {
                            //font score
                                char_tmp = char_tmp + "SCORE : " + "000";
                                SDL_Color textColor = { 255,255,255};
                                if( !gTextTexture2.loadFromRenderedText( char_tmp, textColor ) )
                                {
                                    printf( "Failed to render text texture!\n" );

                                }
                                gTextTexture2.render(SCREEN_WIDTH-120,0,100,50);
                                char_tmp="";
                            }
                            if (type_amo != 0 && count_appear_special_food!=0)
                            {
                                if (type_amo==1) SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );//RED
                                else if (type_amo == 2) SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );//YELLOW
                                else if (type_amo == 3) SDL_SetRenderDrawColor( gRenderer, 0xBE, 0x00, 0xFE, 0xFF );//PURPLE
                                SDL_Rect time_remain_rect = {0,SCREEN_HEIGHT-10,(1-float(count_remain_special_amo)/time_special_amo)*SCREEN_WIDTH,10};
                                SDL_RenderFillRect(gRenderer,&time_remain_rect);

                            }





				SDL_RenderPresent( gRenderer );
//std::cout<<quit;

                        for (int t2=0;t2<MAX_NUM_ENEMY_2;t2++)
                        {
                            if (m2_enemy[t2].get_y()>0 && m2_enemy[t2].get_is_render()==true) enemy_amo_rate[t2]++;
                        }


                        ++dot_amo_rate;
                        ++count_appear_food1;
                        ++count_appear_special_food;
                        if (type_amo != 0) ++count_remain_special_amo;


            }
                    ++countedFrames;
                    int frameTicks = capTimer.getTicks();
                    if( frameTicks < SCREEN_TICK_PER_FRAME )
                    {
                        //Wait remaining time
                        SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
                    }
        }
//std::cout<<quit;


			//std::cout<<quit;
            //GIAI PHONG

		}
		//std::cout<<1;
	}

	//Free resources and close SDL
	close();
std::cout<<"DONE";
	freopen("highscore.txt","w",stdout);
    std::cout<<HIGH_SCORE;

	return 0;
}
