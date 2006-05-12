#ifndef _gun_massive_h
#define _gun_massive_h

#include "gunobj.h"
#include <vector>

using namespace std;

class ECollide;
class SpaceObject;

class WeaponMassiveGun: public WeaponObject{
public:

	WeaponMassiveGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();
	~WeaponMassiveGun();

protected:

	int rising;
	ECollide * diss_collide;
	int ang;

};


#endif
