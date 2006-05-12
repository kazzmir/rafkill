#include "spaceobj.h"
#include "defs.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_emissle.h"

static const int normal_length = 20;

EMissle_WHull::EMissle_WHull():
HullWeapon( 0, 1, 7 ){}

// #define normal_length 20
void EMissle_WHull::Draw( const Bitmap & who, int x, int y ) {
	/*
	rectfill( who, x-2, y, x+2, y-normal_length, makecol(200,200,200) );
	circlefill( who, x, y, 3, makecol(235,235,235) );
	*/
	who.rectangleFill( x-2, y, x+2, y-normal_length, Bitmap::makeColor(200,200,200) );
	who.circleFill( x, y, 3, Bitmap::makeColor(235,235,235) );
}


bool EMissle_WHull::Collide( int mx, int my, SpaceObject * check ) {

	if ( check->HitMe( mx, my ) )
		return true;
	if ( check->HitMe( mx, my-normal_length/2 ) )
		return true;
	if ( check->HitMe( mx, my-normal_length ) )
		return true;
	return false;

}
