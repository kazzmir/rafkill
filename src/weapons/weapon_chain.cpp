#include "hull.h"
#include "weapon_chain.h"
#include "weapon_damage.h"

Chain::Chain( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
Damage_Weapon( qx, qy, kx, ky, 1, hnew, al ){}

/*
void Chain::MoveReal() {
	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	* /
	SpaceObject::MoveReal();
	hull->takeDamage( 1 );
}
*/
