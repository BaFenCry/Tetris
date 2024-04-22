#include "Tetris.h"
const int SPEED_QUICK = 40;


Tetris::Tetris(int rows, int cols, int margin_left, int margin_top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->margin_left = margin_left;
	this->margin_top = margin_top;
	this->blockSize = blockSize;
	for (int i = 0; i < rows; ++i) {
		vector<int> row;
		for (int j = 0; j < cols; ++j) {
			row.push_back(0);
		}
		map.push_back(row);
	}
}

void Tetris::init()
{
	//�����������
	srand(time(NULL));
	delay = SPEED_NORMAL[0];
	//update = true;
	//������Ϸ����
	initgraph(500,478,1);
	//����ͼƬ 
	loadimage(&imgBg, "res/bg2.png");
	//��ʼ����Ϸ����
	for (int i = 0; i < rows; ++i) {
		vector<int> row;
		for (int j = 0; j < cols; ++j) {
			map[i][j] = 0;
		}
	}
	score = 0;
	lineCount = 0;
	level = 1;
}

void Tetris::play()
{
	init();
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;
	int timer = 0;
	while (1) {
		//�����û�����
		keyEvent();
		timer += getDelay();
		if (timer > delay) {
			cout << delay << endl;
			drop();
			timer = 0;
			update = true;
		}
		if (update) {
			update = false;
			//��Ⱦ��Ϸ����
			updateWindow();
			//������Ϸ����(�������еķ���)
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{
	bool rotateFlag = false;
	char op;
	int dx = 0;
	if (_kbhit()) {
		op=_getch();
		if (op == 'w' || op=='W') {
			rotateFlag = true;
		}
		else if(op=='s' || op=='S') {
			//cout << "test" << endl;
			delay = SPEED_QUICK;
		}
		else if (op == 'a' || op == 'A') {
			dx = -1;
		}
		else if (op == 'd' || op == 'D') {
			dx = 1;
		}
	}
	if (rotateFlag) {
		rotate();
		update = true;
	}
	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}

}

void Tetris::updateWindow()
{
	BeginBatchDraw();
	IMAGE** imgs = Block::getImages();
	putimage(0,0,&imgBg); //���Ʊ���
	curBlock->draw(margin_left, margin_top); //��ǰ����
	nextBlock->draw(360, 70);  //Ԥ�淽��
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] == 0) continue;
			int x = margin_left + j * blockSize;
			int y = margin_top + i * blockSize;
			putimage(x, y, imgs[map[i][j]-1]);
		}
	}
	drawScore();
	EndBatchDraw();
}

int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	//cout << currentTime << endl;
	if (lastTime == 0) {
		lastTime = currentTime;
		//cout << "test" << endl;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		//cout << ret << endl;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::drop()
{
	baBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->isLegal(map)) {  //�޷��ƶ�
		//�����޷��½�,�̶�����
		baBlock.solidfy(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}
	delay = SPEED_NORMAL[level-1];
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7) return;
	baBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->isLegal(map)) {
		*curBlock = baBlock;
	}
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1;
	for (int i = rows - 1; i >= 0; --i) {
		int count = 0;
		for (int j = 0; j < cols; ++j) {
			if (map[i][j]) {
				++count;
			}
			map[k][j] = map[i][j];
		}
		if (count != cols) {
			--k;
		}
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		update = true;
		level = (score + 99) / 100;
	}
}

void Tetris::moveLeftRight(int offset)
{
	curBlock->moveLeftRight(offset);
	if (!curBlock->isLegal(map)) {
		*curBlock = baBlock;
	}

}

void Tetris::drawScore()
{
	char text[32];
	sprintf_s(text, sizeof(text), "%d", score);
	//outtextxy(430, 377, text);
	setcolor(RGB(180, 180, 180));
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 100;
	f.lfHeight = 50;
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI BLACK"));
	settextstyle(&f);
	setbkmode(TRANSPARENT); //͸��Ч��
	outtextxy(430, 355, text);

}
