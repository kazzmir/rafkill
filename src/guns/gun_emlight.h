#ifndef _gun_enemy_machine_light_h
#define _gun_enemy_machine_light_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class EnemyMachineLight:public WeaponObject{
public:
	EnemyMachineLight( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual ~EnemyMachineLight();

protected:
	int tear;
};

#endif
