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

	/************  ��ʾ��ӭ����***************/
	showWelcomeWall();
	showWelcomeWords();
	PlaySoundA("sound\\welcome.wav", NULL, SND_FILENAME | SND_SYNC);
	Sleep(2000);
	PlaySoundA("sound\\page.wav", NULL, SND_FILENAME | SND_ASYNC);
	/************ ��ʾ�˵� ����Ϸ **************/
	system("cls");

	while (1) {
		showWelcomeWall();
		showMenu();
		//��ȡ�û�ѡ��
		int nMenuChoice = getMenuChoice(); 
		switch (nMenuChoice) {
		case 1: 
			//��ʼ��Ϸ��
			system("cls");
			playGame(1);
			//������
			Sleep(2000);
			system("cls");
			break;
		case 2:
			//��ʼ��Ϸ��
			system("cls");
			playGame(2);
			Sleep(2000);
			system("cls");
			break;
		case 3:
			//��ʼ��Ϸ��
			system("cls");
			playGame(3);
			Sleep(2000);
			system("cls");
			break;
		case 4:
			//�Զ�����Ϸ
			//��ʼ��Ϸ��
			system("cls");
			playGame(4);
			Sleep(1000);
			system("cls");
			break;
		case 5:
			//������Ϸ
			system("cls");
			playGame(5);
			Sleep(2000);
			system("cls");
			break;
		case 6:
			//������Ϸ
			PlaySoundA("sound\\byebye.wav", NULL, SND_FILENAME | SND_SYNC);
			return 0;
			break;
		default :
			PlaySoundA("sound\\wrong.wav", NULL, SND_FILENAME | SND_ASYNC);
			 break;

		}

	}
	

	/**************  ������Ϸ  ***************/
	
	

}



