#ifndef _gun_beam_h
#define _gun_beam_h

#include "gunobj.h"
#include <vector>

using namespace std;

class SpaceObject;

class WeaponBeam: public WeaponObject{
public:
	WeaponBeam( int z, int d, int al );
	
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Idle( int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

protected:

	int tear;
	int length;
	int fat;
	int angle;
	
};

#endif
