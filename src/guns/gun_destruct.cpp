#include "gun_destruct.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_s_s.h"
#include "spaceobj.h"
#include <vector>
#include "defs.h"

using namespace std;

GunDestruct::GunDestruct( int d, int al ):
WeaponObject( d, "Destruct", 0, al, 0, 0 ) {
	ammo = NULL;
}


void GunDestruct::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	ammo = Ammo;
	lx = x;
	ly = y;
}


GunDestruct::~GunDestruct() {

	if ( ammo == NULL ) return;

	for ( int q = 0; q < Util::rnd( 10 ) + 10; q++ ) {

		double cx = ( (double)( Util::rnd( 11 ) + 11 ) / 19.0 ) * (Util::rnd(2)*2-1);
		double cy = ( (double)( Util::rnd( 11 ) + 11 ) / 20.0 ) * (Util::rnd(2)*2-1);

		ammo->push_back( new WeaponNode(lx,ly,cx,cy,new SS_WHull(), alignment ) );
	}
}


WeaponObject * GunDestruct::copy() {
	return new GunDestruct( dir, alignment );
}
