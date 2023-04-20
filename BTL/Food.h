#ifndef FOOD_H_
#define FOOD_H_
class Food
{
    public:
        enum FoodType
        {
            HEART = 0,
            RED_ORB = 1,
            YELLOW_ORB = 2,
            PURPLE_ORB = 3
        };
        static const int FOOD_WIDTH =30;
		static const int FOOD_HEIGHT = 30;

		//Maximum axis velocity of the dot
		static const int FOOD_VEL = 2;

		//Initializes the variables
		Food();
        //~Food();
		//Moves the dot and checks collision
		void move(SDL_Rect a);

		//Shows the dot on the screen
		void render();

        void set_type( int a) {food_type=a;}
        int get_type () {return food_type;}
		SDL_Rect getRect() {return Food_Rect;}
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		//Dot's collision box
		SDL_Rect Food_Rect;

		int food_type;
        int step_img_food_heart=0;
        int count_img_food_heart=1;

        int step_img_red_orb=0;
        int count_img_red_orb=1;

        int step_img_yellow_orb=0;
        int count_img_yellow_orb=1;

        int step_img_purple_orb=0;
        int count_img_purple_orb=1;
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
    if (bool_pause == false&& bool_game_over == false)
    {
        if (food_type == HEART)
        {
            mPosY+=mVelY;
            Food_Rect.x=mPosX;
            Food_Rect.y=mPosY;
            if (mPosY+FOOD_HEIGHT>=SCREEN_HEIGHT )
            {
                mPosY = -50;
                mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);
                count_appear_food1=0;
            }
            if (checkCollision(Food_Rect,a))
            {
                Mix_PlayChannel( -1, gPickItem, 0 );
                DOT_HEART++;
                if (DOT_HEART>MAX_DOT_HEART) DOT_HEART = MAX_DOT_HEART;
                mPosY = -50;
                mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);
                count_appear_food1=0;

            }
        }

         if (food_type == RED_ORB || food_type == YELLOW_ORB || food_type == PURPLE_ORB)
        {
            mPosY+=mVelY;
            Food_Rect.x=mPosX;
            Food_Rect.y=mPosY;
            if (mPosY+FOOD_HEIGHT>=SCREEN_HEIGHT )
            {
                mPosY = -50;
                mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);
                count_appear_special_food = 0;
                food_type=GetRandom(1,3);
            }
            if (checkCollision(Food_Rect,a))
            {
                //std::cout<<food_type;
                type_amo=food_type;
                Mix_PlayChannel( -1, gPickItem, 0 );
                mPosY = -50;
                mPosX=GetRandom(0,SCREEN_WIDTH-FOOD_WIDTH);
                count_appear_special_food=0;
                count_remain_special_amo=0;
                food_type= (GetRandom(1,3));

            }
        }
    }
}

void Food::render()
{
    //HEART
    if (food_type == HEART )
    {
        SDL_Rect food_1;
        food_1.x=164;
        food_1.y=117;
        food_1.w=65;
        food_1.h=61;
        gFoodTexture1[step_img_food_heart].render( mPosX, mPosY, FOOD_WIDTH, FOOD_HEIGHT ,&food_1);
        if (count_img_food_heart>SPEED_ANIMATION) {step_img_food_heart++;count_img_food_heart=1;}
        count_img_food_heart++;
        if (step_img_food_heart>=NUM_IMG_FOOD_HEART) step_img_food_heart=0;
    }
    //RED_ORB
    if (food_type == RED_ORB )
    {
        SDL_Rect red_rect;
        red_rect.x=97;
        red_rect.y=95;
        red_rect.w=299;
        red_rect.h=302;
        gFoodTexture_Red[step_img_red_orb].render( mPosX, mPosY, FOOD_WIDTH, FOOD_HEIGHT ,&red_rect);
        if (count_img_red_orb>SPEED_ANIMATION) {step_img_red_orb++;count_img_red_orb=1;}
        count_img_red_orb++;
        if (step_img_red_orb>=NUM_IMG_FOOD_RED) step_img_red_orb=0;
    }
    //YELLOW_ORB
    if (food_type == YELLOW_ORB )
    {
        SDL_Rect yellow_rect;
        yellow_rect.x=82;
        yellow_rect.y=64;
        yellow_rect.w=271;
        yellow_rect.h=274;
        gFoodTexture_Yellow[step_img_yellow_orb].render( mPosX, mPosY, FOOD_WIDTH, FOOD_HEIGHT ,&yellow_rect);
        if (count_img_yellow_orb>SPEED_ANIMATION) {step_img_yellow_orb++;count_img_yellow_orb=1;}
        count_img_yellow_orb++;
        if (step_img_yellow_orb>=NUM_IMG_FOOD_YELLOW) step_img_yellow_orb=0;
    }
    //PURPLE_ORB
    if (food_type == PURPLE_ORB )
    {
        SDL_Rect purple_rect;
        purple_rect.x=17;
        purple_rect.y=18;
        purple_rect.w=283;
        purple_rect.h=285;
        gFoodTexture_Purple[step_img_purple_orb].render( mPosX, mPosY, FOOD_WIDTH, FOOD_HEIGHT ,&purple_rect);
        if (count_img_purple_orb>SPEED_ANIMATION) {step_img_purple_orb++;count_img_purple_orb=1;}
        count_img_purple_orb++;
        if (step_img_purple_orb>=NUM_IMG_FOOD_PURPLE) step_img_purple_orb=0;
    }

}
#endif // FOOD_H_
