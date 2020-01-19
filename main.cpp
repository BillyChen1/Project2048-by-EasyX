/********************图形版2048游戏(Windows)*********************/
/************Created by 陈启明 陈航航 胡雅芳 吕欣*****************/
/***********实现功能：基本功能 包括撤销、计分、分数存档*************/
/**************扩展功能：速度模式 可自选限定时间*******************/

#include"Game.h"
#include<iostream>
#include<conio.h>	//使用_getch
#include<graphics.h>
#include<ctime>
#include<windows.h>

using namespace std;


/*声明图像对象*/
IMAGE bk;
IMAGE lose;
IMAGE win;
IMAGE runout;
IMAGE rule;
IMAGE option;



void Interface();	//画出主界面
int mouse();		//鼠标函数，控制游戏模式
int choose();		//鼠标函数，选择速度模式选项
int back();			////失败、时间耗尽、查看规则后返回主界面鼠标的操作



void Interface()
{
	putimage(0, 0, &bk);
}//画出主界面




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
}//鼠标函数，控制游戏模式




int back()
{
	while (true)
	{
		MOUSEMSG n;
		n = GetMouseMsg();
		if (n.mkLButton&&n.x >= 130 && n.x <= 300 && n.y >= 550 && n.y <= 600)
			return 1;
	}
}//失败、时间耗尽、查看规则后返回主界面鼠标的操作




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
		//获取鼠标点击状态，如正常模式、速度模式、规则、退出等

	int startGame = 1;	
		//可用于接受鼠标消息（是否按下返回），如果接受到，则回到主界面
	
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
			static char direction = 'w';	//将方向初始化为w
			game.generateNum();
			game.generateNum();
			game.saveStage(direction);
			game.printBoard();
			game.printMaxScore(bestScore);
			while (game.judge() == CONTINUE)
			{
				direction = _getch();	//不等待回车，读取用户输入的wasd
				game.process(direction);
				if (tolower(direction) == 'w' || tolower(direction) == 'a'
					|| tolower(direction) == 's' || tolower(direction) == 'd')
					//只有在按下w,a,s,d的情况下才会产生随机数
				{
					game.generateNum();
				}
				game.saveStage(direction);
				game.printBoard();
				game.printMaxScore(bestScore);
			}

			if (game.judge() == WIN)
			{
				Sleep(5000);		//游戏成功时，停留5s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &win);
				startGame = back();
			}

			else if (game.judge() == LOSE)
			{
				Sleep(2000);		//游戏结束时，停留2s
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
			int opt = choose();	//opt为choose函数的返回值，代表速度模式的中的时间间隔
			FlushMouseMsgBuffer();
			EndBatchDraw();
			AdvancedGame game;
			bool overTime = false;	//记录是否超时
			int bestScore = game.getMaxScore();
			static char direction = 'w';	//将方向初始化为w，保证游戏开始时产生两个随机数
			game.generateNum();
			while (game.judge() == CONTINUE)
			{
				if (tolower(direction) == 'w' || tolower(direction) == 'a'
					|| tolower(direction) == 's' || tolower(direction) == 'd')
					game.generateNum();
				//只有在按下WASD时才产生随机数
				game.printBoard();
				game.printMaxScore(bestScore);

				clock_t startTime = clock();	//开始计时
				direction = game.timer(startTime, opt);

				if (clock() - startTime >= opt * CLOCKS_PER_SEC)
				{
					overTime = true;
					break;	//跳出当前游戏循环
				}
				game.process(direction);
			}

			if (game.judge() == WIN && !overTime)
			{
				Sleep(5000);		//游戏成功时，停留5s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &win);
				startGame = back();
			}

			else if (game.judge() == LOSE)
			{
				Sleep(2000);		//游戏结束时，停留2s
				FlushMouseMsgBuffer();
				EndBatchDraw();
				putimage(0, 0, &lose);
				startGame = back();
			}

			else if (overTime)
			{
				Sleep(500);		//超时时，停留0.5s
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
