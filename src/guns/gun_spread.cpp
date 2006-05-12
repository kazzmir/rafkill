#include "gunobj.h"
#include "gun_spread.h"
#include "hulls/hull_weapon_spread.h"
#include "weaponobj.h"
#include "spaceobj.h"
#include "trigtable.h"

WeaponSpreadGun::WeaponSpreadGun( int z, int d, int _smp, int al ):
WeaponObject( d, "Spread Gun", 31500, al, z, 4 ) {
	smp = _smp;
}


WeaponObject * WeaponSpreadGun::copy() {
	return new WeaponSpreadGun( strength, dir, smp, alignment );
}


void WeaponSpreadGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight) {
	if ( smp != -1 ){
		Util::playSound( smp, 255 );
	}

	shot_counter = 5;
	int ang = (strength+1) * 30;
	int ds = 50 / (strength+2);
		
	int xpos = x;
	int ypos = y;
	double xspeed = 0;
	double yspeed = -2.6*8.0;
		
	Ammo->push_back( new WeaponNode(xpos,ypos,xspeed,yspeed, new Spread_WHull(7), alignment ) );

	for ( int q = ds; q < ang; q += ds ) {

		xpos = (int)( x + Tcos( (90 + q + 360 ) % 360 ) );
		ypos = (int)( y + Tsine((90 + q + 360 ) % 360 ) );
		xspeed = Tcos((90+q+360)%360)*2.6 * 8.0;
		yspeed = Tsine((90+q+360)%360)*2.6 * 8.0;

		Ammo->push_back( new WeaponNode(xpos,ypos,xspeed,yspeed, new Spread_WHull(7), alignment ) );
		
		xpos = (int)( x + Tcos( (90 - q + 360 ) % 360 ) );
		ypos = (int)( y + Tsine((90 - q + 360 ) % 360 ) );
		xspeed = Tcos((90-q+360)%360)*2.6 * 8.0;
		yspeed = Tsine((90-q+360)%360)*2.6 * 8.0;
	
		Ammo->push_back( new WeaponNode(xpos,ypos,xspeed,yspeed, new Spread_WHull(7), alignment ) );

		/*
		Ammo->push_back( new WeaponNode((int)(x+tcos[(90+q+360)%360]),(int)(y+tsine[(90+q+360)%360]),tcos[(90+q+360)%360]*2.6,tsine[(90+q+360)%360]*2.6, new Spread_WHull(7), alignment ) );
		Ammo->push_back( new WeaponNode((int)(x+tcos[(90-q+360)%360]),(int)(y+tsine[(90-q+360)%360]),tcos[(90-q+360)%360]*2.6,tsine[(90-q+360)%360]*2.6, new Spread_WHull(7), alignment ) );
		*/
	}

}
