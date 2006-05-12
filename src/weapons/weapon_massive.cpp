#include "hull.h"
#include "weaponobj.h"
#include "weapon_massive.h"

Massive_Weapon::Massive_Weapon( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode(qx,qy,kx,ky,hnew,al){}

bool Massive_Weapon::Damage( double much ) {
	return false;
}
