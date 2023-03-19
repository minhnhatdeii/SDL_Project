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

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The dot that will move around on the screen


class Food
{
    public:
        enum FoodType
        {
            NONE = 0,
            Food1 = 1,
            Food2 = 2,
            Food3 = 3,
            Foo4 = 4
        };
        static const int FOOD_WIDTH = 20;
		static const int FOOD_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int FOOD_VEL = 4;

		//Initializes the variables
		Food();
        //~Food();
		//Moves the dot and checks collision
		void move(SDL_Rect a);

		//Shows the dot on the screen
		void render();

        void set_type(int a) {food_type=a;}

		SDL_Rect getRect() {return Food_Rect;}
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Food_Rect;

		int food_type;
};
class Shuriken
{
    public:

        static const int SHURIKEN_WIDTH = 20;
		static const int SHURIKEN_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int SHURIKEN_VEL = 10;

		//Initializes the variables
		Shuriken();
        //~Shuriken();
		//Moves the dot and checks collision
		void move(const int &x_border, const int &y_border);

		//Shows the dot on the screen
		void render();

		SDL_Rect getRect() {return Shuriken_Rect;}
		void setRect(const int &x, const int &y) {mPosX=x;mPosY=y;}
		bool get_is_move() {return is_move;}
		void set_is_move(bool a) {is_move=a;}
		void setwidthheight(int a,int b){Shuriken_Rect.w=a;Shuriken_Rect.h=b;}

    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        bool is_move;
		//Dot's collision box
		SDL_Rect Shuriken_Rect;


};
class LTimer
{


    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};
class Dot
{
    public:

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 6;

		//Initializes the variables
		Dot();
        //~Dot();
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( SDL_Rect& wall );

        SDL_Rect getRect()
        {
            return Dot_Rect;
        }
		//Shows the dot on the screen
		void render();

		void SetAmoList(std::vector<Shuriken*>amo_list) {p_amo_list=amo_list;}
		std::vector<Shuriken*>get_amo_list() {return p_amo_list;}

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Dot_Rect;

        std::vector<Shuriken*> p_amo_list;
};
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

//Scene textures
LTexture gDotTexture;

LTexture gFoodTexture;

LTexture gShurikenTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = SCREEN_HEIGHT-30;

	//Set collision box dimension
	Dot_Rect.w = DOT_WIDTH;
	Dot_Rect.h = DOT_HEIGHT;


    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN  && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= (DOT_VEL+5); break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP  && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += (DOT_VEL+5); break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
    else if( e.type == SDL_MOUSEBUTTONDOWN  )
    {
        Shuriken* p_amo = new Shuriken();
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if( !gShurikenTexture.loadFromFile( "dot2.bmp" ) )
            {
                printf( "Failed to load Shuriken texture!\n" );
            }

            p_amo->setRect(this->mPosX,this->mPosY-DOT_HEIGHT);
            p_amo->set_is_move(true);
            p_amo_list.push_back(p_amo);
        }

    }
}

void Dot::move( SDL_Rect& wall )
{
    //Move the dot left or right
    mPosX += mVelX;
	Dot_Rect.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) || checkCollision( Dot_Rect, wall ) )
    {
        //Move back
        mPosX -= mVelX;
		Dot_Rect.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
	Dot_Rect.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) || checkCollision( Dot_Rect, wall ) )
    {
        //Move back
        mPosY -= mVelY;
		Dot_Rect.y = mPosY;
    }
    if (mPosY<=SCREEN_HEIGHT-21) mPosY+=3;
}

void Dot::render()
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY );
}

Food::Food()
{
    //Initialize the offsets
    mPosX = GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);
    mPosY = 0;

	//Set collision box dimension
	Food_Rect.w = FOOD_WIDTH;
	Food_Rect.h = FOOD_HEIGHT;

    food_type = 0;
    //Initialize the velocityGet
    mVelX = 0;
    mVelY = FOOD_VEL;
}
void Food::move(SDL_Rect a)
{
    //Move the dot left or right
    mPosY+=mVelY;
    Food_Rect.x=mPosX;
    Food_Rect.y=mPosY;
    if (mPosY>=SCREEN_HEIGHT) {mPosY = 0;mPosX=GetRandom(0,SCREEN_WIDTH);}
    if (checkCollision(Food_Rect,a)) {mPosY = 0;mPosX=GetRandom(0,SCREEN_WIDTH);}
}

void Food::render()
{
    //Show the dot
	gFoodTexture.render( mPosX, mPosY );
}
Shuriken::Shuriken()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;


	//Set collision box dimension
	Shuriken_Rect.w = SHURIKEN_WIDTH;
	Shuriken_Rect.h = SHURIKEN_HEIGHT;

    is_move = false;
    //Initialize the velocityGet
    mVelX = 0;
    mVelY = 0;
}
void Shuriken::move(const int & x_border,const int & y_border)
{
    //Move the dot left or right
    mPosY-=SHURIKEN_VEL;

    if (mPosY<=0) is_move=false;
    Shuriken_Rect.x=mPosX;
    Shuriken_Rect.y=mPosY;
    mPosX=mPosX;

}

void Shuriken::render()
{
    //Show the dot
	gShurikenTexture.render( mPosX, mPosY );
}
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
LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
    return mPaused && mStarted;
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

			//The dot that will be moving around on the screen
			Dot dot;
			Food food;
            Shuriken * p_amo;
			//Set the wall
			SDL_Rect wall;
			wall.x = SCREEN_WIDTH/2;
			wall.y = 0;
			wall.w = 2;
			wall.h = SCREEN_HEIGHT-200;

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

                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}
				//Move the dot and check collision
				dot.move( wall );
                food.move(dot.getRect());

                for (int i=0;i<dot.get_amo_list().size();i++)
                {
                    std::vector<Shuriken*> amo_list = dot.get_amo_list();
                    p_amo = amo_list[i];
                    if (p_amo != NULL)
                    {
                        if (p_amo->get_is_move()==true)
                        {
                        p_amo->move(SCREEN_WIDTH,SCREEN_HEIGHT);
                        }

                        else
                        {
                            if (p_amo !=NULL)
                            {
                                amo_list.erase(amo_list.begin()+i);
                                dot.SetAmoList(amo_list);
                                delete p_amo;
                                p_amo = NULL;
                            }
                        }

                    }
                }


                //a.move(SCREEN_WIDTH,SCREEN_HEIGHT);
                //a.set_is_move(true);
                //a.render();
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xaa, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderDrawRect( gRenderer, &wall );

				//Render dot
				for (int i=0;i<dot.get_amo_list().size();i++)
                {
                    std::vector<Shuriken*> amo_list = dot.get_amo_list();
                    Shuriken * p_amo = amo_list[i];
                    if (p_amo != NULL)
                    {
                        if (p_amo->get_is_move()==true)
                        {

                        p_amo->render();
                        }
                    }
                }
				dot.render();
                food.render();
				//Update screen
				SDL_RenderPresent( gRenderer );
				++countedFrames;
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
