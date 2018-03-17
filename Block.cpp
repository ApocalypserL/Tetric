#include "Block.h"
#include "BlackBoard.h"
#include "UIController.h"
#include "time.h"

//数学知识捉鸡 还是用穷举吧 反正就几种
bool Matrix[19][4][4] = {
  {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},	//O

  {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, 	//J
  {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
  {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
  {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},

  {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},	//L
  {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
  {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
  {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},

  {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},	//S
  {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},

  {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},	//Z
  {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},

  {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},	//T
  {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
  {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
  {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},

  {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},	//I
  {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
  };

//16个虚拟方块 构造形状后对应位置被“实化”
Block::Block(int left, int top, int r, int c)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			boxes.push_back(Box(left, top, r + i, c + j));
		}
	}
	Generator(r, c);
}
//方块产生 类似于Box的Reset
void Block::Generator(int r, int c)
{
	srand(time(NULL));
	Shape() = rand() % 18;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			boxes[i * 4 + j].Reset(r + i, c + j, Matrix[Shape()][i][j]);
		}
	}
}

//疯狂赶工 有的地方用迭代器有的地方又没用
void Block::OnDraw(BlackBoard &board)
{
	for(vector<Box>::iterator iter = boxes.begin(); iter != boxes.end(); iter++)
	{
		if(iter->Validity()) iter->OnDraw(board);
	}
}
//移动
void Block::Move(int dx, int dy)
{
	for(vector<Box>::iterator iter = boxes.begin(); iter != boxes.end(); iter++)
	{
		iter->Move(dx, dy);
	}
}
//挨个方块判断能不能移动
bool Block::CanMove(int dx, int dy)
{
	for(vector<Box>::iterator iter = boxes.begin(); iter != boxes.end(); iter++)
	{
		if(iter->Validity())
		{
			if(!(iter->CanMove(dx, dy))) return false;
		}
	}
	return true;
}
//转 菜鸟判断法
void Block::Rotate()
{
	switch(Shape())
	{
		case 0:
			break;
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 9:
		case 11:
		case 13:
		case 14:
		case 15:
		case 17:
			Shape() += 1;
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
				{
					boxes[i * 4 + j].ChangeValidity(Matrix[Shape()][i][j]);
				}
			}
			break;
		case 4:
		case 8:
		case 16:
			Shape() = Shape() - 3;
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
				{
					boxes[i * 4 + j].ChangeValidity(Matrix[Shape()][i][j]);
				}
			}
			break;
		case 10:
		case 12:
		case 18:
			Shape() = Shape() - 1;
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
				{
					boxes[i * 4 + j].ChangeValidity(Matrix[Shape()][i][j]);
				}
			}
			break;
	}
}
//虚拟方块判断能不能转
bool Block::CanRotate()
{
	Block temp(*this);
	temp.Rotate(); 
	return (UIController::handle().HitBlock(temp));
}
