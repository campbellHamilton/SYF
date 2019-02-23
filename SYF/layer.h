#pragma once
//#ifndef LAYER_H
//#define LAYER_H
#include <vector>
#include "Fizzle\Fizzle.h"
#include "box.h"
//whenever you would draw something to the screen instead we send it to this class.
//when the round (a frame) is done we would then draw everything to the screen, we would check the variable against each other so
class layer
{
public:
	layer();

	void push_back(FzlSpriteHandle, double, double, double, int, int);
	//x, y, a
	void reorder(std::vector<Box>&);
	//reorders everything to layer things properly
	void draw();

	void clear();

private:
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> a;
	std::vector<FzlSpriteHandle> spr;
	std::vector<int> order;
	std::vector<int> pos;
	std::vector<int> pos2;

};
//#endif