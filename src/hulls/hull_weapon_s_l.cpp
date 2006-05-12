#include "spaceobj.h"
#include "bitmap.h"
#include "trigtable.h"
#include "hull_weapon.h"
#include "hull_weapon_s_l.h"

SL_WHull::SL_WHull():
HullWeapon( 0, 1, 3 ),
r1( 0 ),
r2( 3 ){}

void SL_WHull::Draw( const Bitmap & who, int x, int y ) {

	int col1 = Bitmap::makeColor( 255, 0, 0 );
	int col2 = Bitmap::makeColor( 255, 250, 250 );

	if ( r1 > r2 ) {
		/*
		circlefill( who, x, y, r1, col1 );
		circlefill( who, x, y, r2, col2 );
		*/
		who.circleFill( x, y, r1, col1 );
		who.circleFill( x, y, r2, col2 );
	}
	else {
		/*
		circlefill( who, x, y, r2, col2 );
		circlefill( who, x, y, r1, col1 );
		*/
		who.circleFill( x, y, r2, col2 );
		who.circleFill( x, y, r1, col1 );
	}

	r2++;
	r1++;
	if ( r2 > 5 ){
		r2 = 1;
	}
	if ( r1 > 5 ){
		r1 = 1;
	}
}


bool SL_WHull::Collide( int mx, int my, SpaceObject * check ) {
	// return false;

	if ( check->HitMe( mx, my ) ){
		return true;
	}

	const int LARGE = 5;

	for ( int sang = 0; sang < 360; sang += 45 ) {

		int ax = (int)(mx + Tcos(sang)*LARGE );
		int ay = (int)(my + Tsine(sang)*LARGE );
		if ( check->HitMe( ax, ay ) )
			return true;

	}

	return false;

}
