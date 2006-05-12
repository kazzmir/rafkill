#ifndef _weapon_beam_h
#define _weapon_beam_h

#include "weaponobj.h"
#include "weapon_damage.h"

class HullObject;
class ExplosionClass;

class Beam:public Damage_Weapon{
public:
	Beam(int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al );
	virtual bool Damage( double much );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );

};

#endif

