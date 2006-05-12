#include "gunobj.h"
#include "gun_shatter.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_shatter.h"
#include "weapons/weapon_shatter.h"
#include "defs.h"
#include <vector>

using namespace std;

WeaponShatter::WeaponShatter( int z, int d, int _smp, int al ):
WeaponObject( d, "Shatter Gun", 38000, al, z, 4 ) {
	smp = _smp;
}


WeaponObject * WeaponShatter::copy() {
	return new WeaponShatter( strength, dir, smp, alignment );
}


void WeaponShatter::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( smp != -1 ){
		Util::playSound( smp, 255 );
	}

	shot_counter = 10;

	Ammo->push_back( new Shatter(x,y,0,-2.1*8, new Shatter_WHull(6+strength*2), alignment, Ammo ) );

}
