#include "defs.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_saber.h"
#include "ebox.h"

Saber_WHull::Saber_WHull( int str, int xf, int yf ):
HullWeapon( 0, 1, str*2 ),
x_size( xf ),
y_size( yf ) {

	drawLevel = 20;
	shade = new int[ 6 ];

	Util::blend_palette( shade, 6, Bitmap::makeColor(210,210,0), Bitmap::makeColor(250,250,0) );

	collide = new ECollide( xf, yf );
	/*
	collide = new ECollide();
	collide->setXS( xf/2 );
	collide->setYS( yf/2 );
	collide->my_size = xf/2;
	EBox * arch = new EBox( 0, 0, xf, yf );
	collide->add( arch );

	collide->finalize();
	*/

}


void Saber_WHull::Draw( const Bitmap & who, int x, int y ) {
	int mx = x_size/2;
	int my = y_size/2;

	Bitmap::drawingMode( Bitmap::MODE_TRANS );

	for ( int q = 0; q < 5 && x-mx+q < x; q++ ) {
		who.line( x-mx+q, y-my, x-mx+q, y+my, shade[q] );
		who.line( x+mx-q, y-my, x+mx-q, y+my, shade[q] );
	}

	if ( x-mx+5 < x ){
		who.rectangleFill( x-mx+5, y-my, x+mx-5, y+my, shade[5] );
	} else {
		who.line( x, y-my, x, y+my, shade[5] );
	}
	
	Bitmap::drawingMode( Bitmap::MODE_SOLID );
}


Saber_WHull::~Saber_WHull() {
	delete collide;
	delete[] shade;
}
