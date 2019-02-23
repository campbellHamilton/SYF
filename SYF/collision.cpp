#include "collision.h"
Collision::Collision()
{
	status = false;
	penetration.setx(0);
	penetration.sety(0);
}
Collision Collision::operator+(Collision& operand)
{
	Collision result;
	if (this->status || operand.status)
		result.status = true;
	result.penetration.setx(this->penetration.getx() + operand.penetration.getx());
	result.penetration.sety(this->penetration.gety() + operand.penetration.gety());
	return result;
}

Collision Collision::operator-(Collision& operand)
{
	Collision result;
	if (this->status || operand.status)
		result.status = true;
	result.penetration.setx(this->penetration.getx() - operand.penetration.getx());
	result.penetration.sety(this->penetration.gety() - operand.penetration.gety());
	return result;
}
