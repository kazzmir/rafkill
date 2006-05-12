#include "gunobj.h"
#include "gun_machine.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_machine.h"
#include "trigtable.h"

// #define MACHINE_SPEED -21.0
const int MACHINE_SPEED = -21;

WeaponMachineGun::WeaponMachineGun( int z, int d, int _smp, int al ):
WeaponObject( d, "Machine Gun", 23500, al, z, -1 ),
dang( 0 ) {
	smp = _smp;
}


WeaponObject * WeaponMachineGun::copy() {
	return new WeaponMachineGun( strength, dir, smp, alignment );
}


void WeaponMachineGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( smp != -1 ){
		// Util::playSample( smp, 255, 128, 1000, false );
		Util::playSound( smp, 255 );
	}

	switch( strength ) {
		case 0  : {

			shot_counter = 1;

			Ammo->push_back( new WeaponNode(x-8,y,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );
			Ammo->push_back( new WeaponNode(x+8,y,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );

			break;

		}
		case 1  : {

			shot_counter = 2;

			Ammo->push_back( new WeaponNode(x-9,y,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );
			Ammo->push_back( new WeaponNode(x+9,y,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );
			Ammo->push_back( new WeaponNode(x-4,y-1,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );
			Ammo->push_back( new WeaponNode(x+4,y-1,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );
			Ammo->push_back( new WeaponNode(x,y-2,0,MACHINE_SPEED, new Machine_WHull(1), alignment ) );

			break;
		}
		case 2  : {
			shot_counter = 2;
			Ammo->push_back( new WeaponNode(x-9,y-3,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			Ammo->push_back( new WeaponNode(x+9,y-3,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			Ammo->push_back( new WeaponNode(x-4,y-2,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			Ammo->push_back( new WeaponNode(x+4,y-2,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			break;
		}
		case 3  : {
			shot_counter = 0;

			Ammo->push_back( new WeaponNode(x+7,y-3,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			Ammo->push_back( new WeaponNode(x-7,y-3,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			//Ammo->push_back( new WeaponNode(x,y-2,0,MACHINE_SPEED, new Machine_WHull(2), alignment ) );
			break;
		}
		case 4  : {
			dang = (dang+30)%360;
			shot_counter = 2;

			#define magx(x) ( (int)( (x)+Tcos(dang)*6 ) )
			#define magy(y) ( (int)( (y)+Tsine(dang) ) )

			Ammo->push_back( new WeaponNode(magx(x-8),y-2,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
			Ammo->push_back( new WeaponNode(magx(x-5),y,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
			Ammo->push_back( new WeaponNode(magx(x+5),y,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
			Ammo->push_back( new WeaponNode(magx(x+8),y-2,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
			break;

		}
		default : {

			shot_counter = 0;
			Ammo->push_back( new WeaponNode(x+7,y,0,MACHINE_SPEED, new Machine_WHull(strength), alignment ) );
			Ammo->push_back( new WeaponNode(x-7,y,0,MACHINE_SPEED, new Machine_WHull(strength), alignment ) );

		}
	}

}
