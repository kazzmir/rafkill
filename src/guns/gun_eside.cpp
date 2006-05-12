#include "gunobj.h"
#include "gun_eside.h"

#include "weaponobj.h"
#include "hulls/hull_weapon_s_l.h"

#include "trigtable.h"

EnemySide::EnemySide( int d, int al ):
WeaponObject( d, "Side", 0, al, 0, 0 ){}

void EnemySide::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 25;

	const double LARGE_BULLET = 1.6 * 8;
	double dx = Tcos(270-25)*LARGE_BULLET;
	double dy = Tsine(270-25)*LARGE_BULLET;

	Ammo->push_back( new WeaponNode(x+5,y,dx,dy, new SL_WHull(), alignment ) );

	dx = Tcos(270+25)*LARGE_BULLET;
	dy = Tsine(270+25)*LARGE_BULLET;

	Ammo->push_back( new WeaponNode(x-5,y,dx,dy, new SL_WHull(), alignment ) );

}
