#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_spread.h"
#include "trigtable.h"

Spread_WHull::Spread_WHull( int str ):
HullWeapon( 0, 1, str ) {
	ang = 0;
}


void Spread_WHull::Draw( const Bitmap & who, int x, int y ) {

	ang = (ang+5)%360;
	// circlefill( who, x, y, 5, makecol(235,20,0) );
	who.circleFill( x, y, 5, Bitmap::makeColor(235,20,0) );
	for ( int q = 0; q < 360; q += 120 ) {

		for ( int z = 0; z < 5; z++ ) {
			int cx = (int)(x + Tcos((ang+q+z*3)%360)*z);
			int cy = (int)(y + Tsine((ang+q+z*3)%360)*z);
			// putpixel( who, cx, cy, makecol(0,20,235) );
			who.putPixel( cx, cy, Bitmap::makeColor(0,20,235) );
		}

	}

}
