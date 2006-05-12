#include "rgbhandle.h"
#include "defs.h"

RGBHandle::RGBHandle() {
	rwant = Util::rnd( 255 );
	gwant = Util::rnd( 255 );
	bwant = Util::rnd( 255 );

	mine.r = rwant;
	mine.g = gwant;
	mine.b = bwant;

}


void RGBHandle::update( int max, int min ) {

	unsigned char * want[ 3 ];
	want[0] = &rwant;
	want[1] = &gwant;
	want[2] = &bwant;

	if ( changecol( mine.r, rwant ) ) {
		if ( Util::rnd( RGB_GO_BLACK ) == Util::rnd( RGB_GO_BLACK ) )
			rwant = 0;
		else    rwant = Util::rnd(max-min)+min;
	}

	if ( changecol( mine.g, gwant ) ) {
		if ( Util::rnd( RGB_GO_BLACK ) == Util::rnd( RGB_GO_BLACK ) )
			gwant = 0;
		else    gwant = Util::rnd(max-min)+min;
	}

	if ( changecol( mine.b, bwant ) ) {
		if ( Util::rnd( RGB_GO_BLACK ) == Util::rnd( RGB_GO_BLACK ) )
			bwant = 0;
		else    bwant = Util::rnd(max-min)+min;
	}

	bool cy = false;
	for ( int q = 0; q < 3; q++ )
		cy = cy || (*(want[q]) >= min && *(want[q]) <= max);
	if ( !cy ) *(want[Util::rnd(3)]) = Util::rnd(max-min)+min;
	cy = true;
	for ( int q = 0; q < 3; q++ )
		cy = cy && *(want[q]) == 0;
	if ( cy ) *(want[Util::rnd(3)]) = Util::rnd(max-min)+min;

}


int RGBHandle::Get( ) {
	return Bitmap::makeColor( mine.r, mine.g, mine.b );
}


bool RGBHandle::changecol( unsigned char & c, unsigned char & dir ) {

	for ( int q = 0; q < 2; q++ ) {
		if ( c > dir ) c--;
		if ( c < dir ) c++;
	}

	return c == dir;

}
