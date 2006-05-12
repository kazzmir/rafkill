#ifndef _gun_enemy_twirl_find_h
#define _gun_enemy_twirl_find_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class ECollide;

class EnemyTwirlFind:public WeaponObject{
public:
	EnemyTwirlFind( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual ~EnemyTwirlFind();

protected:
	ECollide * ecollide;
};

#endif
