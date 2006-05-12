#include "spaceobj.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "trigtable.h"
#include "hull_weapon_pulse_large.h"

LargePulse_WHull::LargePulse_WHull():
HullWeapon( 0, 1, 3 ){}

void LargePulse_WHull::Draw( const Bitmap & who, int x, int y ) {

	for ( int tri = 0; tri < 2; tri++ ) {

		int x1 = x + Util::rnd(7) - 3;
		int x2 = x + Util::rnd(7) - 3;
		int y1 = y + 10 + Util::rnd(8);
		who.triangle( x1,  y, x2, y, (x1+x2)/2, y1-2, Bitmap::makeColor(255,20,0));
		who.triangle( x1,  y, x2, y, (x1+x2)/2, y1, Bitmap::makeColor(240,20,0) );

	}

	who.ellipseFill( x, y-1, 3, 6, Bitmap::makeColor(255,0,0) );
	who.ellipseFill( x, y, 3, 6, Bitmap::makeColor(240,100,0) );

}


bool LargePulse_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	for ( int ang = 0; ang < 360; ang += 65 ) {

		int tx = (int)(mx + Tcos(ang)*6 );
		int ty = (int)(my + Tsine(ang)*6 );
		if ( check->HitMe( tx, ty ) )
			return true;

	}

	return false;

}
