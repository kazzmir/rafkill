#include "defs.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_beam.h"
#include "trigtable.h"
#include "ebox.h"

#ifndef debug
#include <iostream>
#define debug std::cout<<"File: "<<__FILE__<<" Line: "<<__LINE__<<std::endl;
#endif

Beam_WHull::Beam_WHull( double str, int xf, int yf, int ang ):
HullWeapon( 0, 1, str ),
x_size( xf ),
y_size( yf ),
angle( ang ) {

	drawLevel = 20;
	// shade = new int[ 6 ];

	float h;

	h = str * 70.0;
	int r1, g1, b1;
	Bitmap::hsvToRGB( h, 1.0, 1.0, &r1, &g1, &b1 );
	int r2, g2, b2;
	Bitmap::hsvToRGB( h, 1.0, 0.4, &r2, &g2, &b2 );
	Util::blend_palette( shade, 6, Bitmap::makeColor(r2,g2,b2), Bitmap::makeColor( r1, g1, b1) );

	collide = new ECollide( xf, yf );

}


void Beam_WHull::Draw( const Bitmap & who, int x, int y ) {

	int mx = x_size/2;
	int my = y_size/2;
	// my = 0;
	int my2 = y_size/2;

	who.drawingMode( Bitmap::MODE_TRANS );

	for ( int q = 0; q < 5 && x-mx+q < x; q++ ) {
		who.line( x-mx+q, y-my, x-mx+q, y+my2, shade[q] );
		who.line( x+mx-q, y-my, x+mx-q, y+my2, shade[q] );
	}
	if ( x-mx+5 < x ){
		who.rectangleFill( x-mx+5, y-my, x+mx-5, y+my2, shade[5] );
	} else {
		who.line( x, y-my, x, y+my2, shade[5] );
	}

	if ( strength >= 3 ) {

		int color = 1;
		int dir = 1;
		for ( int q = y-my; q < y+my; q++ ) {

			int sang = (angle+q*4+360)%360;
			if ( abs(q) % 10 == 0 ) {
				color += dir;
				if ( color == 5 ) dir = -1;
				if ( color == 0 ) dir = 1;
			}
			if ( color < 0 ) color = 0;
			if ( color > 5 ) color = 5;
			if ( sang >= 90 && sang <= 270 ){
				if ( x_size/2 > 3 ){
					who.circleFill( (int)(x - Tsine(sang)*x_size/2), q, 1, shade[color] );
				}
			}

		}

	}

	who.drawingMode( Bitmap::MODE_SOLID );

	// collide->draw( who, x-x_size/2, y-y_size/2 );
}


Beam_WHull::~Beam_WHull() {
	delete collide;
	// delete[] shade;
}
