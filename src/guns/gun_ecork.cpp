#include "gunobj.h"
#include "gun_ecork.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_cork.h"
#include "trigtable.h"

EnemyCork::EnemyCork( int d, int al ):
WeaponObject( d, "Cork", 0, al, 0, 0 ) {
}


void EnemyCork::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 30;

	const double speed = 7;

	Ammo->push_back( new WeaponNode(x,y,0,speed, new Cork_WHull( 4 ), alignment ) );

}
