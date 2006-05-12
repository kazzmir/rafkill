#ifndef _weapon_laser_h
#define _weapon_laser_h

#include "weaponobj.h"
class HullObject;

class LaserBullet:public WeaponNode{
public:
	LaserBullet( int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	virtual bool Damage( double much );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );
};

#endif

