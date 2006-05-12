#ifndef _weapon_shatter_h
#define _weapon_shatter_h

#include "weaponobj.h"
#include <vector>
#include "spaceobj.h"

class HullObject;

using namespace std;

class Shatter:public WeaponNode{
public:
	Shatter( int qx, int qy, double kx, double ky, HullObject * hnew, int al, vector< SpaceObject * > * Ammo );
	
	virtual bool Damage( double much );
	virtual void Died(SpaceObject * check,ExplosionClass ** explr, int ME );
protected:
	vector< SpaceObject * > * myAmmo;
};

#endif
