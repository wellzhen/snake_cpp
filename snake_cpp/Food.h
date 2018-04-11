#pragma once
#include "Graph.h"
class CFood :
	public CGraph
{
public:
	CFood();
	void setAffect(enumFoodAffect affect);
	enumFoodAffect getAffect();
	~CFood();
private:
	enumFoodAffect m_eAffect;
};
