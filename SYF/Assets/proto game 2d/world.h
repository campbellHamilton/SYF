#include "tank.h"
#include "bullet.h"
class World//should contain everything in our game (plan to eventually create another class called level that creates a world class)
{
public:
	World();

	Tank p1;//creates a player 1
	Tank p2;//creates a player 2
	Tank p3;//creates a player 3 not implemented in functions yet.
	Tank p4;//creates a player 4 not implemented in functions yet.
	int getbulletSpeed() { return bulletSpeed; }

	//Controls players shooting.
	void playersShoot();
	//Controls when players collide with bullets.
	bool getCollision();
private:
	//detects when a bullet hits the specified tank
	bool collision(Tank*, Tank*);
	//detects when a player shoots there weapon
	bool shoot(Tank*, Tank*);
	//number of players
	int players;
	//The speed the bullets travel at
	int bulletSpeed;
	//number of bullets a player can shoot
	int bulletLimit;
	int num = 0;
	bool player1=false;
	bool player2=false;
	int player1Wait = 0;
	int player2Wait = 0;
};