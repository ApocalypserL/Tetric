﻿// Draw.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "BlackBoard.h"
#include "UIController.h"
using namespace std;
// 提供绘图环境的对象
BlackBoard board; 

void ReshapeCallback(int width, int height)
{
	board.UpdateWindowSize(width, height); 
}


// 定时器回调函数，具体功能逻辑交由UIController处理
void TimerCallback(int value)
{
	UIController::handle().OnTimer(value); 

	// GameSpeed在UIController中，可用于控制难度
	board.InstallTimerCallback(UIController::handle().GameSpeed(), TimerCallback, value); 
}

// 窗口用于处理键盘输入的回调函数入口，具体功能逻辑交由UIController处理
void KeyboardCallback(unsigned char key, int x, int y)
{
	UIController::handle().OnKey(key, x, y); 
}

// 窗口用于绘制的回调函数入口，具体功能逻辑交由UIController处理
void DisplayCallback()
{
	board.Clear(); 

	UIController::handle().OnDraw(board); 
	
	board.Flush(); 
}

int main(int argc, char* argv[])
{
	// 以下代码用于初始化窗口等、可忽略
	board.InitCommandLine(&argc, (char **)argv); 
	board.InitWindowSize(600, 1000); 

	board.InitDisplayCallback(DisplayCallback); 
	board.InitKeyboardCallback(KeyboardCallback); 
	board.InitReshapeCallback(ReshapeCallback); 

	board.InstallTimerCallback(UIController::handle().GameSpeed(), TimerCallback, 0);  

	board.Show(); 

	return 0;
}

