#include "Bullet.h"
#include <math.h>
#include "tank.h"
#include <iostream>
//#include "layer.h"
#define pi 3.1415926535
Bullet::Bullet(double x, double y, double sAngle, int _velocity, int tankvelocityX, int tankvelocityY, bool accel)
{
	bouncegrace = false;
	bulletFrame = 0;
	distance = 0;
	posX = x;
	posY = y;
	//up
	if (sAngle < 112.5 && sAngle > 67.5)
	{
		angle = 90;
		angle2 = 2;
	}
	//down
	else if (sAngle > -112.5 && sAngle < -67.5)
	{
		angle = -90;
		angle2 = 6;
	}
	//right
	else if (sAngle > -22.5 && sAngle < 22.5)
	{
		angle = 0;
		angle2 = 0;
	}
	//left
	else if (sAngle > 157.5 || sAngle < -157.5)
	{
		angle = 180;
		angle2 = 4;
	}
	//up right
	else if (sAngle > 22.5 && sAngle < 67.5)
	{
		angle = 45;
		angle2 = 1;
	}
	//down right
	else if (sAngle > -67.5 && sAngle < -22.5)
	{
		angle = -45;
		angle2 = 7;
	}
	//up left
	else if (sAngle > 112.5 && sAngle < 157.5)
	{
		angle = 135;
		angle2 = 3;
	}
	//down left
	else if (sAngle > -157.5 && sAngle < -112.5)
	{
		angle = -135;
		angle2 = 5;
	}
	if (abs(angle) < 91)
		
		
		{
			velocity.sety((_velocity * sin(angle * pi / 180)) + tankvelocityY);
			velocity.setx((_velocity * cos(angle * pi / 180)) + tankvelocityX);
		}
		
	else 
	{
		velocity.setx(-1 * (_velocity * cos((180 - angle) * pi / 180)) + tankvelocityX);
		velocity.sety((_velocity * sin((180 - angle) * pi / 180)) + tankvelocityY);
	}
	//printf("bullet created \n");
	
}


void Bullet::movement(FzlSpriteHandle shot, bool _x, bool _y, layer* temp, float slow, bool accel)
{
	if (_y)
	{
		double velocityY = velocity.gety();
		posY += velocityY  * (1+slow);
		/*if (velocityY * (1 + slow) < 0)
			distance += velocityY * -1 + slow;
		else
			distance += velocityY * 1 + slow;*/
		if (velocityY > 0)
		{
			distance += velocityY * (1 + slow);
		}
		else
		{
			distance += velocityY * (1 + slow);
		}
		if (accel)
		{
			accelgrace++;
			if (accelgrace > 90)
			{
				if (abs(angle < 91))
				{
					velocity.sety((acceleration * sin(angle * pi / 180)) + velocity.gety());

				}
				else
				{
					velocity.sety((acceleration * sin((180 - angle) * pi / 180)) + velocity.gety());
				}
			}
		}
		
	}
	else if (_x)
	{
		double velocityX = velocity.getx();
		posX += velocityX  * (1 + slow);
		/*if (velocityX * 1 + slow < 0)
			distance += velocityX * -1 + slow;
		else
			distance += velocityX * 1 + slow;*/
		
		if (velocityX > 0)
		{
			distance += velocityX * (1 + slow);
		}
		else
		{
			distance += velocityX * (1 + slow);
		}
		if (accel)
		{
			accelgrace++;
			if (accelgrace > 90)
			{
				if (abs(angle < 91))
				{
					velocity.setx((acceleration * cos(angle * pi / 180)) + velocity.getx());
				}
				else
				{
					velocity.setx(-1 * (acceleration * cos((180 - angle) * pi / 180)) + velocity.getx());
				}
			}
		}
	}
	//  << FzlGetDeltaTime()<<std::endl;

}

void Bullet::redirect(double angle, int bulletSpeed)
{
	double velocityY = velocity.gety();
	double velocityX = velocity.getx();
	if (angle == 0)
	{
		velocity.sety(velocityY * -1);
	}
	else if (angle == 90)
	{
		velocity.setx(velocityX * -1);
	}
	//else dot product wall, need angled wall lines to go here
}
bool Bullet::age()
{
	if (lifespan > 1)
	{
		lifespan--;
		return true;
	}
	else
	{
		return false;
	}
}

Bullet::~Bullet()
{
	//printf("bullet deconstructed");
}
void Bullet::setPosX(double _x)
{
	posX = _x;
}
void Bullet::setPosY(double _y)
{
	posY = _y;
}