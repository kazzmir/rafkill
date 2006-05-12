#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_s_s.h"

SS_WHull::SS_WHull():
HullWeapon( 0, 1, 1 ){}

void SS_WHull::Draw( const Bitmap & who, int x, int y ) {
	/*
	circlefill( who, x, y, 3, makecol(255,0,0) );
	circlefill( who, x, y, 1, makecol(255,255,255) );
	*/
	who.circleFill( x, y, 3, Bitmap::makeColor(255,0,0) );
	who.circleFill( x, y, 1, Bitmap::makeColor(255,255,255) );
}
