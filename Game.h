#pragma once
/*棋盘行列均为4*/
const int ROW = 4;
const int COL = 4;


/*输赢状态*/
const int WIN = 1;
const int CONTINUE = 2;
const int LOSE = 3;


const int GRID_SIZE = 100;		//格子大小
const int GRID_PADDING = 10;	//格子间距


/*鼠标响应状态*/
const int NORMAL_MODE = 0;
const int SPEED_MODE = 1;
const int RULE = 2;
const int EXIT = 3;


const int color[16] = {
	0x8a949e,0x2ec2ed,0xc8e0ed,0x79b1f2,
	0x6395f5,0x5f7cf6,0x3b5ef6,0x72cfed,
	0x61cced,0x50c8ed,0x3fc5ed,0x2ec2ed,
	0x50c8ed,0x2ec2ed,0xc8e0ed,0x79b1f2
};		//存储格子的颜色




class Game
{
public:
	Game();
	~Game();
	void generateNum();	//产生随机数
	void process(char);	//接收方向值，进行上下左右的移动操作
	void saveStage(char);	//用于每次生成随机数后，保存状态
	void printBoard();	//展示棋盘以及目前分数
	void printGrid(int, int, int);		//生成每个格子
	int judge();	//判断游戏输赢
	void saveScore();	//保存分数
	int getMaxScore();	//从文件中获取最高分
	void printMaxScore(int);	//展示最高分数
protected:
	int board[4][4];
	int lastBoard[2][4][4];	//存储当前和上一次4*4方格中的状态（每次生成随机数后存储）
	int score;	//分数
	int lastScore[2];	//存储当前和上一次的分数
};




class AdvancedGame: public Game
{
public:
	AdvancedGame();
	~AdvancedGame();
	void process(char);	//接收方向值，进行上下左右的移动操作
	void printTime(int);	//显示倒计时
	char timer(long, int);			//计时工具,接收开始计时的时间以及限定时间，返回按键方向值
};