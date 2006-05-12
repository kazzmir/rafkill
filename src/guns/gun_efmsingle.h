#ifndef _gun_enemy_find_single_machine_h
#define _gun_enemy_find_single_machine_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyFindSingleMachine:public WeaponObject{
public:
	EnemyFindSingleMachine( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual ~EnemyFindSingleMachine();
protected:
	int tear;
};

#endif
