#include "Game.h"
#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<cstdlib>
#include<ctype.h>	//��Сдת������ֿ����û���Сд�������
#include<ctime>
#include<graphics.h>
#include<cmath>
#include<conio.h>	//��ʹ��_getch,_kbhit

using namespace std;


/*---------------------------Game------------------------------*/

Game::Game()
{
	for (int i = 0; i < ROW; i++)	//��ʼ������
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
		GRID_PADDING*(row+1) + GRID_SIZE * row,		//���Ͻ�����
		GRID_PADDING*col + GRID_SIZE * col,
		GRID_PADDING*(row+1) + GRID_SIZE * (row+1),		//���½�����
	};
	
	/*���ø�����ɫ*/
	int index;	//��Ϊcolor�±�
	if (number == 0)
	{
		index = 0;
	}
	else
	{
		index = log(number) / log(2);	//�����յ�����ת��Ϊ0-15�����֣���Ϊcolor�±�
	}
	setfillcolor(color[index]);	//�����ɫ



	/*������*/
	solidroundrect(		//������
		GRID_PADDING*col + GRID_SIZE * (col - 1),
		GRID_PADDING*(row+1) + GRID_SIZE * row,		//���Ͻ�����
		GRID_PADDING*col + GRID_SIZE * col,
		GRID_PADDING*(row+1) + GRID_SIZE * (row+1),		//���½�����
		10, 10);




	/*������*/
	TCHAR num[10];
	sprintf_s(num, sizeof(num), _T("%d"), number);	//������תΪ�ַ������ʹ���num
	if (number != 0)
	{
		if (number != 4)
			settextcolor(WHITE);
		else			//����4��Ӧǳɫ���������Ϊ4����������ɫ��Ϊ��ɫ
			settextcolor(BLACK);
		setbkmode(TRANSPARENT);	//���ֱ���͸�������ɫ��ͬ��
		settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
		drawtext(num, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//��ͼ�����������
	}

}




void Game::printBoard()
{
	/*system("cls");
	cout << "��Ϸ˵����w,a,s,d�����������ҷ���" << endl;
	cout << "x���ڳ���һ�β���(���ֻ���˻�һ����" << endl;
	for (int i = 0; i < ROW; i++)
	{
		cout << "---------------------------------" << endl;
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 0)	//����Ԫ��Ϊ0�����
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



	/*��ʾ��ǰ����*/
	RECT r = {
		GRID_PADDING,
		GRID_PADDING,		//���Ͻ�����
		GRID_PADDING*2 + GRID_SIZE * 2,
		GRID_PADDING + GRID_SIZE ,		//���½�����
	};

	setfillcolor(BLUE);

	solidroundrect (
		GRID_PADDING,
		GRID_PADDING,		//���Ͻ�����
		GRID_PADDING*2 + GRID_SIZE*2,
		GRID_PADDING  + GRID_SIZE ,		//���½�����
		10,10);
	
	
	TCHAR sc[10];
	sprintf_s(sc, sizeof(sc), _T("%d"), score);		//����ת��
	
	
	
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext("Your score:", &r, DT_TOP);	//�����ʾ��Ϣ
	drawtext(sc, &r, DT_SINGLELINE|DT_BOTTOM| DT_CENTER);	//��ͼ�����������
}




int Game::getMaxScore()
{
	int score = 0;
	FILE *fp;
	errno_t err;	//��ȫ��������
	err = fopen_s(&fp, "scoreFile.dat", "r");
	if (err)	//����ļ�û�б�����
	{
		err = fopen_s(&fp, "scoreFile.dat", "w");
		fprintf_s(fp, "%d", score, sizeof(int));	//�ʹ����ļ�����0д���ļ�
	}
	fscanf_s(fp, "%d", &score, sizeof(int));	//���ļ����ݶ����ڴ�
	fclose(fp);

	return score;
}




void Game::printMaxScore(int score)
{
	RECT r = {
		GRID_PADDING * 3 + GRID_SIZE * 2,
		GRID_PADDING,		//���Ͻ�����
		GRID_PADDING * 4 + GRID_SIZE * 4,
		GRID_PADDING + GRID_SIZE ,		//���½�����
	};

	setfillcolor(RED);

	solidroundrect(
		GRID_PADDING * 3 + GRID_SIZE * 2,
		GRID_PADDING,		//���Ͻ�����
		GRID_PADDING * 4 + GRID_SIZE * 4,
		GRID_PADDING + GRID_SIZE,		//���½�����
		10, 10);


	TCHAR sc[10];
	sprintf_s(sc, sizeof(sc), _T("%d"), score);		//����ת��


	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext("Best score:", &r, DT_TOP);	//�����ʾ��Ϣ
	drawtext(sc, &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);	//��ͼ�����������

}




void Game::generateNum()
{
	bool isFull = true;	//���ڼ�¼�Ƿ�������ʼֵ��Ϊ����״̬
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 0)
				isFull = false;
		}
	}
	
	if (isFull == false)	//���û�����������������
	{
		srand((unsigned)time(NULL));	//ʱ����Ϊ����ֵ
		int row;
		int col;
		do {						//�������������row������col(ͬʱ��֤��λ��û�����֣�
			row = rand() % ROW;
			col = rand() % COL;
		} while (board[row][col] != 0);

		int x = rand() % 10;
		if (x == 0)
			board[row][col] = 4;	//ʮ��֮һ�ĸ�������4
		else
			board[row][col] = 2;	//ʮ��֮�ŵĸ�������2
	}
}




void Game::process(char direction)
{
	switch (tolower(direction))
	{
	case'w':	//��
		for (int j = 0; j < COL; j++)	//���б���
		{
			for (int times = 0; times < 3; times++)		//�����£�������Ҫ3�Ρ����ߡ�����
			{
				for (int i = 0; i < ROW - 1; i++)	//��������ȫ�����Ͽ�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i + 1][j];
						board[i + 1][j] = 0;	//���board[i][j]Ϊ0�������·������ָ�������ͬʱ�·������ֱ�Ϊ0
					}
				}
			}

			for (int i = 0; i < ROW - 1; i++)		//��ͬ���ֺϲ�
			{
				if (board[i][j] == board[i + 1][j])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//�ӷ�
					board[i + 1][j] = 0;
				}
			}

			for (int i = 0; i < ROW - 1; i++)	//��������ȫ�����Ͽ�
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		break;
	


	case's':	//��
		for (int j = 0; j < COL; j++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int i = ROW - 1; i > 0; i--)	//��������ȫ�����¿�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i - 1][j];
						board[i - 1][j] = 0;	//���board[i][j]Ϊ0�������Ϸ������ָ�������ͬʱ�Ϸ������ֱ�Ϊ0
					}
				}
			}

			for (int i = ROW - 1; i > 0; i--)	//�ϲ�
			{
				if (board[i][j] == board[i - 1][j])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//�ӷ�
					board[i - 1][j] = 0;
				}
			}

			
			for (int i = ROW - 1; i > 0; i--)	//��������ȫ�����¿�
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i - 1][j];
					board[i - 1][j] = 0;
				}
			}
		}
		break;



	case'a':	//��
		for (int i = 0; i < ROW; i++)	
		{
			for (int times = 0; times < 3; times++)		
			{
				for (int j = 0; j < COL - 1; j++)	//ÿ����������
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j + 1];	
						board[i][j + 1] = 0;	//���board[i][j]Ϊ0�������ұߵ����ָ�������ͬʱ�ұߵ����ֱ�Ϊ0
					}
				}
			}

			for (int j = 0; j < COL - 1; j++)	//�ϲ�
			{
				if (board[i][j] == board[i][j + 1])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//�ӷ�
					board[i][j + 1] = 0;
				}
			}

			
			for (int j = 0; j < COL - 1; j++)	//ÿ����������
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		break;
	


	case'd':	//��
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = COL - 1; j > 0; j--)	//ÿ���������ҿ�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j - 1];
						board[i][j - 1] = 0;	//���board[i][j]Ϊ0��������ߵ����ָ�������ͬʱ��ߵ����ֱ�Ϊ0
					}
				}
			}

			for (int j = COL - 1; j > 0; j--)	//�ϲ�
			{
				if (board[i][j] == board[i][j - 1])
				{
					board[i][j] *= 2;	
					score+=board[i][j];		//�ӷ�
					board[i][j - 1] = 0;
				}
			}

			
			for (int j = COL - 1; j > 0; j--)	//ÿ���������ҿ�
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j - 1];
					board[i][j - 1] = 0;
				}
			}
		}
		break;



	case'x':	//����
		/*�����̵Ĳ���*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				board[i][j] = lastBoard[0][i][j];
			}
		}

		/*�Է����Ĳ���*/
		score = lastScore[0];
		
		break;


	default:
		;			//��������²����κ�����
	}
}




void Game::saveStage(char direction)
{
	
	static int score_1;			//���ڱ���score[0]����Ҫ���ڳ���
	static int board_1[4][4];	//���ڱ���lastBoard[0]����Ҫ���ڳ���
	
	
	//������ͨ������������,lastBoard[0]�����һ��״̬��[1]��ŵ�ǰ״̬
	if (tolower(direction) == 'w' || tolower(direction) == 'a'
		|| tolower(direction) == 's' || tolower(direction) == 'd')		
	{
		/*�����̵Ĳ���*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				board_1[i][j] = lastBoard[0][i][j];
				lastBoard[0][i][j] = lastBoard[1][i][j];
				lastBoard[1][i][j] = board[i][j];

				
			}
		}


		/*�Է����Ĳ���*/
		score_1 = lastScore[0];
		lastScore[0] = lastScore[1];
		lastScore[1] = score;
	}



	//����xΪ��������Ϊ���ڳ����ı������
	else if (tolower(direction) == 'x')		
	{
		/*�����̵Ĳ���*/
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				lastBoard[1][i][j] = lastBoard[0][i][j];
				lastBoard[0][i][j] = board_1[i][j];
			}
		}


		/*�Է����Ĳ���*/
		lastScore[1] = lastScore[0];
		lastScore[0] = score_1;
	}

	else;	//�������κ�����
}




int Game::judge()
{
	for (int i = 0; i < ROW; i++)	//��Ϸʤ���ж�
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == 2048)
				return WIN;
		}
	}


	for (int i = 0; i < ROW; i++)	//������
	{
		for (int j = 0; j < COL - 1; j++)
		{
			if (board[i][j] == 0 || board[i][j] == board[i][j + 1])		//������������Ȼ�ĳһ��Ϊ�գ���Ϸ����
				return CONTINUE;
		}
	}


	for (int j = 0; j < COL; j++)	//������
	{
		for (int i = 0; i < ROW - 1; i++)
		{
			if (board[i][j] == 0 || board[i][j] == board[i + 1][j])		//������������Ȼ�ĳһ��Ϊ�գ���Ϸ����
				return CONTINUE;
		}
	}


	return LOSE;	//���������Ϸ����
}




void Game::saveScore()
{
	FILE *fp;
	errno_t err;	
			//��ȫ��������
	int bestScore;


	err = fopen_s(&fp,"scoreFile.dat","r");	
	fscanf_s(fp, "%d", &bestScore, sizeof(int));	//ȡ���ļ��еķ�������bestScore
	fclose(fp);

	if (score > bestScore)
	{
		err = fopen_s(&fp, "scoreFile.dat", "w");
		fprintf_s(fp, "%d", score, sizeof(int));	//����ǰ���������ļ���
		fclose(fp);
	}
}






/*--------------------------AdvancedGame-------------------------------*/

AdvancedGame::AdvancedGame()
{
	for (int i = 0; i < ROW; i++)	//��ʼ������
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
	case'w':	//��
		for (int j = 0; j < COL; j++)	//���б���
		{
			for (int times = 0; times < 3; times++)		//�����£�������Ҫ3�Ρ����ߡ�����
			{
				for (int i = 0; i < ROW - 1; i++)	//��������ȫ�����Ͽ�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i + 1][j];
						board[i + 1][j] = 0;	//���board[i][j]Ϊ0�������·������ָ�������ͬʱ�·������ֱ�Ϊ0
					}
				}
			}

			for (int i = 0; i < ROW - 1; i++)		//��ͬ���ֺϲ�
			{
				if (board[i][j] == board[i + 1][j])
				{
					board[i][j] *= 2;
					score += board[i][j];		//�ӷ�
					board[i + 1][j] = 0;
				}
			}

			for (int i = 0; i < ROW - 1; i++)	//��������ȫ�����Ͽ�
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		break;



	case's':	//��
		for (int j = 0; j < COL; j++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int i = ROW - 1; i > 0; i--)	//��������ȫ�����¿�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i - 1][j];
						board[i - 1][j] = 0;	//���board[i][j]Ϊ0�������Ϸ������ָ�������ͬʱ�Ϸ������ֱ�Ϊ0
					}
				}
			}

			for (int i = ROW - 1; i > 0; i--)	//�ϲ�
			{
				if (board[i][j] == board[i - 1][j])
				{
					board[i][j] *= 2;
					score += board[i][j];		//�ӷ�
					board[i - 1][j] = 0;
				}
			}


			for (int i = ROW - 1; i > 0; i--)	//��������ȫ�����¿�
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i - 1][j];
					board[i - 1][j] = 0;
				}
			}
		}
		break;



	case'a':	//��
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = 0; j < COL - 1; j++)	//ÿ����������
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j + 1];
						board[i][j + 1] = 0;	//���board[i][j]Ϊ0�������ұߵ����ָ�������ͬʱ�ұߵ����ֱ�Ϊ0
					}
				}
			}

			for (int j = 0; j < COL - 1; j++)	//�ϲ�
			{
				if (board[i][j] == board[i][j + 1])
				{
					board[i][j] *= 2;
					score += board[i][j];		//�ӷ�
					board[i][j + 1] = 0;
				}
			}


			for (int j = 0; j < COL - 1; j++)	//ÿ����������
			{
				if (board[i][j] == 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		break;



	case'd':	//��
		for (int i = 0; i < ROW; i++)
		{
			for (int times = 0; times < 3; times++)
			{
				for (int j = COL - 1; j > 0; j--)	//ÿ���������ҿ�
				{
					if (board[i][j] == 0)
					{
						board[i][j] = board[i][j - 1];
						board[i][j - 1] = 0;	//���board[i][j]Ϊ0��������ߵ����ָ�������ͬʱ��ߵ����ֱ�Ϊ0
					}
				}
			}

			for (int j = COL - 1; j > 0; j--)	//�ϲ�
			{
				if (board[i][j] == board[i][j - 1])
				{
					board[i][j] *= 2;
					score += board[i][j];		//�ӷ�
					board[i][j - 1] = 0;
				}
			}


			for (int j = COL - 1; j > 0; j--)	//ÿ���������ҿ�
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
		;		//�������κ�����
	}
}




void AdvancedGame::printTime(int time)
{
	RECT r = {
		GRID_PADDING * 1 + GRID_SIZE,
		GRID_PADDING* 6 + GRID_SIZE * 5,		//���Ͻ�����
		GRID_PADDING * 4 + GRID_SIZE * 3,
		GRID_PADDING * 6 + GRID_SIZE * 6,		//���½�����
	};

	setfillcolor(GREEN);

	solidroundrect(
		GRID_PADDING * 1 + GRID_SIZE,
		GRID_PADDING * 6 + GRID_SIZE * 5,		//���Ͻ�����
		GRID_PADDING * 4 + GRID_SIZE * 3,
		GRID_PADDING * 6 + GRID_SIZE * 6,		//���½�����
		10, 10);


	TCHAR time1[10];
	sprintf_s(time1, sizeof(time1), _T("%d"), time);		//����ת��



	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Arial"), 0, 0, 50, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	drawtext(time1, &r, DT_TOP | DT_CENTER);	
	drawtext("seconds left", &r, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);	
}




char AdvancedGame::timer(long startTime, int limit)
{
	//limitΪ�޶�ʱ�䣬����Ƶ�����汾�У�limitֻ��ѡ��3s��Ϊ��ʹLimit�ɱ䣬�ʽ�����Ϊ�����ĵڶ����βΣ��ɸ�����ҵ�ѡ��������仯
	char direction;
	
	for (int times = limit; times > 0; times--)
	{
		printTime(times);
		while (clock() - startTime < (limit + 1 - times) * CLOCKS_PER_SEC)
		{
			if (_kbhit())	//�����wasd���룬����ֹͣ��ʱ
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
		if (_kbhit())	//�����wasd���룬����ֹͣ��ʱ
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
		if (_kbhit())	//�����wasd���룬����ֹͣ��ʱ
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

