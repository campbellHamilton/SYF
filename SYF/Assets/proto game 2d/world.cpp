#include "world.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265
#include "Fizzle\Fizzle.h"
World::World() : p1(0, 100, 100), p2(1, 1820, 980)//constructor. sets the players starting location
{
	players = 2;
	bulletSpeed = 13;//jameswashere #spooky
	bulletLimit = 5;
}

bool World::getCollision()
{
	Tank* player;
	Tank* enemy;
	switch (players)
	{
	case 4:
		/*setup = &p4;
		shoot(setup, );*/
	case 3:
		//setup = &p3;
		//shoot(setup);
	case 2:
		player = &p2;//detects whether a bullet has hit the second player
		enemy = &p1;
		if (collision(player, enemy) == true)
			return true;
	case 1:
		player = &p1;//detects whether a bullet has hit the first player
		enemy = &p2;
		if (collision(player, enemy) == true)
			return true;
		break;
	}
	return false;
}

bool World::collision(Tank* player, Tank* Enemy)//detects whether a bullet has collided with the tank parameter
{
	for (int count = 0; count < player->getBullet(); count++)
	{
		std::cout << count << std::endl;
		Coords temp;
		temp.x = player->shot[count].getPosX();
		temp.y = player->shot[count].getPosY();
		if (Enemy->getX() - 16 < temp.x && temp.x < Enemy->getX() + 16 && Enemy->getY() - 16 < temp.y && temp.y < Enemy->getY() + 16)//controls hitbox
		{
			return true;
		}
	}
	return false;
}

bool World::shoot(Tank* player, Tank* enemy)//checks whether a bullet has been fired.
{
	if ((FzlGetKey(FzlKeySpace) || player->getEnemy(true)->conButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) && player->getBullet() < 25)
	{
		player->flipBullet();
		double tempy = bulletSpeed * sin(PI * (player->getA() + player->getAT()) / 180);
		double tempx = bulletSpeed * cos(PI * (player->getA() + player->getAT()) / 180);
		player->shot.push_back(Bullet(player->getX() + (tempx / bulletSpeed) * 22, player->getY() + (tempy / bulletSpeed) * 22, tempx, tempy, player->getA() + player->getAT()));
		num++;
		std::cout << num << std::endl;
		return true;
	}
	return false;
}


void World::playersShoot()//controls the player shooting
{
	Tank* player;
	Tank* enemy;
	switch (players)
	{
	case 4:
		/*setup = &p4;
		shoot(setup, );*/
	case 3:
		//setup = &p3;
		//shoot(setup);
	case 2:
		player = &p2;
		enemy = &p1;
		if (player2 == false)
		{
			player2 = shoot(player, enemy);//detects whether the second player has fired a bullet
		}
		else if (player2Wait <= 3)
		{
			player2Wait++;
		}
		else if (player2Wait > 3)
		{
			player2 = false;
			player2Wait = 0;
		}
	case 1:
		player = &p1;
		enemy = &p2;

		if (player1 == false)
		{
			player1= shoot(player, enemy);//detects whether the second player has fired a bullet
		}
		else if (player1Wait <= 3)
		{
			player1Wait++;
		}
		else if (player1Wait > 3)
		{
			player1 = false;
			player1Wait = 0;
		}
		break;
	}
}
