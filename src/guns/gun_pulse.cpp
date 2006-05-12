#include "gunobj.h"
#include "gun_pulse.h"

#include "weapons/weapon_pulse.h"
#include "hulls/hull_weapon_pulse_small.h"
#include "hulls/hull_weapon_pulse_large.h"

WeaponPulse::WeaponPulse( int z, int d, int al ):
WeaponObject( d, "Pulse", 56000, al, z, 4 ) {
}


WeaponObject * WeaponPulse::copy() {
	return new WeaponPulse( strength, dir, alignment );
}


void WeaponPulse::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	const double speed1 = -2.0 * 8;
	const double speed2 = -1.3 * 8;
	const double speed3 = -1.1 * 8;

	switch( strength ) {
		case 0  : {

			shot_counter = 10;
			Ammo->push_back( new Pulse(x-6,y,0,speed1, new SmallPulse_WHull(), alignment ) );
			Ammo->push_back( new Pulse(x+6,y,0,speed1, new SmallPulse_WHull(), alignment ) );
			break;

		}
		case 1  : {

			shot_counter = 12;
			Ammo->push_back( new Pulse(x,y,0,speed1, new LargePulse_WHull(), alignment ) );
			break;

		}
		case 2  : {
			shot_counter = 13;
			Ammo->push_back( new Pulse(x-9,y,0,speed1, new LargePulse_WHull(), alignment ) );
			Ammo->push_back( new Pulse(x+9,y,0,speed1, new LargePulse_WHull(), alignment ) );
			break;

		}
		case 3  : {
			shot_counter = 14;
			Ammo->push_back( new NovaPulse(x,y,0.4*8,speed2,alignment) );
			Ammo->push_back( new Pulse(x,y,0,speed1, new LargePulse_WHull(), alignment ) );
			Ammo->push_back( new NovaPulse(x,y,-0.4*8,speed2,alignment) );
			break;
		}
		case 4  : {
			shot_counter = 15;
			Ammo->push_back( new NovaPulse(x,y,0.7*8,speed3,alignment) );
			Ammo->push_back( new NovaPulse(x,y,0.3*8,speed3,alignment) );
			Ammo->push_back( new NovaPulse(x,y,-0.3*8,speed3,alignment) );
			Ammo->push_back( new NovaPulse(x,y,-0.7*8,speed3,alignment) );
			Ammo->push_back( new Pulse(x,y,0,speed1, new LargePulse_WHull(), alignment ) );
			break;
		}

	}					  //switch
}
