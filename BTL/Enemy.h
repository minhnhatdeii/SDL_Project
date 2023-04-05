#ifndef ENEMY_H_
#define ENEMY_H_


class Enemy
{
    public:
        enum EnemyType
        {
            NONE = 0,
            ENEMY1 = 1,
            ENEMY2 = 2,
            BOSS = 3
        };
		//The dimensions of the dot
        static const int ENEMY_WIDTH = 70;
		static const int ENEMY_HEIGHT = 70;
        static const int AMO_ENEMY_WIDTH = 20;
		static const int AMO_ENEMY_HEIGHT = 30;
		//Maximum axis velocity of the dot
		int ENEMY_VEL = 2;
        static const int ENEMY_AMO_VEL = 5;
        int ENEMY1_HEART=3;
        int ENEMY2_HEART = 1;
		//Initializes the variables

		Enemy();
        ~Enemy();
		//Takes key presses and adjusts the dot's velocity
		//void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( );

		//enemy1
		int get_enemy1_heart() {return ENEMY1_HEART;}
		void down_enemy1_heart () {ENEMY1_HEART--;}
		void set_enemy1_heart (int a) {ENEMY1_HEART = a;}

		//enemy2

		int get_enemy2_heart() {return ENEMY2_HEART;}
		void down_enemy2_heart () {ENEMY2_HEART--;}
		void set_enemy2_heart (int a) {ENEMY2_HEART = a;}


        void set_xy (int x, int y) {mPosX = x; mPosY = y;}
        void set_is_move(bool a) {is_move=a;}
        bool get_is_move() {return is_move;}
        void set_enemy_vel (int a) {ENEMY_VEL = a;}
        SDL_Rect getRect()
        {
            return Enemy_Rect;
        }

        int getWidth() {return ENEMY_WIDTH;}
        int getHeight() {return ENEMY_HEIGHT;}
		//Shows the dot on the screen
		void render();
        void InitAmo();
        void MakeAmo();
		void SetAmoList(std::vector<Shuriken*>amo_list) {p_amo_list=amo_list;}
		std::vector<Shuriken*>get_amo_list() {return p_amo_list;}
        void reset();
        void remove_amo(int &x);
        void set_type(int a) {enemy_type=a;}
        int get_type () {return enemy_type;}

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        bool is_move;
        //bool enemy_die = false;
		//Dot's collision box
		SDL_Rect Enemy_Rect;

        std::vector<Shuriken*> p_amo_list;
        int enemy_type;
        int step_img_enemy1=1;
        int step_img_enemy2=1;
        int count_img_enemy1=1;
        int count_img_enemy2=1;
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
    //Initialize the offsets
    mPosX =0;
    mPosY = 0;

	//Set collision box dimension
	Enemy_Rect.w =0;
	Enemy_Rect.h = 0;

    is_move=false;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

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
void Enemy::remove_amo(int &x)
{
        if (x<p_amo_list.size() && x>=0)
        {
        Shuriken* p_amo = p_amo_list.at(x);
        p_amo->set_is_move(false);
        p_amo_list.erase(p_amo_list.begin()+x);
        if (p_amo !=NULL)
        {
            delete p_amo;
            p_amo = NULL;
        }
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
void Enemy :: InitAmo()
{
    Shuriken* p2_amo = new Shuriken();
    p2_amo->set_amo_vel(ENEMY_AMO_VEL);
    if (p2_amo)
    {
        if( !gShuriken2Texture.loadFromFile( "purpleflame.png" ) )
            {
                printf( "Failed to load Shuriken texture!\n" );
            }
            p2_amo->setwidthheight(AMO_ENEMY_WIDTH,AMO_ENEMY_HEIGHT);
            p2_amo->setRect(this->mPosX+ENEMY_WIDTH/2,this->mPosY);
            p2_amo->set_is_move(true);

            p_amo_list.push_back(p2_amo);
    }

}
void Enemy::move(  )
{

    //Move the dot up or down
    if (enemy_type == ENEMY1)
    {
        mPosY += ENEMY_VEL;
        Enemy_Rect.y = mPosY;

        //If the dot collided or went too far up or down

        if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
        {
            mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
            mPosY=0;
        }
        Enemy_Rect.x=mPosX;
        Enemy_Rect.y=mPosY;
    }
    if (enemy_type == ENEMY2)
    {
        mPosY += ENEMY_VEL;
        Enemy_Rect.y = mPosY;

        //If the dot collided or went too far up or down

        if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
        {
            mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
            mPosY=0;
        }
        Enemy_Rect.x=mPosX;
        Enemy_Rect.y=mPosY;
    }

}

void Enemy::MakeAmo()
{
            if (enemy_type == ENEMY2)
            {
                 //std::cout<<p_amo_list.size()<<" ";
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
                            p_amo_list.erase(p_amo_list.begin()+i);
                            delete p2_amo;
                            p2_amo=NULL;
                        }

                    }
                }
            }


    //
}

void Enemy::render()
{
    if (enemy_type == 1)
    {
    //Show the dot
        gEnemy1Texture[step_img_enemy1].render( mPosX, mPosY, ENEMY_WIDTH, ENEMY_HEIGHT );

        if (count_img_enemy1>SPEED_ANIMATION) step_img_enemy1++;
        count_img_enemy1++;
        if (step_img_enemy1>NUM_IMG_ENEMY1) {step_img_enemy1=1;count_img_enemy1=1;}
    }
    else if (enemy_type == 2)
    {

    //Show the dot
        SDL_Rect enemy2_rect;
        enemy2_rect.x=266;
        enemy2_rect.y=252;
        enemy2_rect.w=186;
        enemy2_rect.h=154;
        gEnemy2Texture[step_img_enemy2].render( mPosX, mPosY, ENEMY_WIDTH, ENEMY_HEIGHT ,&enemy2_rect);
        if (count_img_enemy2>SPEED_ANIMATION) {step_img_enemy2++;count_img_enemy2=1;}
        count_img_enemy2++;
        if (step_img_enemy2 > NUM_IMG_ENEMY2) step_img_enemy2 = 1;
    }

}


#endif // ENEMY_H_
