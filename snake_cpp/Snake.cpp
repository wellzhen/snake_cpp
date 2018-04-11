#include "Snake.h"
#include "Data.h"
#include <conio.h>
#include "Ctrl.h"


CSnake::CSnake()
{
	//初始化蛇头
	short posX = WALL_WIDTH - 4; //必须是偶数
	short posY = 5;
	m_vecCobra.push_back(new CGraph(posX, posY));
	//初始化方向
	if (WALL_HEIGHT / 2 > posY) {
		m_vecCobra[0]->setDir(DIR_DOWN);
	}
	else {
		m_vecCobra[0]->setDir(DIR_UP);
	}
}

void CSnake::importMap(CMap  map)
{
	m_nMap = map;
}

CMap CSnake::getMap()
{
	return m_nMap;
}



void CSnake::show()
{
	for (unsigned int i = 0; i <  m_vecCobra.size(); i++) {
		if (i == 0) {//蛇头
			m_vecCobra[i]->setColor(COLOR_GREEN);
			m_vecCobra[i]->setShape(SHAPE_CIRCLE_SOLID);
		}
		else {
			m_vecCobra[i]->setColor(COLOR_GREEN_LIGHT);
			m_vecCobra[i]->setShape(SHAPE_CIRCLE_SOLID);
			
		}
		m_vecCobra[i]->show();
	}
}

void CSnake::showDie()
{
	if (m_nScore <= 1) {
		PlaySoundA("sound\\die.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	else if (m_nScore <= 2) {
		PlaySoundA("sound\\die2.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	else {
		PlaySoundA("sound\\die5.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	
	for (unsigned int i = 0; i < m_vecCobra.size(); i++) {
		if (i == 0) {//蛇头
			m_vecCobra[0]->setColor(COLOR_WHITE);
			m_vecCobra[i]->setShape(SHAPE_CIRCLE_SOLID);
			m_vecCobra[i]->show();
		}
		else {
			m_vecCobra[i]->setColor(COLOR_GRAY);
			m_vecCobra[0]->setShape(SHAPE_CIRCLE_SOLID);
			m_vecCobra[i]->show();
		}
	}
}

void CSnake::hide()
{
	for (unsigned int i = 0; i <  m_vecCobra.size(); i++) {
		m_vecCobra[i]->hide();
	}
}

int CSnake::waitKey()
{
	if (_kbhit()) {
		return _getch();
	}
	return 0;
}

enumDir  CSnake::operate(int keyNum)
{
	
	enumDir moveDir;//将要移动到的方向
	int operation = 0;

	if (keyNum == 0) {
		return DIR_NO;
	}
	operation = 0;
	switch (keyNum) {
	case enumWASD::KEYBOARD_W:
		moveDir = DIR_UP;
		operation = 1; //移动
		break;
	case enumWASD::KEYBOARD_A:
		moveDir = DIR_LEFT;
		operation = 1;
		break;
	case enumWASD::KEYBOARD_S:
		moveDir = DIR_DOWN;
		operation = 1;
		break;
	case enumWASD::KEYBOARD_D:
		moveDir = DIR_RIGHT;
		operation = 1;
		break;
	default:
		break;
	}

	if (operation != 1) {
		//continue;
		return DIR_NO;
	}
	//按了移动键
	return moveDir;

	//如果moveDir存在， 则为移动蛇
	//forward(moveDir);
		

}

void  CSnake::forward(enumDir dir)
{
	//变长
	bool isGrow = grow(dir);
	int foodIndex = monitorEatedFood();

	if (isGrow && foodIndex != -1) {
		//头变长 且吃到了食物
		PlaySoundA("sound\\food.wav", NULL, SND_FILENAME | SND_ASYNC);
		switch (m_vecFoods[foodIndex]->getAffect()) {
		case FOOD_INCREASE_SPEED: 
			increaseSpeed();//加速
			break;
		case FOOD_DECREASE_SPEED:
			decreaseSpeed(); //减速
			break;
		case FOOD_INCREASE_BODY:
							 //变长
			break;
		case  FOOD_DECREASE_BODY:
			m_vecCobra.pop_back();//变短
			if (m_vecCobra.size() > 1) {
				m_vecCobra.pop_back();//变短
			}
			
			break;
		default:
			//
			break;
		}

		m_vecFoods[foodIndex]->hide(); //隐藏
		m_vecFoods.erase(m_vecFoods.begin() + foodIndex);  //移除吃掉的食物

	} else if(isGrow &&  foodIndex == -1){
		//长大了却没有吃到食物：移除蛇尾
		PlaySoundA("sound\\footstep.wav", NULL, SND_FILENAME | SND_ASYNC);
		m_vecCobra.pop_back();
	}

}

bool CSnake::willDieByMap(enumDir dir)
{
	//蛇头要移动到的坐标
	short headDestPosX = getHeadDestPosX(dir);
	short headDestPosY = getHeadDestPosY(dir);

	//判断是否碰到了围墙
	vector<CGraph * >  vecWall = m_nMap.getVecWall();
	for (unsigned int i = 0; i < vecWall.size(); i++) {
		if (vecWall[i]->getPosX() == headDestPosX && vecWall[i]->getPosY() == headDestPosY) {
			return true;//死了
		}
	}

	//判断是否碰到了障碍物
	vector<CGraph * >  vecDangerBlock = m_nMap.getVecDangerBlock();
	for (unsigned int i = 0; i < vecDangerBlock.size(); i++) {
		if (vecDangerBlock[i]->getPosX() == headDestPosX && vecDangerBlock[i]->getPosY() == headDestPosY) {
			return true;//死了
		}
	}
	return false;

}

bool CSnake::eatSelf(enumDir dir)
{
	//蛇头要移动到的坐标
	short headDestPosX = getHeadDestPosX(dir);
	short headDestPosY = getHeadDestPosY(dir);

	if (m_vecCobra.size() <= 4) {
		return false;
	}
	for (unsigned int i = 3; i < m_vecCobra.size(); i++) {
		if (m_vecCobra[i]->getPosX() == headDestPosX && m_vecCobra[i]->getPosY() == headDestPosY) {
			return true;
		}
	}

	return false;
}

bool CSnake::grow(enumDir dir)
{
	//蛇头要移动到的坐标
	short headDestPosX = getHeadDestPosX(dir);
	short headDestPosY = getHeadDestPosY(dir);

	headDestPosX = headDestPosX > 0 ? headDestPosX : 0;
	headDestPosY = headDestPosY > 0 ? headDestPosY : 0;

	//如果头移向了身体，则不操作
	if (m_vecCobra.size() > 1) {
		if (headDestPosX == m_vecCobra[1]->getPosX() && headDestPosY == m_vecCobra[1]->getPosY()) {
			PlaySoundA("sound\\wrong.wav", NULL, SND_FILENAME | SND_SYNC);
			return false;
		}
	}

	//创建一个新的块，插入头部
	CGraph * newHead = new CGraph(headDestPosX, headDestPosY);
	//设置头的方向属性
	newHead->setDir(dir);
	//插入新蛇头
	m_vecCobra.insert(m_vecCobra.begin(), newHead);
	return true;
}


short CSnake::getHeadDestPosX(enumDir dir)
{
	//当前蛇头的坐标
	short headPosX = m_vecCobra[0]->getPosX();
	//根据方向确定新蛇头的坐标
	switch (dir)
	{
	case  enumDir::DIR_UP:
		break;
	case enumDir::DIR_DOWN:
		break;
	case enumDir::DIR_LEFT:
		headPosX -= 2;
		break;
	case enumDir::DIR_RIGHT:
		headPosX += 2;
		break;
	default:
		//Never happen
		cout << "传入的方向错误1" << endl;
		break;
	}
	return headPosX;
}

short CSnake::getHeadDestPosY(enumDir dir)
{
	//当前蛇头的坐标
	short headPosY = m_vecCobra[0]->getPosY();
	//根据方向确定新蛇头的坐标
	switch (dir)
	{
	case  enumDir::DIR_UP:
		headPosY--;
		break;
	case enumDir::DIR_DOWN:
		headPosY++;
		break;
	case enumDir::DIR_LEFT:
		break;
	case enumDir::DIR_RIGHT:
		break;
	default:
		//Never happen
		cout << "传入的方向错误2" << endl;
		break;
	}
	return headPosY;
}


bool CSnake::giveFood(CFood* food)
{
	//如果当前坐标有食物，拒绝加入
	for (unsigned int i = 0; i < m_vecFoods.size(); i++) {
		if (food->getPosX() == m_vecFoods[i]->getPosX()
			&& food->getPosY() == m_vecFoods[i]->getPosY()) {
			return false;
		}
		
	}
	//如果与蛇身体重合，拒绝加入
	for (unsigned int i = 0; i < m_vecCobra.size(); i++) {
		if (m_vecCobra[i]->getPosX() == food->getPosX() && m_vecCobra[i]->getPosY() == food->getPosY()) {
			return false;
		}
	}
	//如果与障碍物重合，拒绝加入
	vector<CGraph *> blocks = m_nMap.getVecDangerBlock();
	for (unsigned int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->getPosX() == food->getPosX() && blocks[i]->getPosY() == food->getPosY()) {
			return false;
		}
	}
	


	food->show();
	m_vecFoods.push_back(food);
	return true;
}


bool CSnake::hasEnoughFood(int amount)
{
	if (m_vecFoods.size() < amount) {
		return  false;
	}
	else {
		return true;
	}
}

int CSnake::monitorEatedFood()
{
	unsigned int index = -1;
	short newHeadPosX = m_vecCobra[0]->getPosX();
	short newHeadPosY = m_vecCobra[0]->getPosY();

	for (unsigned int i = 0; i < m_vecFoods.size(); i++) {
		if (m_vecFoods[i]->getPosX() == m_vecCobra[0]->getPosX() && m_vecFoods[i]->getPosY() == m_vecCobra[0]->getPosY()) {
			index = i; //吃到了
			addScore(1);//加分
			break;
		}
	}
	return index;

}

void CSnake::addScore(int addNum) {
	m_nScore += addNum;
}
int CSnake::getScore() {
	return m_nScore;
}

void CSnake::setScore(int newScore)
{
	m_nScore = newScore;
}

void CSnake::setVecCobra(vector<CGraph *> newVecCobra)
{
	m_vecCobra = newVecCobra;
}

vector<CGraph *>  CSnake::getVecCobra()
{
	return m_vecCobra;
}

vector<CFood *> CSnake::getVecFoods()
{
	return m_vecFoods;
}


//速度相关
void CSnake::setSpeed(int speed)
{
	m_nSpeed = speed;
}
int CSnake::getSpeed()
{
	return m_nSpeed;
}
void CSnake::increaseSpeed()
{
	if (m_nSpeed < 70) {
		m_nSpeed += 5;
	}
	else if (m_nSpeed < 80) {
		m_nSpeed += 4;
	}
	else if (m_nSpeed < 90) {
		m_nSpeed += 3;
	}
	else if (m_nSpeed < 100) {
		m_nSpeed += 2;
	}
	
	//限制最高
	if (m_nSpeed >= 100) {
		m_nSpeed = 100;
	}
}
void CSnake::decreaseSpeed()
{
	m_nSpeed-=1;
	if (m_nSpeed <= 1) {
		m_nSpeed = 1;
	}
}

int CSnake::getSleepTime()
{
	return (101 - getSpeed()) * 10;
}

CSnake::~CSnake()
{
}
