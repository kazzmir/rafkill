#ifndef _massive_weapon_h
#define _massive_weapon_h

#include "weaponobj.h"
class SpaceObject;
class HullObject;

class Massive_Weapon:public WeaponNode{
public:
	Massive_Weapon( int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	virtual bool Damage( double much );
};

#endif
