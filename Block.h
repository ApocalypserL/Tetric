#ifndef _BLOCK_H
#define _BLOCK_H

#include "Box.h"
#include <vector>

using std::vector;

class BlackBoard;

class Block
{
private:
	int _shape;
public:
	vector <Box> boxes;
	Block(){}
	Block(int left, int top, int r, int c);
	void Generator(int r, int c);
	void OnDraw(BlackBoard &board);
	void Move(int dx, int dy);
	bool CanMove(int dx, int dy);
	void Rotate();
	bool CanRotate();

	int Shape()const {return _shape;}
	int& Shape() {return _shape;}

protected:
};

#endif
