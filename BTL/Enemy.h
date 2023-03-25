#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy
{
    public:

		//The dimensions of the dot
        static const int ENEMY_WIDTH = 20;
		static const int ENEMY_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int ENEMY_VEL = 2;

		//Initializes the variables
		Enemy();
        ~Enemy();
		//Takes key presses and adjusts the dot's velocity
		//void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( );
        void set_xy (int x, int y) {mPosX = x; mPosY = y;}
        void set_is_move(bool a) {is_move=a;}
        bool get_is_move() {return is_move;}
        SDL_Rect getRect()
        {
            return Enemy_Rect;
        }

        int getWidth() {return ENEMY_WIDTH;}
        int getHeight() {return ENEMY_HEIGHT;}
		//Shows the dot on the screen
		void render();
        void InitAmo(Shuriken* p_amo);

		void SetAmoList(std::vector<Shuriken*>amo_list) {p_amo_list=amo_list;}
		std::vector<Shuriken*>get_amo_list() {return p_amo_list;}
        void reset();
    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        bool is_move;

		//Dot's collision box
		SDL_Rect Enemy_Rect;

        std::vector<Shuriken*> p_amo_list;
};

Enemy::Enemy()
{
    //Initialize the offsets
    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
    mPosY = 0;

	//Set collision box dimension
	Enemy_Rect.w = ENEMY_WIDTH;
	Enemy_Rect.h = ENEMY_HEIGHT;

    is_move=true;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
Enemy:: ~Enemy()
{
    if (p_amo_list.size()>0)
    {
        for (int i=0;i<p_amo_list.size();i++)
        {
            Shuriken* p_amo = p_amo_list.at(i);
            if (p_amo!=NULL)
            {
                delete p_amo;
                p_amo=NULL;
            }
        }
        p_amo_list.clear();
    }
}
void Enemy :: reset()
{
    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
    mPosY = 0;

	//Set collision box dimension
	Enemy_Rect.w = ENEMY_WIDTH;
	Enemy_Rect.h = ENEMY_HEIGHT;

    is_move=true;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
void Enemy :: InitAmo(Shuriken* p2_amo)
{
    p2_amo->set_amo_vel(4);
    if (p2_amo)
    {
        if( !gShuriken2Texture.loadFromFile( "dot4.bmp" ) )
            {
                printf( "Failed to load Shuriken texture!\n" );
            }

            p2_amo->setRect(this->mPosX,this->mPosY);
            p2_amo->set_is_move(true);

            p_amo_list.push_back(p2_amo);
    }
}
void Enemy::move(  )
{

    //Move the dot up or down
    mPosY += ENEMY_VEL;
	Enemy_Rect.y = mPosY;

    //If the dot collided or went too far up or down
    if(  mPosY < 0  )
    {
        //Move back
        mPosY -= mVelY;
		Enemy_Rect.y = mPosY;
    }
    if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT )
    {
        mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
        mPosY=0;
    }
    Enemy_Rect.x=mPosX;
    Enemy_Rect.y=mPosY;

//AMO


    //        std::cout<<p_amo_list.size()<<" ";
                for (int i=0;i<p_amo_list.size();i++)
                {
                    Shuriken* p2_amo = p_amo_list.at(i);
                    if (p2_amo != NULL)
                    {
                        if (p2_amo->get_is_move()==true)
                        {
                        p2_amo->move2(SCREEN_WIDTH,SCREEN_HEIGHT);
                        p2_amo->render2();

                        }

                        else
                        {
                                p2_amo->setRect(this->mPosX,this->mPosY);
                                p2_amo->set_is_move(true);

                                //SetAmoList(p_amo_list);

                        }

                    }
                }
}

void Enemy::render()
{
    if( !gEnemyTexture.loadFromFile( "dot3.bmp" ) )
            {
                printf( "Failed to load Enemy texture!\n" );
            }
    //Show the dot
	gEnemyTexture.render( mPosX, mPosY );
}


#endif // ENEMY_H_
