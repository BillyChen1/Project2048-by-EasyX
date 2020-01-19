/********************ͼ�ΰ�2048��Ϸ(Windows)*********************/
/************Created by ������ �º��� ���ŷ� ����*****************/
/***********ʵ�ֹ��ܣ��������� �����������Ʒ֡������浵*************/
/**************��չ���ܣ��ٶ�ģʽ ����ѡ�޶�ʱ��*******************/

#include"Game.h"
#include<iostream>
#include<conio.h>	//ʹ��_getch
#include<graphics.h>
#include<ctime>
#include<windows.h>

using namespace std;


/*����ͼ�����*/
IMAGE bk;
IMAGE lose;
IMAGE win;
IMAGE runout;
IMAGE rule;
IMAGE option;



void Interface();	//����������
int mouse();		//��꺯����������Ϸģʽ
int choose();		//��꺯����ѡ���ٶ�ģʽѡ��
int back();			////ʧ�ܡ�ʱ��ľ����鿴����󷵻����������Ĳ���



void Interface()
{
	putimage(0, 0, &bk);
}//����������




int mouse()
{
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y > 200 && m.y < 250)
		{
			return NORMAL_MODE;
		}
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y > 300 && m.y < 350)
		{
			return SPEED_MODE;
		}
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y > 410 && m.y < 460)
		{
			return RULE;
		}
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y >= 515 && m.y <= 570)
		{
			return EXIT;
		}
	}
}//��꺯����������Ϸģʽ




int back()
{
	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg();
		if (n.mkLButton&&n.x >= 130 && n.x <= 300 && n.y >= 550 && n.y <= 600)
			return 1;
	}
}//ʧ�ܡ�ʱ��ľ����鿴����󷵻����������Ĳ���




int choose()
{
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y > 300 && m.y < 350)
		{
			return 3;
		}
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y > 410 && m.y < 460)
		{
			return 5;
		}
		if (m.mkLButton&&m.x >= 130 && m.x <= 290 && m.y >= 515 && m.y <= 570)
		{
			return 7;
		}
	}
}




int main()
{
	int state;
		//��ȡ�����״̬��������ģʽ���ٶ�ģʽ�������˳���

	int startGame = 1;	
		//�����ڽ��������Ϣ���Ƿ��·��أ���������ܵ�����ص�������
	
	initgraph(450, 700);
	
	loadimage(&bk, _T("img\\bk.png"), 450, 700);
	loadimage(&lose, _T("img\\lose.png"), 450, 700);
	loadimage(&win, _T("img\\win.png"), 450, 700);
	loadimage(&runout, _T("img\\runout.png"), 450, 700);
	loadimage(&rule, _T("img\\rule.png"), 450, 700);
	loadimage(&option, _T("img\\option.png"), 450, 700);
	
	while (startGame)
	{
		Interface();
		state = mouse();
		BeginBatchDraw();

		if (state == NORMAL_MODE)
		{
			FlushMouseMsgBuffer();
			EndBatchDraw();
			Game game;
			int bestScore = game.getMaxScore();
			static char direction = 'w';	//�������ʼ��Ϊw
			game.generateNum();
			game.generateNum();
			game.saveStage(direction);
			game.printBoard();
			game.printMaxScore(bestScore);
			while (game.judge() == CONTINUE)
			{
				direction = _getch();	//���ȴ��س�����ȡ�û������wasd
				game.process(direction);
				if (tolower(direction) == 'w' || tolower(direction) == 'a'
					|| tolower(direction) == 's' || tolower(direction) == 'd')
					//ֻ���ڰ���w,a,s,d������²Ż���������
				{
					game.generateNum();
				}
				game.saveStage(direction);
				game.printBoard();
				game.printMaxScore(bestScore);
			}

			if (game.judge() == WIN)
			{
				Sleep(5000);		//��Ϸ�ɹ�ʱ��ͣ��5s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &win);
				startGame = back();
			}

			else if (game.judge() == LOSE)
			{
				Sleep(2000);		//��Ϸ����ʱ��ͣ��2s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &lose);
				startGame = back();
			}

			game.saveScore();
			EndBatchDraw();
		}



		else if (state == SPEED_MODE)
		{
			FlushMouseMsgBuffer();
			EndBatchDraw();
			putimage(0, 0, &option);
			int opt = choose();	//optΪchoose�����ķ���ֵ�������ٶ�ģʽ���е�ʱ����
			FlushMouseMsgBuffer();
			EndBatchDraw();
			AdvancedGame game;
			bool overTime = false;	//��¼�Ƿ�ʱ
			int bestScore = game.getMaxScore();
			static char direction = 'w';	//�������ʼ��Ϊw����֤��Ϸ��ʼʱ�������������
			game.generateNum();
			while (game.judge() == CONTINUE)
			{
				if (tolower(direction) == 'w' || tolower(direction) == 'a'
					|| tolower(direction) == 's' || tolower(direction) == 'd')
					game.generateNum();
				//ֻ���ڰ���WASDʱ�Ų��������
				game.printBoard();
				game.printMaxScore(bestScore);

				clock_t startTime = clock();	//��ʼ��ʱ
				direction = game.timer(startTime, opt);

				if (clock() - startTime >= opt * CLOCKS_PER_SEC)
				{
					overTime = true;
					break;	//������ǰ��Ϸѭ��
				}
				game.process(direction);
			}

			if (game.judge() == WIN && !overTime)
			{
				Sleep(5000);		//��Ϸ�ɹ�ʱ��ͣ��5s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &win);
				startGame = back();
			}

			else if (game.judge() == LOSE)
			{
				Sleep(2000);		//��Ϸ����ʱ��ͣ��2s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &lose);
				startGame = back();
			}

			else if (overTime)
			{
				Sleep(500);		//��ʱʱ��ͣ��0.5s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &runout);
				startGame = back();
			}

			game.saveScore();
			EndBatchDraw();

		}

			

		else if (state == RULE)
		{
			FlushMouseMsgBuffer();
			EndBatchDraw();
			putimage(0, 0, &rule);
			startGame = back();
		}



		else if (state == EXIT)
			{
				FlushMouseMsgBuffer();
				EndBatchDraw();
				closegraph();
				return 0;
			}
	
	}
}
