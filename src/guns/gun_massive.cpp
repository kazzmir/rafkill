#include "gun_massive.h"
#include "trigtable.h"
#include "gunobj.h"
#include "hulls/hull_weapon_massive.h"
#include "weaponobj.h"
#include "weapons/weapon_damage.h"
#include "weapons/weapon_massive.h"
#include "spaceobj.h"
#include "ebox.h"
#include "trigtable.h"
#include <vector>

using namespace std;

WeaponMassiveGun::WeaponMassiveGun( int z, int d, int smp, int al ):
WeaponObject( d, "Massive Gun", 43000, al, z, 0 ),
rising( 0 ) {

	Bitmap dopey( 16, 16 );
	dopey.fill( Bitmap::MaskColor );
	dopey.circleFill( 8, 8, 8, Bitmap::makeColor(20,0,0) );
	diss_collide = new ECollide( &dopey );
	ang = 0;

}


WeaponObject * WeaponMassiveGun::copy() {
	return new WeaponMassiveGun( strength, dir, smp, alignment );
}


WeaponMassiveGun::~WeaponMassiveGun() {
	delete diss_collide;
}


void WeaponMassiveGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	shot_counter = 0;
	if ( rising < 200 )
		rising++;
	ang = (ang + 13 ) % 360;

	if ( rising/20 >= 1 ) {
		Ammo->push_back( new Damage_Weapon((int)(x+Tcos(ang)*50),(int)(y+Tsine(ang)*50),0,0,1,new Massive_WHull(rising/20,1,diss_collide), alignment ) );
		Ammo->push_back( new Damage_Weapon((int)(x+Tcos((ang+120)%360)*50),(int)(y+Tsine((ang+120)%360)*50),0,0,1,new Massive_WHull(rising/20,1,diss_collide), alignment ) );
		Ammo->push_back( new Damage_Weapon((int)(x+Tcos((ang+240)%360)*50),(int)(y+Tsine((ang+240)%360)*50),0,0,1,new Massive_WHull(rising/20,1,diss_collide), alignment ) );
	}

}


void WeaponMassiveGun::Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {
	if ( rising == 0 ) return;
	if ( rising/20 >= 1 ) {
		const double speed = 2.0 * 8;
		Ammo->push_back( new Massive_Weapon((int)(x+Tcos(ang)*50),(int)(y+Tsine(ang)*50),Tcos((ang+90)%360)*speed,Tsine((ang+90)%360)*speed,new Massive_WHull(rising/20,1,diss_collide), alignment ) );

		Ammo->push_back( new Massive_Weapon((int)(x+Tcos((ang+120)%360)*50),(int)(y+Tsine((ang+120)%360)*50),Tcos((ang+90+120)%360)*speed,Tsine((ang+90+120)%360)*speed,new Massive_WHull(rising/20,1,diss_collide), alignment ) );

		Ammo->push_back( new Massive_Weapon((int)(x+Tcos((ang+240)%360)*50),(int)(y+Tsine((ang+240)%360)*50),Tcos((ang+90+240)%360)*speed,Tsine((ang+90+240)%360)*speed,new Massive_WHull(rising/20,1,diss_collide), alignment ) );
	}
	ang = 0;
	rising = 0;
}
