#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_mini.h"

Mini_WHull::Mini_WHull( ):
HullWeapon( 0, 1, 4 ) {
	lx = -1;
	ly = -1;
}


void Mini_WHull::Draw( const Bitmap & who, int x, int y ) {

	if ( lx == -1 ) {
		lx = x;
		ly = y;
	}

	//int sx = (int)( x );
	//int sy = (int)( y - 3 );

	double cx = (double)(lx-x)/8.0;
	double cy = (double)(ly-y)/8.0;

	/*
	double rx = x;
	double ry = y;
	for ( int q = 0; q < 3; q++ ) {
		int c = 230-q*16;
		line( who, (int)rx, (int)ry, (int)(rx+cx), (int)(ry+cy), makecol(c,c,c) );
		rx += cx;
		ry += cy;
	}
	*/

	/*
	line( who, x, y, (int)(x+cx*4), (int)(y+cy*4), makecol(255,243,48) );

	putpixel( who, x, y, makecol(255,20,20) );
	*/
	who.line( x, y, (int)(x+cx*4), (int)(y+cy*4), Bitmap::makeColor(255,243,48) );
	who.putPixel( x, y, Bitmap::makeColor(255,20,20) );
	lx = x;
	ly = y;
}
