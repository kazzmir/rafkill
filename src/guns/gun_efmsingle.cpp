#include "gunobj.h"
#include "weaponobj.h"
#include "gun_efmsingle.h"
#include "hulls/hull_weapon_s_s.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

EnemyFindSingleMachine::EnemyFindSingleMachine( int d, int al ):
WeaponObject( d, "Find Single Machine", 0, al, 0, 0 ),
tear( 5 ){}

void EnemyFindSingleMachine::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * objects ) {

	setShotCounter( 40 );

	if ( objects == NULL ) return;
	if ( tear > 0 ) {
		tear--;
		setShotCounter( 10 );
	} else tear = 5;
	if ( objects->empty() ) return;

	/* fixed:
	 * Find actual enemy, not just front
	 */
	SpaceObject obj(0,0,0,0,NULL, NULL, PLANE_AIR|PLANE_GROUND, getTeam() );

	/*
	vector< SpaceObject * > my_fight;
	for ( vector< SpaceObject *>::const_iterator it = objects->begin(); it != objects->end(); it++ ){
		SpaceObject * potential = *it;
		if ( potential->CanbeHit( &gay ) ){
			my_fight.push_back( potential );
		}
	}
	*/

	// if ( my_fight.empty() ) return;
	// const SpaceObject * use = my_fight[ Util::rnd(my_fight.size()) ];
	const SpaceObject * use = getCollidableObject( objects, &obj );

	if ( use != NULL ) {
		const double FIND_BULLET = -1.2 * 8;
		int sang = gang( x, y, use->getX(), use->getY()+7 );
		double sx = Tcos(sang)*FIND_BULLET;
		double sy = Tsine(sang)*FIND_BULLET;
		Ammo->push_back( new WeaponNode(x,y,sx,sy,new SS_WHull(), alignment ) );
	}

}

EnemyFindSingleMachine::~EnemyFindSingleMachine() {
}
