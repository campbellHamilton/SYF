#ifndef BULLET_H
#define BULLET_H
#include "Fizzle/Fizzle.h"
#include "controller.h"
#include "vect.h"
#include "layer.h"
#include <ctime>
class Bullet
{
public:
	//"Ages" the bullet, returns false if the bullet should be despawned.
	bool age();
	bool shoulddelete;
	//constructors
	Bullet(double x, double y, double sAngle, int velocity, int tankveloX, int tankveloY, bool accel);
	Bullet();
	~Bullet();

	//set and reset bullet.
	//move bullet.
	void movement(FzlSpriteHandle shot, bool _x, bool _y, layer* temp, float, bool accel);
	int getA(){ return angle; };
	//accessors
	double getPosX(){ return posX; };
	double getPosY(){ return posY; };
	int getbulletSize(){ return bulletSize; };
	double getDistance(){ return distance; };
	int getAngle2(){return angle2;};
	//mutators
	void setPosY(double);
	void setPosX(double);
	void redirect(double, int);
	int angle2;
	int bulletFrame;
	bool bouncegrace;
	int lifespan = 3;
private:
	int accelgrace = 0;
	double acceleration = 1;
	
	int bulletSize = 15;
	double distance;
	double posX;
	double posY;
	vect<double> velocity;
	int angle;

};
#endif
