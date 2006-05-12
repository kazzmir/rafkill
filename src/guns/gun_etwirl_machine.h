#ifndef _gun_enemy_twirl_machine_h
#define _gun_enemy_twirl_machine_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class ECollide;

class EnemyTwirlMachine:public WeaponObject{
public:
	EnemyTwirlMachine( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual ~EnemyTwirlMachine();

protected:
	ECollide * ecollide;
	int tear;
};

#endif
