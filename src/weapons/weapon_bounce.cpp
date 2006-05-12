#include "defs.h"
#include "weapon_bounce.h"
#include "weaponobj.h"
#include "hull.h"

Bounce::Bounce( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode(qx,qy,kx,ky,hnew, al){}

bool Bounce::Damage( double much ) {
	hull->takeDamage( 1 );

	bool ch[ 2 ];
	if ( Util::rnd(2) ) ch[0] = true;else ch[0]=false;
	if ( Util::rnd(2) ) ch[1] = true;else ch[1]=false;

	if ( !ch[0] && !ch[1] )
	switch( Util::rnd(2) ) {
		case 0  :       ch[0] = true;break;
		case 1  :       ch[1] = true;break;
	}

	/* TODO:
	 * Cleanup
	 */

	/*
	if ( ch[0] ) dx *= -1;
	if ( ch[1] ) dy *= -1;
	*/

	return getLife();
}


/*
void Bounce::MoveReal() {
	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	* /
	SpaceObject::MoveReal();


	/ * TODO:
	 * Cleanup this code
	 * /

	/ *
	bool change = false;

	if ( actualx < 0 ) {
		virtualx = 0;
		dx *= -1;
		change = true;
	}

	if ( actualx > 640 ) {
		virtualx = 640;
		dx *= -1;
		change = true;
	}

	if ( actualy < 0 ) {
		virtualy = 0;
		dy *= -1;
		change = true;
	}

	if ( actualy > 480 ) {
		virtualy = 480;
		dy *= -1;
		change = true;
	}

	if ( change ) {
		double ox = dx;
		double oy = dy;
		if ( !Damage(0) ) {
			actualx = -100;
			actualy = -100;
		}
		else {
			dx = ox;
			dy = oy;
		}
	}
	* /
}
*/
