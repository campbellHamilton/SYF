#ifndef SPRITE_H
#define SPRITE_H
#include "Fizzle\Fizzle.h"
#include <vector>

class SpriteList
{
public:
	SpriteList()
	{
		menu.push_back(FzlLoadSprite("Assets/Loading_Screen.png", 1920, 1080));							//0
		menu.push_back(FzlLoadSprite("Assets/Menus/2_Players.png", 1920, 1080));						//1
		menu.push_back(FzlLoadSprite("Assets/Menus/3_Players.png", 1920, 1080));						//2
		menu.push_back(FzlLoadSprite("Assets/Menus/4_Players.png", 1920, 1080));						//3
		menu.push_back(FzlLoadSprite("Assets/GUI/2_Player.png", 1920, 1080));							//4
		menu.push_back(FzlLoadSprite("Assets/GUI/3_Player.png", 1920, 1080));							//5
		menu.push_back(FzlLoadSprite("Assets/GUI/4_Player.png", 1920, 1080));							//6
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Bomb Mode.png", 1920, 1080));				//7
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Heart Mode.png", 1920, 1080));				//8
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/One Shot Mode.png", 1920, 1080));			//9
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Stock Mode.png", 1920, 1080));				//10
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Standard.png", 1920, 1080));				//11
		menu.push_back(FzlLoadSprite("Assets/Pause_Menu_Resume.png", 1920, 1080));						//12
		menu.push_back(FzlLoadSprite("Assets/Pause_Menu_Exit.png", 1920, 1080));						//13
		menu.push_back(FzlLoadSprite("Assets/SYF_Menu_Play.png", 1920, 1080));							//14
		menu.push_back(FzlLoadSprite("Assets/SYF_Menu_Credits.png", 1920, 1080));						//15
		menu.push_back(FzlLoadSprite("Assets/SYF_Menu_Exit.png", 1920, 1080));							//16
		menu.push_back(FzlLoadSprite("Assets/characters/Round Start.png", 1920, 1080));					//17
		menu.push_back(FzlLoadSprite("Assets/characters/numbers/Numbers Row.png", 90, 90));				//18
		menu.push_back(FzlLoadSprite("Assets/Speed_Up!.png", 1920, 1080));								//19
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Standard.png", 1920, 1080));			//20
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Bomb.png", 1920, 1080));				//21
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Hearts.png", 1920, 1080));				//22
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Stock.png", 1920, 1080));				//23
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_One_Shot.png", 1920, 1080));			//24
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Bomb Mode.png", 1920, 1080));				//25
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Heart Mode.png", 1920, 1080));				//27
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/One Shot Mode.png", 1920, 1080));			//28
		menu.push_back(FzlLoadSprite("Assets/Menus/gamemode/Stock Mode.png", 1920, 1080));				//29																							  
		menu.push_back(FzlLoadSprite("Assets/modifiers/Modifier Menu Base.png", 1920, 1080));			//30
		menu.push_back(FzlLoadSprite("Assets/modifiers/Continue Selected.png", 1920, 1080));			//31
		menu.push_back(FzlLoadSprite("Assets/modifiers/Modifier Menu Highlight.png", 1920, 1080));		//32
		menu.push_back(FzlLoadSprite("Assets/modifiers/Modifier Menu Select.png", 1920, 1080));			//33
		menu.push_back(FzlLoadSprite("Assets/modifiers/Modifier Menu Text.png", 1920, 1080));			//34
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Shield.png", 1920, 1080));				//35
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Time_will_tell.png", 1920, 1080));		//36
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Ricochet.png", 1920, 1080));			//37
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Dash.png", 1920, 1080));				//38
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_AOE.png", 1920, 1080));					//39
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Charge.png", 1920, 1080));				//40
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Melee.png", 1920, 1080));				//41
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Deaths_of_the_Past.png", 1920, 1080));	//42
		menu.push_back(FzlLoadSprite("Assets/tutorials/Tutorial_Acceleration.png", 1920, 1080));		//43
		menu.push_back(FzlLoadSprite("Assets/HUD/clock background.png", 1920, 1080));					//48
		menu.push_back(FzlLoadSprite("Assets/HUD/Player_1_Bomb.png", 1920, 1080));						//49
		menu.push_back(FzlLoadSprite("Assets/HUD/Player_2_Bomb.png", 1920, 1080));						//51
		menu.push_back(FzlLoadSprite("Assets/HUD/Player_3_Bomb.png", 1920, 1080));						//52
		menu.push_back(FzlLoadSprite("Assets/HUD/Player_4_Bomb.png", 1920, 1080));						//53
		menu.push_back(FzlLoadSprite("Assets/tutorials/Controls.png", 1920, 1080));						//57
		menu.push_back(FzlLoadSprite("Assets/tutorials/Map_basic.png", 1920, 1080));					//58
		menu.push_back(FzlLoadSprite("Assets/tutorials/Map_Ice.png", 1920, 1080));						//59
		menu.push_back(FzlLoadSprite("Assets/tutorials/Map_Jungle.png", 1920, 1080));					//60
		menu.push_back(FzlLoadSprite("Assets/tutorials/Map_Desert.png", 1920, 1080));					//61
		menu.push_back(FzlLoadSprite("Assets/tutorials/Map_Island.png", 1920, 1080));					//62
		menu.push_back(FzlLoadSprite("Assets/Credits.png", 1920, 1080));								//63

		menu.push_back(FzlLoadSprite("Assets/2 Player/2 Player 1 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/2 Player/2 Player 2 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/3 Player/3 Player 1 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/3 Player/3 Player 2 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/3 Player/3 Player 3 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/4 Player/4 Player 1 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/4 Player/4 Player 2 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/4 Player/4 Player 3 Win.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/4 Player/4 Player 4 Win.png", 1920, 1080));

		menu.push_back(FzlLoadSprite("Assets/Kills/2 Skulls Score.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/Kills/3 Skulls Score.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/Kills/4 Skulls Score.png", 1920, 1080));

		menu.push_back(FzlLoadSprite("Assets/2nd_Place.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/3rd_Place.png", 1920, 1080));
		menu.push_back(FzlLoadSprite("Assets/4th_Place.png", 1920, 1080));



		tank.push_back(FzlLoadSprite("Assets/tank/SplatterRed.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/dgr.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/Red_Bullet.png", 41, 41));
		tank.push_back(FzlLoadSprite("Assets/Character_Sprites_Animation_Red.png", 88, 88));//creates the tank image
		tank.push_back(FzlLoadSprite("Assets/tank/aoered.png", 200, 200));
		tank.push_back(FzlLoadSprite("Assets/tank/SplatterBlue.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/dgb.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/Blue_Bullet.png", 41, 41));
		tank.push_back(FzlLoadSprite("Assets/Character_Sprites_Animation_Blue.png", 88, 88));//creates the tank image
		tank.push_back(FzlLoadSprite("Assets/tank/aoeblue.png", 200, 200));
		tank.push_back(FzlLoadSprite("Assets/tank/SplatterYellow.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/dgy.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/Yellow_Bullet.png", 41, 41));
		tank.push_back(FzlLoadSprite("Assets/Character_Sprites_Animation_Yellow.png", 88, 88));//creates the tank image
		tank.push_back(FzlLoadSprite("Assets/tank/aoeyellow.png", 200, 200));
		tank.push_back(FzlLoadSprite("Assets/tank/SplatterGreen.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/dgg.png", 88, 88));
		tank.push_back(FzlLoadSprite("Assets/tank/Green_Bullet.png", 41, 41));
		tank.push_back(FzlLoadSprite("Assets/Character_Sprites_Animation_Green.png", 88, 88));//creates the tank image
		tank.push_back(FzlLoadSprite("Assets/tank/aoegreen.png", 200, 200));
		tank.push_back(FzlLoadSprite("Assets/tank/Standard_Mode_Point_Feedback.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/tank/Melee_Feedback.png", 100, 100));
		tank.push_back(FzlLoadSprite("Assets/tank/Shield_CD_Feedback.png", 100, 100));
		tank.push_back(FzlLoadSprite("Assets/tank/1_Heart_Left.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/tank/2_Hearts_Left.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/tank/Heart_Loss_Feedback.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/tank/Bullet_Gain_Feedback.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/tank/Bomb_Mode_Feedback.png", 130, 130));
		tank.push_back(FzlLoadSprite("Assets/unimplimented/Charge_Feedback.png", 110, 110));

		world.push_back(FzlLoadSprite("Assets/Menus/Tutorial_Selected.png", 1920, 1080));//0
		world.push_back(FzlLoadSprite("Assets/Menus/Ice_Selected.png", 1920, 1080));	 //1
		world.push_back(FzlLoadSprite("Assets/Menus/Jungle_Selected.png", 1920, 1080));	 //2
		world.push_back(FzlLoadSprite("Assets/Menus/Desert_Selected.png", 1920, 1080));	 //3
		world.push_back(FzlLoadSprite("Assets/Menus/Island_Selected.png", 1920, 1080));	 //4
		world.push_back(FzlLoadSprite("Assets/Maps/Prototype_Map_1_Top_Layer.png", 1920, 1080));		 //5
		world.push_back(FzlLoadSprite("Assets/Maps/Prototype_Map_1_Bottom_Layer.png", 1920, 1080));		 //6
		world.push_back(FzlLoadSprite("Assets/Maps/Ice_Map_1_Top_Layer.png", 1920, 1080));				 //7
		world.push_back(FzlLoadSprite("Assets/Maps/Ice_Map_1_Bottom_Layer.png", 1920, 1080));			 //8
		world.push_back(FzlLoadSprite("Assets/Maps/Ice_Map_2_Top_Layer.png", 1920, 1080));				 //9
		world.push_back(FzlLoadSprite("Assets/Maps/Ice_Map_2_Bottom_Layer.png", 1920, 1080));			 //10
		world.push_back(FzlLoadSprite("Assets/map.png", 1920, 1080));									 //11
		world.push_back(FzlLoadSprite("Assets/Prototype_Map_Collision_with_Background.png", 1920, 1080));//12
		world.push_back(FzlLoadSprite("Assets/Maps/Desert_Map_1_Top_Layer.png", 1920, 1080));			 //13
		world.push_back(FzlLoadSprite("Assets/Maps/Desert_Map_1_Bottom_Layer.png", 1920, 1080));		 //14
		world.push_back(FzlLoadSprite("Assets/Maps/Island_Map_1_Top_Layer.png", 1920, 1080));			 //15
		world.push_back(FzlLoadSprite("Assets/Maps/Island_Map_1_Bottom_Layer.png", 1920, 1080));		 //16
		world.push_back(FzlLoadSprite("Assets/Maps/Island_Map_2_Top_Layer.png", 1920, 1080));		 //17
		world.push_back(FzlLoadSprite("Assets/Maps/Island_Map_2_Bottom_Layer.png", 1920, 1080));		 //18
		world.push_back(FzlLoadSprite("Assets/Maps/Desert_Map_2_Top_Layer.png", 1920, 1080));			 //19
		world.push_back(FzlLoadSprite("Assets/Maps/Desert_Map_2_Bottom_Layer.png", 1920, 1080));		 //20
		world.push_back(FzlLoadSprite("Assets/Maps/Jungle Map 1 Bottom Layer.png", 1920, 1080));
		world.push_back(FzlLoadSprite("Assets/Maps/Jungle Map 1 Top Layer.png", 1920, 1080));
	}
	std::vector<FzlSpriteHandle> world;
	std::vector<FzlSpriteHandle> menu;
	std::vector<FzlSpriteHandle> tank;

};
// menu
//

enum world
{
	map1,
	map2,
	map3,
	map4,
	map5,
	tut1b,
	tut1t,
	ice1b,
	ice1t,
	ice2b,
	ice2t,
	pro1b,
	pro1t,
	des1b,
	des1t,
	isl1b,
	isl1t,
	jungback,
	jungfront
};

enum menu
{
	loadscreen,
	player2,
	player3,
	player4,
	gui1,
	gui2,
	gui3,
	bombscreen,
	heartscreen,
	oneShotscreen,
	pudding,
	standard,
	paused,
	paused2,
	menu1,
	menu2,
	menu3,
	roundStarting,
	numbers,
	speedUpSprite,
	standardtut,
	bombtut,
	hearttut,
	stocktut,
	oneshottut,
	bomb,
	heart,
	oneshot,
	stock,
	modifiermenubase,
	continuehighlight,
	menuhighlight,
	menuselect,
	menutext,
	tutorialshield,
	tutorialtwt,
	tutorialricochet,
	tutorialdash,
	tutorialaoe,
	tutorialcharge,
	tutorialmelee,
	tutorialdotp,
	tutorialacceleration,
	clockbackground,
	p1bomb,
	p2bomb,
	p3bomb,
	p4bomb,
	controltut,
	tutorialbasic,
	tutorialice,
	tutorialjungle,
	tutorialdesert,
	tutorialisland,
	credits,
	Player12,
	Player22,
	Player13,
	Player23,
	Player33,
	Player14,
	Player24,
	Player34,
	Player44,
	SkullsScore2,
	SkullsScore3,
	SkullsScore4,
	Place2,
	Place3,
	Place4,

};

enum tank
{
	p1splat,
	p1die,
	p1bulletImage,
	p1staticTank,
	p1aoe,
	p2splat,
	p2die,
	p2bulletImage,
	p2staticTank,
	p2aoe,
	p3splat,
	p3die,
	p3bulletImage,
	p3staticTank,
	p3aoe,
	p4splat,
	p4die,
	p4bulletImage,
	p4staticTank,
	p4aoe,
	points,
	melee,
	bubble,
	heart1,
	heart2,
	heartloss,
	bulletgain,
	bombfeedback,
	charge

};

#endif

