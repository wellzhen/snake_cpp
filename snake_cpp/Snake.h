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
	//�����ͼ
	void importMap(CMap  map);

	//������ͼ
	CMap CSnake::getMap();

	//��ʾ�ߵ�ͼ��
	void show();

	//������ɫ
	void CSnake::showDie();

	//�����ߵ�ͼ��
	void hide();

	//�ȴ��û�����
	int waitKey();

	//������
	enumDir  operate(int keyNum);  // ������
	
	//ǰ��
	void  forward(enumDir dir);

	//���ݵ�ͼ�ж��Ƿ��� true: ����
	bool willDieByMap(enumDir dir);

	//�ж��Ƿ�Ҫ�Ե��Լ�
	bool eatSelf(enumDir dir);

	//Ͷ��һ��ʳ��
	bool giveFood(CFood* food);

	//�ж��Ƿ����㹻��ʳ��;
	bool hasEnoughFood(int amount = 1);

	//������Ƿ�Ҫ�Ե�ʳ�� �� ʳ����±�
	int monitorEatedFood();

	//�ָ�������
	void setVecCobra(vector<CGraph *> newVecCobra);

	vector<CGraph *> getVecCobra();
	vector<CFood *> getVecFoods();
	void addScore(int addNum);
	int getScore();
	void setScore(int newScore);

	//�ٶ����
	void setSpeed(int speed);
	int  getSpeed();
	void increaseSpeed();
	void decreaseSpeed();
	int getSleepTime();

	~CSnake();
private:
	//�䳤
	bool grow(enumDir dir);

	short getHeadDestPosX(enumDir dir); //��getHeadDestPosYͬʱʹ��
	short getHeadDestPosY(enumDir dir);

	

private:
	vector<CGraph *> m_vecCobra;
	vector<CFood *>  m_vecFoods;
	CMap  m_nMap;
	int m_nScore;
	int m_nSpeed; //��Χ1-10m/s  ��101-speed) * 10
	
};

