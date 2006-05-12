#include "hull.h"
#include "hull_weapon_dissipate.h"
#include "spaceobj.h"
#include "ebox.h"
#include "defs.h"
#include "trigtable.h"

const int MAX_DISSIPATE_SHADE = 25;

Dissipate_WHull::Dissipate_WHull( int life, ECollide * ec ):
HullWeapon( 0, life, 1 ) {
	shade = new int[ MAX_DISSIPATE_SHADE ];
	mlife = life;
	Util::blend_palette( shade, MAX_DISSIPATE_SHADE, Bitmap::makeColor(10,10,0), Bitmap::makeColor(245,0,5) );
	collide = ec;

	strength = (int)( fsqr((double)life+(double)mlife/5.0) * 1.19 );
	strength = 0;
}


void Dissipate_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 6, shade[ (int)((double)life/(double)mlife*(double)(MAX_DISSIPATE_SHADE-1))] );
	int color = (int)((double)life/(double)mlife*(double)(MAX_DISSIPATE_SHADE-1));
	who.circleFill( x, y, 6, shade[ color ] );
}


void Dissipate_WHull::Moved( double _dx, double _dy, double _ax, double _ay ) {
	strength = (int)( fsqr( ((double)life+(double)mlife/2.0) / 20 ) * 1.19 );
	if ( strength < 1 ) strength = 1;
}


/*
bool Dissipate_WHull::Collide( int mx, int my, SpaceObject * check ) {
	if ( check->HitMe( mx, my ) )
		return true;

	for ( int ang = 0; ang < 360; ang += 60 ) {

		int tx = (int)(mx + tcos[ang]*6 );
		int ty = (int)(my + tsine[ang]*6 );
		if ( check->HitMe( tx, ty ) )
			return true;

}

return false;

}
*/

Dissipate_WHull::~Dissipate_WHull() {
	delete[] shade;
}
