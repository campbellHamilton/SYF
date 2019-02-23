// The MIT License (MIT)
// 
// Copyright (c) 2016 Anastasios Stamadianos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.



#include <iostream>
#include "menu.h"
#include "Fizzle\Fizzle.h"
#include "GameState.h"
#include "layer.h"
#include "sprite.h"
#include "sound.h"


void wait();
void wait(int);
void timer(int, FzlSpriteHandle);

bool fs = false;//full screen

class MainMenu : public GameState//creates a child of the game state class.
{
public:
	MainMenu(Menu &points)
	{
		main_menu = &points;
	}
	void Update()//same as above
	{
		int temp = 0;
		bool done = false;
		while (temp >= 0)
		{
			switch (temp)
			{
			case 0:
				temp = main_menu->mainMenu();

				break;
			case 1:
				temp = main_menu->setPlayerAmnt();
				break;
			case 2:
				temp = main_menu->setGameMode();
				break;
			case 3:
				temp = main_menu->modifiers();
				break;
			case 4:
				temp = main_menu->mapSelect();
				break;
			case 5:
				done = true;
				temp = -5;
				FzlStopSound(main_menu->sounds->smenu[menumusic]);
				break;

			}
		}
		if (done == true)
		{
			m_parent->getGameState("Round")->SetPaused(false);
			m_parent->getGameState("Pause")->SetPaused(false);
			SetPaused(true);
			main_menu->rounds(3);
		}
		else if (temp == -3)
		{
			SetPaused(true);
			main_menu->quit();
		}
	}
private:
	SpriteList* list;
	Menu *main_menu;
};

class Round : public GameState//same as above
{
public:
	Round(Menu &points, SpriteList list)
	{
		round = &points;
		rounds = 0;
		for (int count = 0; count <= 3; count++)
			scores[count] = 0;

		roundCount = 3;
		map = true;


	}
	void Update()//same as above
	{

		int temp;
		temp = round->game();
		if (temp > 0)
		{
			//5 is the play again
			//6 is the go back to menu
			if (temp == 5)
			{
				switch (round->song)
				{
				case 0:
					FzlStopSound(round->sounds->sworld[soundWorld::song1]);
					break;
				case 1:
					FzlStopSound(round->sounds->sworld[soundWorld::song2]);
					break;
				case 2:
					FzlStopSound(round->sounds->sworld[soundWorld::song3]);
					break;
				case 3:
					FzlStopSound(round->sounds->sworld[soundWorld::song4]);
					break;

				}
				round->reset();
				round->setMap(round->mapSelected);
			}
			if (temp == 6)
			{
				switch (round->song)
				{
				case 0:
					FzlStopSound(round->sounds->sworld[soundWorld::song1]);
					break;
				case 1:
					FzlStopSound(round->sounds->sworld[soundWorld::song2]);
					break;
				case 2:
					FzlStopSound(round->sounds->sworld[soundWorld::song3]);
					break;
				case 3:
					FzlStopSound(round->sounds->sworld[soundWorld::song4]);
					break;

				}
				SetPaused(true);//paused the first level
				m_parent->getGameState("MainMenu")->SetPaused(false);
			}

			//rounds++;
			//round->reset();
			//round->arena->setPointer(round);
			//int randomnum = rand() % round->playerAmnt;
			//round->arena->getplayer(randomnum)->giveBomb();
			//round->timeMax = 60;
			//round->time = round->timeMax;
			//if (round->selection.modifiers[modifierlist::standard] == true)
			//	round->timeMax = 120;
			//if (round->selection.modifiers[modifierlist::bomb] == true)
			//	round->timeMax = 60;
			//if (round->selection.modifiers[modifierlist::stock] == true)//last man standing
			//	round->timeMax = 180;
			//round->time = round->timeMax;
			//round->setsecondbomber();
			//round->setMap(round->mapSelected);
		}
		else
		{
			if (round->frametimes.empty())
			{
				round->initframetimes();
			}
			round->normalShot();
			round->setLayers();
		}

	};

private:
	int scores[4];
	int rounds;
	Menu *round;
	int roundCount;
	bool map;
};

class Pause : public GameState//creates a child of the game state class.
{
public:
	Pause(Menu &points, SpriteList list)
	{
		pause = &points;
	}
	void Update()//same as above
	{
		int temp = pause->pause();
		if (temp == 1)
		{
			pause->setMap(pause->mapSelected);
			m_parent->getGameState("MainMenu")->SetPaused(false);
			m_parent->getGameState("Round")->SetPaused(true);
			SetPaused(true);
		}

		//SetPaused(true);
	}
private:
	Menu *pause;
};
class Fullscreen : public GameState//used to switch from fullscreen to windowed. at the moment this can not be implemented. game would need to restart
{
public:
	Fullscreen(Menu &points)
	{
		fullScreen = &points;
	}
	void Update()//same as above
	{

		if (FzlGetKey(FzlKeyEscape) == 0)
		{
		}
		//SetPaused(true);
	}
private:
	Menu *fullScreen;
};


int main()
{

	srand(time(NULL));
	//these variables should be thrown in the world class.
	const int windowWidth = 1920; //Replace this with a command to get screen resoltion
	const int windowHeight = 1080;//Replace this with a command to get screen resoltion
	FzlInit("SYF", windowWidth, windowHeight, 0);//initializes the fzzle window.

	bool check = true;
	FzlSpriteHandle loadingscreen = FzlLoadSprite("Assets/Loading_Screen.png", 1920, 1080);
	FzlDrawSprite(loadingscreen, 960, 540, 0);
	FzlSwapBuffers();
	SpriteList holder; // holds the handles to all of the sprites;
	SoundList sounds;


	FzlDeleteSprite(loadingscreen);

	Menu choice(holder, sounds);





	while (choice.getOn() == true)
	{
		//manager
		GameStateManager manager;
		//game state
		//GameState* mainMenu;
		MainMenu* mainMenu = new MainMenu(choice);//creates pointer to a game state and creates an object of the game state class
		Round* round = new Round(choice, holder); //creates pointer to a game state and creates an object of the game state class
		Pause* pause = new Pause(choice, holder);
		Fullscreen* fullscreen = new Fullscreen(choice);

		manager.addGameState("Fullscreen", fullscreen);
		manager.addGameState("MainMenu", mainMenu);//adds the game state to the manager
		manager.addGameState("Round", round);//adds the game state to the manager
		manager.addGameState("Pause", pause);//adds the game state to the manager

		fullscreen->SetPaused(true);
		round->SetPaused(true);//paused the first level
		pause->SetPaused(true);//paused the first level

		while (choice.getOn() == true && fs != check)
		{
			manager.update();
		}
		FzlDestroy();

	}
	return 0;
}




//game state manager, controls what state where in
//game state what states the game can be in.