#ifndef _gun_shatter_h
#define _gun_shatter_h

#include "gunobj.h"

class SpaceContainer;

class WeaponShatter: public WeaponObject{
public:

	WeaponShatter( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};


#endif
