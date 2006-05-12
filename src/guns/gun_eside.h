#ifndef _gun_enemy_side_h
#define _gun_enemy_side_h

#include "gunobj.h"

class SpaceObject;

class EnemySide:public WeaponObject{
public:
	EnemySide( int d, int al);
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};

#endif
