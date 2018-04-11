#pragma once
#include <iostream>
using namespace std;

//�������˶�����
enum enumDir
{
	DIR_UP = 5,
	DIR_DOWN = 7,
	DIR_LEFT = 2,
	DIR_RIGHT = 3,
	DIR_NO   = 4,
};

//�������WASD
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


//��ɫ
enum enumColor
{
	COLOR_BLACK = 0,

	COLOR_PINK = 13,

	COLOR_RED = 12, //�ʺ�
	COLOR_RED_LIGHT = 4, //����

	COLOR_YELLOW = 14,
	COLOR_YELLOW_LIGHT = 6,

	COLOR_BLUE = 9,
	COLOR_BLUE_LIGHT = 1, 

	COLOR_GREEN = 10,
	COLOR_GREEN_LIGHT = 2,

	COLOR_WHITE = 15,
	COLOR_GRAY = 8,
};

//��״
enum enumShape
{
	SHAPE_SQUARE_SOLID,  //ʵ�ķ���"��" 
	SHAPE_SQUARE_HOLLOW,  // ���ķ���"��"
	SHAPE_CIRCLE_SOLID,//ʵ��Բ��
	SHAPE_IMG_STAR,    // ��
	SHAPE_WALL_SOLID,
	SHAPE_IMG_X ,//X
	SHAPE_IMG_FLOWER, //��
};
//����������� ��� ����$
#define SQUARE_SOLID  "" 
#define SQUARE_HOLLOW  "��"
#define CIRCLE_SOLID   "��"
#define IMG_STAR  "��"
#define WALL_SOLID   "��"
#define IMG_FLOWER  "��"
#define IMG_X  "X"

//��ǽ�ĳߴ�
#define WALL_WIDTH  50  //ǽ�ڵĿռ�ߴ�
#define WALL_HEIGHT   34

//extern int g_nGameSleepTime;  //no use
//extern int g_nScore;


