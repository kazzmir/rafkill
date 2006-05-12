#ifndef _gun_enemy_find_single_h
#define _gun_enemy_find_single_h

#include "weaponobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyFindSingle:public WeaponObject{
public:
	EnemyFindSingle( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

};

#endif
