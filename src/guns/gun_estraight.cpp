#include "gunobj.h"
#include "gun_estraight.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_s_s.h"
#include "spaceobj.h"
#include <vector>

#include "defs.h"

EnemyStraightShooter::EnemyStraightShooter( int d, int al ):
WeaponObject( d, "Straight Shooter", 0, al, 0, 0 ){}

void EnemyStraightShooter::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	setShotCounter( 45 );
	Ammo->push_back( new WeaponNode(x,y,0,10, new SS_WHull(), alignment ) );
}
