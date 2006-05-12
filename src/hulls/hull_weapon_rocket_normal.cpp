#include "spaceobj.h"
#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_rocket_normal.h"
	
static const int Xfactor = 4;
static const int Yfactor = 20;

NormalRocket_WHull::NormalRocket_WHull():
HullWeapon( 0, 1, 20 ){}

void NormalRocket_WHull::Draw( const Bitmap & who, int x, int y ) {
	who.rectangleFill( x, y+3, x+Xfactor, y+Yfactor, Bitmap::makeColor(200,200,200) );
	who.triangle( x, y+3, x+Xfactor/2, y, x+Xfactor, y+3, Bitmap::makeColor(230,230,230) );
}

bool NormalRocket_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;
	if ( check->HitMe( mx+Xfactor/2, my+Yfactor*2/3 ) )
		return true;
	return false;
}
