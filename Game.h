#pragma once
/*�������о�Ϊ4*/
const int ROW = 4;
const int COL = 4;


/*��Ӯ״̬*/
const int WIN = 1;
const int CONTINUE = 2;
const int LOSE = 3;


const int GRID_SIZE = 100;		//���Ӵ�С
const int GRID_PADDING = 10;	//���Ӽ��


/*�����Ӧ״̬*/
const int NORMAL_MODE = 0;
const int SPEED_MODE = 1;
const int RULE = 2;
const int EXIT = 3;


const int color[16] = {
	0x8a949e,0x2ec2ed,0xc8e0ed,0x79b1f2,
	0x6395f5,0x5f7cf6,0x3b5ef6,0x72cfed,
	0x61cced,0x50c8ed,0x3fc5ed,0x2ec2ed,
	0x50c8ed,0x2ec2ed,0xc8e0ed,0x79b1f2
};		//�洢���ӵ���ɫ




class Game
{
public:
	Game();
	~Game();
	void generateNum();	//���������
	void process(char);	//���շ���ֵ�������������ҵ��ƶ�����
	void saveStage(char);	//����ÿ������������󣬱���״̬
	void printBoard();	//չʾ�����Լ�Ŀǰ����
	void printGrid(int, int, int);		//����ÿ������
	int judge();	//�ж���Ϸ��Ӯ
	void saveScore();	//�������
	int getMaxScore();	//���ļ��л�ȡ��߷�
	void printMaxScore(int);	//չʾ��߷���
protected:
	int board[4][4];
	int lastBoard[2][4][4];	//�洢��ǰ����һ��4*4�����е�״̬��ÿ�������������洢��
	int score;	//����
	int lastScore[2];	//�洢��ǰ����һ�εķ���
};




class AdvancedGame: public Game
{
public:
	AdvancedGame();
	~AdvancedGame();
	void process(char);	//���շ���ֵ�������������ҵ��ƶ�����
	void printTime(int);	//��ʾ����ʱ
	char timer(long, int);			//��ʱ����,���տ�ʼ��ʱ��ʱ���Լ��޶�ʱ�䣬���ذ�������ֵ
};