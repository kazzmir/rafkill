#ifndef _weapon_yehat_h
#define _weapon_yehat_h

#include "weaponobj.h"
class SpaceObject;
class HullObject;

class Yehat_Weapon:public WeaponNode{
public:
	Yehat_Weapon( int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );
};



#endif
