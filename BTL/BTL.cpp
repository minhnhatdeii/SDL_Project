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

//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int NUM_ENEMY = 4;

int enemy_amo_rate = 0;
int dot_amo_rate = 0;
const int limit_dot_amo = 10;
const int limit_enemy_amo =50;
int moveY_BG=0;
bool game_over = false;
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
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

//The window renderer
SDL_Renderer* gRenderer = NULL;

#include "LTexture.h"

LTexture gBackground;
//Scene textures
LTexture gDotTexture;//ban than

LTexture gFoodTexture;

LTexture gShurikenTexture;//dan minh

LTexture gShuriken2Texture;//dan dich

LTexture gEnemyTexture;//dich
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
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if( !gBackground.loadFromFile( "tmpbg.jpg" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	//Load press texture
	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gFoodTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load Food texture!\n" );
		success = false;
	}

    gFont = TTF_OpenFont( "lazy2.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
    gFoodTexture.free();
    gShurikenTexture.free();

    TTF_CloseFont( gFont );
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
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
            Shuriken * p_amo;
            Enemy* m_enemy = new Enemy [NUM_ENEMY];
            for (int t=0;t<NUM_ENEMY;t++)
            {
                Enemy* enemy = (m_enemy + t);
                if (enemy)
                {
                    enemy->set_xy(GetRandom(0,SCREEN_WIDTH-50),t*(-100));
                    Shuriken* p2_amo = new Shuriken();
                    enemy->InitAmo(p2_amo);
                }

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

                //SDL_SetRenderDrawColor( gRenderer, 0xaa, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                gBackground.render(0,moveY_BG);
                gBackground.render(0,-SCREEN_HEIGHT+moveY_BG);
                moveY_BG+=1;
                if (moveY_BG>=SCREEN_HEIGHT) moveY_BG=0;

                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
				//Move the dot and check collision
				for (int t=0;t<NUM_ENEMY;t++)
                {
                    Enemy* enemy = (m_enemy + t);
                    if (enemy)
                    {
                         enemy->move();
                        enemy->render();
                    }
                    if (checkCollision(enemy->getRect(),dot.getRect()))
                    {
                        std::cout<<"Game over!";
                        game_over = true;
                        delete []m_enemy;
                        close();
                        break;
                    }
                    amo_list = dot.get_amo_list();
                    for (int ii=0;ii<amo_list.size();ii++)
                    {
                        new_amo = amo_list.at(ii);
                        if (new_amo !=NULL)
                        {
                            if (checkCollision(new_amo->getRect(),enemy->getRect()))
                            {
                                enemy->reset();
                                dot.remove_amo(ii);
                                //std::cout<<1;
                            }
                        }
                    }
                    amo2_list = enemy->get_amo_list();
                    for (int tt=0;tt<amo2_list.size();tt++)
                    {
                        new_amo2 = amo2_list.at(tt);
                        if (new_amo2 !=NULL)
                        {
                            if (checkCollision(new_amo2->getRect(),dot.getRect()))
                            {
                                std::cout<<"Game over!";
                                delete []m_enemy;
                                close();
                                game_over = true;
                                break;
                            }
                        }
                    }
                    if (game_over==true) exit(0);

                }
                if (game_over==true) exit(0);
				dot.move();
                food.move(dot.getRect());
                dot.MakeAmo();
                dot.render();
                food.render();

				//Update screen
				//Render wall





				SDL_RenderPresent( gRenderer );
				++countedFrames;
				++enemy_amo_rate;
				++dot_amo_rate;
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
			}
			delete []m_enemy;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
