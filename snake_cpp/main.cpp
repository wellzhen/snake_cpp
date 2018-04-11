#pragma once
#include <iostream>
#include  "Graph.h"
#include <WinBase.h>
#include "Snake.h"
#include "Food.h"
#include "Map.h"
#include "Data.h"
#include "Ctrl.h"
#include <Windows.h>
#include <mmsyscom.h>
#pragma comment(lib, "WINMM.LIB")
#pragma comment(lib, "User32.lib")


using namespace std;     


int main()
{	
	initWindows();

	/************  显示欢迎界面***************/
	showWelcomeWall();
	showWelcomeWords();
	PlaySoundA("sound\\welcome.wav", NULL, SND_FILENAME | SND_SYNC);
	Sleep(2000);
	PlaySoundA("sound\\page.wav", NULL, SND_FILENAME | SND_ASYNC);
	/************ 显示菜单 和游戏 **************/
	system("cls");

	while (1) {
		showWelcomeWall();
		showMenu();
		//获取用户选择
		int nMenuChoice = getMenuChoice(); 
		switch (nMenuChoice) {
		case 1: 
			//开始游戏；
			system("cls");
			playGame(1);
			//死亡了
			Sleep(2000);
			system("cls");
			break;
		case 2:
			//开始游戏；
			system("cls");
			playGame(2);
			Sleep(2000);
			system("cls");
			break;
		case 3:
			//开始游戏；
			system("cls");
			playGame(3);
			Sleep(2000);
			system("cls");
			break;
		case 4:
			//自定义游戏
			//开始游戏；
			system("cls");
			playGame(4);
			Sleep(1000);
			system("cls");
			break;
		case 5:
			//读档游戏
			system("cls");
			playGame(5);
			Sleep(2000);
			system("cls");
			break;
		case 6:
			//结束游戏
			PlaySoundA("sound\\byebye.wav", NULL, SND_FILENAME | SND_SYNC);
			return 0;
			break;
		default :
			PlaySoundA("sound\\wrong.wav", NULL, SND_FILENAME | SND_ASYNC);
			 break;

		}

	}
	

	/**************  加载游戏  ***************/
	
	

}



