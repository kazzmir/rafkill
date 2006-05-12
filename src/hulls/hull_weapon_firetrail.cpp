#include "spaceobj.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_firetrail.h"
#include "trigtable.h"

#define MAX_TRAIL_LIFE 13

FireTrail_WHull::FireTrail_WHull( int str ):
HullWeapon( 0, 1, str ) {

	life = 1*MAX_TRAIL_LIFE;

}


void FireTrail_WHull::Draw( const Bitmap & who, int x, int y ) {

	/*
	for ( int q = 0; q < life; q++ ){

		for ( int z = 0; z < 10; z++ ){

			int ang = rnd( 360 );
			int d = rnd(4);
			int mx = (int)(x+tcos[ang]*d);
			int my = (int)(y+tsine[ang]*d);

			int col = getpixel(who,mx,my);
	int r = getr(col)+40;
	if ( r > 255 ) r = 255;
	col = makecol( r, getg(col), getb(col) );
	putpixel(who,mx,my,col);

	}

	}
	*/
	double col = (double)life/(double)(1*MAX_TRAIL_LIFE)*255.0;
	// circlefill( who, x, y, 4, makecol((int)col,0,0) );
	who.circleFill( x, y, 4, Bitmap::makeColor((int)col, 0, 0 ) );

}


bool FireTrail_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;
	return false;

	for ( int ang = 0; ang < 360; ang += 35 ) {

		int tx = (int)(mx + Tcos(ang)*4 );
		int ty = (int)(my + Tsine(ang)*4 );
		if ( check->HitMe( tx, ty ) )
			return true;

	}

	return false;

}
