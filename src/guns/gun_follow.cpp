#include "gunobj.h"
#include "gun_follow.h"
#include "weapons/weapon_follow.h"
#include "defs.h"
#include "spaceobj.h"
#include <vector>

WeaponFollow::WeaponFollow( int z, int d, int al ):
WeaponObject( d, "Tracker", 40000, al, z, 4 ) {
}


WeaponObject * WeaponFollow::copy() {
	return new WeaponFollow( strength, dir, alignment );
}


void WeaponFollow::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 12;

	if ( fight == NULL ) return;
	for ( int q = 0; q <= strength; q++ )
		Ammo->push_back( new Follow(x,y,90,fight,alignment, 10+strength*8 ) );

}
