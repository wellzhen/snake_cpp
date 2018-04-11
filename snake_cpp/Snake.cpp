#include "Snake.h"
#include "Data.h"
#include <conio.h>
#include "Ctrl.h"


CSnake::CSnake()
{
	//��ʼ����ͷ
	short posX = WALL_WIDTH - 4; //������ż��
	short posY = 5;
	m_vecCobra.push_back(new CGraph(posX, posY));
	//��ʼ������
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
		if (i == 0) {//��ͷ
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
		if (i == 0) {//��ͷ
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
	
	enumDir moveDir;//��Ҫ�ƶ����ķ���
	int operation = 0;

	if (keyNum == 0) {
		return DIR_NO;
	}
	operation = 0;
	switch (keyNum) {
	case enumWASD::KEYBOARD_W:
		moveDir = DIR_UP;
		operation = 1; //�ƶ�
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
	//�����ƶ���
	return moveDir;

	//���moveDir���ڣ� ��Ϊ�ƶ���
	//forward(moveDir);
		

}

void  CSnake::forward(enumDir dir)
{
	//�䳤
	bool isGrow = grow(dir);
	int foodIndex = monitorEatedFood();

	if (isGrow && foodIndex != -1) {
		//ͷ�䳤 �ҳԵ���ʳ��
		PlaySoundA("sound\\food.wav", NULL, SND_FILENAME | SND_ASYNC);
		switch (m_vecFoods[foodIndex]->getAffect()) {
		case FOOD_INCREASE_SPEED: 
			increaseSpeed();//����
			break;
		case FOOD_DECREASE_SPEED:
			decreaseSpeed(); //����
			break;
		case FOOD_INCREASE_BODY:
							 //�䳤
			break;
		case  FOOD_DECREASE_BODY:
			m_vecCobra.pop_back();//���
			if (m_vecCobra.size() > 1) {
				m_vecCobra.pop_back();//���
			}
			
			break;
		default:
			//
			break;
		}

		m_vecFoods[foodIndex]->hide(); //����
		m_vecFoods.erase(m_vecFoods.begin() + foodIndex);  //�Ƴ��Ե���ʳ��

	} else if(isGrow &&  foodIndex == -1){
		//������ȴû�гԵ�ʳ��Ƴ���β
		PlaySoundA("sound\\footstep.wav", NULL, SND_FILENAME | SND_ASYNC);
		m_vecCobra.pop_back();
	}

}

bool CSnake::willDieByMap(enumDir dir)
{
	//��ͷҪ�ƶ���������
	short headDestPosX = getHeadDestPosX(dir);
	short headDestPosY = getHeadDestPosY(dir);

	//�ж��Ƿ�������Χǽ
	vector<CGraph * >  vecWall = m_nMap.getVecWall();
	for (unsigned int i = 0; i < vecWall.size(); i++) {
		if (vecWall[i]->getPosX() == headDestPosX && vecWall[i]->getPosY() == headDestPosY) {
			return true;//����
		}
	}

	//�ж��Ƿ��������ϰ���
	vector<CGraph * >  vecDangerBlock = m_nMap.getVecDangerBlock();
	for (unsigned int i = 0; i < vecDangerBlock.size(); i++) {
		if (vecDangerBlock[i]->getPosX() == headDestPosX && vecDangerBlock[i]->getPosY() == headDestPosY) {
			return true;//����
		}
	}
	return false;

}

bool CSnake::eatSelf(enumDir dir)
{
	//��ͷҪ�ƶ���������
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
	//��ͷҪ�ƶ���������
	short headDestPosX = getHeadDestPosX(dir);
	short headDestPosY = getHeadDestPosY(dir);

	headDestPosX = headDestPosX > 0 ? headDestPosX : 0;
	headDestPosY = headDestPosY > 0 ? headDestPosY : 0;

	//���ͷ���������壬�򲻲���
	if (m_vecCobra.size() > 1) {
		if (headDestPosX == m_vecCobra[1]->getPosX() && headDestPosY == m_vecCobra[1]->getPosY()) {
			PlaySoundA("sound\\wrong.wav", NULL, SND_FILENAME | SND_SYNC);
			return false;
		}
	}

	//����һ���µĿ飬����ͷ��
	CGraph * newHead = new CGraph(headDestPosX, headDestPosY);
	//����ͷ�ķ�������
	newHead->setDir(dir);
	//��������ͷ
	m_vecCobra.insert(m_vecCobra.begin(), newHead);
	return true;
}


short CSnake::getHeadDestPosX(enumDir dir)
{
	//��ǰ��ͷ������
	short headPosX = m_vecCobra[0]->getPosX();
	//���ݷ���ȷ������ͷ������
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
		cout << "����ķ������1" << endl;
		break;
	}
	return headPosX;
}

short CSnake::getHeadDestPosY(enumDir dir)
{
	//��ǰ��ͷ������
	short headPosY = m_vecCobra[0]->getPosY();
	//���ݷ���ȷ������ͷ������
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
		cout << "����ķ������2" << endl;
		break;
	}
	return headPosY;
}


bool CSnake::giveFood(CFood* food)
{
	//�����ǰ������ʳ��ܾ�����
	for (unsigned int i = 0; i < m_vecFoods.size(); i++) {
		if (food->getPosX() == m_vecFoods[i]->getPosX()
			&& food->getPosY() == m_vecFoods[i]->getPosY()) {
			return false;
		}
		
	}
	//������������غϣ��ܾ�����
	for (unsigned int i = 0; i < m_vecCobra.size(); i++) {
		if (m_vecCobra[i]->getPosX() == food->getPosX() && m_vecCobra[i]->getPosY() == food->getPosY()) {
			return false;
		}
	}
	//������ϰ����غϣ��ܾ�����
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
			index = i; //�Ե���
			addScore(1);//�ӷ�
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


//�ٶ����
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
	
	//�������
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
