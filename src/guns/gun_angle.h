#ifndef _weapon_angle_h
#define _weapon_angle_h

#include "gunobj.h"

class SpaceObject;
class ECollide;

class WeaponAngle: public WeaponObject{
public:
	WeaponAngle( int z, int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual WeaponObject * copy();
	virtual ~WeaponAngle();

protected:
	int * shade;
	ECollide * ecollide;
};

#endif
