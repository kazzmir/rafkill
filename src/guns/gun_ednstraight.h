#ifndef _gun_enemy_double_near_straight_shooter_h
#define _gun_enemy_double_near_straight_shooter_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyDoubleNearStraightShooter:public WeaponObject{
public:
	EnemyDoubleNearStraightShooter( int d, int al);
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

};


#endif
