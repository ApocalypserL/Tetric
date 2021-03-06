﻿#include <iostream>

#include "UIController.h"
#include "BlackBoard.h"

extern BlackBoard board; 

UIController::UIController() : _left(-(COLS * Box::BOX_SIZE / 2)), _bottom(-ROWS * Box::BOX_SIZE / 2), _right(COLS * Box::BOX_SIZE / 2), _top(ROWS * Box::BOX_SIZE / 2), _block(_left, _top, 0, INITIAL_COL)
{
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// 初始没有固定方块
			_boxes[r][c] = false; 
		}
	}
}

UIController::~UIController()
{
}

void UIController::OnDraw(BlackBoard &board) 
{ 
	board.SetColor(1, 0, 1); 
	board.DrawLine(_left,  _top,   _left,  _bottom);
	board.DrawLine(_left,  _top,   _right, _top);
	board.DrawLine(_left,  _bottom,_right, _bottom);
	board.DrawLine(_right, _top,   _right, _bottom);

	board.SetColor(1, 0, 0); 
	_block.OnDraw(board); 

	board.SetColor(0, 1, 1); 
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			if (_boxes[r][c])
			{
				// 借助Box类绘制固定方块
				Box box(_left, _top, r, c); 
				box.OnDraw(board); 
			}
		}
	}
}


void UIController::OnTimer(int code)
{
	MoveBlockDown(); 
}

void UIController::OnKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break; 
	case 'w':
		Rotate();
		break;
	case 's':
		MoveBlockDown(); 
		break; 
	case 'a':
		MoveBlockLeft(); 
		break; 
	case 'd':
		MoveBlockRight(); 
		break; 
	}
}

bool UIController::HitLeft(Box &box)
{
	return box.LeftTo(_left); 
}

bool UIController::HitRight(Box &box)
{
	return box.RightTo(_right); 
}

bool UIController::HitBottom(Box &box)
{
	return box.LowerTo(_bottom); 
}

bool UIController::HitBoxes(Box &box)
{
	return _boxes[box.Row()][box.Col()]; 
}

bool UIController::HitBlock(Block &block)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			if(block.boxes[i * 4 + j].Validity())
			{
				if(block.boxes[i * 4 + j].LeftTo(_left))return false;
				if(block.boxes[i * 4 + j].RightTo(_right))return false;
				if(block.boxes[i * 4 + j].LowerTo(_bottom))return false;
				if(_boxes[block.boxes[i * 4 + j].Row()][block.boxes[i * 4 + j].Col()])return false;
			}
		}
	}
	return true;
}

void UIController::EraseFullRows()
{
	for (int r = 0; r < ROWS; ++r)
	{
		bool fulled = true; 
		for (int c = 0; c < COLS; ++c)
		{
			if (!_boxes[r][c]) 
			{
				// 任意一个位置无固定方块，则满行条件不满足，跳过
				fulled = false; 
				break; 
			}
		}

		if (fulled)
		{
			PushRows(r); 
		}
	}
}

void UIController::PushRows(int row)
{
	for (int r = row; r > 0; --r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// row行之上方块下落
			_boxes[r][c] = _boxes[r - 1][c]; 
		}
	}

	for (int c = 0; c < COLS; ++c)
	{
		// 最顶层一行置空
		_boxes[0][c] = false; 
	}
}

void UIController::MoveBlockLeft()
{
	if (_block.CanMove(0, -1))
	{
		_block.Move(0, -1); 
		board.Update(); 
	}
}

void UIController::MoveBlockRight()
{
	if (_block.CanMove(0, 1))
	{
		_block.Move(0, 1); 
		board.Update(); 
	}
}

void UIController::MoveBlockDown()
{
	if (_block.CanMove(1, 0))
	{
		_block.Move(1, 0); 
		board.Update(); 
	}
	else
	{
		//先判断是不是GG了
		GameOver();
		// 无法下移，则说明下方有障碍（边界或固定方块），则活动方块插入固定方块中
		InsertBlock(_block);

		// 清除满行
		EraseFullRows(); 

		// 活动方块重置，相当于新生成一个新的活动方块
		//_box.Reset(0, INITIAL_COL); 
		_block.Generator(0, INITIAL_COL - 1);
		board.Update(); 
	}
}

void UIController::Rotate()
{
	if (_block.CanRotate())
	{
		_block.Rotate(); 
		board.Update(); 
	}
}

void UIController::GameOver()
{
	for (int c = INITIAL_COL - 2; c < INITIAL_COL + 2; ++c)
	{
		if(_boxes[0][c]) exit(1);
	}
}

