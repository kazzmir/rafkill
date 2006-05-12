#include "gunobj.h"
#include "weaponobj.h"
#include "gun_elarge.h"
#include "hulls/hull_weapon_s_l.h"
#include "defs.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

EnemyLargeStraightShooter::EnemyLargeStraightShooter( int d, int al ):
WeaponObject( d, "Large Straight Shooter", 0, al, 0, 0 ){}

void EnemyLargeStraightShooter::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * >  * fight ) {
	setShotCounter( 60 );
	const double LARGE_BULLET = 1.6 * 8;
	Ammo->push_back( new WeaponNode(x,y,0,LARGE_BULLET, new SL_WHull(), alignment ) );
}
