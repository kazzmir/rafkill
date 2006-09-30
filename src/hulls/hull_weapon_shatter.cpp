#include "spaceobj.h"
#include "bitmap.h"
#include "trigtable.h"
#include "hull_weapon.h"
#include "hull_weapon_shatter.h"

Shatter_WHull::Shatter_WHull( int str ):
HullWeapon( 0, 1, str ){}

void Shatter_WHull::Draw( const Bitmap & who, int x, int y ) {

	who.circleFill( x, y, (int)strength, Bitmap::makeColor(255,20,30) );

}


bool Shatter_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	for ( double f = 2; f < getStrength(); f += 3 ){
		for ( int ang = 0; ang < 360; ang += 60 ) {

			int tx = (int)(mx + Tcos(ang) * f );
			int ty = (int)(my + Tsine(ang) * f );
			if ( check->HitMe( tx, ty ) ){
				return true;
			}
		}
	}

	return false;

}
