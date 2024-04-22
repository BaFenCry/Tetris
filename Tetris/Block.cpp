#include "Block.h"

IMAGE* Block::imgs[7] = { NULL, };
int Block::size = 19;

IMAGE** Block::getImages()
{
	return imgs;
}


Block& Block::operator=(const Block& other)
{
	if (this == &other) return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; ++i) {
		this->smallBlock[i] = other.smallBlock[i];
	}
	return *this;
}

bool Block::isLegal(const vector<vector<int>>& map)
{
	int rows = map.size(), cols = map[0].size();
	for (int i = 0; i < 4; ++i) {
		if (smallBlock[i].col < 0 || smallBlock[i].col >= cols || smallBlock[i].row <0 || smallBlock[i].row >= rows || map[smallBlock[i].row][smallBlock[i].col]) {
			return false;
		}
	}
	return true;
}

void Block::solidfy(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; ++i) {
		//固化方块
		map[smallBlock[i].row][smallBlock[i].col] = blockType;
		cout << blockType << endl;
	}
}

int Block::getBlockType()
{
	return blockType;
}

Block::Block()
{
	int blocks[7][4] = {
		1,3,5,7,// I型
		2,4,5,7,// Z 1型
		3,5,4,6,// Z 2型
		3,5,4,7,// T
		2,3,5,7,// L
		3,5,7,6,// J
		2,3,4,5 // 田型
	};
	if (imgs[0] == NULL) {
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < 7; ++i) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size,0,size,size);
		}
		SetWorkingImage();
	}
	//随机生成某种俄罗斯方块(1...7)
	blockType = 1 + rand() % 7;
	//初始化smallBlock数组
	for (int i = 0; i < 4; ++i) {
		int value = blocks[blockType - 1][i];
		smallBlock[i].row = value / 2;
		smallBlock[i].col = value % 2;
	}
	img = imgs[blockType-1];
}

void Block::drop()
{
	for (auto& block : smallBlock) {
		block.row++;
	}
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; ++i) {
		smallBlock[i].col += offset;
	}
}

void Block::rotate()
{
	Point p = smallBlock[1];
	for (int i = 0; i < 4; ++i) {
		Point temp = smallBlock[i];
		smallBlock[i].col = p.col - temp.row + p.row;
		smallBlock[i].row = p.row + temp.col - p.col;
	}
}

void Block::draw(int marginLeft, int marginTop)
{
	for (int i = 0; i < 4; ++i) {
		int x = marginLeft+ smallBlock[i].col * size;
		int y = marginTop + smallBlock[i].row * size;
		putimage(x, y, img);
	}
}
