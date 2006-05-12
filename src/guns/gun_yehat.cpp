#include "gunobj.h"
#include "gun_yehat.h"
#include "weapons/weapon_yehat.h"
#include "hulls/hull_weapon_yehat.h"
#include "defs.h"

WeaponYehatGun::WeaponYehatGun( int z, int d, int _smp, int al ):
WeaponObject( d, "Yehat Gun", 180000, al, z, 10 ) {
	smp = _smp;
}


WeaponObject * WeaponYehatGun::copy() {
	return new WeaponYehatGun( strength, dir, smp, alignment );
}


void WeaponYehatGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( smp != -1 ){
		Util::playSound( smp, 255 );
	}

	shot_counter = 2;

	const double speed = -2.6 * 8;

	Ammo->push_back( new Yehat_Weapon(x-8,y,0,speed, new Yehat_WHull(10+strength*6), alignment ) );
	Ammo->push_back( new Yehat_Weapon(x+8,y,0,speed, new Yehat_WHull(10+strength*6), alignment ) );
	/*
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

	#define magx(x) ( (int)( (x)+tcos[dang]*6 ) )
	#define magy(y) ( (int)( (y)+tsine[dang] ) )

	Ammo->push_back( new WeaponNode(magx(x-8),y-2,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
	Ammo->push_back( new WeaponNode(magx(x-5),y,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
	Ammo->push_back( new WeaponNode(magx(x+5),y,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );
	Ammo->push_back( new WeaponNode(magx(x+8),y-2,0,MACHINE_SPEED, new Machine_WHull(3), alignment ) );

	}
	}
	*/

}
