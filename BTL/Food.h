#ifndef FOOD_H_
#define FOOD_H_
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
		static const int FOOD_VEL = 3;

		//Initializes the variables
		Food();
        //~Food();
		//Moves the dot and checks collision
		void move(SDL_Rect a);

		//Shows the dot on the screen
		void render();

        void set_type(unsigned int &a) {food_type=a;}
        int get_type () {return food_type;}
		SDL_Rect getRect() {return Food_Rect;}
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Food_Rect;

		unsigned int food_type;
};
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
    if (mPosY>=SCREEN_HEIGHT) {mPosY = 0;mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);}
    if (checkCollision(Food_Rect,a)) {mPosY = 0;mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);}
}

void Food::render()
{
    //Show the dot
	gFoodTexture.render( mPosX, mPosY, FOOD_WIDTH, FOOD_HEIGHT );
}
#endif // FOOD_H_
