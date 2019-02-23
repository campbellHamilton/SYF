#include "controller.h"
#include "bullet.h"
#include <vector>
class Tank
{
public:
	Tank();
	Tank(int, int, int);

	//Accessors

	double getX(){ return tankPosX; };
	double getY(){ return tankPosY; };
	float getA(){ return tankAngle; };
	float getAT(){ return turretAngle; };

	controller* getEnemy(bool type);//used to get the opposite players controller.

	int getBullet(){ return bulletFired; };
	void flipBullet(){ bulletFired++; };
	bool playAgain();

	//Member Functions

	void movement(int);//used to control the movement
	void turretMovement();//used to rotate turret. (want to modifiy the controls for this)
	void rotation(int);//controls the tanks rotation (only for tank movement scheme)

	void bulletMovement(bool bounceToggle, int bulletSpeed);//controls the bullets movement

	std::vector<Bullet> shot;// makes a bullet. will be made into a vector for multiple bullet support

private:
	int bulletFired;//whether a bullet has been fired or yet. will be changed to int evntually to allow for multiple bullets to be fired.
	
	float tankAngle;
	float turretAngle;

	double tankPosX;
	double tankPosY;

	double velocityX;
	double velocityY;

	int acceleration;

	int playerSpeed;
	controller * playerNumber;
	controller * playerNumber2;
	
};