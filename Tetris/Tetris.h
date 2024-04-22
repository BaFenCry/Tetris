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
	Tetris(int rows, int cols, int margin_left, int margin_top,int blockSize);   //游戏行数，列数，左边界，上边界，方块大小
	void init(); //游戏初始化
	void play(); //游戏控制
private:
	void keyEvent();
	void updateWindow();
	int getDelay();  //返回距离上一次调用该函数，间隔了多少时间(ms)
	void drop();
	void rotate();
	void clearLine();
	void moveLeftRight(int offset);
	void drawScore();
private:
	IMAGE imgBg;
	int delay;  //游戏延迟
	int update;//是否更新
	int rows; //行数
	int cols; //列数
	int margin_left;  //左边界
	int margin_top;   //上边界
	int blockSize;    //方块大小
	vector<vector<int>> map;  //游戏方块数据存储,1..7表示该位置有第（1..7）种方块，0表示该位置没有方块

	Block* curBlock;  //当前方块
	Block* nextBlock; //下一个方块
	Block baBlock;  //当前方块降落过程中，备份上一个合法位置

	int score;
	int level;
	int lineCount; 
};

