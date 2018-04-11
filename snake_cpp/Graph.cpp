#include "Graph.h"
#include "Data.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

CGraph::CGraph() 
{
	m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hideCursor();
}
/*构造： 必须传递点的坐标*/
CGraph::CGraph(short posX, short posY):m_nPosX(posX), m_nPosY(posY)
{
	m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hideCursor();
}




short CGraph::getPosX() {
	return m_nPosX;
}

short CGraph::getPosY() {
	return m_nPosY;
}

enumDir CGraph::getDir()
{
	return m_eDir;
}

//显示一个
void CGraph::show()
{
	setCursorColor(m_eColor);
	setCursorPos(m_nPosX, m_nPosY);

	if (m_eShape == SHAPE_SQUARE_SOLID) {
		printf(SQUARE_SOLID);
	}
	else if (m_eShape == SHAPE_SQUARE_HOLLOW)
	{
		printf(SQUARE_HOLLOW);
	}
	else if (m_eShape == SHAPE_IMG_STAR) {
		printf(IMG_STAR);
	}
	else if (m_eShape == SHAPE_IMG_X) {
		printf(IMG_X);
	}
	else if (m_eShape == SHAPE_CIRCLE_SOLID) {
		printf(CIRCLE_SOLID);
	} 
	else if (m_eShape == SHAPE_WALL_SOLID) {
		printf(WALL_SOLID);
	}
	else if (m_eShape == SHAPE_IMG_FLOWER) {
		printf(IMG_FLOWER);
	}
	else {
		printf("—");
	}

}

void CGraph::setDir(enumDir dir)
{
	m_eDir = dir;
}


void CGraph::setPos(short posX, short posY)
{
	m_nPosX = posX;
	m_nPosY = posY;
}

void CGraph::setColor(enumColor color)
{
	m_eColor = color;
}

enumColor CGraph::getColor()
{
	return m_eColor;
}

void CGraph::setShape(enumShape shape)
{
	m_eShape = shape;
}


//移除一个点: 不显示了
void CGraph::hide()
{
	setCursorColor(m_eColor);
	setCursorPos(m_nPosX, m_nPosY);
	printf("  ");
}

//不显示光标
void CGraph::hideCursor()
{
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(m_stdHandle, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(m_stdHandle, &ConsoleCursorInfo);
}


CGraph::~CGraph()
{
}

/**********************  private  *****************/

//设置光标的颜色
void CGraph::setCursorColor(enumColor color)
{
	SetConsoleTextAttribute(m_stdHandle, color);
}


//设置光标的位置
void CGraph::setCursorPos(short posX, short posY)
{
	SetConsoleCursorPosition(m_stdHandle, { posX, posY });
}