#include "Food.h"
#include <time.h>
#include "Ctrl.h"


CFood::CFood()
{
	srand(int(time(0)));
	short X = (rand() % ((WALL_WIDTH - 4)/2)) * 2  + 2;
	short Y = rand() % (WALL_HEIGHT-2)  + 1;
	setPos(X, Y); 
	setAffect((enumFoodAffect)((X + Y) % 3)); 
	
}
void CFood::setAffect(enumFoodAffect affect)
{

	switch (affect) {
	case FOOD_INCREASE_SPEED:
		setColor(COLOR_WHITE);
		setShape(SHAPE_IMG_STAR);
		break;
	case FOOD_DECREASE_SPEED:
		setColor(COLOR_RED);
		setShape(SHAPE_IMG_STAR);
		break;
	case FOOD_INCREASE_BODY:
		setColor(COLOR_YELLOW);
		setShape(SHAPE_IMG_STAR);
		break;
	case FOOD_DECREASE_BODY:
		setColor(COLOR_RED);
		setShape(SHAPE_IMG_X);
		break;
	default:
		break;

	}
	m_eAffect = affect;
}

enumFoodAffect CFood::getAffect()
{
	return m_eAffect;
}

CFood::~CFood()
{
}
