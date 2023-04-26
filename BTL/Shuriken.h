#ifndef SHURIKEN_H_
#define SHURIKEN_H_
class Shuriken
{
    public:

        int SHURIKEN_WIDTH = 20;//me
        int SHURIKEN_HEIGHT = 40;//me
        static const int SHURIKEN2_WIDTH = 20;//enemy
		static const int SHURIKEN2_HEIGHT = 40;//enemy
		//Maximum axis velocity of the dot
        int SHURIKEN_VEL = 5;
        enum Shuriken_Type
        {
            COMMON = 0,
            Shuriken1 = 1,//red
            Shuriken2 = 2,//yellow
            Shuriken3 = 3//purple
        };
		//Initializes the variables
		Shuriken();
        ~Shuriken();
		//Moves the dot and checks collision
		void move();
        void set_amo_vel( int x) {SHURIKEN_VEL=x;}
		//Shows the dot on the screen
		void render();//minh
		void render2();//dich
        void move2();
		SDL_Rect getRect() {return Shuriken_Rect;}
		void setRect(const int &x, const int &y) {mPosX=x;mPosY=y;}
		bool get_is_move() {return is_move;}
		void set_is_move(bool a) {is_move=a;}
		void setwidthheight(int a,int b){Shuriken_Rect.w=a;Shuriken_Rect.h=b;}
        void set_shurikentype (int a) {shuriken_type = a;}
        int get_shurikentype () {return shuriken_type;}

    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

        int save_mPosY;
        bool is_move;
		//Dot's collision box
		SDL_Rect Shuriken_Rect;
		int shuriken_type;

		int step_img_amo_dot=0;
        int step_img_amo_enemy2=0;
        int step_img_amo_red =0;
        int step_img_amo_yellow =0;
        int step_img_amo_purple =0;

        int count_img_amo_dot=1;
        int count_img_amo_enemy2=1;
        int count_img_amo_red=1;
        int count_img_amo_yellow=1;
        int count_img_amo_purple=1;
};
Shuriken::Shuriken()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    shuriken_type = 0;
	//Set collision box dimension
	Shuriken_Rect.w = SHURIKEN_WIDTH;
	Shuriken_Rect.h = SHURIKEN_HEIGHT;

    is_move = false;
    //Initialize the velocityGet
    mVelX = 0;
    mVelY = 0;
}
Shuriken::~Shuriken()
{

    mPosX = 0;
    mPosY = 0;


	//Set collision box dimension
	Shuriken_Rect.w = 0;
	Shuriken_Rect.h = 0;

    is_move = false;
    //Initialize the velocityGet
    mVelX = 0;
    mVelY = 0;
}

//me
void Shuriken::move()
{
    if (bool_pause == false&& bool_game_over == false)
    {
        if (shuriken_type == 0 )
        {
            SHURIKEN_WIDTH = 20;
            SHURIKEN_HEIGHT = 40;
            mPosY-=SHURIKEN_VEL;
            if (mPosY<=0) {is_move=false;}
            Shuriken_Rect.x=mPosX;
            Shuriken_Rect.y=mPosY;

        }
        else if (shuriken_type == 1 || shuriken_type == 2 || shuriken_type == 3)
        {
            SHURIKEN_WIDTH = 40;
            SHURIKEN_HEIGHT = 80;
            mPosY-=SHURIKEN_VEL;
            if (mPosY<=0) {is_move=false;}
            Shuriken_Rect.x=mPosX;
            Shuriken_Rect.y=mPosY;
        }
    }
}
//enemy
void Shuriken::move2()
{
    if (bool_pause == false&& bool_game_over == false)
    {
        mPosY+=SHURIKEN_VEL;
        if (mPosY+SHURIKEN_HEIGHT>=SCREEN_HEIGHT || mPosY<0) {is_move=false;}
        Shuriken_Rect.x=mPosX;
        Shuriken_Rect.y=mPosY;
    }


}

void Shuriken::render()//ta
{
    if (bool_game_over == false)
    {

    if (shuriken_type == 0)
    {
        SDL_Rect amo_dot;
        amo_dot.x=55;
        amo_dot.y=302;
        amo_dot.w=66;
        amo_dot.h=148;
        gShurikenTexture[step_img_amo_dot].render( mPosX, mPosY,SHURIKEN_WIDTH,SHURIKEN_HEIGHT, &amo_dot );
        if (count_img_amo_dot>SPEED_ANIMATION) {step_img_amo_dot++;count_img_amo_dot=1;}
        count_img_amo_dot++;
        if (step_img_amo_dot >= NUM_IMG_AMO_DOT) step_img_amo_dot = 0;
    }
    else if (shuriken_type == 1)//red;
    {
        SDL_Rect amo_red;
        amo_red.x=250;
        amo_red.y=157;
        amo_red.w=98;
        amo_red.h=413;
        gShurikenTexture_SPECIAL[step_img_amo_red].render( mPosX, mPosY,SHURIKEN_WIDTH,SHURIKEN_HEIGHT, &amo_red );
        if (count_img_amo_red>SPEED_ANIMATION) {step_img_amo_red++;count_img_amo_red=1;}
        count_img_amo_red++;
        if (step_img_amo_red >= NUM_IMG_SPECIAL_AMO) step_img_amo_red = 0;
    }
    else if (shuriken_type == 2)
    {
        SDL_Rect amo_yellow;
        amo_yellow.x=125;
        amo_yellow.y=153;
        amo_yellow.w=87;
        amo_yellow.h=430;
        gShurikenTexture_SPECIAL[step_img_amo_yellow].render( mPosX, mPosY,SHURIKEN_WIDTH,SHURIKEN_HEIGHT, &amo_yellow );
        if (count_img_amo_yellow>SPEED_ANIMATION) {step_img_amo_yellow++;count_img_amo_yellow=1;}
        count_img_amo_yellow++;
        if (step_img_amo_yellow >= NUM_IMG_SPECIAL_AMO) step_img_amo_yellow = 0;
    }
    else if (shuriken_type == 3)
    {
        SDL_Rect amo_purple;
        amo_purple.x=8;
        amo_purple.y=151;
        amo_purple.w=103;
        amo_purple.h=422;
        gShurikenTexture_SPECIAL[step_img_amo_purple].render( mPosX, mPosY,SHURIKEN_WIDTH,SHURIKEN_HEIGHT, &amo_purple );
        if (count_img_amo_purple>SPEED_ANIMATION) {step_img_amo_purple++;count_img_amo_purple=1;}
        count_img_amo_purple++;
        if (step_img_amo_purple >= NUM_IMG_SPECIAL_AMO) step_img_amo_purple = 0;
    }
    }
}
void Shuriken::render2()//dich
{
    if (bool_game_over == false)
    {
    SDL_Rect amo_enemy2;
    amo_enemy2.x=132;
    amo_enemy2.y=273;
    amo_enemy2.w=99;
    amo_enemy2.h=123;
	gShuriken2Texture[step_img_amo_enemy2].render( mPosX, mPosY, SHURIKEN2_WIDTH, SHURIKEN2_HEIGHT, &amo_enemy2 );
	if (count_img_amo_enemy2>SPEED_ANIMATION) {step_img_amo_enemy2++;count_img_amo_enemy2=1;}
	count_img_amo_enemy2++;
	if (step_img_amo_enemy2 >= NUM_IMG_AMO_ENEMY2) step_img_amo_enemy2 = 0;
    }
}
#endif // SHURIKEN_H_
