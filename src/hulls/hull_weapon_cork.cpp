#include "spaceobj.h"
#include "trigtable.h"
#include "hull_weapon.h"
#include "hull_weapon_cork.h"
#include "rgbhandle.h"
#include <deque>

#include <stdio.h>

static const int MAX_CORKS = 14;

Cork_WHull::Cork_WHull( int str ):
HullWeapon( 0, 1, str ),
ang( 0 ) {

	for ( int q = 0; q < 2; q++ )
		shade[q] = new int[ MAX_CORKS ];
	for ( int q = 0; q < MAX_CORKS; q++ )
		list.push_back( 0 );

	int r, g, b;
	float h, s, v;
	h = Util::rnd( 360 );
	s = 0.9;
	v = 1.0;
	Bitmap::hsvToRGB( h, s, v, &r, &g, &b );

	Util::blend_palette( shade[0], MAX_CORKS, Bitmap::makeColor(r,g,b), Bitmap::makeColor(0,0,0) );

	h = Util::rnd( 360 );
	Bitmap::hsvToRGB( h, s, v, &r, &g, &b );
	Util::blend_palette( shade[1], MAX_CORKS, Bitmap::makeColor(r,g,b), Bitmap::makeColor(0,0,0) );

}

Cork_WHull::~Cork_WHull() {
	for ( int q = 0; q < 2; q++ )
		delete[] shade[q];
	list.clear();
}

void Cork_WHull::Draw( const Bitmap & who, int x, int y ) {

	ang = ( ang + 17 ) % 360;

	list.pop_back();
	list.push_front( ang );
	int yval = y;
	int col = 0;
	for ( deque< int >::iterator it = list.begin(); it != list.end(); it++, yval -= 2, col++) {
		/*
		circlefill( who, (int)(x+rsine[*it]*7), yval, 1, shade[0][col] );
		circlefill( who, (int)(x+rsine[360-*it]*7), yval, 1, shade[1][col] );
		*/
		const int size = 4;
		int mx = (int)(x + Rsine(*it) * size);
		int my = yval;
		who.circleFill( mx, my, 1, shade[0][col] );
		x = (int)(x + Rsine(360-*it) * size);
		who.circleFill( mx, my, 1, shade[1][col] );
	}

}

bool Cork_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	return false;

}
