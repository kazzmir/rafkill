#include "weaponobj.h"
#include "weapon_rotate.h"
#include "hull.h"
#include "trigtable.h"

Rotate::Rotate( int qx, int qy, double kx, double ky, int _ang, int _max, HullObject * hnew, int al ):
WeaponNode( qx, qy, kx, ky, hnew, al ),
ang( _ang ),
max( _max ),
rad( 0 ),
dir( 1 ){}

void Rotate::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

	MoveReal();
	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );

	rad += dir;
	if ( rad < -max ) dir = 1;
	if ( rad > max ) dir = -1;
	setOffsetX( (int)( Tcos( ang ) * rad ) );
	setOffsetY( (int)( Tsine( ang) * rad ) );

}


/*
void Rotate::MoveReal() {

	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)( virtualx + tcos[ang] * rad );
	actualy = (int)( virtualy + tsine[ang] * rad );
	* /

	rad += dir;
	if ( rad < -max ) dir = 1;
	if ( rad > max ) dir = -1;

}
*/
