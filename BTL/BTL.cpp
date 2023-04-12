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
//Screen dimension constants

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
int NUM_ENEMY1 = 3;
int NUM_ENEMY2 = 3;
const int ENEMY1_HEART = 2;
const int ENEMY1_VEL = 2;
const double ENEMY2_VEL = 1;
const int ENEMY2_HEART = 1;
const int SPEED_BACKGROUND = 1;
const int NUM_IMG_DOT_MOVE=9;
const int NUM_IMG_DOT_STAND=6;
const int NUM_IMG_ENEMY1=6;
const int NUM_IMG_ENEMY2=7;
const int NUM_IMG_AMO_DOT = 9;
const int NUM_IMG_SPECIAL_AMO = 8;
const int NUM_IMG_AMO_ENEMY2 = 7;
const int NUM_IMG_FOOD_HEART=8;
const int NUM_IMG_FOOD_RED=5;
const int NUM_IMG_FOOD_YELLOW=9;
const int NUM_IMG_FOOD_PURPLE=9;

std::string char_tmp;
int type_amo = 0;
int time_special_amo = SCREEN_FPS*7;
int count_remain_special_amo = 0;
int DOT_HEART = 3;
const int COMMON_DOT_AMO_VEL = 7;//dot_amo_vel
const int MAX_DOT_AMO_VEL = 20;//dot_amo_vel
const int MAX_DOT_HEART = 3;
int SCORE =0;
int HIGH_SCORE;
int time;
const int MAX_DAMAGE_AMO = 2;
const int COMMON_DAMAGE_AMO = 1;
int DAMAGE_AMO = COMMON_DAMAGE_AMO;

const int SPEED_ANIMATION = 5;

int count_appear_food1=0;
const int SPEED_APPEAR_FOOD1 =SCREEN_FPS*10;

int count_appear_special_food=0;
const int SPEED_APPEAR_SPECIAL_FOOD =SCREEN_FPS*15;

const int reload_enemy_amo =120;
int dot_amo_rate = 0;
const int common_reload_dot_amo = 15;
const int max_reload_dot_amo = 0;
int reload_dot_amo = common_reload_dot_amo;


std::string path_img_dot_stand="";
std::string path_img_dot_move="";
std::string path_img_enemy1="";
std::string path_img_enemy2="";
std::string path_img_amo_enemy2="";
std::string path_img_amo_dot="";
std::string path_img_food_heart="";
std::string path_img_food_red="";
std::string path_img_food_yellow="";
std::string path_img_food_purple="";
std::string path_img_special_amo="";

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
TTF_Font* gFont2 = NULL;
TTF_Font* gFont3 = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;

#include "LTexture.h"

LTexture gBackground;
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

LTexture gTextTexture;//heart
LTexture gTextTexture2;//score
LTexture gTextTexture3;//time


Mix_Chunk *gKunai = NULL;

Mix_Chunk *gEnemyHurt = NULL;

Mix_Chunk* gPickItem = NULL;

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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

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
    gFont2 = TTF_OpenFont( "font.ttf", 42 );
    if( gFont2 == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );

    }
    gFont3 = TTF_OpenFont( "font.ttf", 42 );
    if( gFont3 == NULL )
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

	return success;
}

void close()
{
	for (int i=0;i<NUM_IMG_DOT_STAND;i++)
	gDotTexture_Stand[i].free();
	for (int i=0;i<NUM_IMG_DOT_MOVE;i++)
	gDotTexture_Move[i].free();

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

    TTF_CloseFont( gFont );
	gFont = NULL;
	TTF_CloseFont( gFont2 );
	gFont2 = NULL;
	TTF_CloseFont( gFont3 );
	gFont3 = NULL;
    gTextTexture.free();
    gTextTexture2.free();
    gTextTexture3.free();
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

int main( int argc, char* args[] )
{
	//Start up SDL and create window
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
			bool quit = false;

			//Event handler
			SDL_Event e;
            std::vector<Shuriken*> amo_list;//me
            std::vector<Shuriken*> amo2_list;//enemy
            Shuriken* new_amo;//me
            Shuriken* new_amo2;//enemy
			Dot dot;
			Food food;
			Food food2;
			food2.set_type(2);
			//food2.set_type(GetRandom(1,3));
            Shuriken * p_amo;
            int enemy_amo_rate[NUM_ENEMY2];
            int tmp;
            Enemy* m_enemy = new Enemy [NUM_ENEMY1];
            Enemy* m2_enemy = new Enemy [NUM_ENEMY2];

            for (int t=0;t<NUM_ENEMY1;t++)
            {
                Enemy *enemy = (m_enemy + t);
                enemy->set_type(1);
                enemy->set_enemy_vel(ENEMY1_VEL);
                enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-600,-100));
                enemy->set_is_move(true);
                enemy->set_enemy1_heart(ENEMY1_HEART);
            }

            for (int t2=0;t2<NUM_ENEMY2;t2++)
            {
                Enemy *enemy2 = (m2_enemy + t2);
                enemy2->set_type(2);
                enemy2->set_enemy_vel(ENEMY2_VEL);
                enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-600,-100));
                enemy_amo_rate[t2] = 0;
                enemy2->set_is_move(true);
                enemy2->set_enemy2_heart(ENEMY2_HEART);

            }

			//Set the wall


			//While application is running
			while( !quit )
			{

			    capTimer.start();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}
				if (quit == true) break;

                //SDL_SetRenderDrawColor( gRenderer, 0xaa, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                //background
                gBackground.render(0,moveY_BG,SCREEN_WIDTH,SCREEN_HEIGHT);
                gBackground.render(0,-SCREEN_HEIGHT+moveY_BG,SCREEN_WIDTH,SCREEN_HEIGHT);
                moveY_BG+=SPEED_BACKGROUND;
                if (moveY_BG>=SCREEN_HEIGHT) moveY_BG=0;


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

				dot.move();
				if (count_remain_special_amo>time_special_amo) {type_amo = 0;count_remain_special_amo=0;}
                dot.MakeAmo();
                dot.render();

//ENEMY1
            for (int t=0;t<NUM_ENEMY1;t++)
                {
                     //tmp = enemy->get_enemy1_heart();std::cout<<tmp;
                    Enemy *enemy = (m_enemy + t);
                    if (enemy!=NULL)
                    {
                        enemy->move();
                        enemy->render();
                        //tmp = enemy->get_enemy1_heart();std::cout<<tmp;
                    }

                    if (enemy !=NULL)
                    {
                            if (checkCollision(enemy->getRect(),dot.getRect()))
                        {
                            SCORE++;
                            if (DOT_HEART <= 1)
                            {
                            std::cout<<"Game over!";

                            quit = true;
                            break;
                            }
                            else
                            {
                                //std::cout<<1;
                                SCORE++;
                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                enemy->set_is_move(true);
                                enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-500,-200));
                                DOT_HEART--;

                            }
                        }
                    }
                    if (quit == true ) break;
                }

//end_ENEMY1
//ENEMY 2
            for (int t2=0;t2<NUM_ENEMY2;t2++)
                {
                    Enemy *enemy2 = (m2_enemy + t2);
                    if (enemy2)
                    {
                        enemy2->move();
                        enemy2->render();

                    }
                    if (enemy_amo_rate[t2]>=reload_enemy_amo )
                    {
                        enemy2->InitAmo();
                        enemy_amo_rate[t2] = 0;
                    }
                    if (enemy2->get_y()>=0 && enemy2->get_y()<=3)
                    {
                        enemy_amo_rate[t2] = reload_enemy_amo-40;;
                    }

                    if (enemy2 !=NULL)
                    {
                            if (checkCollision(enemy2->getRect(),dot.getRect()))
                            {
                                if (DOT_HEART <= 1)
                                {
                                    std::cout<<"Game over!";
                                    quit = true;
                                    break;
                                }
                                else
                                {
                                    //std::cout<<2;
                                    SCORE++;
                                    Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                    enemy2->set_is_move(true);
                                    enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-200,-100));
                                    enemy_amo_rate[t2] = 0;
                                    DOT_HEART--;
                                }
                            }
                        }

                    if (enemy2 != NULL)
                    {
                        amo2_list = enemy2->get_amo_list();
                        for (int tt3=0;tt3<amo2_list.size();tt3++)
                        {
                            new_amo2 = amo2_list.at(tt3);
                            if (new_amo2 !=NULL)
                            {
                                if (checkCollision(new_amo2->getRect(),dot.getRect()) && new_amo2->get_is_move() == true)
                                {
                                    if (DOT_HEART <= 1)
                                    {
                                        std::cout<<"Game over!";

                                        quit = true;
                                        break;
                                    }
                                    else
                                    {
                                        enemy2->remove_amo(tt3);
                                        DOT_HEART--;
                                    }

                                }
                            }
                        }
                        if (quit == true) break;
                    }

                    if (enemy2!=NULL ) enemy2->MakeAmo();

                }
                if (quit == true ) break;
                 amo_list = dot.get_amo_list();
                //std::cout<<amo_list.size();
                for (int ii=0;ii<amo_list.size();ii++)
                {
                    new_amo = amo_list.at(ii);
                        for (int t=0;t<NUM_ENEMY1;t++)
                    {
                     //tmp = enemy->get_enemy1_heart();std::cout<<tmp;
                        Enemy *enemy = (m_enemy + t);
                            if (new_amo !=NULL)
                            {
                                if (new_amo->get_is_move()== true)
                                {
                                    if (type_amo == 0)
                                    {
                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;
                                        if (checkCollision(new_amo->getRect(),enemy->getRect()))
                                        {
                                             Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                            if (enemy->get_type()==1)
                                            {
                                                //std::cout<<enemy->get_enemy1_heart();
                                                enemy->down_enemy1_heart(DAMAGE_AMO);
                                                if (enemy->get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    enemy->set_is_move(true);
                                                    enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-500,-200));
                                                    enemy->set_enemy1_heart(ENEMY1_HEART);
                                                }
                                            }
                                            new_amo->set_is_move(false);
                                        }


                                    }
                                    if (type_amo == 1) //RED
                                    {
                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = MAX_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;
                                        if (checkCollision(new_amo->getRect(),enemy->getRect()))
                                        {
                                             Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                            if (enemy->get_type()==1)
                                            {
                                                //std::cout<<enemy->get_enemy1_heart();
                                                enemy->down_enemy1_heart(DAMAGE_AMO);
                                                if (enemy->get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    enemy->set_is_move(true);
                                                    enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-500,-200));
                                                    enemy->set_enemy1_heart(ENEMY1_HEART);
                                                }
                                            }
                                            new_amo->set_is_move(false);
                                        }
                                    }
                                    if (type_amo == 2) //YELLOW
                                    {
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = max_reload_dot_amo;
                                        dot.set_dot_amo_vel(MAX_DOT_AMO_VEL);
                                        if (checkCollision(new_amo->getRect(),enemy->getRect()))
                                        {
                                             Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                            if (enemy->get_type()==1)
                                            {
                                                //std::cout<<enemy->get_enemy1_heart();
                                                enemy->down_enemy1_heart(DAMAGE_AMO);
                                                if (enemy->get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    enemy->set_is_move(true);
                                                    enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-500,-200));
                                                    enemy->set_enemy1_heart(ENEMY1_HEART);
                                                }
                                            }
                                            new_amo->set_is_move(false);
                                        }
                                    }
                                    if (type_amo == 3) //Purple
                                    {
                                        dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                        DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                        reload_dot_amo = common_reload_dot_amo;

                                        if (checkCollision(new_amo->getRect(),enemy->getRect()))
                                        {
                                             Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                            if (enemy->get_type()==1)
                                            {
                                                //std::cout<<enemy->get_enemy1_heart();
                                                enemy->down_enemy1_heart(DAMAGE_AMO);
                                                if (enemy->get_enemy1_heart()<=0)
                                                {
                                                    SCORE++;
                                                    enemy->set_is_move(true);
                                                    enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-500,-200));
                                                    enemy->set_enemy1_heart(ENEMY1_HEART);
                                                }
                                            }
                                            new_amo->set_is_move(true);
                                        }
                                    }

                                }
                            }
                        }
                        for (int t2=0;t2<NUM_ENEMY2;t2++)
                        {
                            Enemy *enemy2 = (m2_enemy + t2);
                            if (new_amo !=NULL)
                            {
                                if (new_amo->get_is_move() == true )
                                    {
                                        if (type_amo == 0)
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                            if (checkCollision(new_amo->getRect(),enemy2->getRect()))
                                            {
                                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                if (enemy2->get_type()==2)
                                                {
                                                    //std::cout<<enemy2->get_enemy2_heart();
                                                        //tmp = enemy2->get_enemy2_heart();
                                                        enemy2->down_enemy2_heart(DAMAGE_AMO);

                                                    if (enemy2->get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        enemy2->set_is_move(true);
                                                        enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-400,-200));

                                                        enemy_amo_rate[t2]=0;
                                                        enemy2->set_enemy2_heart(ENEMY2_HEART);
                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                                new_amo->set_is_move(false);
                                            }

                                        }
                                        if (type_amo == 1) // red
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = MAX_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                            if (checkCollision(new_amo->getRect(),enemy2->getRect()))
                                            {
                                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                if (enemy2->get_type()==2)
                                                {
                                                    //std::cout<<enemy2->get_enemy2_heart();
                                                        //tmp = enemy2->get_enemy2_heart();
                                                        enemy2->down_enemy2_heart(DAMAGE_AMO);

                                                    if (enemy2->get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        enemy2->set_is_move(true);
                                                        enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-400,-200));

                                                        enemy_amo_rate[t2]=0;
                                                        enemy2->set_enemy2_heart(ENEMY2_HEART);
                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                                new_amo->set_is_move(false);
                                            }
                                        }
                                         if (type_amo == 2) // yellow
                                        {
                                            dot.set_dot_amo_vel(MAX_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = max_reload_dot_amo;
                                            if (checkCollision(new_amo->getRect(),enemy2->getRect()))
                                            {
                                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                if (enemy2->get_type()==2)
                                                {
                                                    //std::cout<<enemy2->get_enemy2_heart();
                                                        //tmp = enemy2->get_enemy2_heart();
                                                        enemy2->down_enemy2_heart(DAMAGE_AMO);

                                                    if (enemy2->get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        enemy2->set_is_move(true);
                                                        enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-400,-200));

                                                        enemy_amo_rate[t2]=0;
                                                        enemy2->set_enemy2_heart(ENEMY2_HEART);
                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                                new_amo->set_is_move(false);
                                            }
                                        }
                                         if (type_amo == 3) // purple
                                        {
                                            dot.set_dot_amo_vel(COMMON_DOT_AMO_VEL);
                                            DAMAGE_AMO = COMMON_DAMAGE_AMO;
                                            reload_dot_amo = common_reload_dot_amo;
                                            if (checkCollision(new_amo->getRect(),enemy2->getRect()))
                                            {
                                                Mix_PlayChannel( -1, gEnemyHurt, 0 );
                                                if (enemy2->get_type()==2)
                                                {
                                                    //std::cout<<enemy2->get_enemy2_heart();
                                                        //tmp = enemy2->get_enemy2_heart();
                                                        enemy2->down_enemy2_heart(DAMAGE_AMO);

                                                    if (enemy2->get_enemy2_heart()<=0)
                                                    {
                                                        SCORE++;
                                                        enemy2->set_is_move(true);
                                                        enemy2->set_xy(GetRandom(0,SCREEN_WIDTH-50),GetRandom(-400,-200));

                                                        enemy_amo_rate[t2]=0;
                                                        enemy2->set_enemy2_heart(ENEMY2_HEART);
                                                    }
                                                }
                                                //dot.remove_amo(ii);
                                                new_amo->set_is_move(true);
                                            }
                                        }
                                    }
                                }

                            }
                        }



                        //font heart
                        //Render text
                        if (DOT_HEART>0)
                        {
                            char_tmp =char_tmp + "HEART : " + int_to_str(DOT_HEART);
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextTexture.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextTexture.render(0,0,100,50);
                            char_tmp="";
                        }
                        else
                        {
                            //font heart
                            //Render text
                            char_tmp =char_tmp + "HEART : " + "0";
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextTexture.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextTexture.render(0,0,100,50);
                            char_tmp="";

                        }
                        //SCORE
                        if (SCORE>0)
                        {
                            //font score
                            char_tmp = char_tmp + "SCORE : " + int_to_str(SCORE);
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextTexture2.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextTexture2.render(SCREEN_WIDTH-130,0,100,50);
                            char_tmp="";
                        }
                        else
                        {
                        //font score
                            char_tmp = char_tmp + "SCORE : " + "0";
                            SDL_Color textColor = { 255,255,255};
                            if( !gTextTexture2.loadFromRenderedText( char_tmp, textColor ) )
                            {
                                printf( "Failed to render text texture!\n" );

                            }
                            gTextTexture2.render(SCREEN_WIDTH-130,0,100,50);
                            char_tmp="";
                        }




				SDL_RenderPresent( gRenderer );
				++countedFrames;
				for (int t=0;t<NUM_ENEMY2;t++)
                {
                    enemy_amo_rate[t]++;
                }
				++dot_amo_rate;
				++count_appear_food1;
				++count_appear_special_food;
				if (type_amo != 0) ++count_remain_special_amo;
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
			}
            //GIAI PHONG
			//giai phong enemy1
			for (int t=0;t<NUM_ENEMY1;t++)
                {
                    Enemy *enemy = (m_enemy+t);
                    if (enemy!=NULL)
                    {
                        delete enemy;
                        enemy = NULL;
                    }
                }
            delete []m_enemy;
            //giai phong enemy2
            for (int t=0;t<NUM_ENEMY2;t++)
                {
                    Enemy *enemy2 = (m2_enemy+t);
                    if (enemy2!=NULL)
                    {
                        if (enemy2->get_amo_list().size()>0) enemy2->get_amo_list().clear();
                        delete enemy2;
                        enemy2 = NULL;
                    }
                }
            delete []m2_enemy;
            amo2_list.clear();
            amo_list.clear();
            if (new_amo2 !=NULL)
            {
                delete new_amo2;
                new_amo2 = NULL;
            }
            if (new_amo != NULL)
            {
                delete new_amo;
                new_amo = NULL;
            }
            if (p_amo != NULL)
            {
                delete p_amo;
                p_amo = NULL;
            }


		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
