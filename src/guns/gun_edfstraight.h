#ifndef _gun_enemy_double_far_straight_shooter_h
#define _gun_enemy_double_far_straight_shooter_h

#include "gunobj.h"
#include <vector>
#include "spaceobj.h"

using namespace std;

class EnemyDoubleFarStraightShooter:public WeaponObject{
public:
	EnemyDoubleFarStraightShooter( int d, int al);
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};

#endif
