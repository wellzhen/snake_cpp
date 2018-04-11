#pragma once
#include <vector>
#include "Graph.h"
#include "Food.h"
#include "Map.h"

using std::vector;

class CSnake
{
public:
	CSnake();
	//导入地图
	void importMap(CMap  map);

	//导出地图
	CMap CSnake::getMap();

	//显示蛇的图形
	void show();

	//死亡变色
	void CSnake::showDie();

	//隐藏蛇的图形
	void hide();

	//等待用户输入
	int waitKey();

	//操作蛇
	enumDir  operate(int keyNum);  // 操作蛇
	
	//前进
	void  forward(enumDir dir);

	//根据地图判断是否将死 true: 死了
	bool willDieByMap(enumDir dir);

	//判断是否将要吃到自己
	bool eatSelf(enumDir dir);

	//投递一份食物
	bool giveFood(CFood* food);

	//判断是否还有足够的食物;
	bool hasEnoughFood(int amount = 1);

	//监控蛇是否要吃到食物 ： 食物的下标
	int monitorEatedFood();

	//恢复、导入
	void setVecCobra(vector<CGraph *> newVecCobra);

	vector<CGraph *> getVecCobra();
	vector<CFood *> getVecFoods();
	void addScore(int addNum);
	int getScore();
	void setScore(int newScore);

	//速度相关
	void setSpeed(int speed);
	int  getSpeed();
	void increaseSpeed();
	void decreaseSpeed();
	int getSleepTime();

	~CSnake();
private:
	//变长
	bool grow(enumDir dir);

	short getHeadDestPosX(enumDir dir); //与getHeadDestPosY同时使用
	short getHeadDestPosY(enumDir dir);

	

private:
	vector<CGraph *> m_vecCobra;
	vector<CFood *>  m_vecFoods;
	CMap  m_nMap;
	int m_nScore;
	int m_nSpeed; //范围1-10m/s  （101-speed) * 10
	
};

