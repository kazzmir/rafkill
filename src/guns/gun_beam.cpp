#include "gunobj.h"
#include "defs.h"
#include "gun_beam.h"
// #include "spaceobj.h"

#include "weapons/weapon_beam.h"
#include "hulls/hull_weapon_beam.h"
#include <vector>

using namespace std;

WeaponBeam::WeaponBeam( int z, int d, int al ):
WeaponObject( d, "Beam", 36300, al, z, 6 ),
tear( 90 ),
length( 0 ),
fat( 20 ),
angle( 0 ) {
}


void WeaponBeam::Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	tear = 0;
}


void WeaponBeam::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 30;
	if ( tear > 0 ) {
		shot_counter = 0;
		tear--;
		length += 63;
		if( length > GRAPHICS_Y ) length = GRAPHICS_Y;
		fat--;
		if ( fat < 1 ) {
			fat = 1;
			tear = 0;
		}
	}
	else {
		tear = 90;
		length = 0;
		fat = 18+(strength+1)*3;
		return;
	}

	angle = (angle-17+360) % 360;
	Ammo->push_back( new Beam(x,y-length/2,0,0,1, new Beam_WHull((strength+1.0)*2.0,fat*2,length,angle), alignment ) );

}


WeaponObject * WeaponBeam::copy() {
	return new WeaponBeam( strength, dir, alignment );
}
