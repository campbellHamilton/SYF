#include "tank.h"
#include "Fizzle\Fizzle.h"
#include <math.h>
#include "controller.h"
#include <Xinput.h>
#include <iostream>

const int windowWidth = 1920;//need to replace the limits with these variables.
const int windowHeight = 1080;

#define PI 3.14159265
controller p1(0);//the controller for player 1. its the first controller plugged in.
controller p2(1);//the controller for player 2. its the first controller plugged in.

Tank::Tank()
{

}

Tank::Tank(int number, int x, int y)//number used for controller number, x and y for starting position
{
	switch (number)
	{
	case 0:
		playerNumber = &p1;
		playerNumber2 = &p2;
		break;
	case 1:
		playerNumber = &p2;
		playerNumber2 = &p1;
		break;
	}

	tankAngle = 0;

	tankPosX = x;
	tankPosY = y;

	turretAngle = 0;

	velocityX = 0;
	velocityY = 0;
	//limit on acceleration, "top speed", one pixel per frame per frame = acceleration?
	acceleration = 10;
	//the number of bullets that a tank has been fired, possibly obselete because bullets are stored in a vector, can just get the length of a vector
	bulletFired = 0;
	//iffy, used for only one movement scheme, was being used in tank controls
	playerSpeed = 2;
	//for (int count = 0; count < 5; count++)
	//{
	//	shot.push_back(Bullet());
	//}
}

void Tank::turretMovement()
{
	Coords pos = playerNumber->getRightStick();
//	if (0.2 > pos.x > -0.2 && 0.2 > pos.y > -0.2) {}
	if (pos.x == 0 && pos.y == 0) {}
	else
	{
		turretAngle = atan2(pos.y, pos.x) * 180 / PI;
	}
	//if (FzlGetKey(FzlKeyQ) || playerNumber2->conButton(XINPUT_GAMEPAD_LEFT_SHOULDER) == true)//controls left rotation
	//{
	//	turretAngle += 2;
	//}
	//else if (FzlGetKey(FzlKeyE) || playerNumber2->conButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)//controls right rotation
	//{
	//	turretAngle -= 2;
	//}
}

void Tank::bulletMovement(bool bounceToggle, int bulletSpeed)//controls bullet movement
{
	if (bulletFired > 0)
	{
		for (int count = 0; count < shot.size(); count++)
		{	//shot is a vector of bullets, count is the index of the vector, 
			shot[count].movement();//moves bullet
			if (shot[count].getPosX() > windowWidth || shot[count].getPosY() > windowHeight || shot[count].getPosY() < 0 || shot[count].getPosX() < 0)//if bullet goes off screen deletes its.
			{
				if (!bounceToggle)
				{
					FzlDeleteSprite(shot[count].getShot());
					shot.erase(shot.begin() + count);
					bulletFired -= 1;
					shot.shrink_to_fit();
				}
				else
				{
					//shot[count].redirect();
					if (shot[count].getPosX() > windowWidth - 12 || shot[count].getPosX() < 12)
					{
						shot[count].redirect(90, bulletSpeed);
					}
					else if (shot[count].getPosY() > windowHeight - 12 || shot[count].getPosY() < 12)
					{
						shot[count].redirect(0, bulletSpeed);
					}
				}
			}
		}
	}
}

void Tank::movement(int choice)//controls the tanks movement
{
	Coords stick;
	stick = playerNumber->getLeftStick();
	double mY;
	double mX;

	switch (choice)//controls what movement scheme is being used
	{
	case 1://tank controls

		mY = playerSpeed * sin(PI * tankAngle / 180);
		mX = playerSpeed * cos(PI * tankAngle / 180);
		if (FzlGetKey(FzlKeyW) || stick.y > 0.25)
		{
			//checking the ys are within the top and bottom, checking the xs are within the width
			if (tankPosY + mY > 0 && tankPosY + mY < 1080 && tankPosX + mX > 0 && tankPosX + mX < 1920)
			{
				tankPosY += mY;
				tankPosX += mX;
			}
		}

		else if (FzlGetKey(FzlKeyS) || stick.y < -0.25)
		{
			if (tankPosY - mY > 0 && tankPosY - mY < 1080 && tankPosX - mX > 0 && tankPosX - mX < 1920)
			{
				tankPosY -= mY;
				tankPosX -= mX;
			}
		}
		break;
	case 2://simple movement
		mY = stick.y;
		mX = stick.x;
		if (tankPosY + mY > 0 && tankPosY + mY < 1080 && tankPosX + mX > 0 && tankPosX + mX < 1920)
		{
			tankPosY += mY;
			tankPosX += mX;
		}
		break;
	case 3://ice surface movement (boundaires need to be finished)

		if (velocityY + stick.y < 10 && velocityY + stick.y > -10 && (stick.y > 0.05 || stick.y < -0.05))
		{
			velocityY += stick.y / 2;
		}
		else if (velocityY>0)
		{
			velocityY -= 0.2;
		}
		else
		{
			velocityY += 0.2;
		}
		if (velocityX + stick.x < 10 && velocityX + stick.x > -10 && (stick.x > 0.05 || stick.x < -0.05))
		{
			velocityX += stick.x / 2;
		}
		else if (velocityX>0)
		{
			velocityX -= 0.05;
		}
		else
		{
			velocityX += 0.05;
		}
		if (tankPosY + velocityY > 0 && tankPosY + velocityY < 1080 && tankPosX + velocityX > 0 && tankPosX + velocityX < 1920)
		{
			tankPosY += velocityY;
			tankPosX += velocityX;
		}
		break;
	case 4://ice surface with no friction (boundaires need to be finished)

		if (velocityY + stick.y < 10 && velocityY + stick.y > -10 && (stick.y > 0.05 || stick.y < -0.05))
		{
			velocityY += stick.y / 2;
		}
		if (velocityX + stick.x < 10 && velocityX + stick.x > -10 && (stick.x > 0.05 || stick.x < -0.05))
		{
			velocityX += stick.x / 2;
		}
		if (tankPosY + velocityY > -10 && tankPosY + velocityY < 1100 && tankPosX + velocityX > -10 && tankPosX + velocityX < 1940)
		{
			tankPosY += velocityY;
			tankPosX += velocityX;
		}
		if (tankPosY + velocityY < -5)
		{
			tankPosY = 1080;
		}
		if (tankPosY + velocityY > 1090)
		{
			tankPosY = 0;
		}
		if (tankPosX + velocityX < -5)
		{
			tankPosX = 1920;
		}
		if (tankPosX + velocityX > 1930)
		{
			tankPosX = 0;
		}
		//else if (tankPosY + velocityY > 0 )
		//{
		//	int temp = velocityY;
		//	velocityY = velocityX;
		//	velocityX = temp;
		//	if (tankPosX + velocityX > 0)
		//	{
		//		velocityX *= -1;
		//		velocityY *= -1;
		//	}
		//}
		//else if (tankPosY + velocityY < 1080)
		//{
		//	int temp = velocityY;
		//	velocityY = velocityX;
		//	velocityX = temp;
		//	if (tankPosX + velocityX < 1920)
		//	{
		//		velocityX *= -1;
		//		velocityY *= -1;
		//	}
		//}
		break;
	}
}
void Tank::rotation(int choice)//controls the rotation of the tank (only for tank movement scheme)
{
	switch (choice)
	{
	case 1:
		Coords stick;
		stick = playerNumber->getLeftStick();
		if (FzlGetKey(FzlKeyA) || stick.x < -0.25)
		{
			tankAngle += 1;
		}
		else if (FzlGetKey(FzlKeyD) || stick.x > 0.25)
		{
			tankAngle -= 1;
		}
		break;
	}
}

bool Tank::playAgain()//controls whether a new game is played or not
{
	while (1)
	{
		if (p1.conButton(XINPUT_GAMEPAD_A) == true)
		{
			return false;
		}
		else if (p1.conButton(XINPUT_GAMEPAD_B) == true)
		{
			return true;
		}
	}
}

controller* Tank::getEnemy(bool type)//return the enemies controller.
{
	if (type == false)
		return playerNumber2;

	else
		return playerNumber;
}