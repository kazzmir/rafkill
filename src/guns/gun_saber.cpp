#include "gun_saber.h"
#include "trigtable.h"
#include "gunobj.h"
#include "hulls/hull_weapon_saber.h"
#include "weapons/weapon_beam.h"
#include "spaceobj.h"
#include "ebox.h"
#include <vector>
#include <math.h>

using namespace std;

static const int MAX_GLOW_SHADE = 15;

saber_point::saber_point() {
	distance = 0;
}

WeaponSaber::WeaponSaber( int z, int d, int smp, int al ):
WeaponObject( d, "Saber Gun", 285000, al, z, 0 ),
rising( 0 ) {

	shade = new int[ MAX_GLOW_SHADE ];
	min_color_r = 80;
	min_color_g = 80;
	shooting = false;

}


WeaponObject * WeaponSaber::copy() {
	return new WeaponSaber( strength, dir, smp, alignment );
}


WeaponSaber::~WeaponSaber() {
	delete[] shade;
}


void WeaponSaber::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 0;

	if ( shooting ) {

		fat += 2;
		if ( fat >= rising / 3 ) {
			shooting = false;
			rising = 0;
		}

		int ff = rising/3 - fabs(fat) + 1;
		Ammo->push_back( new Beam(x,y-GRAPHICS_Y/2,0,0,1, new Saber_WHull(ff/2,ff*2,GRAPHICS_Y), alignment ) );

		return;

	}

	if ( rising < 200 )
		rising++;

}


void WeaponSaber::Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( shooting ) {

		fat += 2;
		if ( fat >= rising / 3 ) {
			shooting = false;
			rising = 0;
		}

		int ff = rising/3 - fabs(fat) + 1;
		Ammo->push_back( new Beam(x,y-GRAPHICS_Y/2,0,0,1, new Saber_WHull(ff/2,ff*2,GRAPHICS_Y), alignment ) );

		return;

	}

	if ( rising == 0 ) return;
	min_color_r = 80;
	min_color_g = 80;

	shooting = true;
	fat = 1;

}


void WeaponSaber::Draw( const Bitmap & less, int x, int y) {

	if ( rising == 0 ) return;

	int ry = y - 25;

	for ( int q = 0; q < MAX_GLOW_SHADE; q++ ){
		shade[q] = Bitmap::addColor( shade[q], Bitmap::makeColor( 6, 6, 7 ) );
	}

	min_color_r++;
	min_color_g++;

	if ( min_color_r > 255 ) min_color_r = 255;
	if ( min_color_g > 255 ) min_color_g = 255;

	Util::blend_palette( shade, MAX_GLOW_SHADE, Bitmap::makeColor(250,250,0), Bitmap::makeColor(min_color_r, min_color_g, 0 ) );

	//circlefill( less, x, ry, rising/30 + 3, makecol( 255, 250, 0 ) );
	for ( int q = MAX_GLOW_SHADE-1; q >= 0; q-- ){
		less.circleFill( x, ry, (int)((double)q*(double)rising/100.0), shade[q] );
	}

	int g = Util::rnd( MAX_GLOW );
	if ( glow[ g ].distance <= 0 ) {
		glow[ g ].distance = Util::rnd( 9 ) + (double)rising/3.0;
		glow[ g ].ang = Util::rnd( 360 );
	}

	for ( int q = 0; q < MAX_GLOW; q++ ){
		if ( glow[q].distance > 0 ) {

			int rad = (int)( 20.0 / (fabs(glow[q].distance)+1) + 1 );

			if ( rad > 4 ) rad = 4;

			int cx = (int)(x+Tcos(glow[q].ang)*glow[q].distance);
			int cy = (int)(ry+Tsine(glow[q].ang)*glow[q].distance);
			int color = Bitmap::makeColor( (int)(250-glow[q].distance*3),(int)(250-glow[q].distance*3), 0);

			less.circleFill( cx, cy, rad, color );

			glow[q].distance -= 1.8;

		}
	}

}
