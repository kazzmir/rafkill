#include "gun_swirl.h"
#include "trigtable.h"
#include "gunobj.h"
#include "hulls/hull_weapon_dissipate.h"
#include "weapons/weapon_damage.h"
#include "spaceobj.h"
#include "bitmap.h"
#include "ebox.h"
#include <vector>

using namespace std;

static const int MAX_RISING = 100;
static const double RISE_SPEED = 1.5 * 8;
static const int MAX_SWIRL_RAD = 15;

WeaponSwirlGun::WeaponSwirlGun( int z, int d, int smp, int al ):
WeaponObject( d, "Swirl Gun", 92450, al, z, 0 ),
rising( 0 ) {

	/*
	BITMAP * dopey = create_bitmap( 12, 12 );
	clear_to_color( dopey, makecol(255,0,255) );
	circlefill(dopey,6,6,6,makecol(20,0,0) );
	// diss_collide = new ECollide( dopey,4,makecol(255,0,255),52);
	diss_collide = new ECollide( dopey );
	destroy_bitmap( dopey );
	shade = new int[ MAX_SWIRL_RAD ];
	blend_palette( shade, MAX_SWIRL_RAD, makecol( 100, 0, 0 ), makecol(250,250,250) );
	feel = new int[ MAX_SWIRL_RAD ];
	for ( int q = 0; q < MAX_SWIRL_RAD; q++ )
		feel[q] = 0;
	*/
	Bitmap dopey( 12, 12 );
	dopey.fill( Bitmap::MaskColor );
	dopey.circleFill( 6, 6, 6, Bitmap::makeColor(20,0,0) );
	diss_collide = new ECollide( &dopey );
	
	shade = new int[ MAX_SWIRL_RAD ];
	Util::blend_palette( shade, MAX_SWIRL_RAD, Bitmap::makeColor( 100, 0, 0 ), Bitmap::makeColor(250,250,250) );
	feel = new int[ MAX_SWIRL_RAD ];
	for ( int q = 0; q < MAX_SWIRL_RAD; q++ ){
		feel[q] = 0;
	}

	radius = 30;
	cur_rad = radius-(MAX_SWIRL_RAD-1);
	dir = 1;

}

WeaponObject * WeaponSwirlGun::copy() {
	return new WeaponSwirlGun( strength, dir, smp, alignment );
}

WeaponSwirlGun::~WeaponSwirlGun() {
	delete diss_collide;
	delete[] shade;
	delete[] feel;
}

void WeaponSwirlGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 0;

	if ( rising == 0 ) rising = 1;
	//if ( rising < 100 )
	//	rising+=2;

}


void WeaponSwirlGun::Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( rising == 0 ) return;

	for ( int q = 0; q < 360; q+=3 )
		Ammo->push_back( new Damage_Weapon(x,y,Tcos(q)*RISE_SPEED,Tsine(q)*RISE_SPEED,1,new Dissipate_WHull(rising/4,diss_collide), alignment ) ); rising = 0;
	radius = 0;
	dir = 1;
}


void WeaponSwirlGun::Draw( const Bitmap & less, int x, int y) {

	if ( rising == 0 ) return;

	for ( int z = 0; z < 3; z++ ) {
		if ( dir == 1 ) {
			cur_rad++;
			if ( cur_rad >= radius ) {
				radius += 1;
				if ( rising < 100 )
					rising += 4;
				dir = -1;
				if ( radius > rising*3/2 ) radius = rising*3/2;
				if ( radius < 40 ) radius = 40;
			}
		}
		else {
			cur_rad--;
			if ( cur_rad <= radius - (MAX_SWIRL_RAD-1) ) {
				dir = 1;
			}
		}

		for ( int q = 0; q < MAX_SWIRL_RAD; q++ ) {
			if ( radius-cur_rad == q ) {
				feel[q] = MAX_SWIRL_RAD-1;
			}
			else if ( feel[q] > 0 ) feel[q]--;
		}
	}

	for ( int q = 0; q < MAX_SWIRL_RAD; q++ ) {
		less.circle( x, y, radius-(MAX_SWIRL_RAD-1)-q, shade[ feel[q] ] );
	}
}
