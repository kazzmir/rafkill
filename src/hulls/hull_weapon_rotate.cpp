#include "hull_weapon.h"
#include "hull_weapon_rotate.h"
#include "ebox.h"
#include "bitmap.h"

Rotate_WHull::Rotate_WHull( int str, ECollide * ec ):
HullWeapon( 0, 1, str ) {
	collide = ec;
}


Rotate_WHull::~Rotate_WHull() {
	delete collide;
}


void Rotate_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 10, makecol(255,255,255) );
	who.circleFill( x, y, 10, Bitmap::makeColor(255,255,255) );
}
