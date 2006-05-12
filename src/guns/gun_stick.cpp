#include "gunobj.h"
#include "gun_stick.h"
#include "ebox.h"
#include "hulls/hull_animation.h"
#include "weapons/weapon_stick.h"
#include "raptor.h"
#include "defs.h"
#include "bitmap.h"
#include <vector>

using namespace std;

WeaponStick::WeaponStick( int z, int d, int al, ECollide ** _collide_list, int _max_collide ):
WeaponObject( d, "Sticky Bomb", 350000, al, z, 4 ) {

	max_collide = _max_collide;
	collide_list = _collide_list;

	/*
	max_collide = 40;
	collide_list = new ECollide*[ max_collide ];
	for ( int q = 0; q < max_collide; q++ ){
		Bitmap * temp = create_Bitmap( (3 + q * 3)*2, (3 + q * 3)*2 );
		int mask = makecol( 255, 0, 255 );
		clear_to_color( temp, mask );
		circlefill( temp, 3 + q * 3, 3 + q * 3, 3 + q * 3, makecol(255,0,0) );
		collide_list[q] = new ECollide( temp, 3, mask, 35.0 );
		destroy_Bitmap( temp );
	}
	*/
	// ecollide = new ECollide( (Bitmap *)global_data[ WEAPON_BOMB_1 ].dat, 2, makecol(255,0,255), 30.0 );
	Bitmap l( Util::getDataSprite( WEAPON_BOMB_1 ) );
	ecollide = new ECollide( &l );

}


void WeaponStick::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 17;

	/*
	ECollide ** temp_collide = new ECollide*[ max_collide ];
	for ( int q = 0; q < max_collide; q++ )
		temp_collide[q] = collide_list[q]->copy();
	*/

	int mpics = WEAPON_BOMB_7 - WEAPON_BOMB_1 + 1;

	vector< Bitmap > pics;
	// Bitmap ** pics = new Bitmap*[ mpics ];
	for ( int q = 0; q < mpics; q++ ){
		pics.push_back( Util::getDataSprite(  WEAPON_BOMB_1 + q ) );
	}

	const double speed = -1.4 * 8;

	vector< Bitmap > shadows;

	Ammo->push_back( new Sticky( x, y, 0, speed, new HullAnimation( pics, shadows, 1, 0, 0, 0, 10, false, ecollide->copy() ), alignment, collide_list, max_collide, (strength)*3+2 ) );

}


WeaponObject * WeaponStick::copy() {
	//ECollide ** temp_list = new ECollide*[ max_collide ];
	//for ( int q = 0; q < max_collide; q++ )
	//	temp_list[q] = collide_list[q]->copy();
	//return new WeaponStick( strength, dir, alignment, temp_list, max_collide );
	return new WeaponStick( strength, dir, alignment, collide_list, max_collide );
}


WeaponStick::~WeaponStick() {

	//for ( int q = 0; q < max_collide; q++ )
	//	delete collide_list[q];
	//delete[] collide_list;
	delete ecollide;

}
