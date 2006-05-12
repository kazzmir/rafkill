#ifndef _weaponobject_h_
#define _weaponobject_h_

#include <vector>
#include <string>
#include "bitmap.h"

class SpaceObject;

using namespace std;

class WeaponObject{
public:

	//basic constructor
	WeaponObject( int direction, const char * name, int _worth, int _alignment, int _strength, int _max_strength );

	//Draw
	//process: draws onto bitmap (unused)
	virtual void Draw( const Bitmap & less, int x, int y);

	//MakeShot
	//process: shoots a bullet, able to use enemy as target
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	//if we dont shoot, we idle. yay!
	virtual void Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	// increase strength by q, cannot excede max_power
	virtual void IncreasePower( int q );

	virtual inline int getPower(){
		return strength;
	}

	//return the name of this gun
	virtual inline const char * GetName() const{
		return gun_name.c_str();
	}
	virtual inline const char * getName() const {
		return gun_name.c_str();
	}

	inline int getTeam(){
		return alignment;
	}

	//how much the gun costs
	virtual int Worth();

	// returns shot_counter
	virtual const int getShotCounter() const;

	virtual void Wait( const int n );

	//returns the maximum strength of the gun
	virtual int maxPower();

	//returns a copy of this object
	virtual WeaponObject * copy();

	//destructor
	virtual ~WeaponObject();

protected:

	const SpaceObject * getCollidableObject( const vector< SpaceObject * > * fight, const SpaceObject * obj );

	void setShotCounter( const int x );

	int shot_counter;	//how much time till next shot
	int strength;		//how strong this gun is
	int max_strength;	//how strong this gun can possibly be
	int dir;		//direction to shoot in, -1 or 1
	int gun_type;		//useless gun type number
	int worth;		//how much the gun is worth
	// const char * gun_name;	//name of gun
	string gun_name;
	int alignment;		//which grouping gun makes bullets for
	int smp;		//played during Makeshot or Idle

};

#endif
