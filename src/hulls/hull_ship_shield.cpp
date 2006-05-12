#include "defs.h"
#include "trigtable.h"
#include "raptor.h"
#include "bitmap.h"
#include "hull.h"
#include "hull_ship_shield.h"
#include "hull_protect.h"
#include "ebox.h"

#define shield_size 8
ShieldHull::ShieldHull( Bitmap * me, double life, int level, ECollide * eb ):
HullObject( me, life, SHIP_DAMAGE, 1, level, 10, false, eb ) {
	for ( int q = 0; q < shield_max; q++ )
		pr[ q ] = new ProtectHull( 1, level );
}


void ShieldHull::Draw( const Bitmap & work, int x, int y ) {

	HullObject::Draw( work, x, y );

	//circlefill( work, x, y, shield_size, color );
	for ( int q = 0; q < shield_max; q++ )
		pr[q]->Draw( work, x, y );
}


double ShieldHull::Damage( double much ) {

	double total = much;
	for ( int q = 0; q < shield_max; q++ )
		if ( pr[q]->haveBeenHit() )
			total = 0;
	return total;

}


ShieldHull::~ShieldHull() {
	for ( int q = 0; q < shield_max; q++ )
		delete pr[q];
}
