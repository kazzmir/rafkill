#include "spaceobj.h"
#include "bitmap.h"
#include "trigtable.h"
#include "hull_weapon.h"
#include "hull_weapon_pulse_nova.h"

NovaPulse_WHull::NovaPulse_WHull():
HullWeapon( 0, 1, 3 ){}

void NovaPulse_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 7, makecol(0,255,10) );
	who.circleFill( x, y, 7, Bitmap::makeColor(0,255,10) );
	return;

	/*
	for ( int tri = 0; tri < 2; tri++ ){

		int x1 = actualx + rnd(7) - 3;
		int x2 = actualx + rnd(7) - 3;
		int y1 = actualy + 10 + rnd(8);
		triangle( who, x1, actualy, x2, actualy, (x1+x2)/2, y1-2, 44);
		triangle( who, x1, actualy, x2, actualy, (x1+x2)/2, y1, 42 );

	}

	ellipsefill( who, actualx, actualy-1, 3, 6, 39 );
	ellipsefill( who, actualx, actualy, 3, 6, 41 );
	*/
}


bool NovaPulse_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	for ( int ang = 0; ang < 360; ang += 45 ) {

		int tx = (int)(mx + Tcos(ang) * 7 );
		int ty = (int)(my + Tsine(ang) * 7 );
		if ( check->HitMe( tx, ty ) )
			return true;

	}

	return false;

}
