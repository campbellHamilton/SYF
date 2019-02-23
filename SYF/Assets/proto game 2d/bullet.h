#include "Fizzle\Fizzle.h"
#pragma once
class Bullet
{
public:
	//constructors
	Bullet(double, double, double, double, int);
	Bullet();

	//set and reset bullet.
	void setBullet(double, double, double, double, int);
	//move bullet.
	void movement();

	FzlSpriteHandle getShot(){ return shot; };
	//accessors

	int getPosX(){ return posX; };
	int getPosY(){ return posY; };

	//mutators
	void redirect(double, int); //changes the angle and x and y components of movement to the passed angle, used for bullet bouncing

private:
	double posX;
	double posY;
	double dirX;
	double dirY;
	int angle;
	bool fired;

	FzlSpriteHandle shot;

};
