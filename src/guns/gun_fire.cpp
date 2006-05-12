#include "gunobj.h"
#include "weaponobj.h"
#include "gun_fire.h"
#include "hulls/hull_weapon_fire.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

WeaponFire::WeaponFire( int z, int d, int al ):
WeaponObject( d, "Fire", 12000, al, z, 0 ) {
}


WeaponObject * WeaponFire::copy() {
	return new WeaponFire( strength, dir, alignment );
}

void WeaponFire::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	const double speed = 9.5;
	shot_counter = 35;
	Ammo->push_back( new WeaponNode(x-7,y,0,dir * speed, new Fire_WHull(), alignment ) );
}
