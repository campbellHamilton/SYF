#ifndef WORLD_H
#define WORLD_H
#include "collision.h"
#include "tank.h"
#include "box.h"
#include <vector>
#include "drawTime.h"
#include "sprite.h"
#include "sound.h"
class Menu;
class World//should contain everything in our game (plan to eventually create another class called level that creates a world class)
{
public:
	World(int, int, int, modifierlist&, SpriteList*, SoundList*);
	~World();		

	Menu* pmenu = nullptr;
	void setPointer(Menu*);
	void resetlastbomber();
	Tank getrandomaliveplayer(int exception);
	Tank getrandomaliveplayer();
	DashShieldStatus p1status;
	DashShieldStatus p2status;
	DashShieldStatus p3status;
	DashShieldStatus p4status;

	Tank* p_1;//creates a player 1
	Tank* p_2;//creates a player 2
	Tank* p_3;//creates a player 3
	Tank* p_4;//creates a player 4

	drawTime splat;
	Tank* getplayer(int);
	//Controls players shooting.

	void playersShoot(bool);
	//Controls when players collide with bullets.
	void getCollision();//normal
	void getCollision(int);//aoe
	//controls when bullets collide
	bool bulletCollision(Tank*, Tank*, int bulletPlayer, int bulletEnemy);


	void getBulletCollsion();
	bool getasteroidsToggle() { return asteroidsToggle; }
	void flipasteroidsToggle();
	bool getbounceToggle() { return bounceToggle; };
	void flipbounceToggle();
	int getbulletSpeed() { return bulletSpeed; };
	int getaccelbulletSpeed() { return accelbulletSpeed; };
	int getplayers() const { return players; }
	int getDetection();
	void setDetection(int);

	bool death[4];

	void		setBulletDelay(int x);
	int			getBulletDelay();
	
	double		clip(double _n, double _lower, double _upper);
	Collision	collide(Tank * _t1, Box _b2);
	Collision	collide(Tank * _t1, Tank * _t2);
	Collision	collide(Box, Box);
	Box getWall(int index) { if (index < walls.size()) { return walls[index]; } };
	modifierlist *list;



	clock_t speedtime;//the time when "Speed Up!" was displayed
	bool drawspeedup = false; //true if the "SPEED UP" thing should be drawn to screen at end of frame
	void vibratehandler();
	void hudhandler();
	void dotphandler();
	Box bodies[4];
	FzlSpriteHandle * speedUpSprite;//created and deleted properly i think
	SpriteList* holder;

	bool playerTurn[4];
	int playerWait[4];

private:

	double vibrateduration = 0.25;
	//detects when a bullet hits the specified tank
	void collision(Tank*);
	void collision(Tank*, int);
	//detects when a player shoots there weapon
	bool shoot(Tank*, Tank*);
	//Return where bullets are
	Coords bulletPosition(int, Tank*);
	//number of players
	int players;
	//The speed the bullets travel at
	int bulletSpeed;
	int accelbulletSpeed = 1;
	//number of bullets a player can shoot
	int bulletLimit;
	//time between each bullet being fired.
	int bulletDelay;
	//state of the bullet bounce modifier
	bool bounceToggle = false;
	//State of the asteroids modifier
	bool asteroidsToggle = false;
	//Represents the players health
	std::vector<Box> walls;
	std::vector<Box> holes;
	std::vector<Box> bounds;
	int num = 0;

	int tankSize = 64;
	int detection;
};


#endif WORLD_H