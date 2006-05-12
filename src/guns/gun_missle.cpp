#include "gunobj.h"
#include "gun_missle.h"

#include "weapons/weapon_rocket.h"
#include "hulls/hull_weapon_rocket_normal.h"
#include "hulls/hull_weapon_rocket_heavy.h"

WeaponMissle::WeaponMissle( int z, int d, int al ):
WeaponObject( d, "Missle", 45000, al, z, 4 ) {
}


WeaponObject * WeaponMissle::copy() {
	return new WeaponMissle( strength, dir, alignment );
}


void WeaponMissle::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	const double speed = -2.0 * 8;

	switch( strength ) {
		case 0  : {

			shot_counter = 17;
			Ammo->push_back( new Rocket(x,y,0,speed, new NormalRocket_WHull(), alignment ) );
			break;

		}
		case 1  : {

			shot_counter = 17;
			Ammo->push_back( new Rocket(x-10,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x+10,y,0,speed, new NormalRocket_WHull(), alignment ) );
			break;

		}

		case 2  : {
			shot_counter = 15;
			Ammo->push_back( new Rocket(x-15,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x+15,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x,y,0,speed, new NormalRocket_WHull(), alignment ) );
			break;
		}

		case 3  : {

			shot_counter = 15;
			Ammo->push_back( new Rocket(x-15,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x+15,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x-25,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x+25,y,0,speed, new NormalRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x,y-5,0,speed, new HeavyRocket_WHull(), alignment ) );

		}

		case 4  : {

			shot_counter = 15;
			Ammo->push_back( new Rocket(x-15,y+5,0,speed, new HeavyRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x+15,y+5,0,speed, new HeavyRocket_WHull(), alignment ) );
			Ammo->push_back( new Rocket(x,   y,  0,speed, new HeavyRocket_WHull(), alignment ) );
			break;
		}

	}					  //switch

}
