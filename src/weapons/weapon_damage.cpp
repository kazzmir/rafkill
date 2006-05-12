#include "hull.h"
#include "spaceobj.h"
#include "weapon_damage.h"
#include "weaponobj.h"
#include <vector>

using namespace std;

Damage_Weapon::Damage_Weapon( int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al ):
WeaponNode( qx, qy, kx, ky, hnew, al ),
damage( dam ){}
	
void Damage_Weapon::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){
	if ( hull ) hull->takeDamage( damage );
	MoveReal();
	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );
}

/*
void Damage_Weapon::MoveReal() {
	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	* /
	SpaceObject::MoveReal();
	hull->takeDamage( damage );
}
*/
