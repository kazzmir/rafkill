#ifndef _gun_enemy_straight_shooter_h
#define _gun_enemy_straight_shooter_h

#include "gunobj.h"
#include <vector>

class SpaceObject;

class EnemyStraightShooter:public WeaponObject{
public:
	EnemyStraightShooter( int d, int al );
	
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};


#endif
