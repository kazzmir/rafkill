#ifndef _gun_missle_h
#define _gun_missle_h

#include "gunobj.h"

class SpaceContainer;

class WeaponMissle: public WeaponObject{
public:

	WeaponMissle( int z, int d, int al );
	
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};

#endif
