#pragma once
#include <windows.h>
#include "Data.h"

class CGraph
{
public:
	CGraph();
	/*构造： 用于初始化*/
	CGraph(short posX, short posY);
	
	//不显示光标
	void hideCursor();

	short getPosX();
	short getPosY();
	enumDir getDir();

	//显示图形
	void show();
	//隐藏
	void hide();


	//设置方向
	void setDir(enumDir dir);
	//设置坐标
	void setPos(short posX, short posY);
	//设置颜色
	void setColor(enumColor color);
	//设置形状
	void setShape(enumShape shape);
	//获取颜色
	enumColor getColor();

	//设置光标的位置
	void setCursorPos(short posX, short posY);

	//设置光标的颜色
	void setCursorColor(enumColor color);


	~CGraph();


protected:
	short m_nPosX;
	short m_nPosY;
	enumColor   m_eColor;
	enumShape   m_eShape;
	enumDir  m_eDir;//记录方向属性
	HANDLE m_stdHandle;
};

