#include "trigtable.h"
#include "bitmap.h"
#include "hull.h"
#include "hull_protect.h"

#define protect_length 35
#define protect_size 9

ProtectHull::ProtectHull( int c, int level ):
HullObject( NULL, 100000, 3, 0, level, 9, false, NULL ) {
	color = c;
	angX = Util::rnd(360);
	angY = Util::rnd(360);

	dirX = Util::rnd(2) * 2 - 1;
	dirY = Util::rnd(2) * 2 - 1;
}


void ProtectHull::angular( int & a, int d ) {
	a += d*10;
	while ( a < 0 ) a += 360;
	while ( a >= 360 ) a -= 360;
}


void ProtectHull::Draw( const Bitmap & work, int x, int y ) {
	angular( angX, dirX );
	angular( angY, dirY );
	int x1 = (int)( x + Tcos( angX ) * protect_length );
	int y1 = (int)( y + Tsine( angY ) * protect_length );
	// circlefill( work, x1, y1, protect_size, makecol( 186, 16, 16 ) );
	// circle( work, x1, y1, protect_size, makecol( 40, 40, 40 ) );
	work.circleFill( x1, y1, protect_size, Bitmap::makeColor(186,16,16));
	work.circle( x1, y1, protect_size, Bitmap::makeColor(40,40,40) );
}


bool ProtectHull::Inside( int mx, int my, int ax, int ay ) {
	//if ( abs(mx-ax)>=protect_size*2 || abs(my-ay)>=protect_size*2 )
	//	return false;
	int x1 = (int)( mx + Tcos( angX ) * protect_length );
	int y1 = (int)( my + Tsine(angY ) * protect_length );
	if ( dist( x1, y1, ax, ay ) < protect_size ) {
		crash = true;
		return true;
	}
	crash = false;
	return false;
}
