#ifndef _menu_h
#define _menu_h

#include <vector>

#include "bitmap.h"

using namespace std;

class WeaponObject;
class SpaceObject;
class RMenu;
class RMenuAnimation;
class Font;
class HullObject;
class Animation;
class ECollide;
class Music;

#define GUN_MACHINE 0
#define GUN_BEAM 1
#define GUN_MINIMISSLE 2
#define GUN_FINDGUN 3
#define GUN_PULSE 4
#define GUN_LASER 5
#define GUN_MISSLE 6
#define GUN_FOLLOW 7
#define GUN_ARC 8
#define GUN_MACHINE_CIRCLE 9
#define GUN_CHAIN 10
#define GUN_CHAIN_FIRE 11
#define GUN_SHATTER 12
#define GUN_SWIRL 13
#define GUN_SPREAD 14
#define GUN_MASSIVE 15
#define GUN_SABER 16
#define GUN_ANGLE 17
#define GUN_TRACTOR 18
#define GUN_ROTATE 19
#define GUN_STICKY 20
#define GUN_YEHAT 21

struct gunPlace{
	int * gunz;
	int mgun;
};

class menuClass{
public:

	menuClass();
	~menuClass();

	bool activate( SpaceObject * player );

private:

	int sellGun( WeaponObject * gun );
	int upgradeCost( WeaponObject * gun );
	int upgradeHelper( int worth, int lev );
	int hull_price( int z );
	void vectorAdd( vector< SpaceObject * > * stable, vector< SpaceObject * > * state );

	char * getFileInfo( int number );

	//RMenuAnimation * GunMenu( int q, WeaponObject * current, BITMAP * intr, int score );
	void GunMenu( RMenu * weap, int q, WeaponObject * current, const Bitmap & intr, int score );
	void GetHullMenu( RMenu * hull_menu, SpaceObject * human, const Bitmap & intr );
	void GetAccessoryMenu( RMenu * weap, WeaponObject ** a_list, const Bitmap & intr, int score );

	void getSaveMenu( RMenu * save_menu );
	void weaponMenu( RMenu * gun_menu, SpaceObject * player );
	SpaceObject * copySpace( SpaceObject * player );
	WeaponObject * GetWeapon( int q );
	Bitmap menuScreen();
	HullObject * playerHull( int q );
	void getAnimation( Animation * hold, SpaceObject * player, vector< SpaceObject * > * ammo, vector< SpaceObject * > * enemy );
	bool accept_sell();

	gunPlace pgun[ 5 ]; //regular guns
	gunPlace agun;	//accessory guns
	// DATAFILE * data;
	// RFont * menu_font;
	Animation * player_animate;

public:
	static ECollide ** gun_sticky_collide_list;
	static int gun_sticky_max_collide;

private:
	Font * menuFont;
	
};

#endif
