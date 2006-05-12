#ifndef _gun_fire_h
#define _gun_fire_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class WeaponFire: public WeaponObject{
public:
	WeaponFire( int z, int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};

#endif

