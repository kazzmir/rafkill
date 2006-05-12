#include "gunobj.h"
#include "gun_minimissle.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_mini.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

WeaponMiniMissle::WeaponMiniMissle( int z, int d, int al ):
WeaponObject( d, "MiniMissile", 31000, al, z, 4 ) {
}


WeaponObject * WeaponMiniMissle::copy() {
	return new WeaponMiniMissle( strength, dir, alignment );
}


void WeaponMiniMissle::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	// #define ___sp 2.55
	const double speed = 2.55 * 8;
	int wide = 0;

	shot_counter = 3;
	switch( strength ) {

		case 0  :       shot_counter = 3; break;
		case 1  :       shot_counter = 3; break;
		case 2  :       shot_counter = 3; break;
		case 3  :       shot_counter = 2; break;
		case 4  :       shot_counter = 2; break;

	}

	for ( int q = 0; q <= strength*3/2; q++ ) {

		wide = (5 + q * 5) * ( q > 0 );
		Ammo->push_back( new WeaponNode(x-9,y,Tcos(90-wide)*speed,Tsine(90-wide)*speed, new Mini_WHull(), alignment ) );
		Ammo->push_back( new WeaponNode(x+10,y,Tcos(90+wide)*speed,Tsine(90+wide)*speed, new Mini_WHull(), alignment ) );

	}
}
