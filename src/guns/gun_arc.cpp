#include "allegro.h"
#include "gunobj.h"
#include "gun_arc.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>
#include "weaponobj.h"
#include "hulls/hull_weapon_arc.h"
#include "ebox.h"

using namespace std;

WeaponArc::WeaponArc( int z, int d, int _smp, int al ):
WeaponObject( d, "Arc", 43000, al, z, -1 ) {
	smp = _smp;

	Bitmap temp( 4, 16 );
	temp.rectangleFill( 0, 0, 3, 15, Bitmap::makeColor(40,40,40) );
	arc_collide = new ECollide( &temp );

	/* fixed
	BITMAP * temp = create_bitmap( 4, 16 );
	rectfill( temp, 0, 0, 3, 15, makecol(40,40,40) );
	// arc_collide = new ECollide( temp, 3, makecol(255,0,255), 40 );
	arc_collide = new ECollide( temp );
	destroy_bitmap( temp );
	*/

}


void WeaponArc::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( smp != -1 ){
		Util::playSound( smp, 255 );
	}

	shot_counter = 13;

	for ( int ang = 2; ang <= 90; ang+=7 ) {
		int ang1 = (720+90-ang)%360;
		int ang2 = (720+90+ang)%360;

		const double speed_div = 4.8 / 8.0;
		int xput = (int)( x + Tcos(ang1) * 4 );
		int yput = (int)( y + Tsine(ang1) * 12 );
		double xspeed = Tcos(ang1) / speed_div;
		double yspeed = -1.72 * 8.0;
		
		Ammo->push_back( new WeaponNode(xput, yput, xspeed, yspeed, new Arc_WHull(strength*2+1,arc_collide), alignment ) );
		
		xput = (int)( x + Tcos(ang2) * 4 );
		yput = (int)( y + Tsine(ang2) * 12 );
		xspeed = Tcos(ang2) / speed_div;
		yspeed = -1.72 * 8.0;
		Ammo->push_back( new WeaponNode(xput, yput, xspeed, yspeed, new Arc_WHull(strength*2+1,arc_collide), alignment ) );

		/*
		Ammo->push_back( new WeaponNode((int)(x+tcos[ang1]*4),(int)(y+tsine[ang1]*12),tcos[ang1]/4.8,-1.72, new Arc_WHull(strength*2+1,arc_collide), alignment ) );
		Ammo->push_back( new WeaponNode((int)(x+tcos[ang2]*4),(int)(y+tsine[ang2]*12),tcos[ang2]/4.8,-1.72, new Arc_WHull(strength*2+1,arc_collide), alignment ) );
		*/
	}

}


WeaponObject * WeaponArc::copy() {

	return new WeaponArc( strength, dir, smp, alignment );

}


WeaponArc::~WeaponArc() {
	delete arc_collide;
}
