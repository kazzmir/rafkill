#include "defs.h"
#include "bitmap.h"
#include "raptor.h"
#include "trigtable.h"

#include "spaceobj.h"
#include "hull.h"
#include "hull_meteor.h"
#include "ebox.h"

MeteorHull::MeteorHull( int level, int lf, ECollide * eb ):
HullObject( NULL, lf, 20, 0, level, 10, false, eb ),
frame( 0 ){}

bool MeteorHull::Collide( int ax, int ay, SpaceObject * check ) {

	return HullObject::Collide( ax, ay, check );

	for ( int zx = ax - 25; zx <= ax + 25; zx += 5 )
		for ( int zy = ay - 25; zy <= ay + 25; zy += 5 )
			if ( Inside( ax, ay, zx, zy ) )
				if ( check->HitMe( zx, zy ) )
					return true;
	return false;
}


bool MeteorHull::Inside( int mx, int my, int ax, int ay ) {

	return HullObject::Inside( mx, my, ax, ay );

	if ( prect( ax, ay, mx-16, my-19, mx+16, my+19 ) ) return true;

	return false;
}


void MeteorHull::Draw( const Bitmap & who, int x, int y ) {

	if ( ++frame > 100 ) frame = 0;
	if ( frame % 2 == 0 )
		if ( ++drawNum > METEOR_9_20 ) drawNum = METEOR_1;

	HullObject::Draw( who, x, y );

}
