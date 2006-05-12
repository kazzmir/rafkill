#ifndef _gun_machine_cirlce_h
#define _gun_machine_cirlce_h

#include "gunobj.h"

class SpaceContainer;

class WeaponMachineCircleGun: public WeaponObject{
public:

	WeaponMachineCircleGun( int z, int d, int smp, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

protected:
	int angle;

};


#endif
