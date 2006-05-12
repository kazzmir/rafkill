#include "hull_weapon.h"
#include "hull_weapon_angle.h"
#include "ebox.h"
#include "bitmap.h"

Angle_WHull::Angle_WHull( int str, int _color, ECollide * ec ):
HullWeapon( 0, 1, str ),
color( _color ) {
	collide = ec;
}


Angle_WHull::~Angle_WHull() {
	delete collide;
}


void Angle_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 2, color );
	who.circleFill( x, y, 2, color );
}
