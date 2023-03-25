#ifndef DOT_H_
#define DOT_H_
#include "Shuriken.h"
class Dot
{
    public:

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 5;

		//Initializes the variables
		Dot();
        ~Dot();
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move(  );

        SDL_Rect getRect()
        {
            return Dot_Rect;
        }
		//Shows the dot on the screen
		void render();
        void MakeAmo();
		void SetAmoList(std::vector<Shuriken*>amo_list) {p_amo_list=amo_list;}
		std::vector<Shuriken*>get_amo_list() {return p_amo_list;}
        void remove_amo(int &x);

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Dot_Rect;

        std::vector<Shuriken*> p_amo_list;
};
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
Dot::~Dot()
{
    for (int i=0;i<=p_amo_list.size();i++)
    {
        Shuriken* p_amo = p_amo_list.at(i);
        if (p_amo != NULL)
        {
            delete p_amo;
            p_amo=NULL;
        }
        p_amo_list.clear();
    }
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

	//Set collision box dimension
	Dot_Rect.w = 0;
	Dot_Rect.h = 0;


    //Initialize the velocitys
    mVelX = 0;
    mVelY = 0;
}
void Dot::remove_amo(int &x)
{


        if (x<p_amo_list.size() && x>=0)
        {
            Shuriken* p_amo = p_amo_list.at(x);
        p_amo_list.erase(p_amo_list.begin()+x);
        if (p_amo !=NULL)
        {
            delete p_amo;
            p_amo = NULL;
        }
        }
}
void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN  && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY -= (DOT_VEL+2); break;
            case SDLK_s: mVelY += (DOT_VEL+2); break;
            case SDLK_a: mVelX -= DOT_VEL; break;
            case SDLK_d: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP  && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY += (DOT_VEL+2); break;
            case SDLK_s: mVelY -= (DOT_VEL+2); break;
            case SDLK_a: mVelX += DOT_VEL; break;
            case SDLK_d: mVelX -= DOT_VEL; break;
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

void Dot::move(  )
{
    //Move the dot left or right
    mPosX += mVelX;
	Dot_Rect.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH )  )
    {
        //Move back
        mPosX -= mVelX;
		Dot_Rect.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
	Dot_Rect.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT )  )
    {
        //Move back
        mPosY -= mVelY;
		Dot_Rect.y = mPosY;
    }
    if (mPosY<=SCREEN_HEIGHT-21) mPosY+=1;
}
void Dot:: MakeAmo()
{
    //std::cout<<p_amo_list.size();
    for (int i=0;i<p_amo_list.size();i++)
    {
        Shuriken*p_amo = p_amo_list.at(i);
        if (p_amo !=NULL)
        {
            if (p_amo->get_is_move())
            {
                p_amo->move();
                p_amo->render();
            }
            else
            {
                p_amo_list.erase(p_amo_list.begin()+i);

                delete p_amo;
                p_amo=NULL;
            }
        }
    }
}
void Dot::render()
{
	gDotTexture.render( mPosX, mPosY );
}
#endif // DOT_H_
