#ifndef _gun_minimissle_
#define _gun_minimissle_

#include "gunobj.h"

class SpaceContainer;

class WeaponMiniMissle: public WeaponObject{
public:

	WeaponMiniMissle( int z, int d, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();
};


#endif
