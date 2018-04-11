#pragma once
#include <iostream>
using namespace std;

//控制蛇运动方向
enum enumDir
{
	DIR_UP = 5,
	DIR_DOWN = 7,
	DIR_LEFT = 2,
	DIR_RIGHT = 3,
	DIR_NO   = 4,
};

//方向控制WASD
enum enumWASD
{
	KEYBOARD_W =  119,
	KEYBOARD_S = 115,
	KEYBOARD_A = 97,
	KEYBOARD_D = 100,
};

enum enumFoodAffect
{
	FOOD_INCREASE_SPEED = 0,
	FOOD_INCREASE_BODY = 1 ,

	FOOD_DECREASE_SPEED = 2,
	FOOD_DECREASE_BODY = 3,
};


//颜色
enum enumColor
{
	COLOR_BLACK = 0,

	COLOR_PINK = 13,

	COLOR_RED = 12, //鲜红
	COLOR_RED_LIGHT = 4, //暗红

	COLOR_YELLOW = 14,
	COLOR_YELLOW_LIGHT = 6,

	COLOR_BLUE = 9,
	COLOR_BLUE_LIGHT = 1, 

	COLOR_GREEN = 10,
	COLOR_GREEN_LIGHT = 2,

	COLOR_WHITE = 15,
	COLOR_GRAY = 8,
};

//形状
enum enumShape
{
	SHAPE_SQUARE_SOLID,  //实心方块"■" 
	SHAPE_SQUARE_HOLLOW,  // 空心方块"□"
	SHAPE_CIRCLE_SOLID,//实心圆●
	SHAPE_IMG_STAR,    // ★
	SHAPE_WALL_SOLID,
	SHAPE_IMG_X ,//X
	SHAPE_IMG_FLOWER, //※
};
//Ⅹ▲◆◇△▽ ★☆ ※×$
#define SQUARE_SOLID  "" 
#define SQUARE_HOLLOW  "□"
#define CIRCLE_SOLID   "●"
#define IMG_STAR  "★"
#define WALL_SOLID   "■"
#define IMG_FLOWER  "※"
#define IMG_X  "X"

//外墙的尺寸
#define WALL_WIDTH  50  //墙内的空间尺寸
#define WALL_HEIGHT   34

//extern int g_nGameSleepTime;  //no use
//extern int g_nScore;


