#include "Game.h"
#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<cstdlib>
#include<ctype.h>	//大小写转换，充分考虑用户大小写输入情况
#include<ctime>
#include<graphics.h>
#include<cmath>
#include<conio.h>	//可使用_getch,_kbhit

using namespace std;


/*---------------------------Game------------------------------*/

Game::Game()
{
	for (int i = 0; i < ROW; i++)	//初始化数组
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = 0;
			lastBoard[0][i][j] = 0;
			lastBoard[1][i][j] = 0;
			lastScore[0] = 0;
			lastScore[1] = 0;
		}
	}

	score = 0;
}




Game::~Game()
{
}




void Game::printGrid(int row, int col, int number)
{
	RECT r = {
		GRID_PADDING*col + GRID_SIZE * (col - 1),
		GRID_PADDING*(row+1) + GRID_SIZE * row,		//左上角坐标
		GRID_PADDING*col + GRID_SIZE * col,
		GRID_PADDING*(row+1) + GRID_SIZE * (row+1),		//右下角坐标
	};
	
	/*设置格子颜色*/
	int index;	//作为color下标
	if (number == 0)
	{
		index = 0;
	}
	else
	{
		index = log(number) / log(2);	//将接收的数字转化为0-15的数字，作为color下标
	}
	setfillcolor(color[index]);	//填充颜色



	/*画格子*/
	solidroundrect(		//画格子
		GRID_PADDING*col + GRID_SIZE * (col - 1),
		GRID_PADDING*(row+1) + GRID_SIZE * row,		//左上角坐标
		GRID_PADDING*col + GRID_SIZE * col,
		GRID_PADDING*(row+1) + GRID_SIZE * (row+1),		//右下角坐标
		10, 10);




	/*填数字*/
	TCHAR num[10];
	sprintf_s(num, sizeof(num), _T("%d"), number);	//将数字转为字符串类型存入num
	if (number != 0)
	{
		if (number != 4)
			settextcolor(WHITE);
		else			//由于4对应浅色背景，如果为4，将字体颜色设为黑色
			settextcolor(BLACK);
		setbkmode(TRANSPARENT);	//文字背景透明（与底色相同）
		settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//向图形里填充数字
	}

}




void Game::printBoard()
{
	/*system("cls");
	cout << "游戏说明：w,a,s,d控制上下左右方向" << endl;
	cout << "x用于撤销一次操作(最多只能退回一步）" << endl;
	for (int i = 0; i < ROW; i++)
	{
		cout << "---------------------------------" << endl;
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 0)	//数组元素为0代表空
			{
				cout << "|   \t";
			}

			else
			{
				cout << "|   " << board[i][j] << "\t";
			}
		}
		cout << "|" << endl;
	}

	cout << "---------------------------------" << endl;
	*/

	cleardevice();
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			printGrid(i, j, board[i - 1][j - 1]);
		}
	}



	/*显示当前分数*/
	RECT r = {
		GRID_PADDING,
		GRID_PADDING,		//左上角坐标
		GRID_PADDING*2 + GRID_SIZE * 2,
		GRID_PADDING + GRID_SIZE ,		//右下角坐标
	};

	setfillcolor(BLUE);

	solidroundrect (
		GRID_PADDING,
		GRID_PADDING,		//左上角坐标
		GRID_PADDING*2 + GRID_SIZE*2,
		GRID_PADDING  + GRID_SIZE ,		//右下角坐标
		10,10);
	
	
	TCHAR sc[10];
	sprintf_s(sc, sizeof(sc), _T("%d"), score);		//类型转换
	
	
	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext("Your score:", &r, DT_TOP);	//填充提示信息
	drawtext(sc, &r, DT_SINGLELINE|DT_BOTTOM| DT_CENTER);	//向图形里填充数字
}




int Game::getMaxScore()
{
	int score = 0;
	FILE *fp;
	errno_t err;	//安全函数必须
	err = fopen_s(&fp, "scoreFile.dat", "r");
	if (err)	//如果文件没有被创建
	{
		err = fopen_s(&fp, "scoreFile.dat", "w");
		fprintf_s(fp, "%d", score, sizeof(int));	//就创建文件并将0写入文件
	}
	fscanf_s(fp, "%d", &score, sizeof(int));	//将文件内容读到内存
	fclose(fp);

	return score;
}




void Game::printMaxScore(int score)
{
	RECT r = {
		GRID_PADDING * 3 + GRID_SIZE * 2,
		GRID_PADDING,		//左上角坐标
		GRID_PADDING * 4 + GRID_SIZE * 4,
		GRID_PADDING + GRID_SIZE ,		//右下角坐标
	};

	setfillcolor(RED);

	solidroundrect(
		GRID_PADDING * 3 + GRID_SIZE * 2,
		GRID_PADDING,		//左上角坐标
		GRID_PADDING * 4 + GRID_SIZE * 4,
		GRID_PADDING + GRID_SIZE,		//右下角坐标
		10, 10);


	TCHAR sc[10];
	sprintf_s(sc, sizeof(sc), _T("%d"), score);		//类型转换


	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext("Best score:", &r, DT_TOP);	//填充提示信息
	drawtext(sc, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);	//向图形里填充数字

}




void Game::generateNum()
{
	bool isFull = true;	//用于记录是否满格，起始值设为满格状态
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 0)
				isFull = false;
		}
	}
	
	if (isFull == false)	//如果没有满格，则生成随机数
	{
		srand((unsigned)time(NULL));	//时间作为种子值
		int row;
		int col;
		do {						//生成随机的行数row、列数col(同时保证该位置没有数字）
			row = rand() % ROW;
			col = rand() % COL;
		} while (board[row][col] != 0);

		int x = rand() % 10;
		if (x == 0)
			board[row][col] = 4;	//十分之一的概率生成4
		else
			board[row][col] = 2;	//十分之九的概率生成2
	}
}




void Game::process(char direction)
{
	switch (tolower(direction))
	{
	case'w':	//上
		for (int j = 0; j < COL; j++)	//按列遍历
		{
			for (int times = 0; times < 3; times++)		//最坏情况下，至少需要3次“靠边”操作
			{
				for (int i = 0; i < ROW - 1; i++)	//该列数字全部向上靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i + 1][j];
						board[i + 1][j] = 0;	//如果board[i][j]为0，将其下方的数字赋给它，同时下方的数字变为0
					}
				}
			}

			for (int i = 0; i < ROW - 1; i++)		//相同数字合并
			{
				if (board[i][j] == board[i + 1][j])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//加分
					board[i + 1][j] = 0;
				}
			}

			for (int i = 0; i < ROW - 1; i++)	//该列数字全部向上靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		break;
	


	case's':	//下
		for (int j = 0; j < COL; j++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int i = ROW - 1; i > 0; i--)	//该列数字全部向下靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i - 1][j];
						board[i - 1][j] = 0;	//如果board[i][j]为0，将其上方的数字赋给它，同时上方的数字变为0
					}
				}
			}

			for (int i = ROW - 1; i > 0; i--)	//合并
			{
				if (board[i][j] == board[i - 1][j])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//加分
					board[i - 1][j] = 0;
				}
			}

			
			for (int i = ROW - 1; i > 0; i--)	//该列数字全部向下靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i - 1][j];
					board[i - 1][j] = 0;
				}
			}
		}
		break;



	case'a':	//左
		for (int i = 0; i < ROW; i++)	
		{
			for (int times = 0; times < 3; times++)		
			{
				for (int j = 0; j < COL - 1; j++)	//每行数字向左靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j + 1];	
						board[i][j + 1] = 0;	//如果board[i][j]为0，将其右边的数字赋给它，同时右边的数字变为0
					}
				}
			}

			for (int j = 0; j < COL - 1; j++)	//合并
			{
				if (board[i][j] == board[i][j + 1])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//加分
					board[i][j + 1] = 0;
				}
			}

			
			for (int j = 0; j < COL - 1; j++)	//每行数字向左靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		break;
	


	case'd':	//右
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = COL - 1; j > 0; j--)	//每行数字向右靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j - 1];
						board[i][j - 1] = 0;	//如果board[i][j]为0，将其左边的数字赋给它，同时左边的数字变为0
					}
				}
			}

			for (int j = COL - 1; j > 0; j--)	//合并
			{
				if (board[i][j] == board[i][j - 1])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//加分
					board[i][j - 1] = 0;
				}
			}

			
			for (int j = COL - 1; j > 0; j--)	//每行数字向右靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j - 1];
					board[i][j - 1] = 0;
				}
			}
		}
		break;



	case'x':	//撤销
		/*对棋盘的操作*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				board[i][j] = lastBoard[0][i][j];
			}
		}

		/*对分数的操作*/
		score = lastScore[0];
		
		break;


	default:
		;			//其他情况下不做任何事情
	}
}




void Game::saveStage(char direction)
{
	
	static int score_1;			//用于保存score[0]，主要用于撤销
	static int board_1[4][4];	//用于保存lastBoard[0]，主要用于撤销
	
	
	//基于普通方向键保存操作,lastBoard[0]存放上一次状态，[1]存放当前状态
	if (tolower(direction) == 'w' || tolower(direction) == 'a'
		|| tolower(direction) == 's' || tolower(direction) == 'd')		
	{
		/*对棋盘的操作*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				board_1[i][j] = lastBoard[0][i][j];
				lastBoard[0][i][j] = lastBoard[1][i][j];
				lastBoard[1][i][j] = board[i][j];

				
			}
		}


		/*对分数的操作*/
		score_1 = lastScore[0];
		lastScore[0] = lastScore[1];
		lastScore[1] = score;
	}



	//按下x为撤销，此为基于撤销的保存操作
	else if (tolower(direction) == 'x')		
	{
		/*对棋盘的操作*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				lastBoard[1][i][j] = lastBoard[0][i][j];
				lastBoard[0][i][j] = board_1[i][j];
			}
		}


		/*对分数的操作*/
		lastScore[1] = lastScore[0];
		lastScore[0] = score_1;
	}

	else;	//否则不做任何事情
}




int Game::judge()
{
	for (int i = 0; i < ROW; i++)	//游戏胜利判断
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 2048)
				return WIN;
		}
	}


	for (int i = 0; i < ROW; i++)	//横向检查
	{
		for (int j = 0; j < COL - 1; j++)
		{
			if (board[i][j] == 0 || board[i][j] == board[i][j + 1])		//横向相邻项相等或某一项为空，游戏继续
				return CONTINUE;
		}
	}


	for (int j = 0; j < COL; j++)	//纵向检查
	{
		for (int i = 0; i < ROW - 1; i++)
		{
			if (board[i][j] == 0 || board[i][j] == board[i + 1][j])		//纵向相邻项相等或某一项为空，游戏继续
				return CONTINUE;
		}
	}


	return LOSE;	//其它情况游戏结束
}




void Game::saveScore()
{
	FILE *fp;
	errno_t err;	
			//安全函数必须
	int bestScore;


	err = fopen_s(&fp,"scoreFile.dat","r");	
	fscanf_s(fp, "%d", &bestScore, sizeof(int));	//取出文件中的分数存入bestScore
	fclose(fp);

	if (score > bestScore)
	{
		err = fopen_s(&fp, "scoreFile.dat", "w");
		fprintf_s(fp, "%d", score, sizeof(int));	//将当前分数存入文件中
		fclose(fp);
	}
}






/*--------------------------AdvancedGame-------------------------------*/

AdvancedGame::AdvancedGame()
{
	for (int i = 0; i < ROW; i++)	//初始化数组
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = 0;
		}
	}

	score = 0;
}




AdvancedGame::~AdvancedGame()
{
}




void AdvancedGame::process(char direction)
{
	switch (tolower(direction))
	{
	case'w':	//上
		for (int j = 0; j < COL; j++)	//按列遍历
		{
			for (int times = 0; times < 3; times++)		//最坏情况下，至少需要3次“靠边”操作
			{
				for (int i = 0; i < ROW - 1; i++)	//该列数字全部向上靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i + 1][j];
						board[i + 1][j] = 0;	//如果board[i][j]为0，将其下方的数字赋给它，同时下方的数字变为0
					}
				}
			}

			for (int i = 0; i < ROW - 1; i++)		//相同数字合并
			{
				if (board[i][j] == board[i + 1][j])
				{
					board[i][j] *= 2;
					score += board[i][j];		//加分
					board[i + 1][j] = 0;
				}
			}

			for (int i = 0; i < ROW - 1; i++)	//该列数字全部向上靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		break;



	case's':	//下
		for (int j = 0; j < COL; j++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int i = ROW - 1; i > 0; i--)	//该列数字全部向下靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i - 1][j];
						board[i - 1][j] = 0;	//如果board[i][j]为0，将其上方的数字赋给它，同时上方的数字变为0
					}
				}
			}

			for (int i = ROW - 1; i > 0; i--)	//合并
			{
				if (board[i][j] == board[i - 1][j])
				{
					board[i][j] *= 2;
					score += board[i][j];		//加分
					board[i - 1][j] = 0;
				}
			}


			for (int i = ROW - 1; i > 0; i--)	//该列数字全部向下靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i - 1][j];
					board[i - 1][j] = 0;
				}
			}
		}
		break;



	case'a':	//左
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = 0; j < COL - 1; j++)	//每行数字向左靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j + 1];
						board[i][j + 1] = 0;	//如果board[i][j]为0，将其右边的数字赋给它，同时右边的数字变为0
					}
				}
			}

			for (int j = 0; j < COL - 1; j++)	//合并
			{
				if (board[i][j] == board[i][j + 1])
				{
					board[i][j] *= 2;
					score += board[i][j];		//加分
					board[i][j + 1] = 0;
				}
			}


			for (int j = 0; j < COL - 1; j++)	//每行数字向左靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		break;



	case'd':	//右
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = COL - 1; j > 0; j--)	//每行数字向右靠
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j - 1];
						board[i][j - 1] = 0;	//如果board[i][j]为0，将其左边的数字赋给它，同时左边的数字变为0
					}
				}
			}

			for (int j = COL - 1; j > 0; j--)	//合并
			{
				if (board[i][j] == board[i][j - 1])
				{
					board[i][j] *= 2;
					score += board[i][j];		//加分
					board[i][j - 1] = 0;
				}
			}


			for (int j = COL - 1; j > 0; j--)	//每行数字向右靠
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j - 1];
					board[i][j - 1] = 0;
				}
			}
		}
		break;

	default:
		;		//否则不做任何事情
	}
}




void AdvancedGame::printTime(int time)
{
	RECT r = {
		GRID_PADDING * 1 + GRID_SIZE,
		GRID_PADDING* 6 + GRID_SIZE * 5,		//左上角坐标
		GRID_PADDING * 4 + GRID_SIZE * 3,
		GRID_PADDING * 6 + GRID_SIZE * 6,		//右下角坐标
	};

	setfillcolor(GREEN);

	solidroundrect(
		GRID_PADDING * 1 + GRID_SIZE,
		GRID_PADDING * 6 + GRID_SIZE * 5,		//左上角坐标
		GRID_PADDING * 4 + GRID_SIZE * 3,
		GRID_PADDING * 6 + GRID_SIZE * 6,		//右下角坐标
		10, 10);


	TCHAR time1[10];
	sprintf_s(time1, sizeof(time1), _T("%d"), time);		//类型转换



	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext(time1, &r, DT_TOP | DT_CENTER);	
	drawtext("seconds left", &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);	
}




char AdvancedGame::timer(long startTime, int limit)
{
	//limit为限定时间，在设计的最初版本中，limit只能选择3s，为了使Limit可变，故将其作为函数的第二个形参，可根据玩家的选择而发生变化
	char direction;
	
	for (int times = limit; times > 0; times--)
	{
		printTime(times);
		while (clock() - startTime < (limit + 1 - times) * CLOCKS_PER_SEC)
		{
			if (_kbhit())	//如果有wasd输入，立即停止计时
			{
				direction = _getch();
				if (tolower(direction) == 'w' || tolower(direction) == 'a'
					|| tolower(direction) == 's' || tolower(direction) == 'd')
				{
					return direction;
				}
			}

		}
	}

	/*printTime(2);
	while (clock() - startTime < 2 * CLOCKS_PER_SEC)
	{
		if (_kbhit())	//如果有wasd输入，立即停止计时
		{
			direction = _getch();
			if (tolower(direction) == 'w' || tolower(direction) == 'a' 
				|| tolower(direction) == 's' || tolower(direction) == 'd')
			{
				return direction;
			}
		}

	}


	printTime(1);
	while (clock() - startTime < 3 * CLOCKS_PER_SEC)
	{
		if (_kbhit())	//如果有wasd输入，立即停止计时
		{
			direction = _getch();
			if (tolower(direction) == 'w' || tolower(direction) == 'a' 
				|| tolower(direction) == 's' || tolower(direction) == 'd')
			{
				return direction;
			}
		}

	}*/


	printTime(0);
}

