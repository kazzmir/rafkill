#include "weapon_shatter.h"
#include "weapon_bounce.h"
#include "weaponobj.h"
#include "hull.h"
#include "trigtable.h"
#include "sound.h"
#include "hulls/hull_weapon_shatter.h"
#include "hulls/hull_weapon_machine.h"

Shatter::Shatter( int qx, int qy, double kx, double ky, HullObject * hnew, int al, vector< SpaceObject * > * Ammo ):
WeaponNode(qx,qy,kx,ky,hnew, al) {
	// myAmmo = Ammo;
}

bool Shatter::Damage( double much ) {
	if ( !hull ) return true;
	hull->takeDamage( getLife() );
	return true;
	// return ( getLife() <= 0 );
}

void Shatter::destroy( vector< SpaceObject * > * objects ){
	for ( int q = 0; q < hull->getStrength() * 3; q++ ) {
		int ang = Util::rnd( 360 );
		double speed = 9.1;

		HullObject * add_h = new Machine_WHull( 1 );
		add_h->life = hull->getStrength() / 3 + 1;
		objects->push_back( new Bounce(getX(),getY(),Tcos(ang)*speed,Tsine(ang)*speed,add_h,alignment ) );

		//myAmmo->add( new Shatter(actualx,actualy,tcos[ang]*2.1,tsine[ang]*2.1, new Shatter_WHull(hull->strength/2), alignment, myAmmo ) );
	}
}

void Shatter::Died(SpaceObject * check,ExplosionClass ** explr,int ME ){

	Util::playSound( SND_SUSTAIN, 50 );
	Explode( explr, ME );

	/*
	if ( myAmmo == NULL ) return;
	for ( int q = 0; q < hull->strength*3; q++ ) {
		int ang = Util::rnd( 360 );

		HullObject * add_h = new Machine_WHull( 1 );
		add_h->life = 4;
		myAmmo->push_back( new Bounce(getX(),getY(),Tcos(ang)*2.1,Tsine(ang)*2.1,add_h,alignment ) );

		//myAmmo->add( new Shatter(actualx,actualy,tcos[ang]*2.1,tsine[ang]*2.1, new Shatter_WHull(hull->strength/2), alignment, myAmmo ) );
	}
	*/

}
