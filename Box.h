#ifndef __BOX__
#define __BOX__

class BlackBoard; 

class Box
{
public:
	const static int BOX_SIZE = 20; 
	
	Box(){}
	Box(int left, int top, int r, int c); 

	void ChangeValidity(bool v)
	{
		_validity = v;
	}

	void Reset(int r, int c, bool v)
	{
		_row = r;
		_col = c;
		_validity = v;
	}

	void OnDraw(BlackBoard &board); 
	
	bool CanMove(int dx, int dy); 
	void Move(int dx, int dy); 
	
	bool LeftTo(int x)
	{
		return _left + _col * BOX_SIZE < x;
	}

	bool RightTo(int x)
	{
		return _left + (_col + 1) * BOX_SIZE - 1 > x; 
	}

	bool LowerTo(int y)
	{
		return _top + (-_row - 1) * BOX_SIZE + 1 < y; 
	}

	int Row() { return _row; }
	int Col() { return _col; }
	bool Validity() {return _validity;}

private:
	int _left, _top; 
	int _row, _col; 
	bool _validity;
}; 


#endif // #ifndef __BOX__
