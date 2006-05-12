#include "gunobj.h"
#include "gun_rotate.h"
#include "trigtable.h"
#include "ebox.h"
#include "spaceobj.h"
#include "defs.h"
#include "weapons/weapon_rotate.h"
#include "hulls/hull_weapon_rotate.h"

WeaponRotateGun::WeaponRotateGun( int z, int d, int _smp, int al ):
WeaponObject( d, "Rotate Gun", 250000, al, z, 4 ) {
	smp = _smp;

	angX = Util::rnd( 360 );
	angY = Util::rnd( 360 );
	dX = (Util::rnd( 8 ) + 10 ) * (Util::rnd(2)*2-1);
	dY = (Util::rnd( 8 ) + 10 ) * (Util::rnd(2)*2-1);
	dwX = dX;
	dwY = dY;
	maxX = 400;
	maxY = 400;

	Bitmap temp( 20, 20 );
	temp.fill( Bitmap::MaskColor );
	temp.circleFill( 10, 10, 10, Bitmap::makeColor( 255, 0, 0 ) );
	collide = new ECollide( temp );

}

WeaponRotateGun::~WeaponRotateGun() {
	delete collide;
}

void WeaponRotateGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 24;
	int dam = 40 + (strength + 1 ) * 10;

	const double speed = -6.5;

	int base = Util::rnd( 100 );
	for ( int q = 0; q < 360; q += 360 / (strength + 4) ){
		Ammo->push_back( new Rotate( x, y, 0, speed, (q+base) % 360, 55, new Rotate_WHull( dam, collide->copy() ), alignment ) );
	}
}

WeaponObject * WeaponRotateGun::copy() {
	return new WeaponRotateGun( strength, dir, smp, alignment );
}
