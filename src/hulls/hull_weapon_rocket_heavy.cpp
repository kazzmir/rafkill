#include "spaceobj.h"
#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_rocket_heavy.h"

static const int HXFactor = 6;
static const int HYFactor = 30;

HeavyRocket_WHull::HeavyRocket_WHull():
HullWeapon( 0, 1, 40 ){}

void HeavyRocket_WHull::Draw( const Bitmap & who, int x, int y ) {

	who.rectangleFill( x,y+3,x+HXFactor,y+HYFactor, Bitmap::makeColor(120,120,120) );
	who.triangle( x-2,y+3,x+HXFactor/2,y,x+HXFactor+2,y+3, Bitmap::makeColor(190,190,190) );
}

bool HeavyRocket_WHull::Collide( int mx, int my, SpaceObject * check ) {

	if ( check->HitMe( mx, my ) )
		return true;
	if ( check->HitMe( mx+HXFactor/2, my+HYFactor*2/3 ) )
		return true;
	return false;

}
