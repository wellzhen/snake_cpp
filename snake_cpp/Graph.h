#pragma once
#include <windows.h>
#include "Data.h"

class CGraph
{
public:
	CGraph();
	/*���죺 ���ڳ�ʼ��*/
	CGraph(short posX, short posY);
	
	//����ʾ���
	void hideCursor();

	short getPosX();
	short getPosY();
	enumDir getDir();

	//��ʾͼ��
	void show();
	//����
	void hide();


	//���÷���
	void setDir(enumDir dir);
	//��������
	void setPos(short posX, short posY);
	//������ɫ
	void setColor(enumColor color);
	//������״
	void setShape(enumShape shape);
	//��ȡ��ɫ
	enumColor getColor();

	//���ù���λ��
	void setCursorPos(short posX, short posY);

	//���ù�����ɫ
	void setCursorColor(enumColor color);


	~CGraph();


protected:
	short m_nPosX;
	short m_nPosY;
	enumColor   m_eColor;
	enumShape   m_eShape;
	enumDir  m_eDir;//��¼��������
	HANDLE m_stdHandle;
};

