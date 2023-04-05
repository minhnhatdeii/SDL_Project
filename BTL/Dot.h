#ifndef DOT_H_
#define DOT_H_
#include "Shuriken.h"
class Dot
{
    public:
        enum Dot_Status
        {

            UP = 1,
            DOWN = 2,
            LEFT = 3,
            RIGHT = 4
        };
		//The dimensions of the dot
		static const int DOT_WIDTH = 60;
		static const int DOT_HEIGHT = 80;
        static const int KUNAI_DOT_WIDTH = 8;
		static const int KUNAI_DOT_HEIGHT = 40;
		//Maximum axis velocity of the dot
		static const int DOT_VEL = 5;
		static const int DOT_AMO_VEL = 10;


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
        int get_dot_status() {return dot_status;}
        void set_dot_status(int a) {dot_status = a;}

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Dot_Rect;
		int dot_status;
		int step_img_dot_stand=1;
        int step_img_dot_up=1;
        int step_img_dot_down=1;
        int step_img_dot_left=1;
        int step_img_dot_right=1;
        bool dot_move_img;
        int solve_bug=0;
        int count_img_dot_stand=1;
        int count_img_dot_up=1;
        int count_img_dot_down=1;
        int count_img_dot_left=1;
        int count_img_dot_right=1;
        std::vector<Shuriken*> p_amo_list;
};
Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = SCREEN_HEIGHT-DOT_HEIGHT;

	//Set collision box dimension
	Dot_Rect.w = DOT_WIDTH;
	Dot_Rect.h = DOT_HEIGHT;
    dot_move_img = false;
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
        solve_bug++;
        dot_move_img = true;
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:
            {
                mVelY -= DOT_VEL;
                dot_status = UP;
                break;
            }
            case SDLK_s:
            {
                mVelY += DOT_VEL;
                dot_status = DOWN;
                break;
            }
            case SDLK_a:
            {
                mVelX -= DOT_VEL;
                dot_status = LEFT;
                break;
            }
            case SDLK_d:
            {
                mVelX += DOT_VEL;
                dot_status = RIGHT;
                break;
            }
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP  && e.key.repeat == 0)
    {
        solve_bug--;
        if (solve_bug==0)
        {
            dot_move_img = false;
        }
        else if (solve_bug>0)
        {

        }
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:
            {
                mVelY += (DOT_VEL);
                break;
            }
            case SDLK_s:
            {
                mVelY -= (DOT_VEL);
                break;
            }
            case SDLK_a:
            {
                mVelX += DOT_VEL;
                break;
            }
            case SDLK_d:
            {
                mVelX -= DOT_VEL;
                break;
            }
        }
    }
    else if( e.type == SDL_MOUSEBUTTONDOWN && dot_amo_rate>=reload_dot_amo )
    {
        Shuriken* p_amo = new Shuriken();
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            dot_move_img = false;
            Mix_PlayChannel( -1, gKunai, 0 );
            if( !gShurikenTexture.loadFromFile( "kunai.png" ) )
            {
                printf( "Failed to load Shuriken texture!\n" );
            }
            p_amo->set_amo_vel(DOT_AMO_VEL);
            p_amo->setwidthheight(KUNAI_DOT_WIDTH,KUNAI_DOT_HEIGHT);
            p_amo->setRect(mPosX+DOT_WIDTH/2,mPosY);
            p_amo->set_is_move(true);
            p_amo_list.push_back(p_amo);
        }
        dot_amo_rate=0;
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
    if (mPosY<=SCREEN_HEIGHT-DOT_HEIGHT) mPosY+=1;
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
    //STAND
    if (dot_move_img == false)
    {
            SDL_Rect stand;
            stand.x=455;
            stand.y=110;
            stand.w=144;
            stand.h=192;
            gDotTexture_Stand[step_img_dot_stand].render( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT,&stand );
            if (count_img_dot_stand>SPEED_ANIMATION) {step_img_dot_stand ++;count_img_dot_stand=1;}

        if (step_img_dot_stand>NUM_IMG_DOT_STAND) step_img_dot_stand=1;
            step_img_dot_right =1;
            step_img_dot_up = 1;
            step_img_dot_left = 1;
            step_img_dot_down = 1;
            count_img_dot_stand++;

    }
    //MOVE
    else if (dot_move_img == true)
    {
           if (dot_status == UP)
        {
            SDL_Rect move_up;
            move_up.x=455;
            move_up.y=110;
            move_up.w=144;
            move_up.h=192;
            gDotTexture_Move[step_img_dot_up].render( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT,&move_up );
            if (count_img_dot_up>SPEED_ANIMATION) {step_img_dot_up ++;count_img_dot_up=1;}
            step_img_dot_down = 1;
            step_img_dot_left = 1;
            step_img_dot_right = 1;
            count_img_dot_up ++;
            count_img_dot_down=1;
            count_img_dot_left=1;
            count_img_dot_right=1;
        }
        else if (dot_status == DOWN)
        {
            SDL_Rect move_down;
            move_down.x=101;
            move_down.y=113;
            move_down.w= 149;
            move_down.h = 188;
                gDotTexture_Move[step_img_dot_down].render( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT ,&move_down);
            if (count_img_dot_down>SPEED_ANIMATION) {step_img_dot_down ++;count_img_dot_down=1;}
            step_img_dot_up = 1;
            step_img_dot_left = 1;
            step_img_dot_right = 1;
            count_img_dot_down ++;
            count_img_dot_up=1;
            count_img_dot_left=1;
            count_img_dot_right=1;
        }
        else if (dot_status == LEFT)
        {
            SDL_Rect move_left;
            move_left.x=266;
            move_left.y=116;
            move_left.w=171;
            move_left.h=182;
            SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;

                gDotTexture_Move[step_img_dot_left].render( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT ,&move_left,0,NULL,flipType);
            if (count_img_dot_left > SPEED_ANIMATION) {step_img_dot_left ++;count_img_dot_left=1;}
            step_img_dot_up = 1;
            step_img_dot_down = 1;
            step_img_dot_right = 1;
            count_img_dot_left ++;
            count_img_dot_down=1;
            count_img_dot_up=1;
            count_img_dot_right=1;
        }
        else if (dot_status == RIGHT)
        {
            SDL_Rect move_right;
            move_right.x=266;
            move_right.y=116;
            move_right.w=171;
            move_right.h=182;
                gDotTexture_Move[step_img_dot_right].render( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT,&move_right );
            if (count_img_dot_right>SPEED_ANIMATION) step_img_dot_right ++;
            step_img_dot_up = 1;
            step_img_dot_left = 1;
            step_img_dot_down = 1;
            count_img_dot_right ++;
            count_img_dot_down=1;
            count_img_dot_left=1;
            count_img_dot_up=1;
        }
        if (step_img_dot_up>NUM_IMG_DOT_MOVE) step_img_dot_up=1;
        if (step_img_dot_down>NUM_IMG_DOT_MOVE) step_img_dot_down=1;
        if (step_img_dot_left>NUM_IMG_DOT_MOVE) step_img_dot_left=1;
        if (step_img_dot_right>NUM_IMG_DOT_MOVE) step_img_dot_right=1;
    }



}
#endif // DOT_H_
