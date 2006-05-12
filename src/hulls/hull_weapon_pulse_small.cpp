#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_pulse_small.h"

SmallPulse_WHull::SmallPulse_WHull():
HullWeapon( 0, 1, 1 ){}

void SmallPulse_WHull::Draw( const Bitmap & who, int x, int y ) {
	who.circleFill( x, y, 2, Bitmap::makeColor(0,200,250) );
	who.triangle( x-2, y+2, x+2, y+2, x, y+7, Bitmap::makeColor(90,245,140) );
}
