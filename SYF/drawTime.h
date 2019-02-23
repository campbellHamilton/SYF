#ifndef DRAWTIME_H
#define DRAWTIME_H
#include <vector>
#include <ctime>
#include "Fizzle\Fizzle.h"
#include <iostream>
struct pointerSprite
{
	pointerSprite(double *_x, double *_y, float _a, FzlSpriteHandle &_ID, int _row)
	{
		row = _row;
		x = _x;
		y = _y;
		a = _a;
		spriteID = &_ID;
		column = 0;
	}
	pointerSprite(double *_x, double *_y, float _a, FzlSpriteHandle &_ID, int _row, int _column)
	{
		row = _row;
		x = _x;
		y = _y;
		a = _a;
		spriteID = &_ID;
		column = _column;
	}
	pointerSprite(double _x, double _y, float _a, FzlSpriteHandle &_ID, int _row, int _column)
	{
		row = _row;
		x = new double(_x);
		y = new double(_y);
		a = _a;
		spriteID = &_ID;
		column = _column;
	}
	pointerSprite(double _x, double _y, float _a, FzlSpriteHandle &_ID, int _row)
	{
		row = _row;
		//td::auto_ptr<int> p1 (new int);
		x = new double(_x);
		y = new double(_y);
		a = _a;
		spriteID = &_ID;
		column = 0;
	}
	int row;
	double *x;
	double *y;
	float a;
	int column;
	FzlSpriteHandle *spriteID;
};

struct drawTime
{
	void push_back(pointerSprite &x, float y)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(0);
		option.push_back(false);
	}
	void push_back(pointerSprite &x, float y, bool z)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(0);
		option.push_back(z);
	}
	void push_back(pointerSprite &x, float y, int z)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(z);
		option.push_back(false);
	}


	void push_back(pointerSprite x, float y)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(0);
		option.push_back(false);
	}
	void push_back(pointerSprite x, float y, bool z)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(0);
		option.push_back(z);
	}
	void push_back(pointerSprite x, float y, int z)//sprite and the time to render it for.
	{
		holder.push_back(x);
		time.push_back(y);
		length.push_back(clock());
		ani.push_back(z);
		option.push_back(false);
	}


	void draw()
	{
		for (int count = 0; count < holder.size(); count++)
		{

		
			if (ani[count] != 0 && option[count] == false)
			{
				FzlDrawAnimatedSprite(*holder[count].spriteID, holder[count].column, holder[count].row, *holder[count].x, *holder[count].y, holder[count].a);
				if ((clock() - length[count]) > time[count])
				{
					std::cout << holder[count].row;
					length[count] = clock();
					holder[count].row++;
					if (holder[count].row > ani[count])
					{
						holder.erase(holder.begin() + count);
						holder.shrink_to_fit();

						time.erase(time.begin() + count);
						time.shrink_to_fit();

						length.erase(length.begin() + count);
						length.shrink_to_fit();

						ani.erase(ani.begin() + count);
						ani.shrink_to_fit();

						count--;
					}
				}
			}
			else if (option[count] == false)
			{
				std::cout << "current time: "<< clock() << std::endl;
				std::cout << "Time since start: "<< length[count] << std::endl;
				std::cout << "Difference of above: "<< clock() - length[count] << std::endl;
				FzlDrawAnimatedSprite(*holder[count].spriteID, holder[count].column, holder[count].row, *holder[count].x, *holder[count].y, holder[count].a);
				if ((clock() - length[count]) > time[count])
				{
					holder.erase(holder.begin() + count);
					holder.shrink_to_fit();

					time.erase(time.begin() + count);
					time.shrink_to_fit();

					length.erase(length.begin() + count);
					length.shrink_to_fit();

					ani.erase(ani.begin() + count);
					ani.shrink_to_fit();

					count--;
				}
			}

		}
		for (int count = 0; count < holder.size(); count++)
		{


			if (ani[count] != 0 && option[count] == true)
			{
				FzlDrawAnimatedSprite(*holder[count].spriteID, holder[count].column, holder[count].row, *holder[count].x, *holder[count].y, holder[count].a);
				if ((clock() - length[count]) > time[count])
				{
					std::cout << holder[count].row;
					length[count] = clock();
					holder[count].row++;
					if (holder[count].row > ani[count])
					{
						holder.erase(holder.begin() + count);
						holder.shrink_to_fit();

						time.erase(time.begin() + count);
						time.shrink_to_fit();

						length.erase(length.begin() + count);
						length.shrink_to_fit();

						ani.erase(ani.begin() + count);
						ani.shrink_to_fit();

						count--;
					}
				}
			}
			else if (option[count] == true)
			{
				std::cout << "current time: " << clock() << std::endl;
				std::cout << "Time since start: " << length[count] << std::endl;
				std::cout << "Difference of above: " << clock() - length[count] << std::endl;
				FzlDrawAnimatedSprite(*holder[count].spriteID, holder[count].column, holder[count].row, *holder[count].x, *holder[count].y, holder[count].a);
				if ((clock() - length[count]) > time[count])
				{
					holder.erase(holder.begin() + count);
					holder.shrink_to_fit();

					time.erase(time.begin() + count);
					time.shrink_to_fit();

					length.erase(length.begin() + count);
					length.shrink_to_fit();

					ani.erase(ani.begin() + count);
					ani.shrink_to_fit();

					count--;
				}
			}

		}
	}
	std::vector<pointerSprite> holder;
	std::vector<int> time;
	std::vector<clock_t> length;
	std::vector <int> ani;
	std::vector <bool> option;
};


#endif