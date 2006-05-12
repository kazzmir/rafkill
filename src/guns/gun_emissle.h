#ifndef _gun_enemy_missle_h
#define _gun_enemy_missle_h

#include "gunobj.h"

class SpaceObject;

class EnemyMissle:public WeaponObject{
public:
	EnemyMissle( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

protected:
	 int tear;
};

#endif
