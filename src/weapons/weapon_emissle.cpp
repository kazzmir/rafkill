#include "weaponobj.h"
#include "weapon_emissle.h"
#include "hulls/hull_weapon_emissle.h"

normalMissle::normalMissle(int qx, int qy, double kx, double ky, int al):
WeaponNode( qx, qy, kx, ky, new EMissle_WHull(), al ){}

void normalMissle::MoveReal() {
	// dy += 0.01;
	setDY( getDY() + 0.01 );
	SpaceObject::MoveReal();
	/*
	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	*/
}
