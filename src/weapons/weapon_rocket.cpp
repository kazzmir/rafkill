#include "weaponobj.h"
#include "weapon_rocket.h"
#include "hull.h"

Rocket::Rocket(int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode(qx,qy,kx,ky,hnew, al),
speed( 0.2 ){}

#define ROCKETSPEED 0.02
void Rocket::MoveReal() {

	/*
	virtualx += dx*speed;
	virtualy += dy*speed;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	*/
	SpaceObject::MoveReal();
	
	speed += ROCKETSPEED;
	if ( speed > 3.2 )
		speed = 3.2;
}
