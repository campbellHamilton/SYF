#ifndef SOUND_H
#define SOUND_H
#include "Fizzle\Fizzle.h"
#include <vector>

class SoundList
{
public:
	std::vector<FzlSpriteHandle> sworld;
	std::vector<FzlSpriteHandle> smenu;
	std::vector<FzlSpriteHandle> stank;
	SoundList()
	{
		stank.push_back(FzlLoadSound("Sound/BaseShot.wav", 0));//done
		stank.push_back(FzlLoadSound("Sound/AltBaseShot.wav", 0));//done
		stank.push_back(FzlLoadSound("Sound/Modifer/playerShield.wav", 0));//done
		stank.push_back(FzlLoadSound("Sound/Modifer/playerDash.wav", 0));//DONE
		stank.push_back(FzlLoadSound("Sound/player_Hit.wav", 0));//
		stank.push_back(FzlLoadSound("Sound/Modifer/aoeShot.wav", 0));			//done
		stank.push_back(FzlLoadSound("Sound/Modifer/chargeInterrupt.wav", 0));	//
		stank.push_back(FzlLoadSound("Sound/Modifer/speedUp.wav", 0));			//done
		stank.push_back(FzlLoadSound("Sound/Modifer/shotAccel.wav", 0));		//
		sworld.push_back(FzlLoadSound("Sound/Mode/bombEnd.wav", 0)); //done
		sworld.push_back(FzlLoadSound("Sound/Mode/lifeLost.wav", 0));//done(?)
		smenu.push_back(FzlLoadSound("Sound/iceWorld.wav", 1));//
		sworld.push_back(FzlLoadSound("Sound/gm_Adventure.wav", 1));
		sworld.push_back(FzlLoadSound("Sound/gm_CanCan.wav", 1));
		sworld.push_back(FzlLoadSound("Sound/gm_Cheeky.wav", 1));
		sworld.push_back(FzlLoadSound("Sound/gm_Hectic.wav", 1));
	}

	
};

enum soundTank
{
	fire,
	fire2,
	shieldS,
	dashS,
	playerHit,
	aoeShot,
	chargeI,
	speedUp,
	shotAccel,


};

enum soundMenu
{
	menumusic
};

enum soundWorld
{
	bombExplode,
	lifeLost,
	song1,
	song2,
	song3,
	song4
	
};
#endif