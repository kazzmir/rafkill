#ifndef _gun_enemy_twirl_straight_h
#define _gun_enemy_twirl_straight_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class ECollide;

class EnemyTwirlStraight:public WeaponObject{
public:
	EnemyTwirlStraight( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual ~EnemyTwirlStraight();

protected:
	ECollide * ecollide;
};

#endif
