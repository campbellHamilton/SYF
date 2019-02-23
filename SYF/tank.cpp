#include "tank.h"
#include "Fizzle\Fizzle.h"
#include <math.h>

#include <Xinput.h>
#include <iostream>
#include "collision.h"
#include "world.h"
#include <cmath>
#include <iostream>
#include <ctime>
#define PI 3.14159265
#include "collision.h"
#include "modifierlist.h"
#include "Menu.h"
#include "drawTime.h"
#include "sound.h"

controller p1(0);//the controller for player 1. its the first controller plugged in.
controller p2(0);//the controller for player 2. its the second controller plugged in.
controller p3(0);//the controller for player 3. its the third controller plugged in.
controller p4(0);//the controller for player 4. its the fourth controller plugged in.
const int windowWidth = 1820;//need to replace the limits with these variables.
const int windowHeight = 980;
const int windowMin = 100;
const int maxX = 1820;
const int maxY = 980;
const int minXY = 100;
void Tank::setPos(int x, int y)
{
	//	if (positionLegality(x, y))
	{
		tankPos.setx(x);
		tankPos.gety(y);
	}
}

Tank::Tank(int number, int x, int y, int size, bool mode, int _offset, bool lazer, modifierlist & list, SpriteList* holder, SoundList* _sounds)//number used for controller number, x and y for starting position
{
	Tank::holder = holder;
	Tank::sounds = _sounds;
	dashSetter = false;
	meleeSetter = false;
	TWTS = 0;


	ismeleeing = false;
	isdashing = false;
	timeWillTell = clock();
	//fire = FzlLoadSound("Sound/BaseShot.wav", 0);
	//fire2 = FzlLoadSound("Sound/AltBaseShot.wav", 0);
	//shieldS = FzlLoadSound("Sound/shieldactive.wav", 0);
	//dashS = FzlLoadSound("Sound/dash_mod.wav", 0);

	soundFire = false;

	deathSpot = 0;

	shield = false;
	Tank::world = world;
	Tank::list = &list;
	tankSize = size;
	health = (Tank::list->modifiers[modifierlist::index::hearts] == true) ? 3 : 1;
	offset = _offset;
	controllernumber = number;
	iamdead == false;
	switch (number)
	{
	case 0:

		playerNumber = &p1;
		playerNumber2 = &p2;

		bulletImage = &holder->tank[tank::p1bulletImage];
		aoe = &holder->tank[tank::p1aoe];
		splat = &holder->tank[tank::p1splat];
		staticTank = &holder->tank[tank::p1staticTank];
		bubble = &holder->tank[tank::bubble];
		die = &holder->tank[tank::p1die];
		playerID = 0;
		break;
	case 1:
		playerNumber = &p2;
		playerNumber2 = &p1;
		bulletImage = &holder->tank[tank::p2bulletImage];
		aoe = &holder->tank[tank::p2aoe];
		splat = &holder->tank[tank::p2splat];
		staticTank = &holder->tank[tank::p2staticTank];
		bubble = &holder->tank[tank::bubble];
		die = &holder->tank[tank::p2die];
		playerID = 1;
		break;
	case 2:
		playerNumber = &p3;
		playerNumber2 = &p1;
		bulletImage = &holder->tank[tank::p3bulletImage];
		aoe = &holder->tank[tank::p3aoe];
		splat = &holder->tank[tank::p3splat];
		staticTank = &holder->tank[tank::p3staticTank];
		bubble = &holder->tank[tank::bubble];
		die = &holder->tank[tank::p3die];
		playerID = 2;
		break;
	case 3:
		playerNumber = &p4;
		playerNumber2 = &p1;
		bulletImage = &holder->tank[tank::p4bulletImage];
		aoe = &holder->tank[tank::p4aoe];
		splat = &holder->tank[tank::p4splat];
		staticTank = &holder->tank[tank::p4staticTank];
		bubble = &holder->tank[tank::bubble];
		die = &holder->tank[tank::p4die];
		playerID = 3;
		break;
	}

	points = 0;

	tankAngle = 0;

	tankPos.setx(x);
	tankPos.sety(y);

	turretAngle = 0;


	acceleration = 5;

	playerSpeed = 300;

	lastvelocity.setx(0);
	lastvelocity.sety(0);
	velocity.setx(0);
	velocity.sety(0);
	//Walls in the level.
	//     y0  y1  x0  x1
	//     RIGHT LEFT TOP  BOTTOM     
	//walls.push_back(Box(1024, 896, 350, 0));
	//walls.push_back(Box(1024, 896, 1080, 730));
	//walls.push_back(Box(400, 0, 640, 536));
	//walls.push_back(Box(1920, 1520, 640, 536));



	// The default proto arena

	dir = 0;
	spriteSpot = 0;
	up = 0;




}


Tank::~Tank()
{
	deleteSprites();
	//  << "tank deconstructed" << std::endl;
}



Collision Tank::wallCollision(World* world)
{
	Collision result;
	//int radius = tankSize / 2;

	Box b1;
	bool collide[2] = { false, false };

	for (int count = 0; count < world->getplayers(); count++)
	{
		Tank *tempPointer = NULL;
		switch (count + 1)
		{
		case 1:
			tempPointer = world->p_1;
			break;
		case 2:
			tempPointer = world->p_2;
			break;
		case 3:
			tempPointer = world->p_3;
			break;
		case 4:
			tempPointer = world->p_4;
			break;
		}
		if (tempPointer != this && tempPointer->deathSpot != 13)
		{
			b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
			Box b2 = tempPointer->getBox(tempPointer->tankPos.getx() + tempPointer->velocity.getx(), tempPointer->tankPos.gety());
			if (b1.rX - b2.lX >= 0)
			if (b2.rX - b1.lX >= 0)
			if (b1.tY - b2.bY >= 0)
			if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
			{
				vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
				penetration.sety(0);
				vect<double> corr = velocity.project(penetration) * -1;
				velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);

				if (world->pmenu->selection.modifiers[modifierlist::melee] || world->pmenu->selection.modifiers[modifierlist::oneshot])
				{
					if (this->lethalspeed && !tempPointer->lethalspeed)
					{
						if (world->pmenu->selection.modifiers[modifierlist::bomb] == false)
						{
							if (world->pmenu->selection.modifiers[modifierlist::standard] != true)
							{
								if (meleed == false && tempPointer->shieldOn == false)
								{
									meleed = true;
									tempPointer->changeHealth(-1);
									FzlPlaySound(sounds->sworld[lifeLost]);
								}
							}
							else
							{
								world->splat.push_back(pointerSprite(this->getXP(), this->getYP(), 0, holder->tank[tank::points], 0, this->playerID), 100, 9);
								if (tempPointer->stunStart == 0)
								{
									this->points++;
									tempPointer->stun = true;
									tempPointer->stunStart = clock();
								}

							}
						}
						else
						{
							this->hasbomb = false;
							tempPointer->giveBomb();
							world->splat.push_back(pointerSprite(tempPointer->getXP(), tempPointer->getYP(), 0, holder->tank[bombfeedback], 0, tempPointer->playerID), 50, 9);
						}
						if (tempPointer->getH() <= 0)
						{
							if (world->pmenu->selection.modifiers[modifierlist::bomb] == false)
							{
								world->death[tempPointer->controllernumber] = true;
								this->hasbullet = true;
								if (world->pmenu->selection.modifiers[modifierlist::oneshot] == false)
									world->splat.push_back(pointerSprite(this->getXP(), this->getYP(), 0, holder->tank[bulletgain], 0, this->playerID), 50, 9);
							}
						}
					}
				}
			}
			b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
			if (b1.rX - b2.lX >= 0)
			if (b2.rX - b1.lX >= 0)
			if (b1.tY - b2.bY >= 0)
			if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
			{
				vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
				penetration.setx(0);
				vect<double> corr = velocity.project(penetration) * -1;
				velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);

				if (world->pmenu->selection.modifiers[modifierlist::melee] || world->pmenu->selection.modifiers[modifierlist::oneshot])
				{
					if (this->lethalspeed && !tempPointer->lethalspeed)
					{
						if (world->pmenu->selection.modifiers[modifierlist::bomb] == false)
						{
							if (world->pmenu->selection.modifiers[modifierlist::standard] != true)
							{
								if (meleed == false && tempPointer->shieldOn == false)
								{
									meleed = true;
									tempPointer->changeHealth(-1);
									FzlPlaySound(sounds->sworld[lifeLost]);
								}
							}
							else
							{
								world->splat.push_back(pointerSprite(this->getXP(), this->getYP(), 0, holder->tank[tank::points], 0, this->playerID), 100, 9);
								if (tempPointer->stunStart == 0)
								{
									this->points++;
									tempPointer->stun = true;
									tempPointer->stunStart = clock();
								}

							}
						}
						else
						{
							this->hasbomb = false;
							tempPointer->giveBomb();
							world->splat.push_back(pointerSprite(tempPointer->getXP(), tempPointer->getYP(), 0, holder->tank[bombfeedback], 0, tempPointer->playerID), 50, 9);
						}
						if (tempPointer->getH() <= 0)
						{
							if (world->pmenu->selection.modifiers[modifierlist::bomb] == false)
							{
								world->death[tempPointer->controllernumber] = true;
								this->hasbullet = true;
								if (world->pmenu->selection.modifiers[modifierlist::oneshot] == false)
									world->splat.push_back(pointerSprite(this->getXP(), this->getYP(), 0, holder->tank[bulletgain], 0, this->playerID), 50, 9);
							}
						}
					}
				}
			}
		}
	}

	for (int count = 0; count < walls.size(); count++)
	{
		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
		Box b2 = walls[count];
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
		{

			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.sety(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);
		}
		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.setx(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);


		}
	}

	for (int count = 0; count < holes.size(); count++)
	{
		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
		Box b2 = holes[count];
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.sety(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);

		}
		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.setx(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);

		}
	}

	for (int count = 0; count < bounds.size(); count++)
	{
		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
		Box b2 = bounds[count];
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.sety(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);

		}
		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.setx(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);
		}
	}
	for (int count = 0; count < walls.size(); count++)
	{
		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
		Box b2 = walls[count];
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.sety(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);

		}
		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
		if (b1.rX - b2.lX >= 0)
		if (b2.rX - b1.lX >= 0)
		if (b1.tY - b2.bY >= 0)
		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
		{
			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
			penetration.setx(0);
			vect<double> corr = velocity.project(penetration) * -1;
			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);
		}
	}

	for (int count = 0; count < 4; count++)
	{
		if (bodies[count].rX != 0)
		{
			b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
			Box b2 = bodies[count];
			if (b1.rX - b2.lX >= 0)
			if (b2.rX - b1.lX >= 0)
			if (b1.tY - b2.bY >= 0)
			if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
			{
				vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
				penetration.sety(0);
				vect<double> corr = velocity.project(penetration) * -1;
				velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);

			}
			b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
			if (b1.rX - b2.lX >= 0)
			if (b2.rX - b1.lX >= 0)
			if (b1.tY - b2.bY >= 0)
			if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
			{
				vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
				penetration.setx(0);
				vect<double> corr = velocity.project(penetration) * -1;
				velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);
			}
		}
	}



	tankPos.setx(tankPos.getx() + velocity.getx());
	tankPos.sety(tankPos.gety() + velocity.gety());

	return result;
}

//player to player box collision. saved here in case we revert

//
//for (int count = 0; count < world->getplayers(); count++)
//{
//	Tank *tempPointer;
//	switch (count + 1)
//	{
//	case 1:
//		tempPointer = &world->p_1;
//		break;
//	case 2:
//		tempPointer = &world->p_2;
//		break;
//	case 3:
//		tempPointer = &world->p_3;
//		break;
//	case 4:
//		tempPointer = &world->p_4;
//		break;
//	}
//	if (tempPointer != this)
//	{
//		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
//		Box b2 = tempPointer->getBox(tempPointer->tankPos.getx() + tempPointer->velocity.getx(), tempPointer->tankPos.gety());
//		if (b1.rX - b2.lX >= 0)
//		if (b2.rX - b1.lX >= 0)
//		if (b1.tY - b2.bY >= 0)
//		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
//		{
//			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
//			penetration.sety(0);
//			vect<double> corr = velocity.project(penetration) * -1;
//			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);
//			tankPos.setx(tankPos.getx() + velocity.getx());
//			collide[0] = true;
//
//		}
//		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
//		if (b1.rX - b2.lX >= 0)
//		if (b2.rX - b1.lX >= 0)
//		if (b1.tY - b2.bY >= 0)
//		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
//		{
//			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
//			penetration.setx(0);
//			vect<double> corr = velocity.project(penetration) * -1;
//			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);
//			tankPos.sety(tankPos.gety() + velocity.gety());
//			collide[1] = true;
//		}
//	}
//}

//other attempt at player to player collision

//for (int count = 0; count < world->getplayers(); count++)
//{
//	Tank *tempPointer;
//	switch (count + 1)
//	{
//	case 1:
//		tempPointer = &world->p_1;
//		break;
//	case 2:
//		tempPointer = &world->p_2;
//		break;
//	case 3:
//		tempPointer = &world->p_3;
//		break;
//	case 4:
//		tempPointer = &world->p_4;
//		break;
//	}
//	if (tempPointer != this)
//	{
//		b1 = this->getBox(this->tankPos.getx() + this->velocity.getx(), this->tankPos.gety());
//		Box b2 = tempPointer->getBox(tempPointer->tankPos.getx() + tempPointer->velocity.getx(), tempPointer->tankPos.gety());
//		if (b1.rX - b2.lX >= 0)
//		if (b2.rX - b1.lX >= 0)
//		if (b1.tY - b2.bY >= 0)
//		if (b2.tY - b1.bY >= 0 && velocity.getx() != 0)
//		{
//			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
//			penetration.sety(0);
//			vect<double> corr = velocity.project(penetration) * -1;
//			velocity.setx(velocity.getx() + corr.normalize().getx() * velocity.magnitude() * -1);
//
//			vect<double> penetration2 = (tempPointer->tankPos - (vect<double>((b1.lX + b1.rX) / 2, (b1.tY + b1.tY) / 2)));
//			penetration2.sety(0);
//			vect<double> corr2 = tempPointer->velocity.project(penetration2) * -1;
//			tempPointer->velocity.setx(tempPointer->velocity.getx() + corr2.normalize().getx() * tempPointer->velocity.magnitude() * -1);
//
//			tankPos.setx(tankPos.getx() + velocity.getx());
//			tempPointer->tankPos.setx(tempPointer->tankPos.getx() + tempPointer->velocity.getx());
//
//			collide[0] = true;
//
//		}
//		b1 = this->getBox(this->tankPos.getx(), this->tankPos.gety() + this->velocity.gety());
//		if (b1.rX - b2.lX >= 0)
//		if (b2.rX - b1.lX >= 0)
//		if (b1.tY - b2.bY >= 0)
//		if (b2.tY - b1.bY >= 0 && velocity.gety() != 0)
//		{
//			vect<double> penetration = (tankPos - (vect<double>((b2.lX + b2.rX) / 2, (b2.tY + b2.tY) / 2)));
//			penetration.setx(0);
//			vect<double> corr = velocity.project(penetration) * -1;
//			velocity.sety(velocity.gety() + corr.normalize().gety() * velocity.magnitude() * -1);
//
//			vect<double> penetration2 = (tempPointer->tankPos - (vect<double>((b1.lX + b1.rX) / 2, (b1.tY + b1.tY) / 2)));
//			penetration2.setx(0);
//			vect<double> corr2 = tempPointer->velocity.project(penetration2) * -1;
//			tempPointer->velocity.sety(tempPointer->velocity.gety() + corr2.normalize().gety() * tempPointer->velocity.magnitude() * -1);
//
//
//			tankPos.sety(tankPos.gety() + velocity.gety());
//			tempPointer->tankPos.sety(tempPointer->tankPos.gety() + tempPointer->velocity.gety());
//
//
//			collide[1] = true;
//		}
//	}
//}

void Tank::setHealth(int set)
{
	if (set < 0)
		health = (list->modifiers[modifierlist::index::hearts] == true) ? 3 : 1;
	else
		health = set;
}

bool Tank::bulletWallCollision(int bulletNum, int choice)
{
	int size = shot[bulletNum].getbulletSize();
	switch (choice)
	{
	case X:
		for (int count = 0; count < walls.size(); count++)
		{
			if ((shot[bulletNum].getPosY() < walls[count].tY + size && shot[bulletNum].getPosY() > walls[count].bY - size) && (shot[bulletNum].getPosX()  > walls[count].lX - size && shot[bulletNum].getPosX() < walls[count].rX + size))
			{
				return true;
			}
		}
		if (list->modifiers[modifierlist::index::deathsofthepast])
		{
			for (int count = 0; count < 4; count++)
			{
				if ((shot[bulletNum].getPosY() < bodies[count].tY + size && shot[bulletNum].getPosY() > bodies[count].bY - size) && (shot[bulletNum].getPosX()  > bodies[count].lX - size && shot[bulletNum].getPosX() < bodies[count].rX + size))
				{
					return true;
				}

			}
		}
		return false;
		break;
	case Y:
		for (int count = 0; count < walls.size(); count++)
		{
			if ((shot[bulletNum].getPosY() < walls[count].tY + size && shot[bulletNum].getPosY() > walls[count].bY - size) && (shot[bulletNum].getPosX()  > walls[count].lX - size && shot[bulletNum].getPosX() < walls[count].rX + size))
			{
				return true;
			}

		}
		if (list->modifiers[modifierlist::index::deathsofthepast])
		{
			for (int count = 0; count < 4; count++)
			{
				if ((shot[bulletNum].getPosY() < bodies[count].tY + size && shot[bulletNum].getPosY() > bodies[count].bY - size) && (shot[bulletNum].getPosX()  > bodies[count].lX - size && shot[bulletNum].getPosX() < bodies[count].rX + size))
				{
					return true;
				}

			}
		}
		return false;
		break;

	case XandY:
		for (int count = 0; count < walls.size(); count++)
		{
			if ((shot[bulletNum].getPosY() < walls[count].tY + size && shot[bulletNum].getPosY() > walls[count].bY - size) && (shot[bulletNum].getPosX()  > walls[count].lX - size && shot[bulletNum].getPosX() < walls[count].rX + size))
			{
				return true;
			}
		}

		if (list->modifiers[modifierlist::index::deathsofthepast])
		{
			for (int count = 0; count < 4; count++)
			{
				if ((shot[bulletNum].getPosY() < bodies[count].tY + size && shot[bulletNum].getPosY() > bodies[count].bY - size) && (shot[bulletNum].getPosX()  > bodies[count].lX - size && shot[bulletNum].getPosX() < bodies[count].rX + size))
				{
					return true;
				}

			}
		}
		return false;
		break;
		//pointless at the moment? won't get rid of it yet because ??????
	case XorY:
		for (int count = 0; count < walls.size(); count++)
		{
			if ((shot[bulletNum].getPosY() < walls[count].tY + size && shot[bulletNum].getPosY() > walls[count].bY - size) || (shot[bulletNum].getPosX()  > walls[count].lX - size && shot[bulletNum].getPosX() < walls[count].rX + size))
			{
				return true;
			}
		}
		if (list->modifiers[modifierlist::index::deathsofthepast])
		{
			for (int count = 0; count < 4; count++)
			{
				if ((shot[bulletNum].getPosY() < bodies[count].tY + size && shot[bulletNum].getPosY() > bodies[count].bY - size) && (shot[bulletNum].getPosX()  > bodies[count].lX - size && shot[bulletNum].getPosX() < bodies[count].rX + size))
				{
					return true;
				}

			}
		}
		return false;
		break;
	}
}

void Tank::turretMovement(bool inverted)
{
	Coords pos;
	if (inverted == false)
		pos = playerNumber->getRightStick();
	else
		pos = playerNumber2->getRightStick();
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


void Tank::bulletMovement(bool bounceToggle, int bulletSpeed, layer* temp)//controls bullet movement
{
	bool erase = false;
	bool collided = false;
	int tempSize = shot.size();
	if (shot.size() > 0)
	{
		for (int count = 0; count < shot.size(); count++)
		{
			//gets the size of the bullet, so i can do it once per frame as opposed to 4 times
			int size = shot[count].getbulletSize();
			shot[count].movement(*bulletImage, true, false, temp, TWTS, list->modifiers[modifierlist::index::bulletacceleration]);//moves bullet in the X direction
			//X
			if (bulletWallCollision(count, X) == true)//if bullet goes off screen deletes its.
			{
				if (bounceToggle == false)
				{

					erase = true;
				}
				else
				{
					//the first argument is the angle, this is a bit of a hacky solution because i haven't implemented support for angled surface bullet reflection, the bulletSpeed is taken as an argument for that, because trigonometry
					if (!shot[count].bouncegrace)
					{
						shot[count].redirect(90, bulletSpeed);
						shot[count].bouncegrace = true;
						shot[count].lifespan--;
					}
					else
					{
						shot[count].bouncegrace = false;
					}
					collided = true;
				}
			}

			if (shot[count].getDistance() > 2500)
			{
				if (bounceToggle)
				{
					if (shot[count].getDistance() > 12000);
					erase = true;
				}
				else
					erase = true;
			}
			else if (shot[count].getPosX() > windowWidth + 100)
			{
				shot[count].setPosX(0);
			}
			else if (shot[count].getPosY() > windowHeight + 100)
			{
				shot[count].setPosY(0);
			}
			else if (shot[count].getPosY() < windowMin - 100)
			{
				shot[count].setPosY(1080);
			}
			else if (shot[count].getPosX() < windowMin - 100)
			{
				shot[count].setPosX(1920);
			}
			shot[count].movement(*bulletImage, false, true, temp, TWTS, list->modifiers[modifierlist::index::bulletacceleration]);//moves bullet
			temp->push_back(*bulletImage, shot[count].getPosX(), shot[count].getPosY(), 0, 0, shot[count].angle2);
			//Y
			if (bulletWallCollision(count, Y) == true)//if bullet goes off screen deletes its.
			{
				if (bounceToggle == false)
				{

					erase = true;
				}
				else
				{
					//the first argument is the angle, this is a bit of a hacky solution because i haven't implemented support for angled surface bullet reflection, the bulletSpeed is taken as an argument for that, because trigonometry
					if (!collided)
					{
						if (!shot[count].bouncegrace)
						{
							shot[count].redirect(0, bulletSpeed);
							shot[count].lifespan--;
							shot[count].bouncegrace = true;
						}
						else
						{
							shot[count].bouncegrace = false;
						}
					}
				}
			}
			temp->push_back(*bulletImage, shot[count].getPosX(), shot[count].getPosY(), 0, 0, shot[count].angle2);
			if (shot[count].lifespan <= 0)
			{
				erase = true;
			}
			if (erase)
			{

				if (shot.size() == tempSize)
				{
					if (world->list->modifiers[modifierlist::aoe] == true)
					{
						world->splat.push_back(pointerSprite(shot[count].getPosX(), shot[count].getPosY(), 0, *aoe, 0), 10, 7);
						world->getCollision(65);
					}
					if (shot.size() == tempSize)
					{
						shot.erase(shot.begin() + count);
						shot.shrink_to_fit();
					}
				}
			}
			erase = false;
		}
	}
}


void Tank::movement(int choice, double time, World* world, layer* layering)//controls the tanks movement
{
	int maxX = 1820;
	int maxY = 980;
	int minXY = 100;
	Coords stick;
	stick = playerNumber->getLeftStick();
	double tempx, tempy; //tempy <3
	double mY;
	double mX;

	switch (choice)//controls what movement scheme is being used
	{

	case 5:
		//"tight" feeling movement
		//"top speed"
		velocityMulty = 1.5 + TWTS / 2;

		if (list->modifiers[modifierlist::dash] == true && dashOn == true)
		{
			if (dashSetter == false)
			{
				lastvelocity.setx(velocity.getx());
				lastvelocity.sety(velocity.gety());
				double fractionx = 384 / (std::abs(velocity.getx()) + std::abs(velocity.gety()));
				double fractiony = 384 / (std::abs(velocity.getx()) + std::abs(velocity.gety()));
				fractionx = sqrt(fractionx * std::abs(velocity.getx()));
				fractiony = sqrt(fractiony * std::abs(velocity.gety()));
				velocity.setx(fractionx);
				velocity.sety(fractiony);

				if ((velocity.getx() > 0 && lastvelocity.getx() < 0) || (velocity.getx() < 0 && lastvelocity.getx() > 0))
					velocity.setx(velocity.getx() *-1);


				if ((velocity.gety() > 0 && lastvelocity.gety() < 0) || (velocity.gety() < 0 && lastvelocity.gety() > 0))
					velocity.sety(velocity.gety() *-1);

				lastvelocity.setx(velocity.getx());
				lastvelocity.sety(velocity.gety());

			}
			else
			{
				velocity.setx(lastvelocity.getx());
				velocity.sety(lastvelocity.gety());
			}
			dashSetter = true;

		}
		else if (dashSetter == true && dashOn == false)
		{
			dashSetter = false;
			velocity.setx(lastvelocity.getx());
			velocity.sety(lastvelocity.gety());
		}
		if (list->modifiers[modifierlist::melee] == true && meleeOn == true)
		{
			if (meleeSetter == false)
			{
				world->splat.push_back(pointerSprite(getXP(), getYP(), 0, holder->tank[tank::melee], 0), 100, 3);

				lastvelocity.setx(velocity.getx());
				lastvelocity.sety(velocity.gety());
				double fractionx = 256 / (std::abs(velocity.getx()) + std::abs(velocity.gety()));
				double fractiony = 256 / (std::abs(velocity.getx()) + std::abs(velocity.gety()));
				lethalspeed = true;
				fractionx = sqrt(fractionx * std::abs(velocity.getx()));
				fractiony = sqrt(fractiony * std::abs(velocity.gety()));
				velocity.setx(fractionx);
				velocity.sety(fractiony);

				if ((velocity.getx() > 0 && lastvelocity.getx() < 0) || (velocity.getx() < 0 && lastvelocity.getx() > 0))
					velocity.setx(velocity.getx() *-1);


				if ((velocity.gety() > 0 && lastvelocity.gety() < 0) || (velocity.gety() < 0 && lastvelocity.gety() > 0))
					velocity.sety(velocity.gety() *-1);

				lastvelocity.setx(velocity.getx());
				lastvelocity.sety(velocity.gety());

			}
			else
			{
				velocity.setx(lastvelocity.getx());
				velocity.sety(lastvelocity.gety());
			}
			meleeSetter = true;

		}
		else if (meleeSetter == true && meleeOn == false)
		{
			meleeSetter = false;
			velocity.setx(lastvelocity.getx());
			velocity.sety(lastvelocity.gety());
		}

		if (list->modifiers[modifierlist::timewilltell] == true)
		{
			time_t timeTemp = clock();

			if ((timeTemp - timeWillTell) / CLOCKS_PER_SEC > 10 && world->drawspeedup == false)
			{
				//display time will tell thing for a second
				timeWillTell = clock();
				if (TWTS <= 1.6)
				{
					TWTS += 0.2;
				}
				world->drawspeedup = true;
				std::cout << "speed up" << std::endl;
				//std::cout << "TimeTemp: " << timeTemp << "Time: " << timeWillTell << std::endl;
			}
			else if (world->drawspeedup == true)
			{
				world->drawspeedup = false;
				world->splat.push_back(pointerSprite(960, 540, 0, *world->speedUpSprite, 0), 1000);
				FzlPlaySound(sounds->stank[speedUp]);
			}
		}

		if (ice == true && snowCheck() == false)
		{


			if (velocity.gety() + stick.y / 0.8 < 8 && velocity.gety() + stick.y / 0.8 > -8)
			{
				velocity.sety(velocity.gety() + stick.y / 0.8);

			}
			else
				velocity.sety(velocity.gety() - (velocity.gety() / 24));
			if (velocity.getx() + stick.x / 0.8 < 8 && velocity.getx() + stick.x / 0.8 > -8)
			{
				velocity.setx(velocity.getx() + stick.x / 0.8);
			}
			else
				velocity.setx(velocity.getx() - (velocity.getx() / 24));


			tempy = velocity.gety();
			tempx = velocity.getx();

			velocity.setx(tempx - (tempx / 32));
			velocity.sety(tempy - (tempy / 32));
			//"friction"
		}
		else
		{
			//  << "snow!" << std::endl;
			velocity.sety(velocity.gety() + stick.y / 0.8);
			velocity.setx(velocity.getx() + stick.x / 0.8);




			tempx = velocity.getx();
			tempy = velocity.gety();
			//"friction"
			velocity.setx(tempx - (tempx / 8));
			velocity.sety(tempy - (tempy / 8));
		}
		if (watery = true && waterCheck() == true)
		{
			velocity.setx(tempx - (tempx / 5));
			velocity.sety(tempy - (tempy / 5));
		}


	}
	vect<double> velocityTemp = velocity;
	velocity = velocity * velocityMulty;
	wallCollision(world);
	velocity = velocityTemp;
	if (tankPos.getx() - 44 < 0)
	{
		if (tankPos.getx() <= 0)
		{
			tankPos.setx(1920);
		}

		layering->push_back(*staticTank, 1920 + tankPos.getx(), static_cast<float>(getY()), 0, spriteSpot, spriteSpot2);
	}
	else if (tankPos.getx() + 44 >= 1920)
	{
		if (tankPos.getx() >= 1920)
			tankPos.setx(0);
		layering->push_back(*staticTank, 0 - (1920 - tankPos.getx()), static_cast<float>(getY()), 0, spriteSpot, spriteSpot2);
	}
	if (tankPos.gety() - 44 <= 0)
	{
		if (tankPos.gety() <= 0)
			tankPos.sety(1080);
		layering->push_back(*staticTank, static_cast<float>(getX()), 1080 + tankPos.gety(), 0, spriteSpot, spriteSpot2);
	}
	else if (tankPos.gety() + 44 >= 1080)
	{
		if (tankPos.gety() >= 1080)
			tankPos.sety(0);
		layering->push_back(*staticTank, static_cast<float>(getX()), 0 - (1080 + tankPos.gety()), 0, spriteSpot, spriteSpot2);
	}

}

double clip(double _n, double _lower, double _upper)
{
	return std::fmax(_lower, std::fmin(_n, _upper));
}



//

bool Tank::snowCheck()
{
	for (int count = 0; count < snow.size(); count++)
	{
		if (tankPos.getx() > snow[count].lX && tankPos.getx() < snow[count].rX)
		{
			if (tankPos.gety() > snow[count].bY && tankPos.gety() < snow[count].tY)
			{
				return true;
			}
		}
	}
	return false;
}
bool Tank::waterCheck()
{
	for (int count = 0; count < water.size(); count++)
	{
		if (tankPos.getx() > water[count].lX && tankPos.getx() < water[count].rX)
		{
			if (tankPos.gety() > water[count].bY && tankPos.gety() < water[count].tY)
			{
				return true;
			}
		}
	}
	return false;
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

controller* Tank::getEnemy(bool type)//return the enemies controller.
{
	if (type == false)
		return playerNumber2;

	else
		return playerNumber;
}

void Tank::inertialMove()
{
	double destinationX = this->getX() + getvelocityX();
	double destinationY = this->getY() + getvelocityY();
	this->setPos(destinationX, destinationY);
}

bool Tank::positionLegality(double _x, double _y)
{

	for (int count = 0; count < walls.size(); count++)
	{
		if ((_y < (walls[count].tY) && _y >(walls[count].bY)) && (_x >(walls[count].lX) && _x < (walls[count].rX)))
		{
			return false;
		}
		if (_x < 100 || _x > 1880 || _y < 100 || _y >  980)
		{
			return false;
		}

	}
	return true;
}

void Tank::setDirection()
{
	Coords temp = this->playerNumber->getLeftStick();

	if (temp.x < 0)
	{
		temp.x *= -1;
	}
	if (temp.y < 0)
	{
		temp.y *= -1;
	}

	if (temp.x > temp.y)
	{
		if (this->playerNumber->getLeftStick().x > 0)
			dir = 2;
		else
			dir = 0;
	}
	else if (temp.y > temp.x)
	{
		if (this->playerNumber->getLeftStick().y > 0)
			dir = 3;
		else
			dir = 1;
	}
	else
	{
		dir = 5;
	}
	//   << getvelocityX() << "   " << getvelocityY() << std::endl;
}

void Tank::map2()
{
	ice = false;
	watery = false;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();

	//	Block 1:
	walls.push_back(Box(209, 779, 110, 695));

	//	Block 2 : 
	walls.push_back(Box(849, 879, 800, 745));
	walls.push_back(Box(849, 879, 700, 845));

	//	Block 3 : 
	walls.push_back(Box(1199, 879, 1050, 845));
	walls.push_back(Box(1099, 879, 1050, 745));

	//	Block 4 :
	walls.push_back(Box(1809, 779, 1710, 695));

	//	Block 5 :
	walls.push_back(Box(509, 579, 410, 500));
	walls.push_back(Box(509, 679, 460, 395));

	//	Block 6 :
	walls.push_back(Box(1459, 679, 1410, 395));
	walls.push_back(Box(1509, 579, 1410, 595));

	//	Block 7 :
	walls.push_back(Box(209, 379, 109, 295));

	//Block 8 :
	walls.push_back(Box(859, 329, 810, 195));
	walls.push_back(Box(859, 229, 710, 195));

	//Block 9 : 
	walls.push_back(Box(1109, 329, 1060, 200));
	walls.push_back(Box(1209, 229, 1060, 200));

	//Block 10 :
	walls.push_back(Box(1809, 379, 1710, 295));


	//Border Collision : Block 1 : 
	walls.push_back(Box(99, 1079, 0, 880));
	walls.push_back(Box(809, 1079, 0, 990));
	//Block 2 : 
	walls.push_back(Box(1919, 1079, 1110, 990));
	walls.push_back(Box(1919, 1079, 1820, 880));
	//Block 3 : 
	walls.push_back(Box(99, 779, 0, 280));
	//	Block 4 : 
	walls.push_back(Box(1919, 779, 1820, 280));
	//Block 5 :
	walls.push_back(Box(99, 179, 0, 0));
	walls.push_back(Box(809, 89, 0, 0));
	//	Block 6 :
	walls.push_back(Box(1919, 179, 1820, 0));
	walls.push_back(Box(1919, 89, 1110, 0));
}

void Tank::map4()
{
	ice = false;
	watery = false;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	walls.push_back(Box(99, 1079, 0, 790));
	walls.push_back(Box(299, 1079, 0, 990));
	walls.push_back(Box(810, 1079, 611, 990));
	walls.push_back(Box(1310, 1079, 1111, 990));
	walls.push_back(Box(1919, 1079, 1620, 990));
	walls.push_back(Box(1919, 1079, 1820, 790));
	walls.push_back(Box(1919, 639, 1820, 440));
	walls.push_back(Box(1919, 289, 1820, 0));
	walls.push_back(Box(1919, 89, 1620, 0));
	walls.push_back(Box(1310, 89, 1111, 0));
	walls.push_back(Box(810, 89, 611, 0));
	walls.push_back(Box(299, 89, 0, 0));
	walls.push_back(Box(99, 289, 0, 0));
	walls.push_back(Box(99, 639, 0, 440));
	walls.push_back(Box(810, 844, 711, 745));
	walls.push_back(Box(1010, 844, 911, 745));
	walls.push_back(Box(1210, 844, 1111, 745));
	walls.push_back(Box(1620, 789, 1521, 700));
	walls.push_back(Box(1620, 599, 1521, 490));
	walls.push_back(Box(1620, 389, 1521, 290));
	walls.push_back(Box(1210, 334, 1111, 235));
	walls.push_back(Box(1010, 334, 911, 235));
	walls.push_back(Box(810, 334, 711, 235));
	walls.push_back(Box(400, 389, 301, 290));
	walls.push_back(Box(400, 599, 301, 490));
	walls.push_back(Box(400, 789, 301, 700));


	holes.push_back(Box(910, 844, 811, 745));
	holes.push_back(Box(1110, 844, 1011, 745));
	holes.push_back(Box(1620, 699, 1521, 600));
	holes.push_back(Box(1620, 489, 1521, 390));
	holes.push_back(Box(1110, 334, 1011, 235));
	holes.push_back(Box(910, 334, 811, 235));
	holes.push_back(Box(400, 489, 301, 390));
	holes.push_back(Box(400, 699, 301, 600));

}

void Tank::map5()
{
	ice = false;
	watery = true;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	walls.push_back(Box(99, 1079, 0, 880));
	walls.push_back(Box(199, 1079, 0, 990));
	walls.push_back(Box(1919, 1079, 1725, 990));
	walls.push_back(Box(1919, 1079, 1820, 881));
	walls.push_back(Box(1919, 189, 1820, 0));
	walls.push_back(Box(1919, 89, 1725, 0));
	walls.push_back(Box(199, 89, 0, 0));
	walls.push_back(Box(99, 189, 0, 0));
	walls.push_back(Box(394, 846, 295, 647));
	walls.push_back(Box(1134, 880, 785, 831));
	walls.push_back(Box(1669, 829, 1470, 730));
	walls.push_back(Box(449, 329, 250, 230));
	walls.push_back(Box(1134, 254, 785, 205));
	walls.push_back(Box(1624, 429, 1525, 230));
	walls.push_back(Box(1009, 588, 910, 489));
	water.push_back(Box(1674, 1079, 250, 990));
	water.push_back(Box(712, 1079, 250, 940));
	water.push_back(Box(1674, 1079, 1213, 940));
	water.push_back(Box(149, 829, 1, 240));
	water.push_back(Box(1919, 830, 1770, 240));
	water.push_back(Box(1674, 89, 250, 0));
	water.push_back(Box(712, 139, 250, 0));
	water.push_back(Box(1674, 139, 1213, 0));
	water.push_back(Box(1212, 692, 713, 393));
	water.push_back(Box(1162, 742, 764, 343));
	water.push_back(Box(1112, 792, 814, 293));


}

void Tank::map3()
{
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	ice = true;
	watery = false;
	//	Block 1:

	//ICE 1 Map coordinates(Bottom left & Top Right)
	walls.push_back(Box(99, 1079, 0, 805)); //1
	walls.push_back(Box(319, 1079, 0, 990)); //2
	walls.push_back(Box(819, 1079, 520, 990));//3
	walls.push_back(Box(1399, 1079, 1100, 990));//4
	walls.push_back(Box(1919, 1079, 1600, 990));//5
	walls.push_back(Box(1919, 1079, 1820, 805));//6
	walls.push_back(Box(1919, 613, 1820, 464));//7
	walls.push_back(Box(1919, 274, 1820, 0));//8
	walls.push_back(Box(1919, 89, 1600, 0));//9
	walls.push_back(Box(1399, 89, 1110, 0));//10
	walls.push_back(Box(819, 89, 520, 0));//11
	walls.push_back(Box(319, 89, 0, 0));//12
	walls.push_back(Box(99, 274, 0, 0));//13 // missed 14 so offset by 1
	walls.push_back(Box(99, 613, 0, 464));//15


	walls.push_back(Box(385, 829, 336, 730));//30
	walls.push_back(Box(785, 829, 737, 730));//31
	walls.push_back(Box(1185, 829, 1136, 730));//32
	walls.push_back(Box(1585, 829, 1536, 730));//33
	walls.push_back(Box(360, 329, 261, 280));//34
	walls.push_back(Box(810, 329, 711, 280));//35
	walls.push_back(Box(1210, 329, 1111, 280));//36
	walls.push_back(Box(1610, 329, 1511, 280));//37


	//holes
	holes.push_back(Box(680, 544, 441, 556));//38
	holes.push_back(Box(1480, 544, 1241, 556));//40

	//snow normal
	snow.push_back(Box(735, 613, 386, 464));//39
	snow.push_back(Box(1535, 613, 1186, 464));//41
	snow.push_back(Box(174, 989, 100, 805));//16
	snow.push_back(Box(319, 989, 100, 915));//17
	snow.push_back(Box(819, 989, 520, 940));//18
	snow.push_back(Box(1399, 989, 1100, 940));//19
	snow.push_back(Box(1819, 989, 1600, 915));//20
	snow.push_back(Box(1819, 989, 1745, 805));//21
	snow.push_back(Box(1819, 613, 1720, 464));//22
	snow.push_back(Box(1819, 294, 1745, 90));//23
	snow.push_back(Box(1819, 164, 1600, 90));//24
	snow.push_back(Box(1399, 139, 1100, 90));//25
	snow.push_back(Box(819, 139, 520, 90));//26
	snow.push_back(Box(319, 164, 100, 90));//27
	snow.push_back(Box(174, 274, 100, 90));//28
	snow.push_back(Box(199, 613, 100, 464));//29
}

void Tank::map7()
{
	watery = false;
	ice = false;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();

	walls.push_back(Box(99, 1079, 0, 790));
	walls.push_back(Box(209, 1079, 0, 990));
	walls.push_back(Box(609, 1079, 310, 990));
	walls.push_back(Box(809, 1079, 710, 990));
	walls.push_back(Box(1209, 1079, 1110, 990));
	walls.push_back(Box(1609, 1079, 1310, 990));
	walls.push_back(Box(1919, 1079, 1710, 990));
	walls.push_back(Box(1919, 1079, 1820, 790));
	walls.push_back(Box(1919, 289, 1820, 0));
	walls.push_back(Box(1919, 89, 1710, 0));
	walls.push_back(Box(1609, 89, 1310, 0));
	walls.push_back(Box(1209, 89, 1110, 0));
	walls.push_back(Box(809, 89, 710, 0));
	walls.push_back(Box(609, 89, 310, 0));
	walls.push_back(Box(209, 89, 0, 0));
	walls.push_back(Box(99, 289, 0, 0));
	walls.push_back(Box(209, 642, 110, 543));
	walls.push_back(Box(409, 642, 310, 543));
	walls.push_back(Box(610, 386, 511, 287));
	walls.push_back(Box(810, 386, 711, 287));
	walls.push_back(Box(1214, 822, 1115, 723));
	walls.push_back(Box(1414, 822, 1315, 723));
	walls.push_back(Box(1606, 563, 1507, 464));
	walls.push_back(Box(1806, 563, 1707, 464));


	holes.push_back(Box(709, 1079, 610, 990));
	holes.push_back(Box(1309, 1079, 1210, 990));
	holes.push_back(Box(309, 1079, 210, 990));
	holes.push_back(Box(1709, 1079, 1610, 990));
	holes.push_back(Box(1709, 89, 1610, 0));
	holes.push_back(Box(1309, 89, 1210, 0));
	holes.push_back(Box(1706, 563, 1607, 464));
	holes.push_back(Box(709, 89, 610, 0));
	holes.push_back(Box(309, 89, 210, 0));
	holes.push_back(Box(309, 642, 210, 543));
	holes.push_back(Box(710, 386, 611, 287));
	holes.push_back(Box(1314, 822, 1215, 723));

}

void Tank::map6()//ice map 2
{
	ice = true;
	watery = false;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	walls.push_back(Box(99, 1079, 0, 690));
	walls.push_back(Box(399, 1079, 0, 990));
	walls.push_back(Box(1207, 1079, 712, 990));
	walls.push_back(Box(1919, 1079, 1511, 990));
	walls.push_back(Box(1919, 1079, 1820, 690));
	walls.push_back(Box(1919, 389, 1820, 0));
	walls.push_back(Box(1919, 89, 1511, 0));
	walls.push_back(Box(1207, 89, 712, 0));
	walls.push_back(Box(399, 89, 0, 0));
	walls.push_back(Box(99, 389, 0, 0));

	walls.push_back(Box(400, 754, 301, 655));
	walls.push_back(Box(500, 754, 301, 705));
	walls.push_back(Box(500, 804, 401, 705));
	walls.push_back(Box(600, 804, 401, 755));
	walls.push_back(Box(600, 854, 501, 755));
	walls.push_back(Box(1425, 854, 1326, 755));
	walls.push_back(Box(1525, 804, 1326, 755));
	walls.push_back(Box(1525, 804, 1426, 705));
	walls.push_back(Box(1625, 754, 1426, 705));
	walls.push_back(Box(1625, 754, 1526, 655));
	walls.push_back(Box(1625, 429, 1526, 330));
	walls.push_back(Box(1625, 379, 1426, 330));
	walls.push_back(Box(1525, 379, 1426, 280));
	walls.push_back(Box(1525, 329, 1326, 280));
	walls.push_back(Box(1425, 329, 1326, 230));
	walls.push_back(Box(400, 429, 301, 330));
	walls.push_back(Box(500, 379, 301, 330));
	walls.push_back(Box(500, 379, 401, 280));
	walls.push_back(Box(600, 329, 401, 280));
	walls.push_back(Box(600, 329, 501, 230));


	snow.push_back(Box(174, 989, 100, 690));
	snow.push_back(Box(399, 989, 100, 915));
	snow.push_back(Box(1819, 989, 1511, 915));
	snow.push_back(Box(1819, 989, 1745, 690));
	snow.push_back(Box(1819, 389, 1745, 90));
	snow.push_back(Box(1819, 164, 1511, 90));
	snow.push_back(Box(399, 164, 100, 90));
	snow.push_back(Box(174, 389, 100, 90));
	snow.push_back(Box(1160, 829, 761, 630));
	snow.push_back(Box(1160, 454, 761, 255));

	holes.push_back(Box(1110, 756, 811, 673));
	holes.push_back(Box(1110, 381, 811, 328));
}


void Tank::map8()//island 2
{
	watery = true;
	ice = false;
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	walls.push_back(Box(99, 1079, 0, 880));
	walls.push_back(Box(509, 1079, 0, 990));
	walls.push_back(Box(1919, 1079, 1410, 990));
	walls.push_back(Box(1919, 1079, 1820, 880));
	walls.push_back(Box(1919, 689, 1820, 390));
	walls.push_back(Box(1919, 179, 1820, 0));
	walls.push_back(Box(1919, 89, 1410, 0));
	walls.push_back(Box(509, 89, 0, 0));
	walls.push_back(Box(99, 179, 0, 0));
	walls.push_back(Box(99, 689, 0, 390));
	walls.push_back(Box(299, 779, 200, 680));
	walls.push_back(Box(699, 679, 600, 580));
	walls.push_back(Box(499, 389, 400, 290));
	walls.push_back(Box(1649, 629, 1300, 530));


	water.push_back(Box(1409, 1079, 510, 990));
	water.push_back(Box(1919, 879, 1820, 690));
	water.push_back(Box(1919, 389, 1820, 180));
	water.push_back(Box(1409, 89, 510, 0));
	water.push_back(Box(99, 389, 0, 180));
	water.push_back(Box(99, 879, 0, 690));
	water.push_back(Box(549, 879, 300, 830));
	water.push_back(Box(549, 879, 425, 780));
	water.push_back(Box(599, 829, 425, 780));
	water.push_back(Box(474, 592, 300, 493));
	water.push_back(Box(399, 542, 250, 443));
	water.push_back(Box(714, 279, 550, 230));
	water.push_back(Box(714, 279, 600, 180));
	water.push_back(Box(774, 229, 600, 180));
	water.push_back(Box(1109, 689, 810, 390));
	water.push_back(Box(1599, 879, 1400, 830));
	water.push_back(Box(1549, 879, 1400, 730));
	water.push_back(Box(1549, 829, 1325, 730));
	water.push_back(Box(1599, 404, 1450, 355));
	water.push_back(Box(1549, 404, 1450, 305));
	water.push_back(Box(1499, 329, 1400, 230));
	water.push_back(Box(1499, 279, 1325, 230));

}

void Tank::layering(layer *temp)
{
	temp->reorder(walls);
	temp->draw();
}


void Tank::map()
{
	walls.clear();
	bounds.clear();
	holes.clear();
	snow.clear();
	ice = false;
	watery = false;
	//	Alain Sangalang
	//block 1
	walls.clear();
	bounds.clear();
	//1
	walls.push_back(Box(99, 1079, 0, 830));
	//2
	walls.push_back(Box(299, 1079, 0, 990));
	//3
	walls.push_back(Box(1259, 1079, 660, 990));
	//4
	walls.push_back(Box(1919, 1079, 1620, 990));
	//5
	walls.push_back(Box(1919, 1079, 1820, 830));
	//6
	walls.push_back(Box(1919, 638, 1820, 439));
	//7
	walls.push_back(Box(1919, 249, 1820, 0));
	//8
	walls.push_back(Box(1919, 89, 1620, 0));
	//9
	walls.push_back(Box(1259, 89, 660, 0));
	//10
	walls.push_back(Box(299, 89, 0, 0));
	//11
	walls.push_back(Box(99, 249, 0, 0));
	//12
	walls.push_back(Box(99, 638, 0, 439));
	//13
	walls.push_back(Box(324, 873, 255, 824));
	//14
	walls.push_back(Box(1669, 873, 1570, 824));
	//15
	walls.push_back(Box(324, 253, 225, 204));
	//16
	walls.push_back(Box(1669, 253, 1570, 204));
	//17
	walls.push_back(Box(619, 586, 570, 488));
	//18
	walls.push_back(Box(1349, 586, 1300, 487));
	//19
	holes.push_back(Box(324, 563, 225, 514));
	//20
	holes.push_back(Box(1694, 563, 1595, 514));
	//21
	holes.push_back(Box(1009, 754, 910, 705));
	//22
	holes.push_back(Box(1009, 354, 910, 305));
}

void Tank::deleteSprites()//buggy dont call
{

}
Box Tank::getBox(int x, int y)
{
	Box hitbox;
	int r = this->getRadius();
	hitbox.lX = x - r;
	hitbox.rX = x + r;
	hitbox.bY = y - r;
	hitbox.tY = y + r;
	return hitbox;
}

void Tank::updateVelocity(vect<double> _velocity)
{
	lastvelocity = velocity;
	velocity = _velocity;
}

void Tank::setPointer(World * _world)
{
	world = _world;

}

void Tank::shielded()
{

	time_t temp = clock();

	if (playerNumber->conButton(XINPUT_GAMEPAD_LEFT_SHOULDER) == true && shield == false)
	{
		FzlPlaySound(sounds->stank[shieldS]);
		shield = true;
		shieldTime = clock();
		shieldOn = true;

		this->greyshield = true;
		//SHIELD GRAYED OUT
		world->splat.push_back(pointerSprite(getXP(), getYP(), playerID, *bubble, 0, playerID), 100, 10);
	}
	else if (shieldOn == true)
	{
		if ((temp - shieldTime) > 1000)
		{
			shieldOn = false;
			shieldTime = clock();


		}
	}
	else if (shieldOn == false && shield == true)
	{
		if ((temp - shieldTime) / CLOCKS_PER_SEC > 4)
		{
			shield = false;

			this->greyshield = false;
		}
	}


}

void Tank::dashed()
{
	time_t temp = clock();

	if ((playerNumber->conButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true && isdashing == false)
		&& (getvelocityX() > 0.5 || getvelocityX() < -0.5 || getvelocityY() > 0.5 || getvelocityY() < -0.5))
	{
		FzlPlaySound(sounds->stank[dashS]);
		isdashing = true;
		dashTime = clock();
		dashOn = true;
		//world->splat.push_back(pointerSprite(getXP(), getYP(), getA(), world->holder->tank[dash], dir), 100, 7);
		this->greydash = true;
		////FzlPlaySound(dashS);

	}
	else if (dashOn == true)
	{

		if ((temp - dashTime) > 100)
		{
			dashOn = false;
			dashTime = clock();
		}
	}
	else if (dashOn == false && isdashing == true)
	{
		if ((temp - dashTime) / CLOCKS_PER_SEC > 0.2)
		{
			isdashing = false;
			this->greydash = false;
		}
	}
}
void Tank::melee()
{
	time_t temp = clock();

	if ((playerNumber->conLeftTrigger() > 0.1 && ismeleeing == false)
		&& (getvelocityX() > 0.5 || getvelocityX() < -0.5 || getvelocityY() > 0.5 || getvelocityY() < -0.5))
	{
		ismeleeing = true;
		meleeTime = clock();
		meleeOn = true;

		this->greydash = true;
		////FzlPlaySound(dashS);

	}
	else if (meleeOn == true)
	{

		if ((temp - meleeTime) > 150)
		{
			meleeOn = false;
			lethalspeed = false;
		}
	}
	else if (meleeOn == false && ismeleeing == true)
	{
		if ((temp - meleeTime) / CLOCKS_PER_SEC > 0.2)
		{
			ismeleeing = false;
			meleed = false;
			//this->greydash = false;
		}
	}
}
static double error = 0.0001;
//the 42 is offset, temporary. reminder to remove
World::World(int x, int _bulletDelay, int _players, modifierlist & list, SpriteList* holder, SoundList* _sounds)




//constructor. sets the players starting location
{

	p_1 = new Tank(0, 150, 150, x, (_bulletDelay <= 5) ? true : true, 42, true, list, holder, _sounds);
	p_2 = new Tank(1, 1740, 945, x, (_bulletDelay <= 5) ? true : true, 42, true, list, holder, _sounds);
	p_3 = new Tank(2, 150, 920, x, (_bulletDelay <= 5) ? true : true, 42, true, list, holder, _sounds);
	p_4 = new Tank(3, 1715, 150, x, (_bulletDelay <= 5) ? true : true, 42, true, list, holder, _sounds);

	World::holder = holder;
	p_1->setPointer(this);
	p_2->setPointer(this);
	p_3->setPointer(this);
	p_4->setPointer(this);


	speedUpSprite = &holder->menu[menu::speedUpSprite];

	World::list = &list;
	for (int count = 0; count < 4; count++)
	{
		playerTurn[count] = false;
		playerWait[count] = 0;
		if (count < _players)
			death[count] = false;
		else
			death[count] = true;
	}

	players = _players;
	bulletSpeed = 20; //pixels / second
	bulletLimit = 100;
	bulletDelay = _bulletDelay;
	//	Alain Sangalang

	//block 1
	walls.push_back(Box(349, 855, 300, 756));
	walls.push_back(Box(349, 755, 250, 597));
	walls.push_back(Box(399, 705, 350, 597));
	//block 2
	walls.push_back(Box(849, 880, 550, 846));
	//block 3
	walls.push_back(Box(1199, 780, 1150, 697));
	//block 4
	walls.push_back(Box(1249, 730, 1200, 697));
	walls.push_back(Box(1449, 830, 1400, 796));
	walls.push_back(Box(1549, 880, 1450, 796));
	//block 5
	walls.push_back(Box(1599, 830, 1550, 796));
	walls.push_back(Box(1499, 530, 1300, 496));
	walls.push_back(Box(1501, 580, 1400, 531));
	walls.push_back(Box(1599, 579, 1502, 550));
	walls.push_back(Box(1599, 630, 1550, 581));
	//block 6
	walls.push_back(Box(299, 280, 250, 196));
	walls.push_back(Box(348, 330, 300, 249));
	//block 7
	walls.push_back(Box(549, 380, 500, 345));
	walls.push_back(Box(550, 430, 500, 381));
	walls.push_back(Box(598, 430, 551, 396));
	//block 8
	walls.push_back(Box(724, 230, 625, 196));
	walls.push_back(Box(774, 330, 725, 196));
	//blcok 9
	walls.push_back(Box(999, 330, 950, 201));
	walls.push_back(Box(1099, 230, 1001, 201));
	//block 10
	walls.push_back(Box(1448, 381, 1400, 297));
	walls.push_back(Box(1599, 381, 1449, 282));
	walls.push_back(Box(1548, 281, 1450, 247));
	walls.push_back(Box(1599, 281, 1549, 232));
	walls.push_back(Box(1599, 231, 1550, 196));
	//90 on the top, hundred on the sides.
	//left side boundary
	bounds.push_back(Box(100, 1080, 0, 0));
	//right side boundary
	bounds.push_back(Box(1920, 1080, 1820, 0));
	//top boundary
	bounds.push_back(Box(1920, 1080, 0, 990));
	//bottom boundary
	bounds.push_back(Box(1920, 90, 0, 0));

}

World::~World()
{
	std::cout << "bad stuff" << std::endl;
}




void World::getCollision()//normal
{
	Tank* player;
	switch (players)
	{
	case 4:
		player = p_4;
		collision(player);
	case 3:
		player = p_3;
		collision(player);
	case 2:
		player = p_2;
		collision(player);
	case 1:
		player = p_1;
		collision(player);
	}
}

void World::getCollision(int size)//aoe
{
	Tank* player;
	if (list->modifiers[modifierlist::aoe] == true)
	{
		switch (players)
		{
		case 4:
			player = p_4;
			collision(player, size);
		case 3:
			player = p_3;
			collision(player, size);
		case 2:
			player = p_2;
			collision(player, size);
		case 1:
			player = p_1;
			collision(player, size);
		}
	}
}

float Distance(Coords p1, Coords p2) // returns the distance between two points
{
	double x = pow((p1.x - p2.x), 2);
	double y = pow((p1.y - p2.y), 2);
	return sqrt(x + y);
}

void World::getBulletCollsion()//dont touch (normal shot)
{
	for (int count = 0; count < p_1->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_2->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_1, p_2, count, count2) == true)
				{
					count--;
					count2 = p_2->shot.size();

				}
			}
		}
	}
	for (int count = 0; count < p_1->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_3->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_1, p_3, count, count2) == true)
				{
					count--;
					count2 = p_3->shot.size();

				}
			}
		}
	}
	for (int count = 0; count < p_1->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_4->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_1, p_4, count, count2) == true)
				{
					count--;
					count2 = p_4->shot.size();

				}
			}
		}
	}
	for (int count = 0; count < p_2->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_3->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_2, p_3, count, count2) == true)
				{
					count--;
					count2 = p_3->shot.size();

				}
			}
		}
	}
	for (int count = 0; count < p_2->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_4->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_2, p_4, count, count2) == true)
				{
					count--;
					count2 = p_4->shot.size();

				}
			}
		}
	}
	for (int count = 0; count < p_3->shot.size(); count++)
	{
		for (int count2 = 0; count2 < p_4->shot.size(); count2++)
		{

			if (count >= 0)
			{
				if (bulletCollision(p_3, p_4, count, count2) == true)
				{
					count--;
					count2 = p_4->shot.size();

				}
			}
		}
	}

}

bool World::bulletCollision(Tank* player, Tank* enemy, int bulletPlayer, int bulletEnemy)//math happens here. 
{
	Coords temp = { (enemy->shot[bulletEnemy].getPosX()), enemy->shot[bulletEnemy].getPosY() };
	Coords temp2 = { (player->shot[bulletPlayer].getPosX()), player->shot[bulletPlayer].getPosY() };
	if (Distance(temp, temp2) <= 30)
	{
		// b1 b2 b3 and b4
		Coords b1 = { player->shot[bulletPlayer].getbulletSize() * sqrt(2) *cos((player->shot[bulletPlayer].getA() + 45)* PI / 180.0), player->shot[bulletPlayer].getbulletSize() * sqrt(2) *sin((player->shot[bulletPlayer].getA() + 45)* PI / 180.0) };
		Coords b2 = { player->shot[bulletPlayer].getbulletSize() * sqrt(2) *cos((player->shot[bulletPlayer].getA() + 135)* PI / 180.0), player->shot[bulletPlayer].getbulletSize() * sqrt(2) *sin((player->shot[bulletPlayer].getA() + 135)* PI / 180.0) };
		Coords b3 = { player->shot[bulletPlayer].getbulletSize() * sqrt(2) *cos((player->shot[bulletPlayer].getA() + 225)* PI / 180.0), player->shot[bulletPlayer].getbulletSize() * sqrt(2) *sin((player->shot[bulletPlayer].getA() + 225)* PI / 180.0) };
		Coords b4 = { player->shot[bulletPlayer].getbulletSize() * sqrt(2) *cos((player->shot[bulletPlayer].getA() + 315)* PI / 180.0), player->shot[bulletPlayer].getbulletSize() * sqrt(2) *sin((player->shot[bulletPlayer].getA() + 315)* PI / 180.0) };

		b1.x += player->shot[bulletPlayer].getPosX();
		b2.x += player->shot[bulletPlayer].getPosX();
		b3.x += player->shot[bulletPlayer].getPosX();
		b4.x += player->shot[bulletPlayer].getPosX();
		b1.y += player->shot[bulletPlayer].getPosY();
		b2.y += player->shot[bulletPlayer].getPosY();
		b3.y += player->shot[bulletPlayer].getPosY();
		b4.y += player->shot[bulletPlayer].getPosY();

		Coords e1 = { enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *cos((enemy->shot[bulletEnemy].getA() + 45)* PI / 180.0), enemy->shot[bulletEnemy].getbulletSize()  * sqrt(2) *sin((enemy->shot[bulletEnemy].getA() + 45)* PI / 180.0) };
		Coords e2 = { enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *cos((enemy->shot[bulletEnemy].getA() + 135)* PI / 180.0), enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *sin((enemy->shot[bulletEnemy].getA() + 135)* PI / 180.0) };
		Coords e3 = { enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *cos((enemy->shot[bulletEnemy].getA() + 225)* PI / 180.0), enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *sin((enemy->shot[bulletEnemy].getA() + 225)* PI / 180.0) };
		Coords e4 = { enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *cos((enemy->shot[bulletEnemy].getA() + 315)* PI / 180.0), enemy->shot[bulletEnemy].getbulletSize() * sqrt(2) *sin((enemy->shot[bulletEnemy].getA() + 315)* PI / 180.0) };

		e1.x += enemy->shot[bulletEnemy].getPosX();
		e2.x += enemy->shot[bulletEnemy].getPosX();
		e3.x += enemy->shot[bulletEnemy].getPosX();
		e4.x += enemy->shot[bulletEnemy].getPosX();
		e1.y += enemy->shot[bulletEnemy].getPosY();
		e2.y += enemy->shot[bulletEnemy].getPosY();
		e3.y += enemy->shot[bulletEnemy].getPosY();
		e4.y += enemy->shot[bulletEnemy].getPosY();

		Coords* c;

		for (int count = 0; count < 4; count++)
		{
			switch (count)
			{
			case 3:
				c = &e1;
				break;
			case 2:
				c = &e2;
				break;
			case 1:
				c = &e3;
				break;
			case 0:
				c = &e4;
				break;
			}
			double area = 0;

			Coords* a = &b1;
			Coords* b = &b2;
			Coords* c = &b2;
			area += abs((a->x*(b->y - c->y) + b->x*(c->y - a->y) + c->x*(a->y - b->y)) / 2);
			a = &b2;
			b = &b3;
			area += abs((a->x*(b->y - c->y) + b->x*(c->y - a->y) + c->x*(a->y - b->y)) / 2);
			a = &b3;
			b = &b4;
			area += abs((a->x*(b->y - c->y) + b->x*(c->y - a->y) + c->x*(a->y - b->y)) / 2);
			a = &b4;
			b = &b1;
			area += abs((a->x*(b->y - c->y) + b->x*(c->y - a->y) + c->x*(a->y - b->y)) / 2);

			double bulletArea = Distance(b1, b2) * Distance(b3, b4);

			if (area <= bulletArea + error)
			{
				player->shot.erase(player->shot.begin() + bulletPlayer);
				player->shot.shrink_to_fit();

				enemy->shot.erase(enemy->shot.begin() + bulletEnemy);
				enemy->shot.shrink_to_fit();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

void World::collision(Tank* player)//detects whether a bullet has collided with the tank parameter. For Normal
{
	for (int count = 0; count < player->shot.size(); count++)
	{
		Coords temp;
		temp.x = player->shot[count].getPosX();
		temp.y = player->shot[count].getPosY();
		int size = tankSize / 2;
		if (p_1 != player && death[0] == false)//controls hitbox
		{
			if (p_1->getX() - size < temp.x && temp.x < p_1->getX() + size)
			{
				if (p_1->getY() - size < temp.y && temp.y < p_1->getY() + size)
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_1->stunStart == 0)
						splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}

					if (p_1->shieldOn == true)
					{

						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_1->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_1->getH() == 3)
							{
								splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								////FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_1->getH() == 2)
							{
								splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[heartloss], 0, 1), 25, 9);
								////FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_1->getH() == 1)
							{
								////FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
						//	player->m(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_1->giveBomb();
							splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[bombfeedback], 0, p_1->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_1->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[0] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_1->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_1->getH() << std::endl;
						player->startvibrate = true;
						if (p_1->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{

							death[0] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_1->stunStart == 0)
							{
								player->points++;
								p_1->stun = true;
								p_1->stunStart = clock();
							}
						}
					}
					if (list->modifiers[modifierlist::aoe] == true)
						getCollision(65);

					//pointerSprite(double &_x, double &_y, float _a, FzlSpriteHandle _ID)

				}
			}

		}
		if (p_2 != player && death[1] == false)//controls hitbox
		{
			if (p_2->getX() - size < temp.x && temp.x < p_2->getX() + size)
			{
				if (p_2->getY() - size < temp.y && temp.y < p_2->getY() + size)
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_2->stunStart == 0)
						splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}

					if (p_2->shieldOn == true)
					{

						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_2->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_2->getH() == 3)
							{
								splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_2->getH() == 2)
							{
								splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 1, holder->tank[heartloss], 0, 1), 25, 9);
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_2->getH() == 1)
							{
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_2->giveBomb();
							splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 0, holder->tank[bombfeedback], 0, p_2->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_2->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[1] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_2->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_2->getH() << std::endl;
						p_2->startvibrate = true;
						if (p_2->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{
							death[1] = true;

							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_2->stunStart == 0)
							{
								player->points++;
								p_2->stun = true;
								p_2->stunStart = clock();
							}
						}
					}
					if (list->modifiers[modifierlist::aoe] == true)
						getCollision(65);

				}
			}
		}

		if (p_3 != player && death[2] == false)//controls hitbox
		{
			if (p_3->getX() - size < temp.x && temp.x < p_3->getX() + size)
			{
				if (p_3->getY() - size < temp.y && temp.y < p_3->getY() + size)
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_3->stunStart == 0)
						splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (p_3->shieldOn == true)
					{

						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
					}
					else
					{

						if (list->modifiers[modifierlist::standard] == true && p_3->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_3->getH() == 3)
							{
								splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_3->getH() == 2)
							{
								splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 1, holder->tank[heartloss], 0, 1), 25, 9);
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_3->getH() == 1)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_3->giveBomb();
							splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 0, holder->tank[bombfeedback], 0, p_3->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_3->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[2] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_3->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_3->getH() << std::endl;
						p_3->startvibrate = true;
						if (p_3->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{
							death[2] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_3->stunStart == 0)
							{
								player->points++;
								p_3->stun = true;
								p_3->stunStart = clock();
							}
						}
					}
					if (list->modifiers[modifierlist::aoe] == true)
						getCollision(65);

				}
			}
		}
		if (p_4 != player && death[3] == false)//controls hitbox
		{
			if (p_4->getX() - size < temp.x && temp.x < p_4->getX() + size)
			{
				if (p_4->getY() - size < temp.y && temp.y < p_4->getY() + size)
				{

					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_4->stunStart == 0)
						splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);

					if (p_4->shieldOn == true)
					{

						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_4->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_4->getH() == 3)
							{
								splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_4->getH() == 2)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
								splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 1, holder->tank[heartloss], 0, 1), 25, 9);
							}
							else if (p_4->getH() == 1)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						player->shot.erase(player->shot.begin() + count);
						player->shot.shrink_to_fit();
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_4->giveBomb();
							splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 0, holder->tank[bombfeedback], 0, p_4->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_4->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[3] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_4->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_4->getH() << std::endl;
						p_4->startvibrate = true;
						if (p_4->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{
							death[3] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_4->stunStart == 0)
							{
								player->points++;
								p_4->stun = true;
								p_4->stunStart = clock();
							}
						}
						if (list->modifiers[modifierlist::aoe] == true)
							getCollision(65);
					}
				}
			}
		}
	}
}

void World::collision(Tank* player, int radi)//detects whether a bullet has collided with the tank parameter. for AOE
{

	bool shoulddelete = false;
	for (int count = 0; count < player->shot.size(); count++)
	{
		Coords temp;
		temp.x = player->shot[count].getPosX();
		temp.y = player->shot[count].getPosY();
		int size = tankSize / 2;
		int bulletsize = player->shot.size();
		if (p_1 != player && death[0] == false)//controls hitbox
		{
			if ((p_1->getX() - size < temp.x + radi && temp.x - radi < p_1->getX() + size) || (p_1->getX() - size < temp.x + radi && temp.x - radi < p_1->getX() + size))
			{
				if ((p_1->getY() - size < temp.y + radi && temp.y - radi < p_1->getY() + size) || (p_1->getY() - size < temp.y + radi && temp.y - radi < p_1->getY() + size))
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_1->stunStart == 0)
						splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}

					if (p_1->shieldOn == true)
					{

						shoulddelete = true;
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_1->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_1->getH() == 3)
							{
								splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_1->getH() == 2)
							{
								splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[heartloss], 0, 1), 25, 9);
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_1->getH() == 1)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						shoulddelete = true;
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_1->giveBomb();
							splat.push_back(pointerSprite(p_1->getXP(), p_1->getYP(), 0, holder->tank[bombfeedback], 0, p_1->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_1->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[0] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_1->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);

						}
						std::cout << p_1->getH() << std::endl;
						player->startvibrate = true;
						if (p_1->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{

							death[0] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_1->stunStart == 0)
							{
								player->points++;
								p_1->stun = true;
								p_1->stunStart = clock();
							}
						}
					}
					//pointerSprite(double &_x, double &_y, float _a, FzlSpriteHandle _ID)
				}
			}

		}
		if (p_2 != player && death[1] == false)//controls hitbox
		{
			if ((p_2->getX() - size < temp.x + radi && temp.x - radi < p_2->getX() + size) || (p_2->getX() - size < temp.x + radi && temp.x - radi < p_2->getX() + size))
			{
				if ((p_2->getY() - size < temp.y + radi && temp.y - radi < p_2->getY() + size) || (p_2->getY() - size < temp.y + radi && temp.y - radi < p_2->getY() + size))
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_2->stunStart == 0)
						splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}

					if (p_2->shieldOn == true)
					{

						shoulddelete = true;
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_2->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_2->getH() == 3)
							{
								splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_2->getH() == 2)
							{
								splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 0, holder->tank[heartloss], 0, 1), 25, 9);
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_2->getH() == 1)
							{
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						shoulddelete = true;
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_2->giveBomb();
							splat.push_back(pointerSprite(p_2->getXP(), p_2->getYP(), 0, holder->tank[bombfeedback], 0, p_2->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_2->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								death[1] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_2->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_2->getH() << std::endl;
						player->startvibrate = true;
						if (p_2->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{

							death[1] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_2->stunStart == 0)
							{
								player->points++;
								p_2->stun = true;
								p_2->stunStart = clock();
							}
						}
					}

					//pointerSprite(double &_x, double &_y, float _a, FzlSpriteHandle _ID)
				}
			}
		}
		if (p_3 != player && death[2] == false)//controls hitbox
		{
			if ((p_3->getX() - size < temp.x + radi && temp.x - radi < p_3->getX() + size) || (p_3->getX() - size < temp.x + radi && temp.x - radi < p_3->getX() + size))
			{
				if ((p_3->getY() - size < temp.y + radi && temp.y - radi < p_3->getY() + size) || (p_3->getY() - size < temp.y + radi && temp.y - radi < p_3->getY() + size))
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_1->stunStart == 0)
						splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}


					if (p_3->shieldOn == true)
					{

						shoulddelete = true;
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_3->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_3->getH() == 3)
							{
								splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_3->getH() == 2)
							{
								splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 0, holder->tank[heartloss], 0, 1), 25, 9);
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_3->getH() == 1)
							{
								//	//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						shoulddelete = true;
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_3->giveBomb();
							splat.push_back(pointerSprite(p_3->getXP(), p_3->getYP(), 0, holder->tank[bombfeedback], 0, p_3->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_3->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								death[2] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_3->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_3->getH() << std::endl;
						player->startvibrate = true;
						if (p_3->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{

							death[2] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_3->stunStart == 0)
							{
								player->points++;
								p_3->stun = true;
								p_3->stunStart = clock();
							}
						}
					}

					//pointerSprite(double &_x, double &_y, float _a, FzlSpriteHandle _ID)
				}
			}
		}
		if (p_4 != player && death[3] == false)//controls hitbox
		{
			if ((p_4->getX() - size < temp.x + radi && temp.x - radi < p_4->getX() + size) || (p_4->getX() - size < temp.x + radi && temp.x - radi < p_4->getX() + size))
			{
				if ((p_4->getY() - size < temp.y + radi && temp.y - radi < p_4->getY() + size) || (p_4->getY() - size < temp.y + radi && temp.y - radi < p_4->getY() + size))
				{
					if (list->modifiers[modifierlist::standard] == false)
						splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);
					else if (p_4->stunStart == 0)
						splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), player->getA(), *player->splat, player->shot[count].getAngle2()), 250, true);


					if (list->modifiers[modifierlist::aoe] == true)
					{
						splat.push_back(pointerSprite(player->shot[count].getPosX(), player->shot[count].getPosY(), 0, *player->aoe, player->playerID), 10, 8);
						FzlPlaySound(p_1->sounds->stank[aoeShot]);
					}

					if (p_4->shieldOn == true)
					{

						shoulddelete = true;
					}
					else
					{
						if (list->modifiers[modifierlist::standard] == true && p_4->stunStart == 0)
							splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[points], 0, player->playerID), 100, 9);
						if (list->modifiers[modifierlist::hearts] == true)
						{
							if (p_4->getH() == 3)
							{
								splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 0, holder->tank[heartloss], 0), 25, 9);
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_4->getH() == 2)
							{
								splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 0, holder->tank[heartloss], 0, 1), 25, 9);
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
							else if (p_4->getH() == 1)
							{
								//		//FzlPlaySound(pmenu->sounds->sworld[soundWorld::lifeLost]);
							}
						}
						shoulddelete = true;
						//	player->changeHealth(-1);
						if (list->modifiers[modifierlist::bomb] == true && player->hasbomb)
						{
							resetlastbomber();
							player->lastbomber = true;
							player->hasbomb = false;
							p_4->giveBomb();
							splat.push_back(pointerSprite(p_4->getXP(), p_4->getYP(), 0, holder->tank[bombfeedback], 0, p_4->playerID), 50, 9);
						}
						else if (list->modifiers[modifierlist::bomb] == true && p_4->hasbomb)
						{
							pmenu->changetime(-5);
							if (pmenu->gettime() <= 0)
							{
								//			//FzlPlaySound(pmenu->sounds->sworld[soundWorld::bombExplode]);
								death[3] = true;
							}
						}
						else if (list->modifiers[modifierlist::bomb] == false)
						{
							p_4->changeHealth(-1);
							FzlPlaySound(player->sounds->sworld[lifeLost]);
						}
						std::cout << p_4->getH() << std::endl;
						player->startvibrate = true;
						if (p_4->getH() <= 0 && list->modifiers[modifierlist::standard] == false)
						{

							death[3] = true;
							if (list->modifiers[modifierlist::oneshot])
							{
								player->hasbullet = true;
								splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[bulletgain], player->playerID), 50, 9);
							}
						}
						if (list->modifiers[modifierlist::standard] == true)
						{
							if (p_4->stunStart == 0)
							{
								player->points++;
								p_4->stun = true;
								p_4->stunStart = clock();
							}
						}
					}

					//pointerSprite(double &_x, double &_y, float _a, FzlSpriteHandle _ID)
				}
			}
		}
		if (shoulddelete)
		{
			player->shot.erase(player->shot.begin() + count);
			player->shot.shrink_to_fit();
		}
	}
}

bool World::shoot(Tank* player, Tank* enemy)//checks whether a bullet has been fired.
{
	if (player->playerNumber->conRightTrigger() > 0.1)
	{
		player->rtheld = true;
		if (!player->rtheldlast)
		{
			player->rttime = clock();
		}
		if (((clock() - player->rttime) / CLOCKS_PER_SEC) < 0.5)
		{
		//	splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[tank::charge], 0), 3);
		}
		else
		{
			splat.push_back(pointerSprite(player->getXP(), player->getYP(), 0, holder->tank[tank::charge], 0), 3);
		//	std::cout << player->playerID << std::endl;
		}
	}
	else
	{
		player->rtheld = false;
		if (list->modifiers[modifierlist::charge] && player->rtheldlast)
		{
			if ((((clock() - player->rttime) / CLOCKS_PER_SEC) > 0.5) && player->shot.size() < bulletLimit && (!list->modifiers[modifierlist::oneshot] || player->hasbullet == true))
			{
				double tempy = bulletSpeed * sin(PI * (player->getA() + player->getAT()) / 180);
				double tempx = bulletSpeed * cos(PI * (player->getA() + player->getAT()) / 180);
				//Could be optimized, dividing is a costly calculation!
				if (player->rttime > 0)
				{
					player->shot.push_back(Bullet(player->getX() + (tempx / bulletSpeed) * player->getOffset(), player->getY() + (tempy / bulletSpeed) * player->getOffset(), player->getA() + player->getAT(), list->modifiers[modifierlist::index::bulletacceleration] ? getaccelbulletSpeed() : getbulletSpeed(), list->modifiers[modifierlist::index::bulletacceleration] ? 0 : player->getvelocityX(), list->modifiers[modifierlist::index::bulletacceleration] ? 0 : player->getvelocityY(), list->modifiers[modifierlist::index::bulletacceleration])); //geta might be a bad thing?!?
					player->rttime = 0;
					player->rtheldlast = false;
				}
				player->hasbullet = false;
				if (player->soundFire == true)
				{
					FzlPlaySound(player->sounds->stank[fire]);
					player->soundFire = false;
				}
				else
				{
					FzlPlaySound(player->sounds->stank[fire2]);
					player->soundFire = true;
				}
				num++;
				return true;
				player->rttime = 0;
			}

		}

	}
	if (player->rtheld && !player->rtheldlast)
	{
		player->rtheldlast = true;
	}
	else if (!player->rtheld && player->rtheldlast)
	{
		player->rtheldlast = false;
		player->rttime = 0;
	}
	if (player->rtheld && player->shot.size() < bulletLimit && (!list->modifiers[modifierlist::oneshot] || player->hasbullet == true) && !list->modifiers[modifierlist::charge])
	{
		double tempy = bulletSpeed * sin(PI * (player->getA() + player->getAT()) / 180);
		double tempx = bulletSpeed * cos(PI * (player->getA() + player->getAT()) / 180);
		//Could be optimized, dividing is a costly calculation!

		player->shot.push_back(Bullet(player->getX() + (tempx / bulletSpeed) * player->getOffset(), player->getY() + (tempy / bulletSpeed) * player->getOffset(), player->getA() + player->getAT(), list->modifiers[modifierlist::index::bulletacceleration] ? getaccelbulletSpeed() : getbulletSpeed(), list->modifiers[modifierlist::index::bulletacceleration] ? 0 : player->getvelocityX(), list->modifiers[modifierlist::index::bulletacceleration] ? 0 : player->getvelocityY(), list->modifiers[modifierlist::index::bulletacceleration])); //geta might be a bad thing?!?	

		player->hasbullet = false;
		if (player->soundFire == true)
		{
			FzlPlaySound(player->sounds->stank[fire]);

			player->soundFire = false;
		}
		else
		{
			////FzlPlaySound(player->fire2);
			FzlPlaySound(player->sounds->stank[fire2]);
			player->soundFire = true;
		}
		num++;
		return true;
	}
	return false;
}


void World::playersShoot(bool inversion)//controls the player shooting
{
	Tank* player;
	Tank* enemy;
	switch (players)
	{
	case 4:
		player = p_4;
		enemy = p_4;
		if (playerTurn[3] == false && death[3] == false)
		{
			if (list->modifiers[modifierlist::standard] == false)
				playerTurn[3] = shoot(player, enemy);//detects whether the second player has fired a bullet
			else
			{
				if (player->stunStart == 0)
					playerTurn[3] = shoot(player, enemy);//detects whether the second player has fired a bullet
			}
		}
		else if (playerWait[3] <= bulletDelay)
		{
			playerWait[3]++;
		}
		else if (playerWait[3] > bulletDelay)
		{
			playerTurn[3] = false;
			playerWait[3] = 0;
		}
	case 3:
		player = p_3;
		enemy = p_3;
		if (playerTurn[2] == false && death[2] == false)
		{
			if (list->modifiers[modifierlist::standard] == false)
				playerTurn[2] = shoot(player, enemy);//detects whether the second player has fired a bullet
			else
			{
				if (player->stunStart == 0)
					playerTurn[2] = shoot(player, enemy);//detects whether the second player has fired a bullet
			}
		}
		else if (playerWait[2] <= bulletDelay)
		{
			playerWait[2]++;
		}
		else if (playerWait[2] > bulletDelay)
		{
			playerTurn[2] = false;
			playerWait[2] = 0;
		}
	case 2:
		player = p_2;
		enemy = p_2;

		if (playerTurn[1] == false && death[1] == false)
		{
			if (list->modifiers[modifierlist::standard] == false)
				playerTurn[1] = shoot(player, enemy);//detects whether the second player has fired a bullet
			else
			{
				if (player->stunStart == 0)
					playerTurn[1] = shoot(player, enemy);//detects whether the second player has fired a bullet
			}
		}
		else if (playerWait[1] <= bulletDelay)
		{
			playerWait[1]++;
		}
		else if (playerWait[1] > bulletDelay)
		{
			playerTurn[1] = false;
			playerWait[1] = 0;
		}

	case 1:
		player = p_1;
		enemy = p_1;

		if (playerTurn[0] == false && death[0] == false)
		{
			if (list->modifiers[modifierlist::standard] == false)
				playerTurn[0] = shoot(player, enemy);//detects whether the second player has fired a bullet
			else
			{
				if (player->stunStart == 0)
					playerTurn[0] = shoot(player, enemy);//detects whether the second player has fired a bullet
			}
		}
		else if (playerWait[0] <= bulletDelay)
		{
			playerWait[0]++;
		}
		else if (playerWait[0] > bulletDelay)
		{
			playerTurn[0] = false;
			playerWait[0] = 0;
		}
		break;
	}
}

void World::flipbounceToggle()
{
	//flips bounceToggle
	bounceToggle = (bounceToggle == false) ? true : false;
}

void World::flipasteroidsToggle()
{
	asteroidsToggle = (asteroidsToggle == false) ? true : false;
}

int World::getDetection()
{
	return detection;
}

void World::setDetection(int _detection)
{
	detection = _detection;
}

void World::setBulletDelay(int x)
{
	bulletDelay = x;
}

int World::getBulletDelay()
{
	return bulletDelay;
}

Collision World::collide(Tank * _t1, Box _b2)
{
	Collision result;
	double r = _t1->getRadius();
	double r2 = r;
	double _tx = _t1->getX();
	double _ty = _t1->getY();

	double px = clip(_tx, _b2.lX, _b2.rX);
	double py = clip(_ty, _b2.bY, _b2.tY);


	double distance = sqrt(pow((px - _tx), 2) + pow((py - _ty), 2));



	if (distance < r)
	{
		result.status = true;
		if (px != _tx)
		if (_t1->getvelocityX() < 0)
			// original	result.penetration.setx((_tx + r) - px);
			result.penetration.setx(px - _tx + r);
		else
			//				original result.penetration.setx((_tx - r) + px);
			result.penetration.setx(_tx - px + r);
		if (py != _ty)
		if (_t1->getvelocityY() < 0)
			//				result.penetration.sety((_ty + r) - py);
			result.penetration.sety(py - _ty + r2);
		else
			result.penetration.sety(_ty - py + r2);
		//				result.penetration.sety((_ty - r) + py);
	}

	result.collidedWith = _b2;
	return  result;
}
//http://stackoverflow.com/questions/9323903/most-efficient-elegant-way-to-clip-a-number
//"clips"(restricts) a number between a lower and an upper bound.
double World::clip(double _n, double _lower, double _upper)
{
	return std::fmax(_lower, std::fmin(_n, _upper));
}
Collision  World::collide(Tank * _t1, Tank * _t2)
{
	Collision result;
	double r1 = _t1->getRadius();
	double r2 = _t2->getRadius();
	double _t1x = _t1->getX();
	double _t1y = _t1->getY();
	double _t2x = _t2->getX();
	double _t2y = _t2->getY();
	double distance = sqrt(pow((_t2x - _t1x), 2) + pow((_t2y - _t1y), 2));
	if (distance < (r1 + r2))
	{
		result.status = true;
		result.penetration.setx(_t2x - _t1x);
		result.penetration.sety(_t2y - _t1y);
	}
	return result;
}

Collision World::collide(Box  _b1, Box  _b2)
{
	double _b1centerx, _b1centery, _b2centerx, _b2centery;
	_b1centerx = (_b1.rX - _b1.lX) / 2;
	_b1centery = (_b1.tY - _b1.bY) / 2;
	_b2centerx = (_b2.rX - _b2.lX) / 2;
	_b2centery = (_b2.tY - _b2.bY) / 2;
	double penetrationX, penetrationY;
	Collision result;
	if (_b1.rX - _b2.lX >= 0)
	if (_b2.rX - _b1.lX >= 0)
	if (_b1.tY - _b2.bY >= 0)
	if (_b2.tY - _b1.bY >= 0)
		result.status = true;
	if (_b2centerx > _b1centerx)
		result.penetration.setx(_b1.rX - _b2.lX);
	else
		result.penetration.setx(_b2.rX - _b1.lX);
	if (_b2centery > _b1centery)
		result.penetration.sety(_b1.tY - _b2.bY);
	else
		result.penetration.sety(_b2.tY - _b1.bY);
	return result;
}
bool Tank::cornerintersect(double px, double py)
{
	double radiussquared = pow(this->getRadius(), 2);
	if (pow(px - this->tankPos.getx(), 2) + pow(py - this->tankPos.gety(), 2) < radiussquared)
		return true;
}
//mostly from http://www.david-amador.com/2012/04/xbox-360-controller-input-in-c-via-xinput/
//takes numbers between 0 and 1 for the left and right motor. 
void Tank::vibrate(double left, double right)
{
	XINPUT_VIBRATION vibration;

	int leftvib = (int)(left * 65535);
	int rightvib = (int)(right * 65535);
	vibration.wLeftMotorSpeed = leftvib;
	vibration.wRightMotorSpeed = rightvib;

	//XInputSetState((int)this->controllernumber, &vibration);
	if (left > 0)
	{
	}
}
void World::vibratehandler()
{
	if (p_1->startvibrate == true)
	{

		p_1->vibrate(0.5, 0.5);
		p_1->startvibrate = false;
		p_1->vibrateend = clock() + (clock_t)this->vibrateduration;

	}
	if (p_2->startvibrate == true)
	{
		p_2->vibrate(0.5, 0.5);
		p_2->startvibrate = false;
		p_2->vibrateend = clock() + (clock_t)this->vibrateduration;
	}
	if (p_3->startvibrate == true)
	{
		p_3->vibrate(0.5, 0.5);
		p_3->startvibrate = false;
		p_3->vibrateend = clock() + (clock_t)this->vibrateduration;
	}
	if (p_4->startvibrate == true)
	{
		p_4->vibrate(0.5, 0.5);
		p_4->startvibrate = false;
		p_4->vibrateend = clock() + (clock_t)this->vibrateduration;
	}
	clock_t time = clock();
	if (time > p_1->vibrateend)
		p_1->vibrate(0, 0);
	if (time > p_2->vibrateend)
		p_2->vibrate(0, 0);
	if (time > p_3->vibrateend)
		p_3->vibrate(0, 0);
	if (time > p_4->vibrateend)
		p_4->vibrate(0, 0);
}
void World::hudhandler()
{

}

void World::dotphandler()
{

	if (death[0] && p_1->bodies[0].rX == 0)
	{
		int radius = p_1->getRadius();
		p_1->bodies[0].bY = p_1->tankPos.gety() - radius;
		p_1->bodies[0].tY = p_1->tankPos.gety() + radius;
		p_1->bodies[0].lX = p_1->tankPos.getx() - radius;
		p_1->bodies[0].rX = p_1->tankPos.getx() + radius;
		p_2->bodies[0].bY = p_1->tankPos.gety() - radius;
		p_2->bodies[0].tY = p_1->tankPos.gety() + radius;
		p_2->bodies[0].lX = p_1->tankPos.getx() - radius;
		p_2->bodies[0].rX = p_1->tankPos.getx() + radius;
		p_3->bodies[0].bY = p_1->tankPos.gety() - radius;
		p_3->bodies[0].tY = p_1->tankPos.gety() + radius;
		p_3->bodies[0].lX = p_1->tankPos.getx() - radius;
		p_3->bodies[0].rX = p_1->tankPos.getx() + radius;
		p_4->bodies[0].bY = p_1->tankPos.gety() - radius;
		p_4->bodies[0].tY = p_1->tankPos.gety() + radius;
		p_4->bodies[0].lX = p_1->tankPos.getx() - radius;
		p_4->bodies[0].rX = p_1->tankPos.getx() + radius;
		bodies[0].bY = p_1->tankPos.gety() - radius;
		bodies[0].tY = p_1->tankPos.gety() + radius;
		bodies[0].lX = p_1->tankPos.getx() - radius;
		bodies[0].rX = p_1->tankPos.getx() + radius;
	}
	if (death[1] && p_1->bodies[0].rX == 0)
	{
		int radius = p_1->getRadius();
		p_1->bodies[1].bY = p_2->tankPos.gety() - radius;
		p_1->bodies[1].tY = p_2->tankPos.gety() + radius;
		p_1->bodies[1].lX = p_2->tankPos.getx() - radius;
		p_1->bodies[1].rX = p_2->tankPos.getx() + radius;
		p_2->bodies[1].bY = p_2->tankPos.gety() - radius;
		p_2->bodies[1].tY = p_2->tankPos.gety() + radius;
		p_2->bodies[1].lX = p_2->tankPos.getx() - radius;
		p_2->bodies[1].rX = p_2->tankPos.getx() + radius;
		p_3->bodies[1].bY = p_2->tankPos.gety() - radius;
		p_3->bodies[1].tY = p_2->tankPos.gety() + radius;
		p_3->bodies[1].lX = p_2->tankPos.getx() - radius;
		p_3->bodies[1].rX = p_2->tankPos.getx() + radius;
		p_4->bodies[1].bY = p_2->tankPos.gety() - radius;
		p_4->bodies[1].tY = p_2->tankPos.gety() + radius;
		p_4->bodies[1].lX = p_2->tankPos.getx() - radius;
		p_4->bodies[1].rX = p_2->tankPos.getx() + radius;
		bodies[1].bY = p_2->tankPos.gety() - radius;
		bodies[1].tY = p_2->tankPos.gety() + radius;
		bodies[1].lX = p_2->tankPos.getx() - radius;
		bodies[1].rX = p_2->tankPos.getx() + radius;
	}
	if (death[2] && p_1->bodies[0].rX == 0)
	{
		int radius = p_1->getRadius();
		p_1->bodies[2].bY = p_3->tankPos.gety() - radius;
		p_1->bodies[2].tY = p_3->tankPos.gety() + radius;
		p_1->bodies[2].lX = p_3->tankPos.getx() - radius;
		p_1->bodies[2].rX = p_3->tankPos.getx() + radius;
		p_2->bodies[2].bY = p_3->tankPos.gety() - radius;
		p_2->bodies[2].tY = p_3->tankPos.gety() + radius;
		p_2->bodies[2].lX = p_3->tankPos.getx() - radius;
		p_2->bodies[2].rX = p_3->tankPos.getx() + radius;
		p_3->bodies[2].bY = p_3->tankPos.gety() - radius;
		p_3->bodies[2].tY = p_3->tankPos.gety() + radius;
		p_3->bodies[2].lX = p_3->tankPos.getx() - radius;
		p_3->bodies[2].rX = p_3->tankPos.getx() + radius;
		p_4->bodies[2].bY = p_3->tankPos.gety() - radius;
		p_4->bodies[2].tY = p_3->tankPos.gety() + radius;
		p_4->bodies[2].lX = p_3->tankPos.getx() - radius;
		p_4->bodies[2].rX = p_3->tankPos.getx() + radius;
		bodies[2].bY = p_3->tankPos.gety() - radius;
		bodies[2].tY = p_3->tankPos.gety() + radius;
		bodies[2].lX = p_3->tankPos.getx() - radius;
		bodies[2].rX = p_3->tankPos.getx() + radius;
	}
	if (death[3] && p_1->bodies[0].rX == 0)
	{
		int radius = p_1->getRadius();
		p_1->bodies[3].bY = p_4->tankPos.gety() - radius;
		p_1->bodies[3].tY = p_4->tankPos.gety() + radius;
		p_1->bodies[3].lX = p_4->tankPos.getx() - radius;
		p_1->bodies[3].rX = p_4->tankPos.getx() + radius;
		p_2->bodies[3].bY = p_4->tankPos.gety() - radius;
		p_2->bodies[3].tY = p_4->tankPos.gety() + radius;
		p_2->bodies[3].lX = p_4->tankPos.getx() - radius;
		p_2->bodies[3].rX = p_4->tankPos.getx() + radius;
		p_3->bodies[3].bY = p_4->tankPos.gety() - radius;
		p_3->bodies[3].tY = p_4->tankPos.gety() + radius;
		p_3->bodies[3].lX = p_4->tankPos.getx() - radius;
		p_3->bodies[3].rX = p_4->tankPos.getx() + radius;
		p_4->bodies[3].bY = p_4->tankPos.gety() - radius;
		p_4->bodies[3].tY = p_4->tankPos.gety() + radius;
		p_4->bodies[3].lX = p_4->tankPos.getx() - radius;
		p_4->bodies[3].rX = p_4->tankPos.getx() + radius;
		bodies[3].bY = p_4->tankPos.gety() - radius;
		bodies[3].tY = p_4->tankPos.gety() + radius;
		bodies[3].lX = p_4->tankPos.getx() - radius;
		bodies[3].rX = p_4->tankPos.getx() + radius;
	}
}

void DashShieldStatus::operator=(bool status)
{
	this->greydash = status;
	this->greyshield = status;
	this->ungreyshield = status;
	this->ungreydash = status;
}
controller Tank::getcontrollerstatus(int selection)
{
	switch (selection)
	{
	case 1:
		return p1;
		break;
	case 2:
		return p2;
		break;
	case 3:
		return p3;
		break;
	case 4:
		return p4;
		break;
	}
}
Tank* World::getplayer(int _selection)
{
	switch (_selection)
	{
	case 0:
		return p_1;
		break;
	case 1:
		return p_2;
		break;
	case 2:
		return p_3;
		break;
	case 3:
		return p_4;
		break;
	}
}
void World::setPointer(Menu * _menu)
{
	World::pmenu = _menu;
}
void World::resetlastbomber()
{
	p_1->lastbomber = false;
	p_2->lastbomber = false;
	p_3->lastbomber = false;
	p_4->lastbomber = false;
}
Tank World::getrandomaliveplayer(int exception)
{
	std::vector<Tank> alive;
	if (death[0] == false || exception != 1)
	{
		alive.push_back(*p_1);
	}
	if (death[1] == false || exception != 2)
	{
		alive.push_back(*p_2);
	}
	if (death[2] == false || exception != 3)
	{
		alive.push_back(*p_3);
	}
	if (death[3] == false || exception != 4)
	{
		alive.push_back(*p_4);
	}
	return alive[rand() % pmenu->getliveplayers()];
}
Tank World::getrandomaliveplayer()
{
	std::vector<Tank> alive;
	if (death[0] == false)
	{
		alive.push_back(*p_1);
	}
	if (death[1] == false)
	{
		alive.push_back(*p_2);
	}
	if (death[2] == false)
	{
		alive.push_back(*p_3);
	}
	if (death[3] == false)
	{
		alive.push_back(*p_4);
	}
	return alive[rand() % pmenu->getliveplayers()];
}