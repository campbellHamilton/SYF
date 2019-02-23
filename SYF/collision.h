#ifndef COLLISION_H
#define COLLISION_H
#include "vect.h"
#include "box.h"
struct Collision
{
public:
	Collision();
	bool status;
	vect<double> penetration;
	Collision operator+(Collision& operand);
	Collision operator-(Collision& operand);
	Box collidedWith;
};
#endif
