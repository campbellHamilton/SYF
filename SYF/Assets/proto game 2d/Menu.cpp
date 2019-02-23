#include "Fizzle\Fizzle.h"
#include "Menu.h"
#include "world.h"
//Default constructor
//Menu is for the menus, 
Menu::Menu(){};
void Menu::game()
{
	bool shouldClose = false;//controls when the game is left.

	while (!shouldClose)
	{


		FzlSpriteHandle staticTank = FzlLoadSprite("Assets/tank/tank.png", 32, 32);//creates the tank image
		FzlSpriteHandle staticTankTurret = FzlLoadSprite("Assets/tank/tank-turret.png", 64, 64);//creates the turret image

		FzlSpriteHandle staticTank2 = FzlLoadSprite("Assets/tank/tank2.png", 32, 32);//creates the tank image for second player
		FzlSpriteHandle staticTankTurret2 = FzlLoadSprite("Assets/tank/tank-turret2.png", 64, 64);//creates the turret image second player


		World game;// creates the world object (contains data for things in game.)

		while (!shouldClose)
		{
			//We can use this function to draw a static sprite at a given position and rotation
			FzlDrawSprite(staticTank, static_cast<float>(game.p1.getX()), static_cast<float>(game.p1.getY()), game.p1.getA() + 90);//sets the tanks position and rotation
			FzlDrawSprite(staticTankTurret, static_cast<float>(game.p1.getX()), static_cast<float>(game.p1.getY()), game.p1.getAT() + game.p1.getA() + 270);//sets the turret rotation

			FzlDrawSprite(staticTank2, static_cast<float>(game.p2.getX()), static_cast<float>(game.p2.getY()), game.p2.getA() + 90); //sets the tanks position and rotation second player
			FzlDrawSprite(staticTankTurret2, static_cast<float>(game.p2.getX()), static_cast<float>(game.p2.getY()), game.p2.getAT() + game.p2.getA() + 270);//sets the turret rotation second play

			shouldClose = FzlGetKey(FzlKeyEscape);//used to exit the game (broken at the moment)

			if (FzlGetKey(FzlKeyP) && movement < 4)//used to cycle the movement scheme
			{
				movement++;
				wait(2);
			}
			if (FzlGetKey(FzlKeyO) && movement > 0)//used to cycle the movement scheme
			{
				wait(2);
				movement--;
			}
			if (FzlGetKey(FzlKeyI))
			{
				bulletBounceToggle = true;
			}
			game.p1.turretMovement();  //used to rotate turret
			game.p1.movement(movement);//used to to move tank
			game.p1.bulletMovement(bulletBounceToggle, game.getbulletSpeed());  //moves the bullet
			game.p1.rotation(movement);//used to rotate tank (only for tank controls)
			game.p2.turretMovement();  //used to rotate turret
			game.p2.movement(movement);//used to to move tank
			game.p2.bulletMovement(bulletBounceToggle, game.getbulletSpeed());  //moves the bullet
			game.p2.rotation(movement);//used to rotate tank (only for tank controls)
			game.playersShoot(); //controls shooting bullets. handles both players shots
			shouldClose = game.getCollision(); // detects whether a player is hit by a bullet.
			wait();//waits for a few millaseconds. Controls framerate
			FzlSwapBuffers();//used to load new frame.
		}
		if (shouldClose == true)//controls the game over screen
		{

			FzlSpriteHandle staticWin = FzlLoadSprite("Assets/play-again.png", 400, 300);//displays the game over png
			FzlDrawSprite(staticWin, static_cast<float>(960), static_cast<float>(540), 0);
			FzlSwapBuffers();//used to load new frame.
			shouldClose = game.p1.playAgain();//used to check wether player presses play again or quit
			wait(0.5);//used to create delay between new game so player can release the play again button.
		}
	}
}

void Menu::wait()//Controls the games framerate. runs at 62fps at the moment. (needs to be modified)
{
	double time = FzlGetTimeSinceStart();
	double wait = 0.0;
	while (time - wait > -0.016)
	{
		wait = FzlGetTimeSinceStart();
	}
}
void Menu::wait(int x)//used to wait an variable amount of time
{
	double time = FzlGetTimeSinceStart();
	double wait = 0.0;
	while (time - wait > -x)
	{
		wait = FzlGetTimeSinceStart();
	}
}
#include "controller.h"
controller p(0);
bool Menu::start()
{
	FzlSpriteHandle menu1 = FzlLoadSprite("Assets/start-normal.png", 400, 200);
	FzlSpriteHandle menu2 = FzlLoadSprite("Assets/menu-inverted.png", 400, 200);
	FzlSpriteHandle menu3 = FzlLoadSprite("Assets/text-highlight.png", 400, 200);
	FzlSpriteHandle menu4 = FzlLoadSprite("Assets/A-button.png", 64, 64);

	int x = 500;
	bool done = false;
	bool choice;
	while (done == false)
	{
		if (p.getRightStick().y < 0)
		{
			if (x == 700)
				x = 500;
		}
		else if (p.getRightStick().y > 0)
		{
			if (x == 500)
				x = 700;
		}
		if (p.conButton(XINPUT_GAMEPAD_A) == true)
		{
			done = true;
			if (x == 500)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		FzlDrawSprite(menu3, 960, x, 0);
		FzlDrawSprite(menu4, 700, x, 0);
		FzlDrawSprite(menu1, 960, 700, 0);
		FzlDrawSprite(menu2, 960, 500, 0);
		FzlSwapBuffers();
	}
}