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

//右侧显示的游戏参数
void showScore(CSnake& snake);
void showSpeed(CSnake& snake);
//导出游戏进度
void exportGameProgressToFile(CSnake& snake);
//恢复游戏进度
void recoverGameProcess(CSnake& snake);

void writeWords(short posX, short posY, char * pStr);

void writelog(short posX, short posY, short a, short b);