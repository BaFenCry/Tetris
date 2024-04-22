#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <graphics.h>
#include <conio.h>
#include "Block.h"
#define MAX_LEVEL 5
const int SPEED_NORMAL[MAX_LEVEL] = { 500,300,150,100,80 };

using namespace std;

class Tetris
{
public:
	Tetris(int rows, int cols, int margin_left, int margin_top,int blockSize);   //��Ϸ��������������߽磬�ϱ߽磬�����С
	void init(); //��Ϸ��ʼ��
	void play(); //��Ϸ����
private:
	void keyEvent();
	void updateWindow();
	int getDelay();  //���ؾ�����һ�ε��øú���������˶���ʱ��(ms)
	void drop();
	void rotate();
	void clearLine();
	void moveLeftRight(int offset);
	void drawScore();
private:
	IMAGE imgBg;
	int delay;  //��Ϸ�ӳ�
	int update;//�Ƿ����
	int rows; //����
	int cols; //����
	int margin_left;  //��߽�
	int margin_top;   //�ϱ߽�
	int blockSize;    //�����С
	vector<vector<int>> map;  //��Ϸ�������ݴ洢,1..7��ʾ��λ���еڣ�1..7���ַ��飬0��ʾ��λ��û�з���

	Block* curBlock;  //��ǰ����
	Block* nextBlock; //��һ������
	Block baBlock;  //��ǰ���齵������У�������һ���Ϸ�λ��

	int score;
	int level;
	int lineCount; 
};

