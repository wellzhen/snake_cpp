#include "Map.h"
#include <time.h>



CMap::CMap()
{
}

void CMap::setWallSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}
void CMap::createSquareWall()
{
	CGraph * block;
	for (int row = 0; row <= m_nHeight + 1; row++)
	{
		for (int col = 0;col <= m_nWidth + 2; col+=2)
		{
			if (row == 0 || row == m_nHeight + 1 || col == 0 || col == m_nWidth + 2) {
				block = new CGraph(col, row);
				block->setColor(COLOR_GRAY);
				block->setShape(SHAPE_WALL_SOLID);
				m_vecWall.push_back(block);
				block->show();
			}
		}
	}
}

void CMap::createDangerBlock(int amount)
{
	CGraph * block;

	short posX = 0;
	short posY = 0;

	srand(int(time(0)));
	for (int i = 0; i < amount; i++) {
		//获取随机数
		
		posX = (rand() % ((WALL_WIDTH - 8)/2) * 2) + 2;
		posY = rand() % (WALL_HEIGHT - 6) + 2;
		
		block = new CGraph(posX, posY);
		block->setColor(COLOR_GRAY);
		block->setShape(SHAPE_WALL_SOLID);
		m_vecDangerBlock.push_back(block);
		block->show();
	}
}

void CMap::createCustomDangerBlock()
{
	CGraph * block;

	short posX = 0;
	short posY = 0;
	//
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	while (1)
	{
		ReadConsoleInput(hStdin, &stcRecord, 1, &dwRead);
		if (stcRecord.EventType == MOUSE_EVENT) {
			MOUSE_EVENT_RECORD mer = stcRecord.Event.MouseEvent;
			switch (mer.dwEventFlags)
			{
			case 0:
				if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					//左键单击
					//
				}
				else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				{
					//右键单击: 结束编辑编辑
					return;
				}
				break;
			case DOUBLE_CLICK:
				//双击 : 生成障碍物
				//判断坐标是否有效
				if (posX % 2 != 0) {
					posX--;
				}
				if (posX >= 2 && posX <= WALL_WIDTH + 2 && posY >= 1 && posY < WALL_HEIGHT + 1) {
					block = new CGraph(posX, posY);
					block->setColor(COLOR_GRAY);
					block->setShape(SHAPE_WALL_SOLID);
					m_vecDangerBlock.push_back(block);
					block->show();
					
					PlaySoundA("sound\\drop.wav", NULL, SND_FILENAME | SND_ASYNC);
				}

				break;
			case MOUSE_MOVED:
				posX = mer.dwMousePosition.X;
				posY = mer.dwMousePosition.Y;
				break;
			}
		}
	}

}

void CMap::recoverDangerBlock(vector<CGraph *> vecBlocks)
{
	m_vecDangerBlock = vecBlocks;
}


vector<CGraph * >  CMap::getVecWall()
{
	return m_vecWall;
}

vector<CGraph * >  CMap::getVecDangerBlock()
{
	return m_vecDangerBlock;
}



CMap::~CMap()
{
}
