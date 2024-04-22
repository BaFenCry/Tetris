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
	void drop();  //�½�
	void moveLeftRight(int offset); //�����ƶ�
	void rotate(); //��ת
	void draw(int marginLeft,int marginTop); //���Ʒ���
	static IMAGE** getImages();
	Block& operator=(const Block &other);
	bool isLegal(const vector<vector<int>> & map); //�жϵ�ǰ�����˶��������Ƿ�Ϸ�
	void solidfy(vector<vector<int>>& map);
	int getBlockType();
private:
	int blockType; //��������
	Point smallBlock[4]; //�洢�ĸ�С�������λ�ã�������������
	IMAGE* img;
	static IMAGE* imgs[7];
	static int size;
};

