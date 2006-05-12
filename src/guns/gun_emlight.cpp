#include "gunobj.h"
#include "gun_emlight.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_light.h"
#include "trigtable.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

EnemyMachineLight::EnemyMachineLight( int d, int al ):
WeaponObject( d, "Machine Light", 0, al, 0, 0 ),
tear( 7 ){}

void EnemyMachineLight::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 45;
	if ( fight == NULL ) return;
	if ( tear > 0 ) {
		tear--;
		shot_counter = 3;
	} else tear = 7;

	if ( fight->empty() ) return;

	SpaceObject obj( 0, 0, 0, 0, NULL, NULL, PLANE_AIR, this->getTeam() );
	const SpaceObject * use = getCollidableObject( fight, &obj );

	if ( use != NULL ) {
		int sang = getAngle( x, y, use->getX(), use->getY()+7 );
		const double FIND_BULLET = 1.2 * 8;
		double sx = Tcos(sang)*FIND_BULLET;
		double sy = Tsine(sang)*FIND_BULLET;
		Ammo->push_back( new WeaponNode(x,y,sx,sy, new Light_WHull(), alignment ) );
	}

}


EnemyMachineLight::~EnemyMachineLight() {
}
