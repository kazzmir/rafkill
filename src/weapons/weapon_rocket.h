#ifndef _weapon_rocket_h
#define _weapon_rocket_h

#include "weaponobj.h"
class HullObject;

class Rocket:public WeaponNode{
public:
	Rocket(int qx, int qy, double kx, double ky, HullObject * hnew, int al);
	virtual void MoveReal();

protected:

double speed;

};

#endif

