#include "bitmap.h"
#include "trigtable.h"
#include "spaceobj.h"
#include "hull_weapon.h"
#include "hull_weapon_fire.h"

Fire_WHull::Fire_WHull():
HullWeapon( 0, 1, 9 ){}

void Fire_WHull::Draw( const Bitmap & who, int x, int y ) {
	int zx = x;
	int zy = y-12;
	for ( int q = 0; q < 6; q++ ) {
		int sz = (q+3) / 2;
		int col = (int)( (double)q / 6.0 * (double)(MAX_E_COLOR-20) + 19 );
		// circlefill( who, zx, zy, sz, e_color[col] );
		who.circleFill( zx, zy, sz, Util::e_color[col] );
		zy += 2;
	}
}


bool Fire_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	for ( int sang = 0; sang < 360; sang += 45 ) {

		int ax = (int)(mx + Tcos(sang)*4 );
		int ay = (int)(my + Tsine(sang)*4 );
		if ( check->HitMe( ax, ay ) )
			return true;

	}
	return false;
}
