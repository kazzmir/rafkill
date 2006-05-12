#ifndef _gun_follow_h
#define _gun_follow_h

#include "gunobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class WeaponFollow: public WeaponObject{
public:
	WeaponFollow( int z, int d, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

};

#endif
