#pragma once
struct modifierlist
{
	modifierlist()
	{
		for (int count = 0; count < 16; count++)
			modifiers[count] = false;
	}

	bool modifiers[18];
	enum index
	{
		standard, bomb, hearts, stock, oneshot, highrise, timewilltell, deathsofthepast, powerups, shield, dash, charge, melee, aoe, ricochet, railgun, bulletacceleration,
	};
	void operator=(bool arg)
	{
		for (int count = 0; count < 18; count++)
			modifiers[count] = arg;
	}
};
