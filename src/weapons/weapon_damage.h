#ifndef _hooray_damage_weapon_h
#define _hooray_damage_weapon_h

#include "weaponobj.h"
#include <vector>

class HullObject;
class SpaceObject;
class Section;

using namespace std;

class Damage_Weapon:public WeaponNode{
public:
	Damage_Weapon(int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al );
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );

protected:
	int damage;
};

#endif

