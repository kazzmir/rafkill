#include "gunobj.h"
#include "weaponobj.h"
#include "gun_efsingle.h"
#include "hulls/hull_weapon_s_s.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

EnemyFindSingle::EnemyFindSingle( int d, int al ):
WeaponObject( d, "Find Single", 0, al, 0, 0 ){}

void EnemyFindSingle::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	setShotCounter( 40 );

	if ( fight == NULL ) return;
	if ( fight->empty() ) return;

	SpaceObject obj( 0, 0, 0, 0, NULL, NULL, PLANE_AIR, this->getTeam() );
	const SpaceObject * use = getCollidableObject( fight, &obj );
	// SpaceObject * use = fight->front();

	if ( use != NULL ) {
		const double FIND_BULLET = 1.2 * 8;
		int sang = getAngle( x, y, use->getX(), use->getY()+7 );
		double sx = Tcos(sang)*FIND_BULLET;
		double sy = Tsine(sang)*FIND_BULLET;
		Ammo->push_back( new WeaponNode(x,y,sx,sy,new SS_WHull(), alignment ) );
	}
}
