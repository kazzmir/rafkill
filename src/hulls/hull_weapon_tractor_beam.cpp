#include "hull_weapon.h"
#include "hull_weapon_tractor_beam.h"
#include "ebox.h"
#include "bitmap.h"

Tractor_WHull::Tractor_WHull( int str, int _color, ECollide * ec ):
HullWeapon( 0, 1, str ),
color( _color ) {
	collide = ec;
}


Tractor_WHull::~Tractor_WHull() {
	delete collide;
}


void Tractor_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 3, color );
	who.circleFill( x, y, 3, color );
}
