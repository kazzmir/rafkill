#include "bitmap.h"
#include "hull_weapon.h"
#include "hull_weapon_massive.h"
#include "spaceobj.h"
#include "trigtable.h"
#include "ebox.h"
#include "raptor.h"
#include "rgbhandle.h"

Massive_WHull::Massive_WHull( int str, int life, ECollide * ecollide ):
HullWeapon( 0, life, str ) {

	collide = ecollide;
	ang = 0;
	max_massive = str*3/2;
	for ( int q = 0; q < 10; q++ )
		side[q] = Util::rnd( max_massive/2 ) + max_massive;
	handle = new RGBHandle();

}


Massive_WHull::~Massive_WHull() {
	delete handle;
}


void Massive_WHull::Draw( const Bitmap & who, int x, int y ) {

	for ( int q = 0; q < 10; q++ ) {
		side[q] += Util::rnd( 2 ) * 2 - 1;
		if ( side[q] < max_massive/2 ) side[q] = max_massive/2;
		if ( side[q] > max_massive*2 ) side[q] = max_massive*2;
	}
	handle->update( 180, 130 );

	ang = (ang+5) % 360;

	// int * verts = new int[ 20 ];
	int verts[ 20 ];
	for ( int q = 0; q < 10; q++ ) {
		verts[q*2] = (int)(x + Tcos((ang+q*36)%360) * side[q] );
		verts[q*2+1] = (int)(y + Tsine((ang+q*36)%360) * side[q] );
	}

	who.polygon( verts, 10, handle->Get() );
	// polygon( who, 10, verts, handle->Get() );

	// delete[] verts;

}
