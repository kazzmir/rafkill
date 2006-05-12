#ifndef _gun_enemy_destruct_h_
#define _gun_enemy_destruct_h_

#include "gunobj.h"
#include <vector>
#include "spaceobj.h"

using namespace std;

class GunDestruct:public WeaponObject{
public:
	GunDestruct( int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();
	virtual ~GunDestruct();

protected:
	vector< SpaceObject * > * ammo;
	int max_ammo;
	int lx, ly;

};

#endif
