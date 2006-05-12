#include "gunobj.h"
#include "gun_laser.h"
#include "weapons/weapon_laser.h"
#include "hulls/hull_weapon_laser.h"
#include "trigtable.h"
#include "defs.h"
#include <vector>
#include <iostream>

using namespace std;

WeaponLaser::WeaponLaser( int z, int d, int al ):
WeaponObject( d, "Laser", 36000, al, z, 4 ) {
}

WeaponObject * WeaponLaser::copy() {
	return new WeaponLaser( strength, dir, alignment );
}

void WeaponLaser::produceLaser( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, int x, int y, HullObject * hwho, int al ) {
	
	// if ( fight == NULL || fight->empty() ) return;
	vector< SpaceObject * > fight_hold;
	SpaceObject * use = NULL;

	// SpaceObject * gay = new SpaceObject(0,0,0,0,NULL,NULL,PLANE_AIR|PLANE_GROUND, alignment );
	SpaceObject gay(0,0,0,0,NULL, NULL, PLANE_AIR|PLANE_GROUND, alignment );
	// bool quit = fight->empty();
	int ang = 0;

	for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); it++ ){
		if ( (*it)->CanbeHit( &gay ) ){
	
			SpaceObject * look = *it;
			ang = getAngle( x, y, look->getX(), look->getY() );
			if ( ang > 75 && ang < 105 ) {
				fight_hold.push_back( look );
			}

		}
	}

	if ( !fight_hold.empty() ){
		use = fight_hold[ Util::rnd( fight_hold.size() ) ];
	}

	/*
	while ( !quit ) {

		/ *
		SpaceObject * look = fight->front();
		fight_hold.push_back( look );
		fight->erase( fight->begin() );
		* /
		SpaceObject * look = (*fight)[ rnd( fight->size() ) ];
		fight_hold.push_back( look );
		vector< SpaceObject * >::iterator erase_it;
		for ( erase_it = fight->begin(); *erase_it != look; erase_it++ ); 
		
		// fight->erase( erase_it );

		if ( look->CanbeHit( &gay ) ) {

			ang = gang( x, y, look->getX(), look->getY() );
			if ( ang > 70 && ang < 110 ) {
				quit = true;
				use = look;
			}
 
		}

		quit = quit || fight->empty();

	}
	*/

	double dx, dy;
	dx = 0;
	const double speed = 22;
	dy = -speed;
	if ( use != NULL ) {
		ang = getAngle( x, y, use->getX(), use->getY() );
		dx = Tcos( ang ) * speed;
		dy = Tsine( ang) * speed;
	}

	Ammo->push_back( new LaserBullet( x, y, dx, dy, hwho, al ) );

	/*
	for ( vector<SpaceObject *>::iterator it = fight_hold.begin(); it != fight_hold.end(); ) {
		fight->push_back( *it );
		fight_hold.erase( it );
	}
	*/

}


void WeaponLaser::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 7;

	switch( strength ) {
		case 0  : {
			produceLaser( Ammo, fight, x, y, new Laser_WHull(0), alignment );
			break;
		}
		case 1  : {
			produceLaser( Ammo, fight, x-4*3, y, new Laser_WHull(0), alignment );
			produceLaser( Ammo, fight, x+4*3, y, new Laser_WHull(0), alignment );
			break;
		}
		case 2  : {
			produceLaser( Ammo, fight, x-8*3, y, new Laser_WHull(0), alignment );
			produceLaser( Ammo, fight, x+8*3, y, new Laser_WHull(0), alignment );
			produceLaser( Ammo, fight, x-3*3, y, new Laser_WHull(0), alignment );
			produceLaser( Ammo, fight, x+3*3, y, new Laser_WHull(0), alignment );

			break;
		}
		case 3  : {
			produceLaser( Ammo, fight, x, y, new Laser_WHull(1), alignment );
			produceLaser( Ammo, fight, x-4*4, y, new Laser_WHull(0), alignment );
			produceLaser( Ammo, fight, x+4*4, y, new Laser_WHull(0), alignment );
			break;
		}
		case 4  : {
			produceLaser( Ammo, fight, x, y, new Laser_WHull(1), alignment );
			produceLaser( Ammo, fight, x-4*4, y, new Laser_WHull(1), alignment );
			produceLaser( Ammo, fight, x+4*4, y, new Laser_WHull(1), alignment );
			break;
		}
	}
}
