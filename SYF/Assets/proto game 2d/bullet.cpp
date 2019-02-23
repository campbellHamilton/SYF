#include "Bullet.h"
#include <math.h>
//x and y origin (tanks position), set direction x, set direction y, angle that the bullet's on
Bullet::Bullet(double x, double y, double sDirX, double sDirY, int sAngle)
{
	shot = FzlLoadSprite("Assets/tank/bullet.png", 16, 16);
	posX = x;
	posY = y;
	dirX = sDirX;
	dirY = sDirY;
	angle = sAngle;
	fired = false;
}
//if you need to create a bullet at a point, was used to make bullets off screen for testing
Bullet::Bullet()
{
	shot = FzlLoadSprite("Assets/tank/bullet.png", 16, 16);
	posX = -30;
	posY = -30;
	dirX = 0;
	dirY = 0;
	angle = 0;
	fired = false;
}
//obselete, one of the two needs to be deleted! 
void Bullet::setBullet(double x, double y, double sDirX, double sDirY, int sAngle)
{
	shot = FzlLoadSprite("Assets/tank/bullet.png", 16, 16);
	posX = x;
	posY = y;
	dirX = sDirX;
	dirY = sDirY;
	angle = sAngle;
}

void Bullet::movement()
{
	posX += dirX;
	posY += dirY;
	FzlDrawSprite(shot, static_cast<float>(posX), static_cast<float>(posY), angle);
}
//Will be needed in the future for bouncing bullets off of angled surfaces, only works for 90 degree surfaces for now
void Bullet::redirect(double givenangle, int givenSpeed)
{
//	angle = givenangle;
//	dirX = angle;
//	dirY = angle;
//	atan2();
	if (givenangle == 0)
	{
		dirY *= -1;
	}
	else if (givenangle == 90)
	{
		dirX *= -1;
	}
}