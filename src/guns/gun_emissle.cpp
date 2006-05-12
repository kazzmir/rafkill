#include "gunobj.h"
#include "gun_emissle.h"

#include "weapons/weapon_emissle.h"

#include "defs.h"

EnemyMissle::EnemyMissle( int d, int al ):
WeaponObject( d, "Missle", 0, al, 0, 0 ),
tear( 3 ){}

void EnemyMissle::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 50;
	if ( tear > 0 ) {
		tear--;
		shot_counter = 8;
	} else tear = 3;

	const double ENEMY_MISSLE = 1.9 * 8;
	Ammo->push_back( new normalMissle(x,y,0,ENEMY_MISSLE,alignment) );

}
