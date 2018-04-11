#pragma once
#include "Graph.h"
#include <vector>

using  std::vector;
class CMap :
	public CGraph
{
public:
	CMap();

	void setWallSize(int width = WALL_WIDTH, int height = WALL_HEIGHT);
	//��Χǽ
	void createSquareWall();

	//�ϰ�ǽ
	void createDangerBlock(int amount = 2);
	//�Զ���ǽ
	void createCustomDangerBlock();
	//�ָ�ǽ������)
	void recoverDangerBlock(vector<CGraph *> vecBlocks);

	vector<CGraph * > getVecWall();
	vector<CGraph * > getVecDangerBlock();

	~CMap();

private:
	int m_nWidth;
	int m_nHeight;
	vector<CGraph * >  m_vecWall;
	vector<CGraph * >  m_vecDangerBlock;
};

