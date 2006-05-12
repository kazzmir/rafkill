#include "defs.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_light.h"

Light_WHull::Light_WHull():
HullWeapon( 0, 1, 1 ){}

void Light_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 2, makecol(0,100,250) );
	who.circleFill( x, y, 2, Bitmap::makeColor(0,100,250) );
}
