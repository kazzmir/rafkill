#include "spaceobj.h"
#include "defs.h"
#include "hull.h"
#include "hull_weapon.h"
#include "ebox.h"

HullWeapon::HullWeapon( int drawnum, int life, double str ):
HullObject( NULL, life, str, 0, 0, 9, false, NULL ){}

/*
bool HullWeapon::Collide( int mx, int my, SpaceObject * check ) {
	if ( collide && check->getHull() && check->getHull()->collide )
		return collide->Collision( check->getHull()->collide, mx, my, check->getX(), check->getY() );
	return check->HitMe( mx, my );
}
*/

/*
bool HullWeapon::hullCollide( ECollide * col, int mx, int my, int ax, int ay ){
	return false;
}
*/
