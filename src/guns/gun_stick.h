#ifndef _gun_stick_h
#define _gun_stick_h

#include "gunobj.h"

class SpaceObject;
class ECollide;

class WeaponStick: public WeaponObject{
public:
	WeaponStick( int z, int d, int al, ECollide ** _collide_list, int _max_collide );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual WeaponObject * copy();
	virtual ~WeaponStick();

protected:
	ECollide ** collide_list;
	int max_collide;
	ECollide * ecollide;
};

#endif
