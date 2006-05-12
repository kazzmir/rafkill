#ifndef _gun_spread_h
#define _gun_spread_h

#include "gunobj.h"

class SpaceObject;

class WeaponSpreadGun: public WeaponObject{
public:

	WeaponSpreadGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};


#endif
