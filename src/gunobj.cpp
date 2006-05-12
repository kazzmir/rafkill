#include "gunobj.h"
#include <vector>
#include "bitmap.h"
#include "spaceobj.h"

using namespace std;

/* Constructor:
 * paramters:
 * direction - direction the bullets should move in. Should either be 1 or -1 for up for down.
 * name - the name of the gun
 * _worth - the cost of the gun used for the buy menu for the guns the player can buy.
 * _alignment - the TEAM of the gun. this will also be the TEAM of the bullets produced.
 */
WeaponObject::WeaponObject( int direction, const char * name, int _worth, int _alignment, int _strength, int _max_strength ):
shot_counter( 0 ),
strength( _strength ),
max_strength( _max_strength ),
dir( direction ),
worth( _worth ),
alignment( _alignment ) {
	gun_name = name;
}


/*
int WeaponObject::getPower(){
	return strength;
}
*/

/* Draw:
 * Allows the object to draw itself onto the specified bitmap.
 * Defualt behavior is to do nothing.
 */
void WeaponObject::Draw( const Bitmap & less,int x,int y){}

/* MakeShot:
 * Makes a bullet, or bullets, given a list of ammo and a list of the object enemies.
 * Default behavior is to do nothing.
 */
void WeaponObject::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ){}

/* Idle:
 * If the object containing the gun object shoots, the MakeShot method is called,
 * otherwise the Idle method is called.
 * Default behavior is to do nothing.
 */
void WeaponObject::Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ){}

/* GetName:
 * Returns the name of the gun.
 */
 /*
const char * WeaponObject::GetName() const {
	return gun_name.c_str();
}
*/

const int WeaponObject::getShotCounter() const{
	return shot_counter;
}
	
void WeaponObject::setShotCounter( const int x ){
	shot_counter = x;
}
	
void WeaponObject::Wait( const int n ) {
	shot_counter -= n;
}
	
const SpaceObject * WeaponObject::getCollidableObject( const vector< SpaceObject * > * fight, const SpaceObject * enemy ){
	for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); it++ ){
		const SpaceObject * object = *it;
		if ( object->CanbeHit( enemy ) ){
			return object;
		}
	}
	return NULL;
}

/* Worth:
 * Returns the cost of the gun.
 */
int WeaponObject::Worth() {
	return worth;
}


WeaponObject * WeaponObject::copy() {

	WeaponObject * who = new WeaponObject( dir, gun_name.c_str(), worth, alignment, strength, max_strength );
	return who;

}


/* maxPower:
 * Returns the maximum strength of the gun
 */
int WeaponObject::maxPower() {
	return max_strength;
}


/* IncreasePower:
 * Increases the strength of the gun initiliazed to 0. Currently, the maximum power of any gun
 * is 4.
 */
void WeaponObject::IncreasePower( int q ) {

	strength += q;
	if ( max_strength != -1 )
		if ( strength > max_strength ) strength = max_strength;

}


/* Destructor:
 * Does nothing
 */
WeaponObject::~WeaponObject(){}
