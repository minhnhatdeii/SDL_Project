#ifndef SHURIKEN_H_
#define SHURIKEN_H_
class Shuriken
{
    public:

        static const int SHURIKEN_WIDTH = 20;
		static const int SHURIKEN_HEIGHT = 20;

		//Maximum axis velocity of the dot
        int SHURIKEN_VEL = 10;

		//Initializes the variables
		Shuriken();
        ~Shuriken();
		//Moves the dot and checks collision
		void move();
        void set_amo_vel(const int &x) {SHURIKEN_VEL=x;}
		//Shows the dot on the screen
		void render();//minh
		void render2();//dich
        void move2(const int & x_border,const int & y_border);
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

        int save_mPosY;
        bool is_move;
		//Dot's collision box
		SDL_Rect Shuriken_Rect;


};
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
    //Move the dot left or right
    mPosY-=SHURIKEN_VEL;

    if (mPosY<=0 && dot_amo_rate>=limit_dot_amo) {is_move=false;dot_amo_rate=0;}
    Shuriken_Rect.x=mPosX;
    Shuriken_Rect.y=mPosY;


}
//enemy
void Shuriken::move2(const int & x_border,const int & y_border)
{
    //Move the dot left or right
    mPosY+=SHURIKEN_VEL;
    if (mPosY+SHURIKEN_HEIGHT>=SCREEN_HEIGHT && enemy_amo_rate>=limit_enemy_amo) {is_move=false;enemy_amo_rate=0;}
    Shuriken_Rect.x=mPosX;
    Shuriken_Rect.y=mPosY;


}
void Shuriken::render()//ta
{
    //Show the dot
	gShurikenTexture.render( mPosX, mPosY );
}
void Shuriken::render2()//dich
{
    //Show the dot
	gShuriken2Texture.render( mPosX, mPosY );
}
#endif // SHURIKEN_H_
