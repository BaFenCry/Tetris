#pragma once
#include <stdlib.h>
#include <graphics.h>
#include <vector>
#include <iostream>
using namespace std;

extern int blocks[7][4];

struct Point {
	int row, col;
	Point(int r=0,int c=0):row(r),col(c){}
};

class Block
{
public:
	Block();
	void drop();  //下降
	void moveLeftRight(int offset); //左右移动
	void rotate(); //旋转
	void draw(int marginLeft,int marginTop); //绘制方块
	static IMAGE** getImages();
	Block& operator=(const Block &other);
	bool isLegal(const vector<vector<int>> & map); //判断当前方块运动过程中是否合法
	void solidfy(vector<vector<int>>& map);
	int getBlockType();
private:
	int blockType; //方块类型
	Point smallBlock[4]; //存储四个小方块具体位置（行数和列数）
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

