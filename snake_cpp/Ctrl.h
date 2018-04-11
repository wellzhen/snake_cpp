#pragma once
#include <iostream>
#include  "Graph.h"
#include <WinBase.h>
#include "Snake.h"
#include "Food.h"
#include "Map.h"
#include "Data.h"
#include <conio.h>

void showWelcomeWall();
void showWelcomeWords();
void showMenu();
int  getMenuChoice();
void playGame(int gameType);
void initWindows();
void gameOver();
int  getBufferKey();

//�Ҳ���ʾ����Ϸ����
void showScore(CSnake& snake);
void showSpeed(CSnake& snake);
//������Ϸ����
void exportGameProgressToFile(CSnake& snake);
//�ָ���Ϸ����
void recoverGameProcess(CSnake& snake);

void writeWords(short posX, short posY, char * pStr);

void writelog(short posX, short posY, short a, short b);