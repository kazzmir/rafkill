#ifndef _gun_enemy_large_straight_shooter_h
#define _gun_enemy_large_straight_shooter_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyLargeStraightShooter:public WeaponObject{
public:
	EnemyLargeStraightShooter( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};

#endif
