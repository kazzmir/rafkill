#include "hull.h"
#include "weapon_damage.h"
#include "weapon_only_damage.h"

Only_Damage_Weapon::Only_Damage_Weapon(int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al ):
Damage_Weapon(qx,qy,kx,ky,dam,hnew,al) {
}


bool Only_Damage_Weapon::Damage( double much ) {
	return false;
}
