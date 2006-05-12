#ifndef _gun_enemy_cork_h
#define _gun_enemy_cork_h

#include "gunobj.h"

class SpaceObject;

class EnemyCork:public WeaponObject{
public:
	EnemyCork( int d, int al);
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};

#endif
