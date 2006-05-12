#ifndef _weapon_pulse_h
#define _weapon_pulse_h

#include "gunobj.h"

class SpaceObject;

class WeaponPulse: public WeaponObject{
public:
	WeaponPulse( int z, int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual WeaponObject * copy();
};

#endif
