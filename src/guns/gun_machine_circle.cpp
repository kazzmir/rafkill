#include "gunobj.h"
#include "gun_machine_circle.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_machine.h"
#include "trigtable.h"

// #define d_circle_move (2.9*8)

WeaponMachineCircleGun::WeaponMachineCircleGun( int z, int d, int _smp, int al ):
WeaponObject( d, "Radix Gun", 25000, al, z, 4 ),
angle( 0 ) {
	smp = _smp;
}


WeaponObject * WeaponMachineCircleGun::copy() {
	return new WeaponMachineCircleGun( strength, dir, smp, alignment );
}


void WeaponMachineCircleGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	if ( smp != -1 ){
		Util::playSound( smp, 255 );
	}

	shot_counter = 1;
	angle = (angle + 20 ) % 360;

	const double d_circle_move = 2.9 * 8;

	for ( int q = -(30+strength*2); q < 30+strength*2; q += 7-strength ) {

		int ra = ( angle + q + 360 ) % 360;
		int bul;
		if ( q != 0 )
			bul = (strength+1)*11 / abs( q );
		else bul = 3;

		if ( bul > 3 ) bul = 3;
		if ( bul < 1 ) bul = 1;
		Ammo->push_back( new WeaponNode(x,y,Tcos(ra)*d_circle_move,Tsine(ra)*d_circle_move, new Machine_WHull(bul), alignment ) );

	}

}
