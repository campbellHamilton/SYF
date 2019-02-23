#include "Fizzle/Fizzle.h"
#include "Menu.h"
#include <iostream>
#include <math.h>
#include <numeric>
#include <ctime>
#include "store.h"
#include "modifierlist.h"
#include <exception>

bool playAgain();
controller p(0);//the controller for player 1. its the first controller plugged in.
int Menu::game()
{
	if (frame > 60)
		frame = 0;
	frame++;
	int deathCount = 0;
	animation = 0;
	FzlSetFrameRate(59);
	int shouldClose = 0;//controls when the game is left.
	deathCount = playerAmnt - 1;
	//up

	//  << arena->p_1->playerNumber->getLeftStick().x << "               ";
	//  << arena->p_1->playerNumber->getLeftStick().y << std::endl;
	tankCollision(playerAmnt);


	//if (FzlGetKey(FzlKeyP) && movement < 4)//used to cycle the movement scheme
	//{
	//	movement++;
	//	wait(1);
	//}
	//if (FzlGetKey(FzlKeyO) && movement > 0)//used to cycle the movement scheme
	//{
	//	wait(1);
	//	movement--;
	//}
	if (FzlGetKey(FzlKeyI))
	{
		arena->flipbounceToggle();
	}
	if (FzlGetKey(FzlKeyO))
	{
		arena->flipasteroidsToggle();
	}



	int temp = 0;
	if (arena->death[0] == true)
		temp++;
	if (arena->death[1] == true)
		temp++;
	if (arena->death[2] == true)
		temp++;
	if (arena->death[3] == true)
		temp++;

	if (temp >= 3)
	{
		shouldClose = true;
	}

	if (getTime() == 0 && selection.modifiers[modifierlist::standard] == true)
	{
		roundover = clock();
		int clockTemp = clock();
		while (clockTemp - roundover < 3000)
		{
			clockTemp = clock();
			lazerShot();
			setLayers();
		}
		switch (playerAmnt)
		{
		case 4:
			if (arena->p_4->points >= arena->p_3->points)
			{
				if (arena->p_4->points >= arena->p_2->points)
				{
					if (arena->p_4->points >= arena->p_1->points)
						FzlDrawSprite(holder->menu[menu::Player44], 960, 540, 0);
					else
						FzlDrawSprite(holder->menu[menu::Player14], 960, 540, 0);
				}
				else if (arena->p_2->points >= arena->p_1->points)
					FzlDrawSprite(holder->menu[menu::Player24], 960, 540, 0);
				else
					FzlDrawSprite(holder->menu[menu::Player14], 960, 540, 0);
			}
			else if (arena->p_3->points >= arena->p_2->points)
			{
				if (arena->p_3->points >= arena->p_1->points)
					FzlDrawSprite(holder->menu[menu::Player34], 960, 540, 0);
				else
					FzlDrawSprite(holder->menu[menu::Player14], 960, 540, 0);
			}
			else if (arena->p_2->points >= arena->p_1->points)
			{
				FzlDrawSprite(holder->menu[menu::Player24], 960, 540, 0);
			}
			else
				FzlDrawSprite(holder->menu[menu::Player14], 960, 540, 0);
			FzlDrawSprite(holder->menu[menu::SkullsScore4], 960, 540, 0);

			if (arena->p_1->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points/10, 0, 280, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points%10, 0, 340, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_1->points, 280, 190, 0);
			if (arena->p_2->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points / 10, 760, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points % 10, 840, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points, 760, 190, 0);

			if (arena->p_3->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points / 10, 1240, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points % 10, 1320, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points, 1240, 190, 0);

			if (arena->p_4->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_4->points / 10, 1720, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_4->points % 10, 1800, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_4->points, 1720, 190, 0);
			break;
		case 3:

			if (arena->p_3->points >= arena->p_2->points)
			{
				if (arena->p_3->points >= arena->p_1->points)
					FzlDrawSprite(holder->menu[menu::Player33], 960, 540, 0);
				else
					FzlDrawSprite(holder->menu[menu::Player13], 960, 540, 0);
			}
			else if (arena->p_2->points >= arena->p_1->points)
			{
				FzlDrawSprite(holder->menu[menu::Player23], 960, 540, 0);
			}
			else
				FzlDrawSprite(holder->menu[menu::Player13], 960, 540, 0);
			FzlDrawSprite(holder->menu[menu::SkullsScore3], 960, 540, 0);
			if (arena->p_1->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points / 10, 0, 280 + 240, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points % 10, 0, 340 + 240, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_1->points, 280 + 240, 190, 0);
			if (arena->p_2->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points / 10, 760 + 240, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points % 10, 840 + 240, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points, 760 + 240, 190, 0);

			if (arena->p_3->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points / 10, 1240 + 240, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points % 10, 1320 + 240, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_3->points, 1240 + 240, 190, 0);
			break;
		case 2:
			if (arena->p_2->points >= arena->p_1->points)
			{
				FzlDrawSprite(holder->menu[menu::Player22], 960, 540, 0);
			}
			else
				FzlDrawSprite(holder->menu[menu::Player12], 960, 540, 0);
			FzlDrawSprite(holder->menu[menu::SkullsScore2], 960, 540, 0);
			if (arena->p_1->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points / 10, 0, 280 + 480, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], arena->p_1->points % 10, 0, 340 + 480, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_1->points, 280 + 480, 190, 0);
			if (arena->p_2->points >= 10)
			{
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points / 10, 760 + 480, 190, 0);
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points % 10, 840 + 480, 190, 0);
			}
			else
				FzlDrawAnimatedSprite(holder->menu[numbers], 0, arena->p_2->points, 760 + 480, 190, 0);

			break;
		}
		FzlSwapBuffers();
		int choice = 0;
		while (choice == 0)
		{
			if (p.conButton(XINPUT_GAMEPAD_A) == true)
			{
				choice = 5;
			}
			if (p.conButton(XINPUT_GAMEPAD_B) == true)
			{
				choice = 6;
			}
		}
		roundover = clock();
		return choice;
	}

	if (shouldClose > 0)//controls the game over screen
	{
		roundover = clock();
		int clockTemp = clock();
		while (clockTemp - roundover < 3000)
		{
			clockTemp = clock();
			lazerShot();
			setLayers();
		}
		switch (playerAmnt)
		{
		case 4:
			if (arena->death[0] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player14], 960, 540, 0);
			}
			else if (arena->death[1] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player24], 960, 540, 0);
			}
			else if (arena->death[2] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player34], 960, 540, 0);
			}
			else if (arena->death[3] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player44], 960, 540, 0);
			}
			break;
		case 3:
			if (arena->death[0] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player13], 960, 540, 0);
			}
			else if (arena->death[1] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player23], 960, 540, 0);
			}
			else if (arena->death[2] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player33], 960, 540, 0);
			}
			break;
		case 2:
			if (arena->death[0] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player12], 960, 540, 0);
			}
			else if (arena->death[1] == false)
			{
				FzlDrawSprite(holder->menu[menu::Player22], 960, 540, 0);
			}
			break;
		}
		FzlSwapBuffers();


		int choice = 0;
		while (choice == 0)
		{
			if (p.conButton(XINPUT_GAMEPAD_A) == true)
			{
				choice = 5;
			}
			if (p.conButton(XINPUT_GAMEPAD_B) == true)
			{
				choice = 6;
			}
		}
		shouldClose = 0;
		roundover = clock();
		return choice;
	}
	roundover = clock();
	return 0;


}

void Menu::normalShot()
{

	framestart = clock();


	arena->playersShoot(inversion);
	arena->getCollision(); // detects whether a player is hit by a bullet.


	switch (playerAmnt)
	{
	case 4:
		if (arena->death[3] == false)
		{
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_4->shielded();
			}
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_4->dashed();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_4->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_4, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_4->stunStart == 0)
					moveTank(arena->p_4, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_4->stunStart > 675)
					{
						moveTank(arena->p_4, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_4->stunStart > 1500)
					{
						arena->p_4->stunStart = 0;
					}
				}
			}
		}

	case 3:
		if (arena->death[2] == false)
		{
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_3->shielded();
			}
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_3->dashed();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_3->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_3, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_3->stunStart == 0)
					moveTank(arena->p_3, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_3->stunStart > 675)
					{
						moveTank(arena->p_3, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_3->stunStart > 1500)
					{
						arena->p_3->stunStart = 0;
					}
				}
			}
		}
	case 2:
		if (arena->death[1] == false)
		{
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_2->dashed();
			}
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_2->shielded();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_2->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_2, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_2->stunStart == 0)
					moveTank(arena->p_2, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_2->stunStart > 675)
					{
						moveTank(arena->p_2, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_2->stunStart > 1500)
					{
						arena->p_2->stunStart = 0;
					}
				}
			}

		}
		if (arena->death[0] == false)
		{
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_1->dashed();
			}
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_1->shielded();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_1->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_1, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_1->stunStart == 0)
					moveTank(arena->p_1, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_1->stunStart > 675)
					{
						moveTank(arena->p_1, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_1->stunStart > 1500)
					{
						arena->p_1->stunStart = 0;
					}
				}
			}

		}
		else
		{

		}
		break;

	}

	arena->getBulletCollsion();
}

void Menu::lazerShot()//repurposed for end of round shooting.
{

	framestart = clock();


	//arena->playersShoot(inversion);


	arena->getCollision(); // detects whether a player is hit by a bullet.
	switch (playerAmnt)
	{
	case 4:
		if (arena->death[3] == false)
		{
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_4->shielded();
			}
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_4->dashed();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_4->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_4, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_4->stunStart == 0)
					moveTank(arena->p_4, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_4->stunStart > 675)
					{
						moveTank(arena->p_4, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_4->stunStart > 1500)
					{
						arena->p_4->stunStart = 0;
					}
				}
			}
		}

	case 3:
		if (arena->death[2] == false)
		{
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_3->shielded();
			}
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_3->dashed();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_3->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_3, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_3->stunStart == 0)
					moveTank(arena->p_3, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_3->stunStart > 675)
					{
						moveTank(arena->p_3, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_3->stunStart > 1500)
					{
						arena->p_3->stunStart = 0;
					}
				}
			}
		}
	case 2:
		if (arena->death[1] == false)
		{
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_2->dashed();
			}
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_2->shielded();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_2->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_2, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_2->stunStart == 0)
					moveTank(arena->p_2, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_2->stunStart > 675)
					{
						moveTank(arena->p_2, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_2->stunStart > 1500)
					{
						arena->p_2->stunStart = 0;
					}
				}
			}

		}
		if (arena->death[0] == false)
		{
			if (selection.modifiers[modifierlist::dash] == true)
			{
				arena->p_1->dashed();
			}
			if (selection.modifiers[modifierlist::shield] == true)
			{
				arena->p_1->shielded();
			}
			if (selection.modifiers[modifierlist::melee] == true)
			{
				arena->p_1->melee();
			}
			if (selection.modifiers[modifierlist::standard] == false)
				moveTank(arena->p_1, getframetimeEstimate(), arena);
			else
			{
				if (arena->p_1->stunStart == 0)
					moveTank(arena->p_1, getframetimeEstimate(), arena);
				else
				{
					if (clock() - arena->p_1->stunStart > 675)
					{
						moveTank(arena->p_1, getframetimeEstimate(), arena);
					}
					if (clock() - arena->p_1->stunStart > 1500)
					{
						arena->p_1->stunStart = 0;
					}
				}
			}

		}
		else
		{

		}
		break;

	}

	arena->getBulletCollsion();


}

int Menu::mainMenu()
{
	FzlPlaySound(sounds->smenu[menumusic]);
	//wait(0.5);
	int pos = 1;
	float x;
	float y;
	bool tutlock = false;
	bool creditlock = false;

	//	while (p.conButton(XINPUT_GAMEPAD_A) == true) {}
	int counter = 0;
	int choice = 0;
	while (true)
	{

		x = p.getLeftStick().x;
		y = p.getLeftStick().y;
		//wait(0.2);
		if (!tutlock && !creditlock)
		{
			if ((y < -0.2 || p.conButton(XINPUT_GAMEPAD_DPAD_UP) == true) && counter < 2)
			{
				counter++;
				//	wait(0.15);
			}
			else if ((y > 0.2 || p.conButton(XINPUT_GAMEPAD_DPAD_DOWN) == true) && counter > 0)
			{
				counter--;
				//	wait(0.15);
			}
		}
		if (counter == 0)
		{
			FzlDrawSprite(holder->menu[menu1], 960, 540, 0);
			choice = 1;
		}
		else if (counter == 1)
		{
			FzlDrawSprite(holder->menu[menu2], 960, 540, 0);
			choice = -1;
		}
		else if (counter == 2)
		{
			FzlDrawSprite(holder->menu[menu3], 960, 540, 0);
			choice = -3;
		}
		if (!tutlock && !creditlock)
		{
			if (p.conButton(XINPUT_GAMEPAD_A))
			{
				while (p.conButton(XINPUT_GAMEPAD_A)) {};
				if (counter == 1)
				{
					creditlock = true;
				}
				else
				{
					return choice;
				}
			}
			if (p.conButton(XINPUT_GAMEPAD_Y))
			{
				//wait(0.15);
				tutlock = true;
			}
		}

		else if (creditlock)
		{
			FzlDrawSprite(holder->menu[credits], 960, 540, 0);
			if (p.conButton(XINPUT_GAMEPAD_B))
			{
				while (p.conButton(XINPUT_GAMEPAD_B)) {};
				//wait(0.15);
				creditlock = false;
			}
		}
		else
		{
			FzlDrawSprite(holder->menu[controltut], 960, 540, 0);
			if (p.conButton(XINPUT_GAMEPAD_B))
			{
				while (p.conButton(XINPUT_GAMEPAD_B)) {};
				//wait(0.15);
				tutlock = false;
			}
		}
		while ((p.getLeftStick().x > 0 || p.conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == 1)) {}
		while ((p.getLeftStick().x < 0 || p.conButton(XINPUT_GAMEPAD_DPAD_LEFT) == 1)) {}
		while (p.conButton(XINPUT_GAMEPAD_B)) {};
		while (p.conButton(XINPUT_GAMEPAD_A)) {};
		FzlSwapBuffers();

	}
	return 0;
}

bool playAgain()//controls whether a new game is played or not
{
	while (1)
	{
		if (p.conButton(XINPUT_GAMEPAD_A) == true)
		{
			return false;
		}
		else if (p.conButton(XINPUT_GAMEPAD_B) == true)
		{
			return true;
		}
	}
}

void Menu::wait()
{
	int count = 0;
	double time = FzlGetDeltaTime();
	while (time > 0.0000000000016)
	{
		count++;
		time = FzlGetDeltaTime();
	}
}
void Menu::wait(double x)//used to wait a variable amount of time
{
	double time = FzlGetTimeSinceStart();
	double wait = 0.0;
	while (time - wait > -x)
	{
		wait = FzlGetTimeSinceStart();
	}
}

void Menu::moveTank(Tank *tank, double time, World* world)
{
	tank->setDirection();
	tank->turretMovement(inversion);  //used to rotate turret
	tank->movement(movement, time, world, &layers);//used to to move tank
	tank->rotation(movement);//used to rotate tank (only for tank controls)


}

void Menu::direction(Tank *move, int player)
{
	int frameSpeed = 60;
	int multiply = 3;

	if (move->dir == 0 || move->dir == 1)
	{
		multiply *= -1;
	}

	if (move->dir == 0 || move->dir == 2)
		frameSpeed = 30 - move->getvelocityX() * multiply;
	else if (move->dir == 1 || move->dir == 3)
		frameSpeed = 30 - move->getvelocityY() * multiply;
	if (frameSpeed > 30)
	{
		frameSpeed = 6;
	}
	else if (frameSpeed > 20)
	{
		frameSpeed = 5;
	}
	else if (frameSpeed > 15)
	{
		frameSpeed = 4;
	}
	else
	{
		frameSpeed = 3;
	}
	if (move->dir == 5)
	{
		frameSpeed = 15;
	}


	if (frame % frameSpeed == 0)
	{
		if (move->dir == 1)
		{
			if (move->spriteSpot < 3)
			{
				move->spriteSpot++;
			}
			else
			{
				move->spriteSpot = 0;
			}
		}
		else if (move->dir == 3)
		{
			if (move->spriteSpot > 4)
				move->spriteSpot = 3;
			else if (move->spriteSpot > 0)
			{
				move->spriteSpot--;
			}
			else
			{
				move->spriteSpot = 3;
			}
		}
		else if (move->dir == 0)
		{
			if (move->spriteSpot > 10)
				move->spriteSpot = 5;
			else if (move->spriteSpot < 4)
				move->spriteSpot = 5;
			else if (move->spriteSpot < 10) // 5 - 10
				move->spriteSpot++;
			else
				move->spriteSpot = 5;
		}
		else if (move->dir == 2)
		{
			if (move->spriteSpot > 10)
			{
				move->spriteSpot = 10;
			}
			else if (move->spriteSpot > 5) // 5 - 10
				move->spriteSpot--;
			else
				move->spriteSpot = 10;
		}
		else if (move->dir == 5)
		{
			if (move->spriteSpot == 12)
				move->spriteSpot = 13;
			else
				move->spriteSpot = 12; // 12 and 13
		}

	}
	//down
	if (selection.modifiers[modifierlist::standard] == false)
	{
		if (move->getAT() > -112.5 && move->getAT() < -67.5)
		{
			move->spriteSpot2 = 0;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 0, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}
		//down right
		else if (move->getAT() > -67.5 && move->getAT() < -22.5)
		{
			move->spriteSpot2 = 1;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//	FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 1, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}

		//right
		else if (move->getAT() > -22.5 && move->getAT() < 22.5)
		{
			move->spriteSpot2 = 2;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 2, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}

		//up right
		else if (move->getAT() > 22.5 && move->getAT() < 67.5)
		{
			move->spriteSpot2 = 3;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 3, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}

		//up
		else if (move->getAT() < 112.5 && move->getAT() > 67.5)
		{
			move->spriteSpot2 = 4;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 4, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);
		}

		//up left
		else if (move->getAT() > 112.5 && move->getAT() < 157.5)
		{
			move->spriteSpot2 = 5;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 5, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}

		//left
		else if (move->getAT() > 157.5 || move->getAT() < -157.5)
		{
			move->spriteSpot2 = 6;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 6, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}

		//down left
		else if (move->getAT() > -157.5 && move->getAT() < -112.5)
		{
			move->spriteSpot2 = 7;
			layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
			//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 7, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
		}
		if (move->shield == false && selection.modifiers[modifierlist::shield])
		{
			layers.push_back(*move->bubble, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->playerID, 0);
		}
	}
	else
	{
		if (move->stunStart == 0)
		{
			if (move->getAT() > -112.5 && move->getAT() < -67.5)
			{
				move->spriteSpot2 = 0;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 0, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}
			//down right
			else if (move->getAT() > -67.5 && move->getAT() < -22.5)
			{
				move->spriteSpot2 = 1;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//	FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 1, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//right
			else if (move->getAT() > -22.5 && move->getAT() < 22.5)
			{
				move->spriteSpot2 = 2;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 2, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//up right
			else if (move->getAT() > 22.5 && move->getAT() < 67.5)
			{
				move->spriteSpot2 = 3;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 3, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//up
			else if (move->getAT() < 112.5 && move->getAT() > 67.5)
			{
				move->spriteSpot2 = 4;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 4, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);
			}

			//up left
			else if (move->getAT() > 112.5 && move->getAT() < 157.5)
			{
				move->spriteSpot2 = 5;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 5, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//left
			else if (move->getAT() > 157.5 || move->getAT() < -157.5)
			{
				move->spriteSpot2 = 6;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 6, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//down left
			else if (move->getAT() > -157.5 && move->getAT() < -112.5)
			{
				move->spriteSpot2 = 7;
				layers.push_back(*move->staticTank, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->spriteSpot, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 7, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}
		}
		else if (clock() - move->stunStart > 675)
		{
			if (move->getAT() > -112.5 && move->getAT() < -67.5)
			{
				move->spriteSpot2 = 0;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 0, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}
			//down right
			else if (move->getAT() > -67.5 && move->getAT() < -22.5)
			{
				move->spriteSpot2 = 1;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//	FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 1, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//right
			else if (move->getAT() > -22.5 && move->getAT() < 22.5)
			{
				move->spriteSpot2 = 2;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 2, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//up right
			else if (move->getAT() > 22.5 && move->getAT() < 67.5)
			{
				move->spriteSpot2 = 3;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 3, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//up
			else if (move->getAT() < 112.5 && move->getAT() > 67.5)
			{
				move->spriteSpot2 = 4;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 4, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);
			}

			//up left
			else if (move->getAT() > 112.5 && move->getAT() < 157.5)
			{
				move->spriteSpot2 = 5;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 5, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//left
			else if (move->getAT() > 157.5 || move->getAT() < -157.5)
			{
				move->spriteSpot2 = 6;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 6, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}

			//down left
			else if (move->getAT() > -157.5 && move->getAT() < -112.5)
			{
				move->spriteSpot2 = 7;
				layers.push_back(*move->die, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, 10, move->spriteSpot2);
				//FzlDrawAnimatedSprite(move->staticTank, move->spriteSpot, 7, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0);//sets the tanks position and rotation
			}
		}
		if (move->shield == false && selection.modifiers[modifierlist::shield])
		{
			layers.push_back(*move->bubble, static_cast<float>(move->getX()), static_cast<float>(move->getY()), 0, move->playerID, 0);
		}
	}
}

int Menu::setGameMode()
{
	selection.modifiers[modifierlist::standard] = false;
	selection.modifiers[modifierlist::bomb] = false;
	selection.modifiers[modifierlist::stock] = false;
	selection.modifiers[modifierlist::hearts] = false;
	selection.modifiers[modifierlist::oneshot] = false;
	wait(0.5);
	selection = false;
	bool tutlock = false;

	int x = 0;
	int y = 0;
	int count = 0;
	bool done = false;

	while (done == false)
	{
		if (!tutlock)
		{

			float temp = p.getLeftStick().x;
			if (p.getLeftStick().x > .3)
			{
				if (x < 2)
					x++;
				wait(0.25);
			}
			else if (p.getLeftStick().x < -.3)
			{
				if (x > 0)
					x--;
				wait(0.25);
			}
			else if (p.getLeftStick().y > .3)
			{
				if (y == 1)
					y = 0;
				wait(0.25);
			}
			else if (p.getLeftStick().y < -.3)
			{
				if (y == 0)
					y = 1;
				wait(0.25);
			}
		}
		switch (x)
		{
		case 0:
			FzlDrawSprite(holder->menu[standard], 960, 540, 0);
			//	FzlSwapBuffers();
			break;
		case 1:
			if (y == 0)
			{
				FzlDrawSprite(holder->menu[bombscreen], 960, 540, 0);

				//	FzlSwapBuffers();

			}
			else
			{
				FzlDrawSprite(holder->menu[heartscreen], 960, 540, 0);

				//	FzlSwapBuffers();
			}
			break;
		case 2:
			if (y == 0)
			{
				FzlDrawSprite(holder->menu[pudding], 960, 540, 0);

				//	FzlSwapBuffers();
			}
			else
			{
				FzlDrawSprite(holder->menu[oneShotscreen], 960, 540, 0);

				//	FzlSwapBuffers();
			}
			break;

		}
		if (!tutlock)
		{
			if (p.conButton(XINPUT_GAMEPAD_A) == true)
			{
				done = true;
				switch (x)
				{


				case 0: //standard
					selection.modifiers[modifierlist::index::standard] = true;

					break;
				case 1: //bomb/heart
					if (y == 0)
						selection.modifiers[modifierlist::index::bomb] = true;
					else
						selection.modifiers[modifierlist::index::hearts] = true;
					break;
				case 2: //stock/oneshot
					if (y == 0)
						selection.modifiers[modifierlist::index::stock] = true;
					else
						selection.modifiers[modifierlist::index::oneshot] = true;

					break;

				}
				wait(0.25);

			}
			if (p.conButton(XINPUT_GAMEPAD_B) == true)
			{
				return 1;
			}
			if (p.conButton(XINPUT_GAMEPAD_Y) == true)
			{
				tutlock = true;
				wait(0.25);


			}
		}
		if (tutlock)

		{
			switch (x)
			{

			case 0: //standard
				FzlDrawSprite(holder->menu[standardtut], 960, 540, 0);
				break;
			case 1: //bomb/heart
				if (y == 0)
					FzlDrawSprite(holder->menu[bombtut], 960, 540, 0);
				else
					FzlDrawSprite(holder->menu[hearttut], 960, 540, 0);
				break;
			case 2: //stock/oneshot
				if (y == 0)
					FzlDrawSprite(holder->menu[stocktut], 960, 540, 0);
				else
					FzlDrawSprite(holder->menu[oneshottut], 960, 540, 0);
				break;

			}
			//	FzlSwapBuffers();
			if (p.conButton(XINPUT_GAMEPAD_B) == true)
			{
				tutlock = false;
				while (p.conButton(XINPUT_GAMEPAD_B)){}
			}
		}
		FzlSwapBuffers();
	}
	if (selection.modifiers[modifierlist::standard] == true)
		timeMax = 120;
	if (selection.modifiers[modifierlist::bomb] == true)
		timeMax = 60;
	if (selection.modifiers[modifierlist::stock] == true)//last man standing
		timeMax = 180;
	time = timeMax;

	return 3;
}


int Menu::setPlayerAmnt()
{



	wait(0.5);
	int x = 0;
	int count = 0;
	bool done = false;
	bool error = false;
	while (done == false)
	{
		if (!error)
		{
			float temp = p.getLeftStick().x;
			if (p.getLeftStick().x > 0)
			{
				if (x < 2)
					x++;
				wait(0.25);
			}
			else if (p.getLeftStick().x < 0)
			{
				if (x > 0)
					x--;
				wait(0.25);
			}
		}


		switch (x)
		{
		case 0:
			FzlDrawSprite(holder->menu[player2], 960, 540, 0);

			break;
		case 1:
			FzlDrawSprite(holder->menu[player3], 960, 540, 0);

			break;
		case 2:
			FzlDrawSprite(holder->menu[player4], 960, 540, 0);

			break;
		}

		if (p.conButton(XINPUT_GAMEPAD_A) == true)
		{
			while (p.conButton(XINPUT_GAMEPAD_A)) {};


			done = true;

			/*	if (error)
				{
				done = false;
				}*/

		}
		else if (p.conButton(XINPUT_GAMEPAD_B) == true)
			return 0;

		else if (error)
		{
			if (p.conButton(XINPUT_GAMEPAD_B) == true)
			{
				wait(0.15);
				error = false;
			}
		}

		FzlSwapBuffers();
	}
	playerAmnt = x + 2;
	arena = new World(88, (inversion == true) ? 30 : 30, playerAmnt, selection, holder, sounds);
	//get to the chopper

	return 2;
}
//Main Game Frame Loop Ends Here
void timer(int&, FzlSpriteHandle);
void Menu::setLayers()
{
	clock_t temp = clock();
	arena->p_1->deathTime = clock();
	arena->p_2->deathTime = clock();
	arena->p_3->deathTime = clock();
	arena->p_4->deathTime = clock();

	FzlDrawSprite(*mapP, 960, 540, 0);
	layers.push_back(*tempP, 960, 540, 0, -1, -1);
	//	layers.push_back(*gui, 960, 540, 0, -1, -1);

	switch (playerAmnt)
	{
	case 4:
		if (selection.modifiers[modifierlist::index::hearts] == true)
		{
			if (arena->p_4->getH() == 3)
				layers.push_back(holder->tank[heart2], arena->p_4->getX(), arena->p_4->getY(), arena->p_4->getA(), -1, -1);
			if (arena->p_4->getH() == 2)
				layers.push_back(holder->tank[heart1], arena->p_4->getX(), arena->p_4->getY(), arena->p_4->getA(), -1, -1);

		}
		if (arena->death[3] == false)
		{
			direction(arena->p_4, 3);
			arena->p_4->bulletMovement(selection.modifiers[modifierlist::index::ricochet], arena->getbulletSpeed(), &layers);//moves the bullet
			arena->p_4->deathStart = clock();
		}
		else if (arena->p_4->deathSpot != 13)
		{
			if ((arena->p_4->deathTime - arena->p_4->deathStart) > 150)
			{
				arena->p_4->deathStart = arena->p_4->deathTime;
				arena->p_4->deathSpot++;
			}
			layers.push_back(*arena->p_4->die, arena->p_4->getX(), arena->p_4->getY(), arena->p_4->getA(), arena->p_4->deathSpot, arena->p_4->spriteSpot2);


		}
		else
			arena->p_4->iamdead = true;
		if (selection.modifiers[modifierlist::index::deathsofthepast] == true && arena->p_4->deathSpot >= 9)
		{
			if (arena->death[3] && arena->p_1->bodies[3].rX != 0)
				FzlDrawAnimatedSprite(*arena->p_4->die, 9, arena->p_4->spriteSpot2, arena->p_1->bodies[3].lX + arena->p_1->getRadius(), arena->p_1->bodies[3].bY + arena->p_1->getRadius(), 0);
		}
		if (arena->p_4->stun == true && selection.modifiers[modifierlist::index::standard] == true)
		{
			arena->p_4->stun = false;
			arena->splat.push_back(pointerSprite(arena->p_4->getX(), arena->p_4->getY(), arena->p_4->getA(), *arena->p_4->die, 0, arena->p_4->spriteSpot2), 75, 9);
		}
	case 3:
		if (selection.modifiers[modifierlist::index::hearts] == true)
		{
			if (arena->p_3->getH() == 3)
				layers.push_back(holder->tank[heart2], arena->p_3->getX(), arena->p_3->getY(), arena->p_3->getA(), -1, -1);
			if (arena->p_3->getH() == 2)
				layers.push_back(holder->tank[heart1], arena->p_3->getX(), arena->p_3->getY(), arena->p_3->getA(), -1, -1);

		}
		if (arena->death[2] == false)
		{
			direction(arena->p_3, 2);
			arena->p_3->bulletMovement(selection.modifiers[modifierlist::index::ricochet], arena->getbulletSpeed(), &layers);//moves the bullet
			arena->p_3->deathStart = clock();
		}
		else if (arena->p_3->deathSpot != 13)
		{
			if ((arena->p_3->deathTime - arena->p_3->deathStart) > 150)
			{
				arena->p_3->deathStart = arena->p_3->deathTime;
				arena->p_3->deathSpot++;
			}
			layers.push_back(*arena->p_3->die, arena->p_3->getX(), arena->p_3->getY(), arena->p_3->getA(), arena->p_3->deathSpot, arena->p_3->spriteSpot2);

		}
		if (selection.modifiers[modifierlist::index::deathsofthepast] == true && arena->p_3->deathSpot >= 9)
		{
			if (arena->death[2] && arena->p_1->bodies[2].rX != 0)
				FzlDrawAnimatedSprite(*arena->p_3->die, 9, arena->p_3->spriteSpot2, arena->p_1->bodies[2].lX + arena->p_1->getRadius(), arena->p_1->bodies[2].bY + arena->p_1->getRadius(), 0);
		}
		if (arena->p_3->stun == true && selection.modifiers[modifierlist::index::standard] == true)
		{
			arena->p_3->stun = false;
			arena->splat.push_back(pointerSprite(arena->p_3->getX(), arena->p_3->getY(), arena->p_3->getA(), *arena->p_3->die, 0, arena->p_3->spriteSpot2), 75, 9);
		}
	case 2:

		if (arena->p_2->stun == true && selection.modifiers[modifierlist::index::standard] == true)
		{
			arena->p_2->stun = false;
			arena->splat.push_back(pointerSprite(arena->p_2->getX(), arena->p_2->getY(), arena->p_2->getA(), *arena->p_2->die, 0, arena->p_2->spriteSpot2), 75, 9);
		}

		if (arena->p_1->stun == true && selection.modifiers[modifierlist::index::standard] == true)
		{
			arena->p_1->stun = false;
			arena->splat.push_back(pointerSprite(arena->p_1->getX(), arena->p_1->getY(), arena->p_1->getA(), *arena->p_1->die, 0, arena->p_1->spriteSpot2), 75, 9);
		}

		if (selection.modifiers[modifierlist::index::hearts] == true)
		{
			if (arena->p_2->getH() == 3)
				layers.push_back(holder->tank[heart2], arena->p_2->getX(), arena->p_2->getY(), arena->p_2->getA(), -1, -1);
			if (arena->p_2->getH() == 2)
				layers.push_back(holder->tank[heart1], arena->p_2->getX(), arena->p_2->getY(), arena->p_2->getA(), -1, -1);

		}
		if (selection.modifiers[modifierlist::index::hearts] == true)
		{
			if (arena->p_1->getH() == 3)
				layers.push_back(holder->tank[heart2], arena->p_1->getX(), arena->p_1->getY(), arena->p_1->getA(), -1, -1);
			if (arena->p_1->getH() == 2)
				layers.push_back(holder->tank[heart1], arena->p_1->getX(), arena->p_1->getY(), arena->p_1->getA(), -1, -1);

		}
		if (arena->death[1] == false)
		{
			direction(arena->p_2, 1);
			arena->p_2->bulletMovement(selection.modifiers[modifierlist::index::ricochet], arena->getbulletSpeed(), &layers);//moves the bullet
			arena->p_2->deathStart = clock();
		}
		else if (arena->p_2->deathSpot != 13)
		{
			if ((arena->p_2->deathTime - arena->p_2->deathStart) > 150)
			{
				arena->p_2->deathStart = arena->p_2->deathTime;
				arena->p_2->deathSpot++;
			}
			layers.push_back(*arena->p_2->die, arena->p_2->getX(), arena->p_2->getY(), arena->p_2->getA(), arena->p_2->deathSpot, arena->p_2->spriteSpot2);
		}
		if (selection.modifiers[modifierlist::index::deathsofthepast] == true && arena->p_2->deathSpot >= 9)
		{
			if (arena->death[1] && arena->p_1->bodies[1].rX != 0)
				FzlDrawAnimatedSprite(*arena->p_2->die, 9, arena->p_2->spriteSpot2, arena->p_1->bodies[1].lX + arena->p_1->getRadius(), arena->p_1->bodies[1].bY + arena->p_1->getRadius(), 0);
		}
		if (arena->death[0] == false)
		{
			direction(arena->p_1, 0);
			arena->p_1->bulletMovement(selection.modifiers[modifierlist::index::ricochet], arena->getbulletSpeed(), &layers);//moves the bullet
			arena->p_1->deathStart = clock();
		}
		else if (arena->p_1->deathSpot != 13)
		{
			if ((arena->p_1->deathTime - arena->p_1->deathStart) > 150)
			{
				arena->p_1->deathStart = arena->p_1->deathTime;
				arena->p_1->deathSpot++;
			}
			layers.push_back(*arena->p_1->die, arena->p_1->getX(), arena->p_1->getY(), arena->p_1->getA(), arena->p_1->deathSpot, arena->p_1->spriteSpot2);

		}
		if (selection.modifiers[modifierlist::index::deathsofthepast] == true && arena->p_1->deathSpot >= 9)
		{
			if (arena->death[0] && arena->p_1->bodies[0].rX != 0)
				FzlDrawAnimatedSprite(*arena->p_1->die, 9, arena->p_1->spriteSpot2, arena->p_1->bodies[0].lX + arena->p_1->getRadius(), arena->p_1->bodies[0].bY + arena->p_1->getRadius(), 0);
		}
		break;

	}




	double deltat = FzlGetDeltaTime();
	arena->p_1->layering(&layers);
	if (!selection.modifiers[modifierlist::hearts] && !selection.modifiers[modifierlist::oneshot])
	{
		timer(time, numbers);
	}
	if ((temp - timing) / CLOCKS_PER_SEC > 0.5)
	{
		time--;
		timing = temp;
	}
	if (selection.modifiers[modifierlist::index::deathsofthepast])
	{
		arena->dotphandler();
	}
	arena->hudhandler();
	arena->splat.draw();
	FzlSwapBuffers();//used to load new frame.
	layers.clear();
	frameend = clock();
	double deltatclock = frameend - framestart;
	double deltatclockseconds = deltatclock / CLOCKS_PER_SEC;
	//if(FzlGetDeltaTime() < 0.016)
	//	wait(0.01 - FzlGetDeltaTime());
	addframetime((double)(deltatclockseconds));
	//	  << 1 / getframetimeEstimate() << std::endl; 
	//  << deltat << std::endl;
	arena->vibratehandler();

	//end of frame
}


void Menu::reset()
{
	//World::World(int x, int _bulletDelay, int _players, modifierlist & list, SpriteList* holder)
	arena->p_1 = new Tank(0, 150, 150, 88, true, 42, true, selection, holder, sounds);
	arena->p_2 = new Tank(1, 1740, 945, 88, true, 42, true, selection, holder, sounds);
	arena->p_3 = new Tank(2, 150, 920, 88, true, 42, true, selection, holder, sounds);
	arena->p_4 = new Tank(3, 1715, 150, 88, true, 42, true, selection, holder, sounds);
	time = 60;
	arena->p_1->setPointer(arena);
	arena->p_2->setPointer(arena);
	arena->p_3->setPointer(arena);
	arena->p_4->setPointer(arena);
	for (int count = 0; count < 4; count++)
	{
		arena->playerTurn[count] = false;
		arena->playerWait[count] = 0;
		if (count < arena->getplayers())
			arena->death[count] = false;
		else
			arena->death[count] = true;
	}

}

void Menu::deletion()
{
	delete arena;
}

int Menu::pause()
{

	int temp = 2;
	if (arena->p_1->playerNumber->conButton(XINPUT_GAMEPAD_START) == true)
	{
		FzlDrawSprite(holder->menu[paused], 960, 540, 0);
		FzlSwapBuffers();
		while (temp >= 1)
		{
			if (arena->p_1->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_LEFT) == true || arena->p_1->playerNumber->getLeftStick().x < 0)
			{
				FzlDrawSprite(holder->menu[paused], 960, 540, 0);
				FzlSwapBuffers();
				temp = 2;
			}
			else if (arena->p_1->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true || arena->p_1->playerNumber->getLeftStick().x > 0)
			{
				FzlDrawSprite(holder->menu[paused2], 960, 540, 0);
				FzlSwapBuffers();
				temp = 1;
			}
			else if (arena->p_1->playerNumber->conButton(XINPUT_GAMEPAD_A) == true)
			{
				wait(0.5);
				return temp;
			}
		}
	}
	else if (arena->p_2->playerNumber->conButton(XINPUT_GAMEPAD_START) == true)
	{
		FzlDrawSprite(holder->menu[paused], 960, 540, 0);
		FzlSwapBuffers();
		while (temp >= 1)
		{
			if (arena->p_2->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_LEFT) == true || arena->p_2->playerNumber->getLeftStick().x < 0)
			{
				FzlDrawSprite(holder->menu[paused], 960, 540, 0);
				FzlSwapBuffers();
				temp = 2;
			}
			else if (arena->p_2->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true || arena->p_2->playerNumber->getLeftStick().x > 0)
			{
				FzlDrawSprite(holder->menu[paused2], 960, 540, 0);
				FzlSwapBuffers();
				temp = 1;
			}
			else if (arena->p_2->playerNumber->conButton(XINPUT_GAMEPAD_A) == true)
			{
				wait(0.5);
				return temp;
			}
		}
	}
	else if (arena->p_3->playerNumber->conButton(XINPUT_GAMEPAD_START) == true)
	{
		FzlDrawSprite(holder->menu[paused], 960, 540, 0);
		FzlSwapBuffers();
		while (temp >= 1)
		{
			if (arena->p_3->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_LEFT) == true || arena->p_3->playerNumber->getLeftStick().x < 0)
			{
				FzlDrawSprite(holder->menu[paused], 960, 540, 0);
				FzlSwapBuffers();
				temp = 2;
			}
			else if (arena->p_3->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true || arena->p_3->playerNumber->getLeftStick().x > 0)
			{
				FzlDrawSprite(holder->menu[paused2], 960, 540, 0);
				FzlSwapBuffers();
				temp = 1;
			}
			else if (arena->p_3->playerNumber->conButton(XINPUT_GAMEPAD_A) == true)
			{
				//wait(0.5);
				return temp;
			}
		}
	}
	else if (arena->p_4->playerNumber->conButton(XINPUT_GAMEPAD_START) == true)
	{
		FzlDrawSprite(holder->menu[paused], 960, 540, 0);
		FzlSwapBuffers();
		while (temp >= 1)
		{
			if (arena->p_4->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_LEFT) == true || arena->p_4->playerNumber->getLeftStick().x < 0)
			{
				FzlDrawSprite(holder->menu[paused], 960, 540, 0);
				FzlSwapBuffers();
				temp = 2;
			}
			else if (arena->p_4->playerNumber->conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true || arena->p_4->playerNumber->getLeftStick().x > 0)
			{
				FzlDrawSprite(holder->menu[paused2], 960, 540, 0);
				FzlSwapBuffers();
				temp = 1;
			}
			else if (arena->p_4->playerNumber->conButton(XINPUT_GAMEPAD_A) == true)
			{
				//wait(0.5);
				return temp;
			}
		}
	}

	return 0;
}

void Menu::quit()
{
	on = false;
}

bool Menu::getOn()
{
	return on;
}

bool Menu::tankAABB(Tank* _t1, Tank* _t2)
{
	double _t1x = _t1->getX();
	double _t1y = _t1->getY();
	double _t2x = _t2->getX();
	double _t2y = _t2->getY();
	int tankradius = 32;//ankSize / 2;
	//AABB tests, if any of these tests are true, not colliding, return false.
	if (_t1x - tankradius > _t2x + tankradius)
		return false;
	if (_t2x - tankradius > _t1x + tankradius)
		return false;
	if (_t1y + tankradius < _t2y - tankradius)
		return false;
	if (_t2y + tankradius < _t1y - tankradius)
		return false;
	return true;

}

void Menu::tankCollision(int)
{	//If player 1 and 2 are colliding, bounce them.
	if (tankAABB(arena->p_1, arena->p_2))
	{
		tankBounce(arena->p_1, arena->p_2);
	}
	//if the player count is more than 2, then you have to test 1 and 2 against 3
	if (playerAmnt > 2)
	{
		if (arena->death[0] == false && arena->death[2] == false && tankAABB(arena->p_1, arena->p_3))
		{
			tankBounce(arena->p_1, arena->p_3);
		}

		if (arena->death[1] == false && arena->death[2] == false && tankAABB(arena->p_2, arena->p_3))
		{
			tankBounce(arena->p_2, arena->p_3);
		}
		//if the player count is more than 3, then you have to test 1, 2 and 3 against 4
		if (playerAmnt > 3)
		{
			if (arena->death[0] == false && arena->death[3] == false && tankAABB(arena->p_1, arena->p_4))
			{
				tankBounce(arena->p_1, arena->p_4);
			}
			if (arena->death[1] == false && arena->death[3] == false && tankAABB(arena->p_2, arena->p_4))
			{
				tankBounce(arena->p_2, arena->p_4);
			}
			if (arena->death[2] == false && arena->death[3] == false && tankAABB(arena->p_3, arena->p_4))
			{
				tankBounce(arena->p_3, arena->p_4);
			}
		}
	}
}

bool Menu::tankAABC(Tank* _t1, Tank* _t2)
{
	double _t1x = _t1->getX();
	double _t1y = _t1->getY();
	double _t2x = _t2->getX();
	double _t2y = _t2->getY();

	//if the radius of a player is less than the distance between the centres of the 2 players, return true.
	if (30 < sqrt(pow(_t2x - _t1x, 2) + pow(_t2y - _t1y, 2)))
		return true;
	return false;
}
//tankBounce can be updated to take player size/mass into account if we want to do cool stuff, but that's not important right now.

void Menu::tankBounce(Tank* _t1, Tank* _t2)
{
	if (tankAABC(_t1, _t2))
	{
		double _t1x = _t1->getVelocity()->getx();
		double _t1y = _t1->getVelocity()->gety();
		double _t2x = _t2->getVelocity()->getx();
		double _t2y = _t2->getVelocity()->gety();

		_t1->getVelocity()->setx(_t2x);
		_t1->getVelocity()->sety(_t2y);
		_t2->getVelocity()->setx(_t1x);
		_t2->getVelocity()->sety(_t1y);

		_t1->inertialMove();
		_t2->inertialMove();
		if (selection.modifiers[modifierlist::melee] || selection.modifiers[modifierlist::oneshot])
		{
			if (_t1->lethalspeed && !_t2->lethalspeed)
			{
				if (selection.modifiers[modifierlist::bomb] == false)
				{
					_t2->changeHealth(-1);
					FzlPlaySound(sounds->sworld[lifeLost]);
				}
				else
				{
					_t1->hasbomb = false;
					_t2->giveBomb();
					arena->splat.push_back(pointerSprite(_t2->getXP(), _t2->getYP(), 0, holder->tank[bombfeedback], 0, _t2->playerID), 50, 9);
				}
				if (_t2->getH() <= 0)
				{
					arena->death[_t2->controllernumber] = true;
					_t1->hasbullet = true;
					arena->splat.push_back(pointerSprite(_t1->getXP(), _t1->getYP(), 0, holder->tank[bulletgain], 0, _t1->playerID), 50, 9);
				}
			}

			else if (_t2->lethalspeed && !_t1->lethalspeed)
			{
				if (selection.modifiers[modifierlist::bomb] == false)
				{
					_t1->changeHealth(-1);
					FzlPlaySound(sounds->sworld[lifeLost]);
				}
				else
				{
					_t2->hasbomb = false;
					_t1->giveBomb();
					arena->splat.push_back(pointerSprite(_t1->getXP(), _t1->getYP(), 0, holder->tank[bombfeedback], 0, _t1->playerID), 50, 9);
				}
				if (_t1->getH() <= 0)
				{
					arena->death[_t1->controllernumber] = true;
					_t2->hasbullet = true;

					arena->splat.push_back(pointerSprite(_t2->getXP(), _t2->getYP(), 0, holder->tank[bulletgain], _t2->playerID), 50, 9);
				}
			}
		}
		if (tankAABB(_t1, _t2))
		{
			_t1->inertialMove();
			_t2->inertialMove();
		}
	}
}



Menu::Menu(SpriteList & pc, SoundList & sc)
{


	on = true;
	inversion = false;
	shootWait = 0;
	movement = 5;//this controls what movement scheme where using
	//tankSize = 88;

	holder = &pc;
	sounds = &sc;

	gameOver = false;
	gameDone = false;

	frame = 0;
	timing = clock();

}

void Menu::setMap(int level)
{
	song = rand() % 4;
	switch (song)
	{
	case 0:
		FzlPlaySound(sounds->sworld[soundWorld::song1]);
		break;
	case 1:
		FzlPlaySound(sounds->sworld[soundWorld::song2]);
		break;
	case 2:
		FzlPlaySound(sounds->sworld[soundWorld::song3]);
		break;
	case 3:
		FzlPlaySound(sounds->sworld[soundWorld::song4]);
		break;

	}

	switch (level)
	{
	case 1://tutorial

		tempP = &holder->world[tut1b];
		mapP = &holder->world[tut1t];
		arena->p_1->map2();
		arena->p_2->map2();
		arena->p_3->map2();
		arena->p_4->map2();
		break;
	case 2://ice

		if (rand() % 2 == 0)
		{
			tempP = &holder->world[7];
			mapP = &holder->world[8];
			arena->p_1->map3();
			arena->p_2->map3();
			arena->p_3->map3();
			arena->p_4->map3();
		}
		else
		{
			tempP = &holder->world[9];
			mapP = &holder->world[10];
			arena->p_1->map6();
			arena->p_2->map6();
			arena->p_3->map6();
			arena->p_4->map6();
		}
		break;
	case 3://jungle

		tempP = &holder->world[jungfront + 4];
		mapP = &holder->world[jungback + 4];
		arena->p_1->map();
		arena->p_2->map();
		arena->p_3->map();
		arena->p_4->map();
		break;

	case 4://Desert
		if (rand() % 2 == 0)
		{
			tempP = &holder->world[13];
			mapP = &holder->world[14];
			arena->p_1->map4();
			arena->p_2->map4();
			arena->p_3->map4();
			arena->p_4->map4();
		}
		else
		{
			tempP = &holder->world[19];
			mapP = &holder->world[20];
			arena->p_1->map7();
			arena->p_2->map7();
			arena->p_3->map7();
			arena->p_4->map7();
		}

		break;
	case 5://island
		if (rand() % 2 == 0)
		{
			tempP = &holder->world[15];
			mapP = &holder->world[16];
			arena->p_1->map5();
			arena->p_2->map5();
			arena->p_3->map5();
			arena->p_4->map5();
		}
		else
		{
			tempP = &holder->world[17];
			mapP = &holder->world[18];
			arena->p_1->map8();
			arena->p_2->map8();
			arena->p_3->map8();
			arena->p_4->map8();
		}
		break;
	}
	time = timeMax;
}

void Menu::initframetimes()
{
	for (int i = 0; i < 60; i++)
	{
		frametimes.push_back(0.01666);
	}
	frametimestotal = 1.0;
}
void Menu::addframetime(double _t)
{
	frametimestotal += _t;
	frametimestotal -= frametimes[59];
	frametimes.push_front(_t);
	frametimes.pop_back();
}


int Menu::getTime()
{
	return time;
}

int Menu::mapSelect()
{
	//wait(0.5);
	bool tutlock = false;

	bool done = false;
	int count = 1;
	while (!done)
	{
		if (p.conButton(XINPUT_GAMEPAD_A) == true)
		{
			//wait(0.25);
			setMap(count);
			mapSelected = count;
			return 5;
			done = true;
		}
		if (p.conButton(XINPUT_GAMEPAD_B) == true)
		{
			if (!tutlock)
			{
				return 3;
				done = true;
			}
		}
		if (p.conButton(XINPUT_GAMEPAD_Y) == true)
		{
			//	wait(0.15);
			tutlock = true;
		}
		switch (count)
		{
		case 1:
			FzlDrawSprite(holder->world[0], 960, 540, 0);
			if (tutlock)
			{
				FzlDrawSprite(holder->menu[tutorialbasic], 960, 540, 0);
			}
			break;
		case 2:

			FzlDrawSprite(holder->world[1], 960, 540, 0);
			if (tutlock)
			{
				FzlDrawSprite(holder->menu[tutorialice], 960, 540, 0);
			}

			break;
		case 3:
			FzlDrawSprite(holder->world[2], 960, 540, 0);
			if (tutlock)
			{
				FzlDrawSprite(holder->menu[tutorialjungle], 960, 540, 0);
			}
			break;
		case 4:
			FzlDrawSprite(holder->world[3], 960, 540, 0);
			if (tutlock)
			{
				FzlDrawSprite(holder->menu[tutorialdesert], 960, 540, 0);
			}
			break;
		case 5:
			FzlDrawSprite(holder->world[4], 960, 540, 0);
			if (tutlock)
			{
				FzlDrawSprite(holder->menu[tutorialisland], 960, 540, 0);
			}
			break;

		}
		if (!tutlock)
		{
			if ((p.getLeftStick().x > 0 || p.conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == 1) && count < 5)
			{
				count++;
				wait(0.25);
			}
			else if ((p.getLeftStick().x < 0 || p.conButton(XINPUT_GAMEPAD_DPAD_LEFT) == 1) && count > 1)
			{
				count--;
				//		wait(0.25);
			}
		}
		else
		{
			if (p.conButton(XINPUT_GAMEPAD_B) == 1)
			{
				tutlock = false;
				while ((p.conButton(XINPUT_GAMEPAD_B) == 1)) {};
				//	wait(0.15);
			}
		}
		while ((p.getLeftStick().x > 0 || p.conButton(XINPUT_GAMEPAD_DPAD_RIGHT) == 1)) {}
		while ((p.getLeftStick().x < 0 || p.conButton(XINPUT_GAMEPAD_DPAD_LEFT) == 1)) {}

		FzlSwapBuffers();
	}

	return 0;
}

void Menu::rounds(int round)
{

	bool loop = true;
	int count = 0;
	time_t temp;
	while (loop == true)
	{
		temp = clock();
		if ((temp - timing) / CLOCKS_PER_SEC > 0.5 && count < 3)
		{
			timing = temp;

			FzlDrawSprite(*mapP, 960, 540, 0);
			layers.push_back(*tempP, 960, 540, 0, -1, -1);
			switch (playerAmnt)
			{
			case 4:
				direction(arena->p_4, 3);
			case 3:
				direction(arena->p_3, 3);
			case 2:
				direction(arena->p_2, 3);
				direction(arena->p_1, 3);
				break;
			}
			arena->p_1->layering(&layers);
			layers.clear();

			FzlDrawAnimatedSprite(holder->menu[numbers], 0, 3 - count, 960, 540, 0);
			FzlSwapBuffers();
			count++;

		}
		if ((temp - timing) / CLOCKS_PER_SEC > 0.5 && count == 3)
		{
			timing = temp;
			FzlDrawSprite(*mapP, 960, 540, 0);
			layers.push_back(*tempP, 960, 540, 0, -1, -1);
			switch (playerAmnt)
			{
			case 4:
				direction(arena->p_4, 3);
			case 3:
				direction(arena->p_3, 3);
			case 2:
				direction(arena->p_2, 3);
				direction(arena->p_1, 3);
				break;
			}
			arena->p_1->layering(&layers);
			layers.clear();

			FzlDrawSprite(holder->menu[roundStarting], 980, 540, 0);
			arena->p_1->setHealth(-1);
			arena->p_2->setHealth(-1);
			arena->p_3->setHealth(-1);
			arena->p_4->setHealth(-1);
			FzlSwapBuffers();
			loop = false;
			while ((temp - timing) / CLOCKS_PER_SEC < 0.5) { temp = clock(); }
		}
	}
	arena->p_1->timeWillTell = clock();
	arena->p_2->timeWillTell = clock();
	arena->p_3->timeWillTell = clock();
	arena->p_4->timeWillTell = clock();
}
//Modifier Menu
int Menu::modifiers()
{

	Menu::selection.modifiers[modifierlist::index::shield] = false;
	Menu::selection.modifiers[modifierlist::index::timewilltell] = false;
	Menu::selection.modifiers[modifierlist::index::ricochet] = false;
	Menu::selection.modifiers[modifierlist::index::dash] = false;
	Menu::selection.modifiers[modifierlist::index::aoe] = false;
	Menu::selection.modifiers[modifierlist::index::charge] = false;
	if (!Menu::selection.modifiers[modifierlist::index::oneshot])
	{
		Menu::selection.modifiers[modifierlist::index::melee] = false;
	}
	Menu::selection.modifiers[modifierlist::index::deathsofthepast] = false;
	Menu::selection.modifiers[modifierlist::index::bulletacceleration] = false;

	//Menu::selection = false;
	arena->setPointer(this);
	wait(0.5);
	int posX = 0;
	int posY = 2;
	bool set = true;
	store highlights;
	bool tutlock = false;
	if (Menu::selection.modifiers[modifierlist::oneshot])
	{
		sprite result(960 + (573 * 2), 38 + (251 * 2), 0, holder->menu[menuhighlight]);
		highlights.push_back(result);
	}
	while (set == true)
	{

		if (!tutlock)
		{
			if (p.getLeftStick().x < -0.5 && posX > 0)

			{
				posX--;
				wait(0.15);
			}
			else if (p.getLeftStick().x > 0.5 && posX < 3)
			{
				posX++;
				wait(0.15);
			}
			if (p.getLeftStick().y < -0.5 && posY > 0)
			{
				posY--;
				wait(0.15);
			}
			else if (p.getLeftStick().y > 0.5 && posY < 2)
			{
				posY++;
				wait(0.15);
			}
		}
		if (p.conButton(XINPUT_GAMEPAD_B) == true && !tutlock)
		{
			while (p.conButton(XINPUT_GAMEPAD_B) == true){}
			return 2;
		}
		FzlDrawSprite(holder->menu[modifiermenubase], 960, 540, 0);
		highlights.draw();
		if (posX < 3)
		{
			FzlDrawSprite(holder->menu[menuselect], 960 + (573 * posX), 38 + (251 * posY), 0);
		}
		else
		{
			FzlDrawSprite(holder->menu[continuehighlight], 960, 540, 0);
		}

		FzlDrawSprite(holder->menu[menutext], 960, 540, 0);
		if (tutlock)
		{
			//FzlDrawSprite(tutorial, 960, 540, 0);
			if (p.conButton(XINPUT_GAMEPAD_B) == 1)
			{
				tutlock = false;
				wait(0.15);
				while (p.conButton(XINPUT_GAMEPAD_B)){}
			}
		}
		if (p.conButton(XINPUT_GAMEPAD_A) == 1 || p.conButton(XINPUT_GAMEPAD_Y) == 1 || tutlock)
		{
			if (p.conButton(XINPUT_GAMEPAD_Y) == 1)
			{
				while (p.conButton(XINPUT_GAMEPAD_Y)) {};
				tutlock = true;
			}

			switch (posX)
			{
			case 0:
				if (posY == 2)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialshield], 960, 540, 0);
					}
					else
						Menu::selection.modifiers[modifierlist::index::shield] = Menu::selection.modifiers[modifierlist::index::shield] ? false : true;
				}
				else if (posY == 1)
				{
					if (tutlock)
					{
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Time_will_tell.png", 1920, 1080);
						FzlDrawSprite(holder->menu[tutorialtwt], 960, 540, 0);
					}
					else
						Menu::selection.modifiers[modifierlist::index::timewilltell] = Menu::selection.modifiers[modifierlist::index::timewilltell] ? false : true;
				}
				else if (posY == 0)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialricochet], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Ricochet.png", 1920, 1080);
					}
					else
						Menu::selection.modifiers[modifierlist::index::ricochet] = Menu::selection.modifiers[modifierlist::index::ricochet] ? false : true;
				}
				break;
			case 1:
				if (posY == 2)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialdash], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Dash.png", 1920, 1080);
					}
					else
						Menu::selection.modifiers[modifierlist::index::dash] = Menu::selection.modifiers[modifierlist::index::dash] ? false : true;
				}
				else if (posY == 1)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialaoe], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_AOE.png", 1920, 1080);
					}
					else
						Menu::selection.modifiers[modifierlist::index::aoe] = Menu::selection.modifiers[modifierlist::index::aoe] ? false : true;
				}
				else if (posY == 0)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialcharge], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Charge.png", 1920, 1080);
					}
					else
					{
						Menu::selection.modifiers[modifierlist::index::charge] = Menu::selection.modifiers[modifierlist::index::charge] ? false : true;
					}
				}
				break;
			case 2:
				if (posY == 2)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialmelee], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Melee.png", 1920, 1080);
					}
					else if (!selection.modifiers[modifierlist::oneshot])
					{
						Menu::selection.modifiers[modifierlist::index::melee] = Menu::selection.modifiers[modifierlist::index::melee] ? false : true;
					}
				}
				else if (posY == 1)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialdotp], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Deaths_of_the_past.png", 1920, 1080);
					}
					else
						Menu::selection.modifiers[modifierlist::index::deathsofthepast] = Menu::selection.modifiers[modifierlist::index::deathsofthepast] ? false : true;
				}
				else if (posY == 0)
				{
					if (tutlock)
					{
						FzlDrawSprite(holder->menu[tutorialacceleration], 960, 540, 0);
						//tutorial = FzlLoadSprite("Assets/tutorials/Tutorial_Acceleration.png", 1920, 1080);
					}
					else
						Menu::selection.modifiers[modifierlist::index::bulletacceleration] = Menu::selection.modifiers[modifierlist::index::bulletacceleration] ? false : true;
				}
				break;
			case 3:
				if (Menu::selection.modifiers[modifierlist::index::oneshot] == true)
				{
					Menu::selection.modifiers[modifierlist::index::melee] = true;
				}
				if (Menu::selection.modifiers[modifierlist::index::bomb] == true)
				{
					timeMax = 60;
					time = timeMax;
					int randomnum = rand() % playerAmnt;
					setsecondbomber();

					arena->getplayer(randomnum)->giveBomb();
					arena->splat.push_back(pointerSprite(arena->getplayer(randomnum)->getXP(), arena->getplayer(randomnum)->getYP(), 0, holder->tank[bombfeedback], 0, arena->getplayer(randomnum)->playerID), 50, 9);
					std::cout << whohasbomb();
				}
				set = false;
				break;
			}

			if (!tutlock)
			{
				if (selection.modifiers[modifierlist::index::oneshot] != true || (posX != 2 || posY != 2))
				{
					sprite result(960 + (573 * posX), 38 + (251 * posY), 0, holder->menu[menuhighlight]);
					if (highlights.remove(result) == false && posX < 3)
					{
						highlights.push_back(result);
					}
				}
			}
		}





		while (p.conButton(XINPUT_GAMEPAD_A)){}
		FzlSwapBuffers();


	}
	arena->p_1->setHealth(-1);//set health acording to wheter lives are on.
	arena->p_2->setHealth(-1);//set health acording to wheter lives are on.
	arena->p_3->setHealth(-1);//set health acording to wheter lives are on.
	arena->p_4->setHealth(-1);//set health acording to wheter lives are on.

	return 4;
}

void Menu::deleteSprites()
{
	//bool heart = selection.modifiers[modifierlist::index::hearts];
	//bool dash = selection.modifiers[modifierlist::index::dash];
	//bool shield = selection.modifiers[modifierlist::index::shield];
	//if (!heart)
	//{
	//	if (!dash)
	//	{
	//		if (!shield)
	//		{
	//			//none
	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//		}
	//		else
	//		{
	//			//S

	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//			FzlDeleteSprite(holder->menu[p1s]);
	//			FzlDeleteSprite(holder->menu[p2s]);
	//			FzlDeleteSprite(holder->menu[p3s]);
	//			FzlDeleteSprite(holder->menu[p4s]);
	//		}
	//	}
	//	else
	//	{
	//		if (!shield)
	//		{


	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//			FzlDeleteSprite(holder->menu[p1d]);
	//			FzlDeleteSprite(holder->menu[p2d]);
	//			FzlDeleteSprite(holder->menu[p3d]);
	//			FzlDeleteSprite(holder->menu[p4d]);
	//		}
	//		else
	//		{
	//			//DS

	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//			FzlDeleteSprite(holder->menu[p1d]);
	//			FzlDeleteSprite(holder->menu[p2d]);
	//			FzlDeleteSprite(holder->menu[p3d]);
	//			FzlDeleteSprite(holder->menu[p4d]);
	//			FzlDeleteSprite(holder->menu[p1s]);
	//			FzlDeleteSprite(holder->menu[p2s]);
	//			FzlDeleteSprite(holder->menu[p3s]);
	//			FzlDeleteSprite(holder->menu[p4s]);
	//		}
	//	}



	//}
	//else
	//{
	//	if (!dash)
	//	{
	//		if (!shield)
	//		{
	//			//H

	//			FzlDeleteSprite(holder->menu[p11]);
	//			FzlDeleteSprite(holder->menu[p21]);
	//			FzlDeleteSprite(holder->menu[p31]);
	//			FzlDeleteSprite(holder->menu[p41]);
	//			FzlDeleteSprite(holder->menu[p10]);
	//			FzlDeleteSprite(holder->menu[p20]);
	//			FzlDeleteSprite(holder->menu[p30]);
	//			FzlDeleteSprite(holder->menu[p40]);
	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);

	//		}
	//		else
	//		{
	//			//HS

	//			FzlDeleteSprite(holder->menu[p1s]);
	//			FzlDeleteSprite(holder->menu[p2s]);
	//			FzlDeleteSprite(holder->menu[p3s]);
	//			FzlDeleteSprite(holder->menu[p4s]);
	//			FzlDeleteSprite(holder->menu[p11]);
	//			FzlDeleteSprite(holder->menu[p21]);
	//			FzlDeleteSprite(holder->menu[p31]);
	//			FzlDeleteSprite(holder->menu[p41]);
	//			FzlDeleteSprite(holder->menu[p10]);
	//			FzlDeleteSprite(holder->menu[p20]);
	//			FzlDeleteSprite(holder->menu[p30]);
	//			FzlDeleteSprite(holder->menu[p40]);
	//			FzlDeleteSprite(holder->menu[mh2]);
	//			FzlDeleteSprite(holder->menu[mh3]);
	//			FzlDeleteSprite(holder->menu[mh4]);
	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);

	//		}
	//	}
	//	else
	//	{
	//		if (!shield)
	//		{
	//			//HD

	//			FzlDeleteSprite(holder->menu[p1d]);
	//			FzlDeleteSprite(holder->menu[p2d]);
	//			FzlDeleteSprite(holder->menu[p3d]);
	//			FzlDeleteSprite(holder->menu[p4d]);
	//			FzlDeleteSprite(holder->menu[p11]);
	//			FzlDeleteSprite(holder->menu[p21]);
	//			FzlDeleteSprite(holder->menu[p31]);
	//			FzlDeleteSprite(holder->menu[p41]);
	//			FzlDeleteSprite(holder->menu[p10]);
	//			FzlDeleteSprite(holder->menu[p20]);
	//			FzlDeleteSprite(holder->menu[p30]);
	//			FzlDeleteSprite(holder->menu[p40]);
	//			FzlDeleteSprite(holder->menu[mh2]);
	//			FzlDeleteSprite(holder->menu[mh3]);
	//			FzlDeleteSprite(holder->menu[mh4]);
	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//		}
	//		else
	//		{
	//			//HDS
	//			printf("Deleted Sprite: %d%s", holder->menu[p11], "\n");
	//			FzlDeleteSprite(holder->menu[p11]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p21], "\n");
	//			FzlDeleteSprite(holder->menu[p21]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p31], "\n");
	//			FzlDeleteSprite(holder->menu[p31]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p41], "\n");
	//			FzlDeleteSprite(holder->menu[p41]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p10], "\n");
	//			FzlDeleteSprite(holder->menu[p10]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p20], "\n");
	//			FzlDeleteSprite(holder->menu[p20]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p30], "\n");
	//			FzlDeleteSprite(holder->menu[p30]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p40], "\n");
	//			FzlDeleteSprite(holder->menu[p40]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p1s], "\n");
	//			FzlDeleteSprite(holder->menu[p1s]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p1d], "\n");
	//			FzlDeleteSprite(holder->menu[p1d]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p2s], "\n");
	//			FzlDeleteSprite(holder->menu[p2s]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p2d], "\n");
	//			FzlDeleteSprite(holder->menu[p2d]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p3s], "\n");
	//			FzlDeleteSprite(holder->menu[p3s]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p3d], "\n");
	//			FzlDeleteSprite(holder->menu[p3d]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p4s], "\n");
	//			FzlDeleteSprite(holder->menu[p4s]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p4d], "\n");
	//			FzlDeleteSprite(holder->menu[p4d]);
	//			printf("Deleted Sprite: %d%s", holder->menu[mh2], "\n");
	//			FzlDeleteSprite(holder->menu[mh2]);
	//			printf("Deleted Sprite: %d%s", holder->menu[mh3], "\n");
	//			FzlDeleteSprite(holder->menu[mh3]);
	//			printf("Deleted Sprite: %d%s", holder->menu[mh4], "\n");
	//			FzlDeleteSprite(holder->menu[mh4]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p1elim], "\n");
	//			FzlDeleteSprite(holder->menu[p1elim]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p2elim], "\n");
	//			FzlDeleteSprite(holder->menu[p2elim]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p3elim], "\n");
	//			FzlDeleteSprite(holder->menu[p3elim]);
	//			printf("Deleted Sprite: %d%s", holder->menu[p4elim], "\n");
	//			FzlDeleteSprite(holder->menu[p4elim]);
	//		}
	//	}
	//}
}

void Menu::initilizeModifiers()
{
	//bool heart = Menu::selection.modifiers[modifierlist::index::hearts];
	//bool dash = Menu::selection.modifiers[modifierlist::index::dash];
	//bool shield = Menu::selection.modifiers[modifierlist::index::shield];
	//if (!heart)
	//{
	//	if (!dash)
	//	{
	//		if (!shield)
	//		{
	//			//none
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Player_1_Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1elim], "\n");
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Player_2_Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2elim], "\n");
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Player_3_Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3elim], "\n");
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Player_4_Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4elim], "\n");
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[gui1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[gui2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[gui3];
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			//S
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUIS1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUIS2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUIS3];
	//				break;
	//			}
	//			holder->menu[p1s] = FzlLoadSprite("Assets/HUD/Shield CD HUD/Player 1 CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1s], "\n");
	//			holder->menu[p2s] = FzlLoadSprite("Assets/HUD/Shield CD HUD/Player 2 CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2s], "\n");
	//			holder->menu[p3s] = FzlLoadSprite("Assets/HUD/Shield CD HUD/Player 3 CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3s], "\n");
	//			holder->menu[p4s] = FzlLoadSprite("Assets/HUD/Shield CD HUD/Player 4 CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4s], "\n");
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 1 Eliminated Shield.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1elim], "\n");
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 2 Eliminated Shield.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2elim], "\n");
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 3 Eliminated Shield.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3elim], "\n");
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 4 Eliminated Shield.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4elim], "\n");
	//		}
	//	}
	//	else
	//	{
	//		if (!shield)
	//		{
	//			//D
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUID1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUID2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUID3];
	//				break;
	//			}
	//			holder->menu[p1d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 1 Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1d], "\n");
	//			holder->menu[p2d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 2 Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2d], "\n");
	//			holder->menu[p3d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 3 Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3d], "\n");
	//			holder->menu[p4d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 4 Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4d], "\n");
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 1 Eliminated Dash.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1elim], "\n");
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 2 Eliminated Dash.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2elim], "\n");
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 3 Eliminated Dash.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3elim], "\n");
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 4 Eliminated Dash.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4elim], "\n");
	//		}
	//		else
	//		{
	//			//DS
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUISD1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUISD2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUISD3];
	//				break;
	//			}

	//			holder->menu[p1s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 1 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1s], "\n");
	//			holder->menu[p1d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 1 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1d], "\n");
	//			holder->menu[p2s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 2 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2s], "\n");
	//			holder->menu[p2d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 2 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2d], "\n");
	//			holder->menu[p3s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 3 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3s], "\n");
	//			holder->menu[p3d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 3 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3d], "\n");
	//			holder->menu[p4s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 4 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4s], "\n");
	//			holder->menu[p4d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 4 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4d], "\n");
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 1 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1elim], "\n");
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 2 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2elim], "\n");
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 3 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3elim], "\n");
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 4 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4elim], "\n");

	//		}
	//	}



	//}
	//else
	//{
	//	if (!dash)
	//	{
	//		if (!shield)
	//		{
	//			//H
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUIH1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUIH2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUIH3];
	//				break;

	//			}
	//			holder->menu[p11] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_1_Heart_1.png", 1920, 1080);

	//			holder->menu[p21] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_2_Heart_1.png", 1920, 1080);

	//			holder->menu[p31] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_3_Heart_1.png", 1920, 1080);

	//			holder->menu[p41] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_4_Heart_1.png", 1920, 1080);

	//			holder->menu[p10] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_1_Heart_0.png", 1920, 1080);

	//			holder->menu[p20] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_2_Heart_0.png", 1920, 1080);

	//			holder->menu[p30] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_3_Heart_0.png", 1920, 1080);

	//			holder->menu[p40] = FzlLoadSprite("Assets/HUD/Heart_Mode/Just_Hearts/Player_4_Heart_0.png", 1920, 1080);

	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Just Hearts/Player 1 Eliminated Heart.png", 1920, 1080);

	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Just Hearts/Player 2 Eliminated Heart.png", 1920, 1080);

	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Just Hearts/Player 3 Eliminated Heart.png", 1920, 1080);

	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Just Hearts/Player 4 Eliminated Heart.png", 1920, 1080);

	//		}
	//		else
	//		{
	//			//HS
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUIS1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUIS2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUIS3];
	//				break;
	//			}

	//			holder->menu[p1s] = FzlLoadSprite("Assets/HUD/Shield CD Hud/Player 1 CD.png", 1920, 1080);
	//			holder->menu[p2s] = FzlLoadSprite("Assets/HUD/Shield CD Hud/Player 2 CD.png", 1920, 1080);
	//			holder->menu[p3s] = FzlLoadSprite("Assets/HUD/Shield CD Hud/Player 3 CD.png", 1920, 1080);
	//			holder->menu[p4s] = FzlLoadSprite("Assets/HUD/Shield CD Hud/Player 4 CD.png", 1920, 1080);
	//			holder->menu[p11] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p21] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p31] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p41] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p10] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 No Hearts.png", 1920, 1080);
	//			holder->menu[p20] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 No Hearts.png", 1920, 1080);
	//			holder->menu[p30] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 No Hearts.png", 1920, 1080);
	//			holder->menu[p40] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 No Hearts.png", 1920, 1080);
	//			holder->menu[mh2] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/2 Player Hearts.png", 1920, 1080);
	//			holder->menu[mh3] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/3 Player Hearts.png", 1920, 1080);
	//			holder->menu[mh4] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/4 Player Hearts.png", 1920, 1080);
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 1 Eliminated Shield.png", 1920, 1080);
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 2 Eliminated Shield.png", 1920, 1080);
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 3 Eliminated Shield.png", 1920, 1080);
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Shield/Player 4 Eliminated Shield.png", 1920, 1080);

	//		}
	//	}
	//	else
	//	{
	//		if (!shield)
	//		{
	//			//HD
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUID1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUID2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUID3];
	//				break;
	//			}
	//			holder->menu[p1d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 1 Dash CD.png", 1920, 1080);
	//			holder->menu[p2d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 2 Dash CD.png", 1920, 1080);
	//			holder->menu[p3d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 3 Dash CD.png", 1920, 1080);
	//			holder->menu[p4d] = FzlLoadSprite("Assets/HUD/Dash Mode HUD/Player 4 Dash CD.png", 1920, 1080);
	//			holder->menu[p11] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p21] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p31] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p41] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 Heart 1 Left.png", 1920, 1080);
	//			holder->menu[p10] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 No Hearts.png", 1920, 1080);
	//			holder->menu[p20] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 No Hearts.png", 1920, 1080);
	//			holder->menu[p30] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 No Hearts.png", 1920, 1080);
	//			holder->menu[p40] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 No Hearts.png", 1920, 1080);
	//			holder->menu[mh2] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/2 Player Hearts.png", 1920, 1080);
	//			holder->menu[mh3] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/3 Player Hearts.png", 1920, 1080);
	//			holder->menu[mh4] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/4 Player Hearts.png", 1920, 1080);
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 1 Eliminated Dash.png", 1920, 1080);
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 2 Eliminated Dash.png", 1920, 1080);
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 3 Eliminated Dash.png", 1920, 1080);
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Dash/Player 4 Eliminated Dash.png", 1920, 1080);
	//		}
	//		else
	//		{
	//			//HDS
	//			switch (playerAmnt)
	//			{
	//			case 2:
	//				gui = &holder->menu[GUIA1];
	//				break;
	//			case 3:
	//				gui = &holder->menu[GUIA2];
	//				break;
	//			case 4:
	//				gui = &holder->menu[GUIA3];
	//				break;
	//			}
	//			holder->menu[p11] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 Heart 1 Left.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p11], "\n");
	//			holder->menu[p21] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 Heart 1 Left.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p21], "\n");
	//			holder->menu[p31] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 Heart 1 Left.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p31], "\n");
	//			holder->menu[p41] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 Heart 1 Left.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p41], "\n");
	//			holder->menu[p10] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 1 No Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p10], "\n");
	//			holder->menu[p20] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 2 No Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p20], "\n");
	//			holder->menu[p30] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 3 No Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p30], "\n");
	//			holder->menu[p40] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/Player 4 No Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p40], "\n");
	//			holder->menu[p1s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 1 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1s], "\n");
	//			holder->menu[p1d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 1 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1d], "\n");
	//			holder->menu[p2s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 2 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2s], "\n");
	//			holder->menu[p2d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 2 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2d], "\n");
	//			holder->menu[p3s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 3 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3s], "\n");
	//			holder->menu[p3d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 3 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3d], "\n");
	//			holder->menu[p4s] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Shield/Shield CD/Player 4 DS Shield CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4s], "\n");
	//			holder->menu[p4d] = FzlLoadSprite("Assets/HUD/Multiple Mode HUD/Dash/Dash CD/Player 4 DS Dash CD.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4d], "\n");
	//			holder->menu[mh2] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/2 Player Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[mh2], "\n");
	//			holder->menu[mh3] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/3 Player Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[mh3], "\n");
	//			holder->menu[mh4] = FzlLoadSprite("Assets/HUD/Heart_Mode/Multiple Mod Hearts/4 Player Hearts.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[mh4], "\n");
	//			holder->menu[p1elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 1 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p1elim], "\n");
	//			holder->menu[p2elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 2 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p2elim], "\n");
	//			holder->menu[p3elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 3 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p3elim], "\n");
	//			holder->menu[p4elim] = FzlLoadSprite("Assets/HUD/eliminated/Eliminated Everything/Player 4 Eliminated.png", 1920, 1080);
	//			printf("Created Sprite: %d%s", holder->menu[p4elim], "\n");
	//			bool test = true;
	//			if (test == false)
	//			{
	//				for (int count = 0; count <= holder->menu[p4elim]; count++)
	//				{
	//					FzlDrawSprite(count, 960, 540, 0);
	//					FzlSwapBuffers();
	//				}
	//			}

	//		}
	//	}
	//}
}

void Menu::timer(int& time, FzlSpriteHandle numbers)
{
	//timer expired
	if (time <= 0)
	{
		if (selection.modifiers[modifierlist::bomb])
		{
			int hadbomb = whohasbomb();
			arena->death[whohasbomb() - 1] = true;
			FzlPlaySound(sounds->sworld[bombExplode]);
			switch (hadbomb)
			{
			case 1:
				arena->splat.push_back(pointerSprite(arena->p_1->tankPos.getx(), arena->p_1->tankPos.gety(), 0, *arena->p_1->aoe, arena->p_1->playerID), 50, 8);
				break;
			case 2:
				arena->splat.push_back(pointerSprite(arena->p_2->tankPos.getx(), arena->p_2->tankPos.gety(), 0, *arena->p_2->aoe, arena->p_2->playerID), 50, 8);
				break;
			case 3:
				arena->splat.push_back(pointerSprite(arena->p_3->tankPos.getx(), arena->p_3->tankPos.gety(), 0, *arena->p_3->aoe, arena->p_3->playerID), 50, 8);
				break;
			case 4:
				arena->splat.push_back(pointerSprite(arena->p_4->tankPos.getx(), arena->p_4->tankPos.gety(), 0, *arena->p_4->aoe, arena->p_4->playerID), 50, 8);
				break;
			}

			if (!getlastbomber())
			{
				setsecondbomber();
			}
			getlastbomber()->giveBomb();


			arena->resetlastbomber();
			setsecondbomber();
			switch (hadbomb)
			{
			case 1:
				arena->p_1->hasbomb = false;
				break;
			case 2:
				arena->p_2->hasbomb = false;
				break;
			case 3:
				arena->p_3->hasbomb = false;
				break;
			case 4:
				arena->p_4->hasbomb = false;
				break;
			}
			arena->splat.push_back(pointerSprite(getlastbomber()->getXP(), getlastbomber()->getYP(), 0, holder->tank[bombfeedback], 0, getlastbomber()->playerID), 50, 9);



		}
		time = 60;
	}
	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	int posX = 860;

	if (time > 0)
	{

		ones = time % 10;
		if (time >= 10)
		{
			tens = (time - ones) / 10;
			if (tens >= 6)
			{
				hundreds = tens / 6;
				for (int count = 0; count < hundreds; count++)
					tens -= 6;
			}
		}
		else
			tens = 0;


	}
	if (selection.modifiers[modifierlist::bomb])
	{
		int bomber = whohasbomb();
		if (bomber == 0)
		{
			if (!arena->death[0])
			{
				arena->p_1->giveBomb();
			}
			else if (!arena->death[1])
			{
				arena->p_2->giveBomb();
			}
			else if (!arena->death[2])
			{
				arena->p_3->giveBomb();
			}
			else
			{
				arena->p_4->giveBomb();
			}
		}
		switch (whohasbomb())
		{
		case 1:
			FzlDrawSprite(holder->menu[p1bomb], 960, 540, 0);
			break;
		case 2:
			FzlDrawSprite(holder->menu[p2bomb], 960, 540, 0);
			break;
		case 3:
			FzlDrawSprite(holder->menu[p3bomb], 960, 540, 0);
			break;
		case 4:
			FzlDrawSprite(holder->menu[p4bomb], 960, 540, 0);
			break;
		}
	}
	else if (!selection.modifiers[modifierlist::hearts] && !selection.modifiers[modifierlist::oneshot])
	{
		FzlDrawSprite(holder->menu[clockbackground], 960, 540, 0);
	}
	int yoffset = (selection.modifiers[modifierlist::bomb]) ? -24 : 0;
	FzlDrawAnimatedSprite(holder->menu[numbers], 0, hundreds, posX, 1013 + yoffset, 0);
	FzlDrawAnimatedSprite(holder->menu[numbers], 0, 10, posX += 60, 1013 + yoffset, 0);
	posX += 60;
	FzlDrawAnimatedSprite(holder->menu[numbers], 0, tens, posX, 1013 + yoffset, 0);
	FzlDrawAnimatedSprite(holder->menu[numbers], 0, ones, posX += 60, 1013 + yoffset, 0);
	
}

Menu::~Menu()
{

}
int Menu::whohasbomb()
{
	if (arena->p_1->hasbomb)
	{
		return 1;
	}
	else if (arena->p_2->hasbomb)
	{
		return 2;
	}
	else if (arena->p_3->hasbomb)
	{
		return 3;
	}
	else if (arena->p_4->hasbomb)
	{
		return 4;
	}
	else
		return 0;
}
Tank* Menu::getlastbomber()
{
	if (arena->p_1->lastbomber)
	{
		return arena->p_1;
	}
	else if (arena->p_2->lastbomber)
	{
		return arena->p_2;
	}
	else if (arena->p_3->lastbomber)
	{
		return arena->p_3;
	}
	else if (arena->p_4->lastbomber);
	{
		return arena->p_4;
	}
}
void Menu::setsecondbomber()
{
	//int randomnum = rand() % playerAmnt;
	switch (playerAmnt)
	{
	case 2:
		if (arena->p_1->hasbomb)
		{
			arena->p_2->lastbomber = true;
		}
		else
		{
			arena->p_1->lastbomber = true;
		}
		break;
	case 3:
		if (arena->p_1->hasbomb)
		{
			if (((rand() % 2) == 1) && !arena->death[1])
			{
				arena->p_2->lastbomber = true;
			}
			else
			{
				arena->p_3->lastbomber = true;
			}
		}
		else if (arena->p_2->hasbomb)
		{
			if (((rand() % 2) == 1) && !arena->death[0])
			{
				arena->p_1->lastbomber = true;
			}
			else
			{
				arena->p_3->lastbomber = true;
			}
		}
		else if (arena->p_3->hasbomb)
		{
			if (((rand() % 2) == 1) && !arena->death[0])
			{
				arena->p_1->lastbomber = true;
			}
			else
			{
				arena->p_2->lastbomber = true;
			}
		}
		break;
	case 4:
		int fourrand = rand() % 3;
		if (getliveplayers() < 4)
		{
			arena->getrandomaliveplayer().setlastbomber();
		}
		if (arena->p_1->hasbomb)
		{
			if (fourrand == 0)
			{
				if (arena->death[1] == false)
				{
					arena->p_2->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 1)
			{
				if (arena->death[2] == false)
				{
					arena->p_3->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 2)
			{
				if (arena->death[3] == false)
				{
					arena->p_4->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
		}
		else if (arena->p_2->hasbomb)
		{
			if (fourrand == 0)
			{
				if (arena->death[0] == false)
				{
					arena->p_1->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 1)
			{
				if (arena->death[2] == false)
				{
					arena->p_3->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 2)
			{
				if (arena->death[3] == false)
				{
					arena->p_4->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
		}
		else if (arena->p_3->hasbomb)
		{
			if (fourrand == 0)
			{
				if (arena->death[0] == false)
				{
					arena->p_1->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 1)
			{
				if (arena->death[1] == false)
				{
					arena->p_2->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
			else if (fourrand == 2)
			{
				if (arena->death[3] == false)
				{
					arena->p_4->lastbomber = true;
				}
				else
				{
					arena->getrandomaliveplayer().setlastbomber();
				}
			}
		}
		break;
	}

}
int Menu::getliveplayers()
{
	int result = playerAmnt;
	if (arena->death[0])
	{
		result--;
	}
	if (arena->death[1])
	{
		result--;
	}
	if (playerAmnt > 2 && arena->death[2])
	{
		result--;
	}
	if (playerAmnt > 3 && arena->death[3])
	{
		result--;
	}
	return result;

}