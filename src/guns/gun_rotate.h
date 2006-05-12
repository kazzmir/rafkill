#ifndef _gun_rotate_h
#define _gun_rotate_h

#include "gunobj.h"

class SpaceObject;
class ECollide;

class WeaponRotateGun: public WeaponObject{
public:

	WeaponRotateGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();
	virtual ~WeaponRotateGun();

protected:
	
	int angX;
	int angY;
	int dX;
	int dY;
	int dwX;
	int dwY;
	int sd;
	int maxX, maxY;

	ECollide * collide;

};


#endif
