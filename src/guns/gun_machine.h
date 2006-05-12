#ifndef _gun_machine_h
#define _gun_machine_h

#include "gunobj.h"

class SpaceContainer;

class WeaponMachineGun: public WeaponObject{
public:

	WeaponMachineGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

protected:
	int dang;

};


#endif
