#include "trigtable.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_follow.h"

Follow_WHull::Follow_WHull( int _life ):
HullWeapon( 0, _life, 2 ){}

void Follow_WHull::Draw( const Bitmap & who, int x, int y ) {

	for ( int q = 0; q < 12; q++ ) {
		double sx, sy;
		sx = x;
		sy = y;
		double ox = sx;
		double oy = sy;
		int mang = Util::rnd( 360 );
		for ( int z = 0; z < 7; z++ ) {

			sx += Tcos(mang)*2;
			sy += Tsine(mang)*2;
			mang += (Util::rnd( 17 ) - 8) * 4;
			mang += 360;
			mang %= 360;

			int gf = 150 + z * 5;
			// line( who, (int)sx, (int)sy, (int)ox, (int)oy, makecol(gf,gf,gf) );
			who.line( (int)sx, (int)sy, (int)ox, (int)oy, Bitmap::makeColor(gf,gf,gf) );
			ox = sx;
			oy = sy;

		}
	}
	// circlefill( who, x, y, 3, makecol(255,255,255) );
	who.circleFill( x, y, 3, Bitmap::makeColor(255,255,255) );

}
