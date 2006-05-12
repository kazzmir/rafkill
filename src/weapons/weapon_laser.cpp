#include "hull.h"
#include "weaponobj.h"
#include "weapon_laser.h"
#include "defs.h"

LaserBullet::LaserBullet( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode( qx, qy, kx, ky, hnew, al ){}

bool LaserBullet::Damage( double much ) {
	hull->takeDamage( 2 );
	return false;
}

void LaserBullet::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {
	addExplode( explr, M_EX, new ExplosionClass(getX(),getY(),0,0,Util::rnd(6) + 3 ) ); 
	if ( hull ) hull->Collided();
}
