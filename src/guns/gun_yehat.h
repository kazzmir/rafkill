#ifndef _gun_yehat_h
#define _gun_yehat_h

#include "gunobj.h"

class SpaceContainer;

class WeaponYehatGun: public WeaponObject{
public:

	WeaponYehatGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};


#endif
