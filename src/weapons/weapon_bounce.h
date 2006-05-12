#ifndef _weapon_bounce_h
#define _weapon_bounce_h

#include "weaponobj.h"
class HullObject;

class Bounce:public WeaponNode{
public:
	Bounce( int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	virtual bool Damage( double much );
	// virtual void MoveReal();

protected:
	int bounces;
};

#endif
