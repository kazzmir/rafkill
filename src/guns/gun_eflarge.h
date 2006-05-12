#ifndef _gun_enemy_find_large_h
#define _gun_enemy_find_large_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyFindLarge:public WeaponObject{
public:
	EnemyFindLarge( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
};

#endif
