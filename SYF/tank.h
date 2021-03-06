#ifndef TANK_H
#define TANK_H
#include "controller.h"
#include "bullet.h"
#include "layer.h"
#include <vector>
#include "collision.h"
#include "modifierlist.h"
#include <ctime>
#include "sprite.h"
#include "controller.h"
#include "sound.h"
class World;
struct DashShieldStatus;
struct Proximity;
enum Options { Y, X, Intersection, XandY, XorY };
class Tank
{
public:
	Tank();
	bool rtheld = false;
	bool rtheldlast = false;
	clock_t rttime;
	int controllernumber;
	bool hasbullet = true;
	bool greyshield = false;
	bool greydash = false;
	bool lethalspeed = false;
	bool hasbomb = false;
	bool lastbomber = false;
	void setlastbomber(){ lastbomber = true; }
	void giveBomb() { this->hasbomb = true; }

	Tank(int, int, int, int, bool, int, bool, modifierlist&, SpriteList*, SoundList*);
	void setPointer(World*);
	~Tank();
	//Accessors
	int getH() { return health; };
	double getX() { return tankPos.getx(); };
	double getY() { return tankPos.gety(); };
	double* getXP() { return tankPos.getxp(); };
	double* getYP() { return tankPos.getyp(); };
	controller getcontrollerstatus(int);
	float getA() { return tankAngle; };
	float getAT() { return turretAngle; };
	controller* getEnemy(bool type);//used to get the opposite players controller.
	void changeHealth(int x) 
	{ 
		this->health += x; 
	};
	int getOffset() const { return offset; };
	vect<double>* getVelocity() { return &velocity; };

	//Member Functions
	void inertialMove(); // updates position of tank following inertia.
	void movement(int, double, World*, layer* temp);//used to control the movement
	void turretMovement(bool);//used to rotate turret. (want to modifiy the controls for this)
	void rotation(int);//controls the tanks rotation (only for tank movement scheme)
	bool snowCheck(); // checks whether we are on snow or ice
	bool waterCheck();
	void bulletMovement(bool bounceToggle, int bulletSpeed, layer* temp);

	std::vector<Bullet> shot;// makes a bullet. will be made into a vector for multiple bullet support

	void setPos(int, int);

	float getvelocityX() const { return velocity.getx(); };
	float getvelocityY() const { return velocity.gety(); };

	controller * playerNumber;
	controller * playerNumber2;
	double getbuoyancy() const { return buoyancy; }
	void setbuoyancy(double _b) { buoyancy = _b; }
	void setDirection();
	//switch the three below variables to getters and setters at somepoint
	int dir;
	int spriteSpot;
	int up;//controls the players animation state.
	
	bool positionLegality(double _x, double _y);
	void map8();//island 2
	void map7();
	void map6();
	void map3();
	void map2();
	void map();
	Box getBox(int, int);

	void deleteSprites();
	void layering(layer* temp);

	int getRadius()const { return tankSize / 2; }
	void settopSpeed(float _f) { topSpeed = _f; }
	float gettopSpeed() const { return topSpeed; }

	void updateVelocity(vect<double> velocity);

	void setacceleration(float _a) { acceleration = _a; }
	float getacceleration() const { return acceleration; }

	float getvelocitymagnitude() { return velocity.magnitude(); };

	void shielded();
	void dashed();
	void melee();
	bool shieldOn;//controls when the shield is on and off
	bool dashOn;
	bool meleeOn;
	FzlSpriteHandle* splat;
	FzlSpriteHandle* bubble;
	FzlSpriteHandle* die;
	FzlSpriteHandle* bulletImage;
	FzlSpriteHandle* aoe;
	FzlSpriteHandle* staticTank;
	SoundList* sounds;
	bool soundFire;
	int spriteSpot2;
	bool cornerintersect(double, double);
	void setHealth(int);

	void playerCollision();
	
	bool ismeleeing;
	time_t  deathTime;
	time_t  deathStart;
	time_t stunStart = 0;
	int deathSpot;
	void vibrate(double, double);
	bool startvibrate;
	clock_t vibrateend;

	void map4();
	void map5();
	time_t timeWillTell;
	Box bodies[4];
	vect<double> tankPos;

	int playerID;
	bool shield;//controls the shielf if and else

	int points;
	bool stun = false;
	bool iamdead;
	bool meleed = false;
private:
	
	SpriteList *holder;

	bool dashSetter;
	bool meleeSetter;

	float TWTS;//time will tell slow

	bool isdashing;
	
	time_t shieldTime;
	time_t dashTime;
	time_t meleeTime;
	World *world;
	modifierlist *list;
	Box hitbox;
	double buoyancy = 0.8;
	float tankAngle;
	float turretAngle;
	int velocityMulty;

	

	vect<double> velocity;
	vect<double> lastvelocity;

	float acceleration=5;
	float topSpeed = 300;
	float velocitymagnitude;
	//float lastvelocitymagnitude;
	Proximity proximityCheck();
	Collision wallCollision(World*);
	bool bulletWallCollision(int, int);
	std::vector<Box> walls;
	std::vector<Box> holes;
	std::vector<Box> bounds;
	bool ice = false;
	bool watery = false;
	std::vector<Box> snow;
	std::vector<Box> water;

	int health;
	int playerSpeed;

	int offset;
	int tankSize;



};
struct Proximity
{
public:
	std::vector<int> holes;
	std::vector<int> walls;
	std::vector<int> bounds;
};
struct DashShieldStatus
{
public:
	bool greydash;
	bool ungreydash;
	bool greyshield;
	bool ungreyshield;
	void operator=(bool status);
};

#endif TANK_H