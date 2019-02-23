#ifndef MENU_H
#define MENU_H
#include "tank.h"
#include "world.h"
#include <deque>
#include <ctime>
#include "sprite.h"
#include "modifierlist.h"
#include "sound.h"
class World; //forward declaration so we can pass a world object, so we can call world collision functions.
class Menu
{
public:
	Menu(SpriteList&, SoundList&);
	~Menu();
	void setsecondbomber();
	void changetime(int t){ time += t; }
	int gettime() const { return time; }
	int whohasbomb();
	Tank* getlastbomber();
	int getliveplayers();
	int game();
	int mainMenu();
	int setPlayerAmnt();//sets how many players are playing
	int setGameMode();//sets the game mode
	void reset();//resets the players to the start points
	int pause();//controls the 
	void quit();//quits the game
	bool getOn();//returns the state of the game.
	void normalShot();
	void lazerShot();
	void setLayers();
	void setMap(int);
	std::deque <double> frametimes;
	double frametimestotal;
	void initframetimes();
	void addframetime(double);
	double getframetimeEstimate() { return frametimestotal / 60; }
	void deletion();
	int getTime();
	clock_t framestart;
	clock_t frameend;
	int mapSelect();
	void rounds(int);
	int modifiers();
	int mapSelected;
	void initilizeModifiers();
	void timer(int& time, FzlSpriteHandle numbers);
	void deleteSprites();
	World *arena;
	int time;
	int timeMax;
	modifierlist selection;
	int playerAmnt;
	int song;
	clock_t roundover = 0;
	void direction(Tank*, int);

	FzlSpriteHandle* mapP;
	FzlSpriteHandle* tempP;
	layer layers;

	bool gameOver;//used to signifiy when someone wins
	bool gameDone;//used to signifiy when the round should end.

	SoundList* sounds;

private:
	SpriteList *holder;

	clock_t timing;
	//FzlSpriteHandle clockbackground = FzlLoadSprite("Assets/HUD/clock background.png", 1920, 1080);
	FzlSpriteHandle mapMods1;
	FzlSpriteHandle playerMods1;
	FzlSpriteHandle projectileMods1;
	FzlSpriteHandle* gui;//?


	void moveTank(Tank*, double, World*);
	bool tankAABB(Tank*, Tank*);
	bool tankAABC(Tank*, Tank*);
	void tankCollision(int);
	void tankBounce(Tank*, Tank*);
	bool on;// controls whether the game is running or not.
	int animation;
	bool inversion;
	int shootWait;
	void wait();
	void wait(double);
	int movement;//this controls what movement scheme where using
	int tankSize;
	
	int frame;
	
};

#endif