#include "hull_weapon.h"
#include "hull_weapon_arc.h"
#include "spaceobj.h"
#include "defs.h"
#include "bitmap.h"
#include <math.h>
#include "ebox.h"

#define MAX_ARC_SHADE 16

Arc_WHull::Arc_WHull( int str, ECollide * mycollide ):
HullWeapon( 0, 1, str ) {
	shade = new int[ MAX_ARC_SHADE ];
	strength = str;

	/*
	switch( str ) {
		case 1  :       blend_palette( shade, MAX_ARC_SHADE, makecol(220,0,80), makecol(25,50,2) ); break;
		case 3  :       blend_palette( shade, MAX_ARC_SHADE, makecol(85,230,0), makecol(10,0,75) ); break;
		case 5  :       blend_palette( shade, MAX_ARC_SHADE, makecol(110,30,230), makecol(50,20,20) ); break;
		case 7  :       blend_palette( shade, MAX_ARC_SHADE, makecol(0,80,240), makecol(10,30,60) ); break;
		case 9  :       blend_palette( shade, MAX_ARC_SHADE, makecol(65,235,100), makecol(180,180,180) ); break;
	}
	*/

	int r1, g1, b1;
	int r2, g2, b2;
	int color;

	color = (str*25)%360;
	Bitmap::hsvToRGB( (float)color, 1.0, 1.0, &r1, &g1, &b1 );
	color = (color + 12 ) % 360;
	Bitmap::hsvToRGB( (float)color, 1.0, 0.8, &r2, &g2, &b2 );
	Util::blend_palette( shade, MAX_ARC_SHADE/3, Bitmap::makeColor(r1,g1,b1), Bitmap::makeColor(r2,g2,b2) );
	color = (color + 18 ) % 360;
	Bitmap::hsvToRGB( (float)color, 1.0, 0.5, &r1, &g1, &b1 );
	Util::blend_palette( shade+MAX_ARC_SHADE/3, MAX_ARC_SHADE-MAX_ARC_SHADE/3, Bitmap::makeColor(r2,g2,b2), Bitmap::makeColor(r1,g1,b1) );

	collide = mycollide;

	// look = create_bitmap( 5, MAX_ARC_SHADE );
	look = new Bitmap( 5, MAX_ARC_SHADE );
	// clear( look );
	look->clear();

	//int c = shade[0];
	for ( int sy = 0; sy < MAX_ARC_SHADE; sy++ ){
		// hline( look, 0, sy, 4, shade[sy] );
		look->hLine( 0, sy, 4, shade[sy] );
	}

}


void Arc_WHull::Draw( const Bitmap & who, int x, int y ) {
	// draw_sprite( who, look, x-2, y );
	look->draw( x-2, y, who );
}


Arc_WHull::~Arc_WHull() {
	delete[] shade;
	// destroy_bitmap( look );
	delete look;
}
