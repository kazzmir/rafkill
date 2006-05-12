#include "gunobj.h"
#include "weaponobj.h"
#include "gun_eflarge.h"
#include "hulls/hull_weapon_s_l.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

EnemyFindLarge::EnemyFindLarge( int d, int al ):
WeaponObject( d, "Find Large", 0, al, 0, 0 ){}

void EnemyFindLarge::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	shot_counter = 40;
	if ( fight == NULL ) return;
	if ( fight->empty() ) return;

	// SpaceObject * use = fight->front();
	SpaceObject obj( 0, 0, 0, 0, NULL, NULL, PLANE_AIR, this->getTeam() );
	const SpaceObject * use = getCollidableObject( fight, &obj );

	if ( use != NULL ) {
		const double FIND_BULLET = -1.2 * 8;
		int sang = gang( x, y, use->getX(), use->getY()+7 );
		double sx = Tcos(sang)*FIND_BULLET;
		double sy = Tsine(sang)*FIND_BULLET;
		Ammo->push_back( new WeaponNode( x, y, sx, sy, new SL_WHull(), this->getTeam() ) );
	}

}
