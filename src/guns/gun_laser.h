#ifndef _gun_laser_h
#define _gun_laser_h

#include "gunobj.h"

class HullObject;
class SpaceObject;

class WeaponLaser: public WeaponObject{
public:
	WeaponLaser( int z, int d, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight);
	virtual WeaponObject * copy();

protected:
	void produceLaser( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, int x, int y, HullObject * hwho, int al );
};

#endif
