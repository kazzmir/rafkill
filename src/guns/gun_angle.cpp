#include "gunobj.h"
#include "gun_angle.h"
#include "bitmap.h"
#include "weapons/weapon_angle.h"
#include "hulls/hull_weapon_angle.h"
#include "trigtable.h"
#include "ebox.h"

static const int MAX_ANGLE_SHADE = 20;

WeaponAngle::WeaponAngle( int z, int d, int al ):
WeaponObject( d, "Taurus Gun", 145000, al, z, 4 ) {
	//strength = z;
	shade = new int[ MAX_ANGLE_SHADE ];

	Bitmap weapon_bitmap(6,6);
	weapon_bitmap.fill( Bitmap::makeColor(255,0,255) );
	weapon_bitmap.circleFill( 3, 3, 2, Bitmap::makeColor(255,0,0) );
	ecollide = new ECollide( weapon_bitmap );
}

WeaponAngle::~WeaponAngle() {
	delete[] shade;
	delete ecollide;
}

WeaponObject * WeaponAngle::copy() {
	return new WeaponAngle( strength, dir, alignment );
}


void WeaponAngle::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	// shot_counter = 13;
	setShotCounter( 13 );

	int r1, g1, b1, r2, g2, b2;

	r1 = (255-(strength+1)*13+256)%256;
	g1 = (90+(strength+1)*2+256)%256;
	b1 = (20+(strength+1)*6+256)%256;

	r2 = (r1-(strength+1)*11+256)%256;
	g2 = (g1+(strength+1)*8+256)%256;
	b2 = (b1+(strength+1)*19+256)%256;

	Util::blend_palette( shade, MAX_ANGLE_SHADE/2, Bitmap::makeColor(r1,g1,b1), Bitmap::makeColor(r2,g2,b2) );
	Util::blend_palette( shade+MAX_ANGLE_SHADE/2, MAX_ANGLE_SHADE-MAX_ANGLE_SHADE/2, Bitmap::makeColor(r2,g2,b2), Bitmap::makeColor(r1,g1,b1) );

	const double speed = -1.65 * 8;

	int color = 0;
	const double angle_dist = 26;
	for ( int q = 0; q < 360; q+= 8, color = (color+1) % MAX_ANGLE_SHADE ){

		/*
		int rx = (int)( x + Tcos(q) * angle_dist );
		int ry = (int)( y + Tsine(q) * angle_dist );
		*/

		int rx = x;
		int ry = y;

		/*
		double fx = Tcos(q+90) * 5;
		double fy = Tsine(q+90) * 5;
		*/
		double fx = 0;
		double fy = speed;

		Ammo->push_back( new Angle( rx, ry, fx, fy, angle_dist, new Angle_WHull( 3*(strength+1), shade[color], ecollide->copy() ), alignment, q%360 ) );
	}

}
