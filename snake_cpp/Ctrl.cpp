#include "Ctrl.h"



void showWelcomeWall()
{
	CMap helloWall;
	helloWall.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	helloWall.createSquareWall();
}

void showWelcomeWords()
{
	writeWords(24, 12, "贪吃蛇");
	writeWords(20, 14, "WELCOME TO SNAKE");
}

void showMenu()
{
	writeWords(22, 10, "1  s级难度");
	writeWords(22, 12, "2  ss级难度");
	writeWords(22, 14, "3  sss级难度");
	writeWords(22, 16, "4  自定义地图");
	writeWords(22, 18, "5  读档游戏");
	writeWords(22, 20, "6  退出游戏");
	writeWords(22, 22, "请输入您的选择\n");
	writeWords(26, 24, "");
}

int getMenuChoice()
{
	int menuNum = 0;
	while (1) {
		if (menuNum == 1 || menuNum == 2 || menuNum == 3 || menuNum == 4|| menuNum == 5 || menuNum == 6) {
			return menuNum;
		}
		else {
			//menuNum = 0;
			scanf_s("%d", &menuNum);
		}
	}
}



void showScore(CSnake& snake)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 4 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("得分：%d", snake.getScore());
	
}



void showSpeed(CSnake& snake)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 6 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("速度：%d ", snake.getSpeed());
}

void showGPS(CSnake& snake) 
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 8 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("定位：(%d %d) ", ((snake.getVecCobra())[0])->getPosX(), ((snake.getVecCobra())[0])->getPosY());
}

void showFoodSize(CSnake& snake)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 10 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("食物：%d", snake.getVecFoods().size());

}


void playGame(int gameType)
{
	system("cls");
	//生成墙  和 障碍物
	CMap greatMap;
	greatMap.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	greatMap.createSquareWall();
	if (gameType == 1) {//简单
		greatMap.createDangerBlock(5);
	}
	else if (gameType == 2) {
		greatMap.createDangerBlock(30); // 障碍物数量
		PlaySoundA("sound\\bark.wav", NULL, SND_FILENAME | SND_SYNC);
	}
	else if(gameType == 3){ 
		PlaySoundA("sound\\difficult.wav", NULL, SND_FILENAME | SND_SYNC);
		greatMap.createDangerBlock(200); // 障碍物数量
	}else if (gameType == 4) {//自定义
		PlaySoundA("sound\\trouble.wav", NULL, SND_FILENAME | SND_SYNC);
		greatMap.createCustomDangerBlock();
	}
	else if (gameType == 5) { //读档案游戏
		
	}
		

	//初始化一条蛇
	CSnake snake;
	snake.setSpeed(70);//初始速度6 
	

	//传入地图
	snake.importMap(greatMap);


	//如果是读档案，则修改游戏的内部参数
	if (gameType == 5) {
		recoverGameProcess(snake);
	}
	
	snake.show();
	/*************************操作蛇********************/
	enumDir dir;//移动方向
	bool hasStop = false;
	while (1) {
		//食物检测
		if (snake.hasEnoughFood(5 * gameType) == false) {
			CFood* food_star_a = new CFood();
			snake.giveFood(food_star_a); 
		}
		
		//showFoodSize(snake);
		//控制移动速度
		Sleep(snake.getSleepTime()); 
		int keyNum = snake.waitKey();
		//是否按下了暂停
		if ((keyNum == 32 && hasStop == false)) {
			hasStop = true;
			continue;
		}
		else if (keyNum == 32 && hasStop == true) {
			hasStop = false;
		}
		else if (hasStop == true) {
			continue;
		}
		else if (keyNum == 27) { // ESC导出
			exportGameProgressToFile(snake);
			break;
		}

		dir = snake.operate(keyNum);
		//判断dir是否有效,否则使用蛇头方向
		if (dir == DIR_NO) {
			dir = snake.getVecCobra()[0]->getDir();
		}

		snake.hide();
		//判断是否会因撞墙而死
		if (snake.willDieByMap(dir)) {
			PlaySoundA("sound\\crunch.wav", NULL, SND_FILENAME | SND_SYNC);
			snake.showDie();
			break;
		}
		//判断是否吃到自己死了
		if (snake.eatSelf(dir)) {
			snake.showDie();
			break;
		}
		snake.forward(dir);
		snake.show();
		//蛇头位置显示
		showGPS(snake);
		//分数显示
		showScore(snake);
		//速度显示
		showSpeed(snake); 
		//食物数量
		showFoodSize(snake);
		
	}

}


void exportGameProgressToFile(CSnake& snake)
{
	FILE* pFile;
	fopen_s(&pFile, "log.db", "wb");
	//1.分数
	int score = snake.getScore();
	fwrite(&score, sizeof(int), 1, pFile);	   // printf("分数：%d \n", score);
	//fprintf_s(pFile, "%d ", score);
	//2.速度
	int speed = snake.getSpeed();
	//fprintf_s(pFile, "%d ", speed);
	fwrite(&speed, sizeof(int), 1, pFile);     //printf("速度：%d \n", speed);
	//3.障碍物
	vector<CGraph *> vecBlocks = snake.getMap().getVecDangerBlock();
	//3.1障碍物数量
	int blockCount = vecBlocks.size();
	//fprintf_s(pFile, "%d ", blockCount);
	fwrite(&blockCount, sizeof(int), 1, pFile);   // printf("障碍物数量：%d \n", blockCount);
	//3.2障碍物参数
	short posX1;
	short posY1;
	for (int i = 0; i < blockCount; i++) {
		posX1 = vecBlocks[i]->getPosX();
		posY1 = vecBlocks[i]->getPosY();
		//fprintf_s(pFile, "%d  %d ", posX1, posY1);
		fwrite(&posX1, sizeof(short), 1, pFile);
		fwrite(&posY1, sizeof(short), 1, pFile);		// printf("障碍物%d坐标：(%d %d) \n", i, posX, posY);
	}
	//4.食物
	vector<CFood *> vecFoods = snake.getVecFoods();
	// 4.1 食物数量
	int foodCount = vecFoods.size();
	//fprintf_s(pFile, "%d ", foodCount);
	fwrite(&foodCount, sizeof(int), 1, pFile);		  //printf("食物数量：%d \n", foodCount);
	// 4.2  食物参数
	enumFoodAffect  affect;
	short posX2;
	short posY2;
	for (int i = 0; i < foodCount; i++) {
		posX2 = vecFoods[i]->getPosX();
		posY2 = vecFoods[i]->getPosY();
		affect = vecFoods[i]->getAffect();

		//fprintf_s(pFile, "%d %d %d ", posX2, posY2, affect);
		fwrite(&posX2, sizeof(short), 1, pFile);
		fwrite(&posY2, sizeof(short), 1, pFile);
		fwrite(&affect, sizeof(affect), 1, pFile);	  // printf("食物%d坐标：(%d %d) %d--%d \n", i, posX, posY, affect, sizeof(affect));
	}
	//5.蛇块
	vector<CGraph *> vecCobra= snake.getVecCobra();
	// 5.1 蛇块数量
	int cobraCount = vecCobra.size();
	//fprintf_s(pFile, "%d ", cobraCount);
	fwrite(&cobraCount, sizeof(int), 1, pFile);			// printf("蛇块数量：%d \n", cobraCount);
	// 5.2 蛇块参数
	enumDir dir;
	short posX3;
	short posY3;
	for (int i = 0; i < cobraCount; i++) {
		posX3 = vecCobra[i]->getPosX();
		posY3 = vecCobra[i]->getPosY();
		dir = vecCobra[i]->getDir();
		//fprintf_s(pFile, "%d %d %d ", posX3, posY3, dir);
		fwrite(&posX3, sizeof(short), 1, pFile);
		fwrite(&posY3, sizeof(short), 1, pFile);
		fwrite(&dir, sizeof(dir), 1, pFile);		// printf("蛇块%d坐标：(%d %d) %d -- %d\n", i, posX, posY, dir, sizeof(dir));
	}
	
	//关闭
	fclose(pFile);									//Sleep(1000);
	
}

void recoverGameProcess(CSnake& snake)
{
	//障碍物 null;食物 null ;身体: 只有头
	FILE * pFile;
	fopen_s(&pFile, "log.db", "rb");
	
	//1.分数
	int score;
	//fscanf_s(pFile, "%d ", &score);				//system("cls"); printf("分数：%d \n", score); Sleep(5000);
	fread_s(&score, sizeof(int), sizeof(int), 1, pFile);		
	snake.setScore(score);
	//2.速度
	int speed;
	//fscanf_s(pFile, "%d ", &speed);				//system("cls");  printf("速度：%d \n", speed); Sleep(5000);
	fread_s(&speed, sizeof(int), sizeof(int), 1, pFile);		
	snake.setSpeed(speed);
	/***map**/
	CMap greatMap;
	greatMap.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	greatMap.createSquareWall();

	//3.障碍物
	vector<CGraph *> vecBlocks ;
	//3.1障碍物数量
	int blockCount;
	//fscanf_s(pFile, "%d ", &blockCount);									//system("cls");  printf("障碍物数量：%d \n", blockCount); Sleep(5000);
	fread_s(&blockCount, sizeof(int), sizeof(int), 1, pFile);		
	//3.2障碍物参数
	short posX1;
	short posY1;
	CGraph * block;
	for (int i = 0; i < blockCount; i++) {
		//fscanf_s(pFile, "%d %d", &posX1, &posY1);                   // system("cls");   printf("障碍物%d坐标：(%d %d) \n", i, posX, posY); Sleep(5000);
		fread_s(&posX1, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&posY1, sizeof(short), sizeof(short), 1, pFile);		
		block = new CGraph(posX1, posY1);
		block->setColor(COLOR_GRAY);
		block->setShape(SHAPE_WALL_SOLID);
		vecBlocks.push_back(block);
		block->show();
	}
	greatMap.recoverDangerBlock(vecBlocks);
	snake.importMap(greatMap);

	//4.食物
	vector<CFood *> vecFoods;
	// 4.1 食物数量
	int foodCount;
	//fscanf_s(pFile, "%d ", &foodCount);					//system("cls");  printf("食物数量：%d \n", foodCount); Sleep(5000);
	fread_s(&foodCount, sizeof(int), sizeof(int), 1, pFile);	
	// 4.2  食物参数
	enumFoodAffect  affect;
	CFood * food;
	short posX2;
	short posY2;
	for (int i = 0; i < foodCount; i++) {
		//fscanf_s(pFile, "%d %d %d", &posX2, &posY2, &affect);    // system("cls");   printf("食物%d坐标：(%d %d) %d %d \n", i, posX, posY, affect, sizeof(affect)); Sleep(5000);
		fread_s(&posX2, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&posY2, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&affect, sizeof(affect), sizeof(affect), 1, pFile);		
		food = new CFood();
		food->setPos(posX2, posY2);
		food->setAffect(affect);
		snake.giveFood(food);
	}
	//5.蛇块
	vector<CGraph *> vecCobra ;
	CGraph * cobra;
	// 5.1 蛇块数量
	int cobraCount;
	//fscanf_s(pFile, "%d ", &cobraCount);						//system("cls"); printf("蛇块数量：%d \n", cobraCount); Sleep(5000);
	fread_s(&cobraCount, sizeof(int), sizeof(int), 1, pFile);	  
	// 5.2 蛇块参数  
	enumDir dir;
	short posX3;
	short posY3;
	for (int i = 0; i < cobraCount; i++) {

		//fscanf_s(pFile, "%d %d %d ", &posX3, &posY3, &dir);			//system("cls");  printf("蛇块%d坐标：(%d %d) %d  %d\n", i, posX, posY, dir, sizeof(dir)); Sleep(5000);
		fread_s(&posX3, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&posY3, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&dir, sizeof(dir), sizeof(dir), 1, pFile);			

		cobra = new CGraph();
		cobra->setPos(posX3, posY3); 
		cobra->setDir(dir);
		vecCobra.push_back(cobra);
	}
	snake.setVecCobra(vecCobra);										

	//关闭
	fclose(pFile);//Sleep(5000);



}

void initWindows()
{
	system("title");
	system("mode con cols=70 lines=42");

	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}


void gameOver()
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { 4, WALL_HEIGHT + 4 });
	printf("GAME OVER !\n");
	system("pause");
	return;
}

void writeWords(short posX, short posY, char * pStr)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { posX, posY});
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("%s", pStr);
}

int getBufferKey()
{
	if (_kbhit()) {
		return _getch();
	}
	return 0;
}

void writelog(short posX, short posY, short a, short b)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { posX, posY });
	printf("(%d %d) ", a, b);
}

