#ifndef _only_damage_weapon_h
#define _only_damage_weapon_h

#include "weaponobj.h"
#include "weapon_damage.h"

class HullObject;

class Only_Damage_Weapon:public Damage_Weapon{
public:
	Only_Damage_Weapon(int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al );
	virtual bool Damage( double much );

};

#endif

