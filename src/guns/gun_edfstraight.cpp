#include "weaponobj.h"
#include "gun_edfstraight.h"
#include "gunobj.h"
#include "hulls/hull_weapon_s_s.h"
#include "spaceobj.h"
#include <vector>
#include "defs.h"

using namespace std;

EnemyDoubleFarStraightShooter::EnemyDoubleFarStraightShooter( int d, int al ):
WeaponObject( d, "Double Far Straight Shooter", 0, al, 0, 0 ){}

void EnemyDoubleFarStraightShooter::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	setShotCounter( 45 );
	Ammo->push_back( new WeaponNode(x+15,y,0,10, new SS_WHull(), alignment ) );
	Ammo->push_back( new WeaponNode(x-15,y,0,10, new SS_WHull(), alignment ) );
}
