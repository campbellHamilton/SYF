#include "layer.h"
#include "box.h"
layer::layer(){}
void layer::push_back(FzlSpriteHandle _spr, double _x, double _y, double _a, int _pos, int _pos2)
{
	spr.push_back(_spr);
	x.push_back(_x);
	y.push_back(_y);
	a.push_back(_a);
	pos.push_back(_pos);
	pos2.push_back(_pos2);
}

void layer::reorder(std::vector<Box> & temp)
{

	for (int i = 1; i < y.size(); i++)
	{
		for (int count = 0; count < temp.size(); count++)
		{
			if (temp[count].tY < y[i] && temp[count].lX - 32< x[i] && temp[count].rX + 32> x[i])
			{
				order.push_back(i);
				count = temp.size();

			}
		}
	}

	order.push_back(0);
	for (int i = 0; i < a.size(); i++)
	{
		bool set = false;
		for (int count = 0; count < order.size(); count++)
		{
			if (order[count] == i)
			{
				set = true;
				count = order.size();
			}

		}
		if (set == false)
		{
			order.push_back(i);
		}
	}
	if (order.size() > a.size())
	{
		int x;
		x = 5;
		x *= 5;
	}
}

void layer::draw()
{
	for (int count = 0; count < order.size(); count++)
	{

		if (pos[order[count]] == -1)
		{
			FzlDrawSprite(spr[order[count]], x[order[count]], y[order[count]], a[order[count]]);
		}
		else
			FzlDrawAnimatedSprite(spr[order[count]], pos[order[count]], pos2[order[count]], x[order[count]], y[order[count]], a[order[count]]);

	}
}

void layer::clear()
{
	spr.clear();
	a.clear();
	x.clear();
	y.clear();
	pos.clear();
	pos2.clear();
	order.clear();
}