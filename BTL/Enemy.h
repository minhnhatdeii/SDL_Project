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
            ENEMY3 = 3
        };
		//The dimensions of the dot
        static const int ENEMY_WIDTH = 70;
		static const int ENEMY_HEIGHT = 70;
        static const int AMO_ENEMY_WIDTH = 20;
		static const int AMO_ENEMY_HEIGHT = 30;
		//Maximum axis velocity of the dot
		//int corner_special_move=25;//25do
		int ENEMY_VEL_Y = 2;
		double ENEMY_VEL_X = 4.5;
        static const int ENEMY_AMO_VEL = 3;
        int ENEMYHEART1_LOCAL= 2;
        int ENEMYHEART2_LOCAL = 1;
        int ENEMYHEART3_LOCAL = 1;
		//Initializes the variables

		Enemy();
        ~Enemy();
		//Takes key presses and adjusts the dot's velocity
		//void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( );
		void special_move();

		//enemy1
		int get_enemy1_heart() {return ENEMYHEART1_LOCAL;}
		void down_enemy1_heart (int DAMAGE_AMO) {ENEMYHEART1_LOCAL -= DAMAGE_AMO;}
		void set_enemy1_heart (int a) {ENEMYHEART1_LOCAL = a;}

		//enemy2

		int get_enemy2_heart() {return ENEMYHEART2_LOCAL;}
		void down_enemy2_heart (int DAMAGE_AMO) {ENEMYHEART2_LOCAL-=DAMAGE_AMO;}
		void set_enemy2_heart (int a) {ENEMYHEART2_LOCAL = a;}

		//enemy 3
		//enemy2

		int get_enemy3_heart() {return ENEMYHEART3_LOCAL;}
		void down_enemy3_heart (int DAMAGE_AMO) {ENEMYHEART3_LOCAL-=DAMAGE_AMO;}
		void set_enemy3_heart (int a) {ENEMYHEART3_LOCAL = a;}

        void set_typemove (int a) {typemove=a;}
        int get_typemove () {return typemove;}

        void set_xy (int x, int y) {mPosX = x; mPosY = y;}
        int get_y() {return mPosY;}
        void set_y(int h) {mPosY=h;}
        void set_is_move(bool a) {is_move=a;}
        bool get_is_move() {return is_move;}

        void set_is_render(bool a) {is_render=a;}
        bool get_is_render() {return is_render;}

        void set_enemy_vel (int a) {ENEMY_VEL_Y = a;}
        SDL_Rect getRect()
        {
            return Enemy_Rect;
        }

        int getWidth() {return ENEMY_WIDTH;}
        int getHeight() {return ENEMY_HEIGHT;}
		//Shows the dot on the screen
		void render();
		void die_render();
        void InitAmo();
        void InitAmo2();//enemy3
        void MakeAmo();
		void SetAmoList(std::vector<Shuriken>amo_list) {p_amo_list=amo_list;}
		std::vector<Shuriken>get_amo_list() {return p_amo_list;}
        void remove_amo(int &x);
        void set_type(int a) {enemy_type=a;}
        int get_type () {return enemy_type;}
        void set_explosion(bool b) {explosion=b;}
        bool get_explosion() {return explosion;}
        void clear_amo()
        {
                p_amo_list.clear();
        }

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        bool is_move;
        bool explosion;
        bool is_render;
		//Dot's collision box
		SDL_Rect Enemy_Rect;
        int direction_ramdom;
        std::vector<Shuriken> p_amo_list;
        int enemy_type;
        int step_img_enemy1=0;
        int step_img_enemy2=0;
        int count_img_enemy1=1;
        int count_img_enemy2=1;
        int step_img_enemy3=0;
        int count_img_enemy3=1;
        int step_img_explosion=0;
        int count_img_explosion=1;
        int typemove=0;//0 laf di thang 1 laf di chuyen cheo
};

Enemy::Enemy()
{
    //Initialize the offsets
    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
    mPosY = 0;
    explosion = false;
	//Set collision box dimension
	Enemy_Rect.w = ENEMY_WIDTH;
	Enemy_Rect.h = ENEMY_HEIGHT;

    is_move=true;
    is_render = false;
    if (GetRandom(1,2) == 1) direction_ramdom = 1;
    else direction_ramdom = -1;
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
        p_amo_list.clear();
}
void Enemy::remove_amo(int &x)
{
    if (bool_pause == false && bool_game_over == false && level_render_success==true)
    {
        if (x<p_amo_list.size() && x>=0)
        {
            p_amo_list[x].set_is_move(false);
            p_amo_list.erase(p_amo_list.begin()+x);
        }
    }
}

void Enemy :: InitAmo()//enemy2
{
    if (bool_pause == false && bool_game_over == false &&level_render_success==true)
    {
        if (mPosY>=0 && mPosY +ENEMY_HEIGHT<=SCREEN_HEIGHT)
        {
            Shuriken p2_amo;
            p2_amo.set_amo_vel(ENEMY_AMO_VEL);
            p2_amo.setwidthheight(AMO_ENEMY_WIDTH,AMO_ENEMY_HEIGHT);
            p2_amo.setRect(this->mPosX+ENEMY_WIDTH/2,this->mPosY);
            p2_amo.set_is_move(true);
            p_amo_list.push_back(p2_amo);
        }

    }
}
void Enemy :: InitAmo2()//enemy3
{
    if (bool_pause == false && bool_game_over == false && level_render_success==true)
    {
        if (mPosY>=0 && mPosY +ENEMY_HEIGHT<=SCREEN_HEIGHT)
        {
            Shuriken p3_amo;
            p3_amo.set_amo_vel(ENEMY_AMO_VEL);
            p3_amo.setwidthheight(AMO_ENEMY_WIDTH,AMO_ENEMY_HEIGHT);
            p3_amo.setRect(this->mPosX+ENEMY_WIDTH/2,this->mPosY);
            p3_amo.set_is_move(true);
            p_amo_list.push_back(p3_amo);
        }
    }
}
void Enemy::move(  )
{
    if (bool_pause == false && bool_game_over == false && level_render_success==true && typemove == 0)
    {
                //Move the dot up or down
            if (enemy_type == ENEMY1)
            {
                mPosY += ENEMY_VEL_Y;
                Enemy_Rect.y = mPosY;

                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-300,-100);
                    is_move = true;
                    ENEMYHEART1_LOCAL=2;
                }

                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
            else if (enemy_type == ENEMY2)
            {
                mPosY += ENEMY_VEL_Y;
                Enemy_Rect.y = mPosY;

                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-150,-50);
                    ENEMYHEART2_LOCAL = 1;
                    is_move = true;
                }
                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
            else if (enemy_type == ENEMY3)
            {
                mPosY += ENEMY_VEL_Y;
                Enemy_Rect.y = mPosY;

                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-400,-100);
                    ENEMYHEART3_LOCAL = 1;
                    is_move = true;
                }
                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
        }
        else if (bool_pause == false && bool_game_over == false && level_render_success==true && typemove == 1)
    {
                //Move the dot up or down
            if (enemy_type == ENEMY1)
            {
                mPosY += (1);
                Enemy_Rect.y = mPosY;
                if (direction_ramdom ==-1)
                {
                    mPosX-=ENEMY_VEL_X;
                }
                else
                {
                    mPosX+=ENEMY_VEL_X;
                }
                if (mPosX>SCREEN_WIDTH-ENEMY_WIDTH) direction_ramdom=-1;
                else if (mPosX<0)direction_ramdom=1;
                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-300,-100);
                    is_move = true;
                    ENEMYHEART1_LOCAL=2;
                }

                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
            else if (enemy_type == ENEMY2)
            {
                mPosY += (1);
                Enemy_Rect.y = mPosY;
                if (direction_ramdom ==-1)
                {
                    mPosX-=ENEMY_VEL_X;
                }
                else
                {
                    mPosX+=ENEMY_VEL_X;
                }
                if (mPosX>SCREEN_WIDTH-ENEMY_WIDTH) direction_ramdom=-1;
                else if (mPosX<0)direction_ramdom=1;
                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-150,-50);
                    is_move = true;
                    ENEMYHEART2_LOCAL=2;
                }

                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
            else if (enemy_type == ENEMY3)
            {
                mPosY += (1);
                Enemy_Rect.y = mPosY;
                if (direction_ramdom ==-1)
                {
                    mPosX-=ENEMY_VEL_X;
                }
                else
                {
                    mPosX+=ENEMY_VEL_X;
                }
                if (mPosX>SCREEN_WIDTH-ENEMY_WIDTH) direction_ramdom=-1;
                else if (mPosX<0)direction_ramdom=1;
                //If the dot collided or went too far up or down

                if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT || is_move == false)
                {
                    mPosX = GetRandom(0,SCREEN_WIDTH-ENEMY_WIDTH);
                    mPosY = GetRandom(-400,-100);
                    is_move = true;
                    ENEMYHEART3_LOCAL=2;
                }

                Enemy_Rect.x=mPosX;
                Enemy_Rect.y=mPosY;
            }
        }
    }
void Enemy::special_move( )
{}

void Enemy::MakeAmo()
{
    if (bool_pause == false&& bool_game_over == false && level_render_success==true)
    {
            if (enemy_type == ENEMY2)
            {
                 //std::cout<<p_amo_list.size()<<" ";
                for (int i=0;i<p_amo_list.size();i++)
                {

                    if (p_amo_list[i].get_is_move()==true)
                    {
                        p_amo_list[i].move2();
                        p_amo_list[i].render2();

                    }

                    else
                    {
                        p_amo_list.erase(p_amo_list.begin()+i);
                    }


                }
            }


   // if (bool_pause == false&& bool_game_over == false)
            if (enemy_type == ENEMY3)
            {

            }

    }
}

void Enemy::render()
{
    if (bool_game_over == false && level_render_success==true)
    {
    if (enemy_type == ENEMY1)
    {
    //Show the dot
        SDL_Rect enemy1_rect;
        enemy1_rect.x=47;
        enemy1_rect.y=53;
        enemy1_rect.w=388;
        enemy1_rect.h=404;
        gEnemy1Texture[step_img_enemy1].render( mPosX, mPosY, ENEMY_WIDTH, ENEMY_HEIGHT );

        if (count_img_enemy1>SPEED_ANIMATION) {step_img_enemy1++;count_img_enemy1=1;}
        count_img_enemy1++;
        if (step_img_enemy1>=NUM_IMG_ENEMY1) step_img_enemy1=0;
    }
    else if (enemy_type == ENEMY2)
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
        if (step_img_enemy2 >= NUM_IMG_ENEMY2) step_img_enemy2 = 0;
    }
    else if (enemy_type == ENEMY3)
    {

    //Show the dot
        SDL_Rect enemy3_rect;
        enemy3_rect.x=60;
        enemy3_rect.y=230;
        enemy3_rect.w=186;
        enemy3_rect.h=173;
        gEnemy3Texture[step_img_enemy3].render( mPosX, mPosY, ENEMY_WIDTH, ENEMY_HEIGHT ,&enemy3_rect);

        if (count_img_enemy3>SPEED_ANIMATION) {step_img_enemy3++;count_img_enemy3=1;}
        count_img_enemy3++;
        if (step_img_enemy3 >= NUM_IMG_ENEMY3) step_img_enemy3 = 0;
    }
    }
}

void Enemy::die_render()
{
     if (bool_game_over == false && explosion == true && level_render_success==true )
    {
        gExplosion[step_img_explosion].render( mPosX-20, mPosY-20, ENEMY_WIDTH+40, ENEMY_HEIGHT+40 );
        //std::cout<<step_img_explosion;
        if (count_img_explosion>SPEED_ANIMATION) {step_img_explosion++;count_img_explosion=1;}
        count_img_explosion++;
        if (step_img_explosion >= NUM_IMG_EXPLOSION) {step_img_explosion = 0;explosion=false;}
    }
}
#endif // ENEMY_H_
