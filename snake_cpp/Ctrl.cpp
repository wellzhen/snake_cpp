#include "Ctrl.h"



void showWelcomeWall()
{
	CMap helloWall;
	helloWall.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	helloWall.createSquareWall();
}

void showWelcomeWords()
{
	writeWords(24, 12, "̰����");
	writeWords(20, 14, "WELCOME TO SNAKE");
}

void showMenu()
{
	writeWords(22, 10, "1  s���Ѷ�");
	writeWords(22, 12, "2  ss���Ѷ�");
	writeWords(22, 14, "3  sss���Ѷ�");
	writeWords(22, 16, "4  �Զ����ͼ");
	writeWords(22, 18, "5  ������Ϸ");
	writeWords(22, 20, "6  �˳���Ϸ");
	writeWords(22, 22, "����������ѡ��\n");
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
	printf("�÷֣�%d", snake.getScore());
	
}



void showSpeed(CSnake& snake)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 6 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("�ٶȣ�%d ", snake.getSpeed());
}

void showGPS(CSnake& snake) 
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 8 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("��λ��(%d %d) ", ((snake.getVecCobra())[0])->getPosX(), ((snake.getVecCobra())[0])->getPosY());
}

void showFoodSize(CSnake& snake)
{
	HANDLE m_stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(m_stdHandle, { WALL_WIDTH + 4, 10 });
	SetConsoleTextAttribute(m_stdHandle, COLOR_RED);
	printf("ʳ�%d", snake.getVecFoods().size());

}


void playGame(int gameType)
{
	system("cls");
	//����ǽ  �� �ϰ���
	CMap greatMap;
	greatMap.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	greatMap.createSquareWall();
	if (gameType == 1) {//��
		greatMap.createDangerBlock(5);
	}
	else if (gameType == 2) {
		greatMap.createDangerBlock(30); // �ϰ�������
		PlaySoundA("sound\\bark.wav", NULL, SND_FILENAME | SND_SYNC);
	}
	else if(gameType == 3){ 
		PlaySoundA("sound\\difficult.wav", NULL, SND_FILENAME | SND_SYNC);
		greatMap.createDangerBlock(200); // �ϰ�������
	}else if (gameType == 4) {//�Զ���
		PlaySoundA("sound\\trouble.wav", NULL, SND_FILENAME | SND_SYNC);
		greatMap.createCustomDangerBlock();
	}
	else if (gameType == 5) { //��������Ϸ
		
	}
		

	//��ʼ��һ����
	CSnake snake;
	snake.setSpeed(70);//��ʼ�ٶ�6 
	

	//�����ͼ
	snake.importMap(greatMap);


	//����Ƕ����������޸���Ϸ���ڲ�����
	if (gameType == 5) {
		recoverGameProcess(snake);
	}
	
	snake.show();
	/*************************������********************/
	enumDir dir;//�ƶ�����
	bool hasStop = false;
	while (1) {
		//ʳ����
		if (snake.hasEnoughFood(5 * gameType) == false) {
			CFood* food_star_a = new CFood();
			snake.giveFood(food_star_a); 
		}
		
		//showFoodSize(snake);
		//�����ƶ��ٶ�
		Sleep(snake.getSleepTime()); 
		int keyNum = snake.waitKey();
		//�Ƿ�������ͣ
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
		else if (keyNum == 27) { // ESC����
			exportGameProgressToFile(snake);
			break;
		}

		dir = snake.operate(keyNum);
		//�ж�dir�Ƿ���Ч,����ʹ����ͷ����
		if (dir == DIR_NO) {
			dir = snake.getVecCobra()[0]->getDir();
		}

		snake.hide();
		//�ж��Ƿ����ײǽ����
		if (snake.willDieByMap(dir)) {
			PlaySoundA("sound\\crunch.wav", NULL, SND_FILENAME | SND_SYNC);
			snake.showDie();
			break;
		}
		//�ж��Ƿ�Ե��Լ�����
		if (snake.eatSelf(dir)) {
			snake.showDie();
			break;
		}
		snake.forward(dir);
		snake.show();
		//��ͷλ����ʾ
		showGPS(snake);
		//������ʾ
		showScore(snake);
		//�ٶ���ʾ
		showSpeed(snake); 
		//ʳ������
		showFoodSize(snake);
		
	}

}


void exportGameProgressToFile(CSnake& snake)
{
	FILE* pFile;
	fopen_s(&pFile, "log.db", "wb");
	//1.����
	int score = snake.getScore();
	fwrite(&score, sizeof(int), 1, pFile);	   // printf("������%d \n", score);
	//fprintf_s(pFile, "%d ", score);
	//2.�ٶ�
	int speed = snake.getSpeed();
	//fprintf_s(pFile, "%d ", speed);
	fwrite(&speed, sizeof(int), 1, pFile);     //printf("�ٶȣ�%d \n", speed);
	//3.�ϰ���
	vector<CGraph *> vecBlocks = snake.getMap().getVecDangerBlock();
	//3.1�ϰ�������
	int blockCount = vecBlocks.size();
	//fprintf_s(pFile, "%d ", blockCount);
	fwrite(&blockCount, sizeof(int), 1, pFile);   // printf("�ϰ���������%d \n", blockCount);
	//3.2�ϰ������
	short posX1;
	short posY1;
	for (int i = 0; i < blockCount; i++) {
		posX1 = vecBlocks[i]->getPosX();
		posY1 = vecBlocks[i]->getPosY();
		//fprintf_s(pFile, "%d  %d ", posX1, posY1);
		fwrite(&posX1, sizeof(short), 1, pFile);
		fwrite(&posY1, sizeof(short), 1, pFile);		// printf("�ϰ���%d���꣺(%d %d) \n", i, posX, posY);
	}
	//4.ʳ��
	vector<CFood *> vecFoods = snake.getVecFoods();
	// 4.1 ʳ������
	int foodCount = vecFoods.size();
	//fprintf_s(pFile, "%d ", foodCount);
	fwrite(&foodCount, sizeof(int), 1, pFile);		  //printf("ʳ��������%d \n", foodCount);
	// 4.2  ʳ�����
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
		fwrite(&affect, sizeof(affect), 1, pFile);	  // printf("ʳ��%d���꣺(%d %d) %d--%d \n", i, posX, posY, affect, sizeof(affect));
	}
	//5.�߿�
	vector<CGraph *> vecCobra= snake.getVecCobra();
	// 5.1 �߿�����
	int cobraCount = vecCobra.size();
	//fprintf_s(pFile, "%d ", cobraCount);
	fwrite(&cobraCount, sizeof(int), 1, pFile);			// printf("�߿�������%d \n", cobraCount);
	// 5.2 �߿����
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
		fwrite(&dir, sizeof(dir), 1, pFile);		// printf("�߿�%d���꣺(%d %d) %d -- %d\n", i, posX, posY, dir, sizeof(dir));
	}
	
	//�ر�
	fclose(pFile);									//Sleep(1000);
	
}

void recoverGameProcess(CSnake& snake)
{
	//�ϰ��� null;ʳ�� null ;����: ֻ��ͷ
	FILE * pFile;
	fopen_s(&pFile, "log.db", "rb");
	
	//1.����
	int score;
	//fscanf_s(pFile, "%d ", &score);				//system("cls"); printf("������%d \n", score); Sleep(5000);
	fread_s(&score, sizeof(int), sizeof(int), 1, pFile);		
	snake.setScore(score);
	//2.�ٶ�
	int speed;
	//fscanf_s(pFile, "%d ", &speed);				//system("cls");  printf("�ٶȣ�%d \n", speed); Sleep(5000);
	fread_s(&speed, sizeof(int), sizeof(int), 1, pFile);		
	snake.setSpeed(speed);
	/***map**/
	CMap greatMap;
	greatMap.setWallSize(WALL_WIDTH, WALL_HEIGHT);
	greatMap.createSquareWall();

	//3.�ϰ���
	vector<CGraph *> vecBlocks ;
	//3.1�ϰ�������
	int blockCount;
	//fscanf_s(pFile, "%d ", &blockCount);									//system("cls");  printf("�ϰ���������%d \n", blockCount); Sleep(5000);
	fread_s(&blockCount, sizeof(int), sizeof(int), 1, pFile);		
	//3.2�ϰ������
	short posX1;
	short posY1;
	CGraph * block;
	for (int i = 0; i < blockCount; i++) {
		//fscanf_s(pFile, "%d %d", &posX1, &posY1);                   // system("cls");   printf("�ϰ���%d���꣺(%d %d) \n", i, posX, posY); Sleep(5000);
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

	//4.ʳ��
	vector<CFood *> vecFoods;
	// 4.1 ʳ������
	int foodCount;
	//fscanf_s(pFile, "%d ", &foodCount);					//system("cls");  printf("ʳ��������%d \n", foodCount); Sleep(5000);
	fread_s(&foodCount, sizeof(int), sizeof(int), 1, pFile);	
	// 4.2  ʳ�����
	enumFoodAffect  affect;
	CFood * food;
	short posX2;
	short posY2;
	for (int i = 0; i < foodCount; i++) {
		//fscanf_s(pFile, "%d %d %d", &posX2, &posY2, &affect);    // system("cls");   printf("ʳ��%d���꣺(%d %d) %d %d \n", i, posX, posY, affect, sizeof(affect)); Sleep(5000);
		fread_s(&posX2, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&posY2, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&affect, sizeof(affect), sizeof(affect), 1, pFile);		
		food = new CFood();
		food->setPos(posX2, posY2);
		food->setAffect(affect);
		snake.giveFood(food);
	}
	//5.�߿�
	vector<CGraph *> vecCobra ;
	CGraph * cobra;
	// 5.1 �߿�����
	int cobraCount;
	//fscanf_s(pFile, "%d ", &cobraCount);						//system("cls"); printf("�߿�������%d \n", cobraCount); Sleep(5000);
	fread_s(&cobraCount, sizeof(int), sizeof(int), 1, pFile);	  
	// 5.2 �߿����  
	enumDir dir;
	short posX3;
	short posY3;
	for (int i = 0; i < cobraCount; i++) {

		//fscanf_s(pFile, "%d %d %d ", &posX3, &posY3, &dir);			//system("cls");  printf("�߿�%d���꣺(%d %d) %d  %d\n", i, posX, posY, dir, sizeof(dir)); Sleep(5000);
		fread_s(&posX3, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&posY3, sizeof(short), sizeof(short), 1, pFile);
		fread_s(&dir, sizeof(dir), sizeof(dir), 1, pFile);			

		cobra = new CGraph();
		cobra->setPos(posX3, posY3); 
		cobra->setDir(dir);
		vecCobra.push_back(cobra);
	}
	snake.setVecCobra(vecCobra);										

	//�ر�
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

